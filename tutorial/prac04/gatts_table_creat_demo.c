#include "gatts_table_creat_demo.h"
#include "adc.h"

/* Globals */

AppData_t AppData;
DisData_t DisData;

uint16_t cycling_power_handle_table[IDX_SVC1_NB];
uint16_t device_info_handle_table[IDX_SVC2_NB];

static bool rpm_connected = false;
static bool pwr_connected = false;

static prepare_type_env_t a_prepare_write_env;
static prepare_type_env_t b_prepare_write_env;

// Task responsible for pushing data to the BLE client
static void send_task(void *pvParameter) {
    while (1) {
        // Dynamic delay based on AppData.refresh_time
        vTaskDelay(pdMS_TO_TICKS(AppData.refresh_time * 1000));

        if (rpm_connected) {
            // Using 'false' for need_confirm to act as a Notification
            esp_ble_gatts_send_indicate(
                cycling_power_handle_table[IDX_SVC1_NB], 
                0, 
                cycling_power_handle_table[IDX_CHAR_VAL_RPM], 
                sizeof(uint32_t), 
                (uint8_t *)&AppData.rpm, 
                false
            );
        }
    }
}

// Handler for when the user writes to a characteristic
void gatt_write_event_handler(esp_gatts_cb_param_t *param) {
    // 1. Update Refresh Rate
    if (cycling_power_handle_table[IDX_CHAR_VAL_REFRESH_TIME] == param->write.handle) {
        if (param->write.len == sizeof(uint16_t)) {
            AppData.refresh_time = *(uint16_t *)param->write.value;
        }
    }
    
    // 2. Enable/Disable Notifications (CCCD)
    if (cycling_power_handle_table[IDX_CHAR_CFG_RPM] == param->write.handle) {
        uint16_t descr_val = param->write.value[1] << 8 | param->write.value[0];
        rpm_connected = (descr_val == 0x0001); 
    }

}

// --------------------------------------------
void app_init(void)
{
    AppData.cranck_mm = 180;
    AppData.pwr_offset = 0;
    AppData.refresh_time = 3;
    memcpy(DisData.manufacturer, "TBC", 5);
    memcpy(DisData.model_number, "1", 2);
    memcpy(DisData.serial_number, "SN001", 5);
    memcpy(DisData.hardware_ver, "RevA", 5);
    memcpy(DisData.firmware_ver, "0.0.1", 5);
    memcpy(DisData.software_ver, "0.0.1", 5);
}

void app_main(void)
{
    esp_err_t ret;

    /* Initialize NVS. */
    ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK( ret );
    ESP_ERROR_CHECK(esp_bt_controller_mem_release(ESP_BT_MODE_CLASSIC_BT));
   esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    ret = esp_bt_controller_init(&bt_cfg);
    if (ret) {
        ESP_LOGE(GATTS_TAG, "%s enable controller failed: %s", __func__, esp_err_to_name(ret));
        return;
    }

    ret = esp_bt_controller_enable(ESP_BT_MODE_BLE);
    if (ret) {
        ESP_LOGE(GATTS_TAG, "%s enable controller failed: %s", __func__, esp_err_to_name(ret));
        return;
    }

    ret = esp_bluedroid_init();
    if (ret) {
        ESP_LOGE(GATTS_TAG, "%s init bluetooth failed: %s", __func__, esp_err_to_name(ret));
        return;
    }

    ret = esp_bluedroid_enable();
    if (ret) {
        ESP_LOGE(GATTS_TAG, "%s enable bluetooth failed: %s", __func__, esp_err_to_name(ret));
        return;
    }

    ret = esp_ble_gatts_register_callback(gatts_event_handler);
    if (ret){
        ESP_LOGE(GATTS_TAG, "gatts register error, error code = %x", ret);
        return;
    }

    ret = esp_ble_gap_register_callback(gap_event_handler);
    if (ret){
        ESP_LOGE(GATTS_TAG, "gap register error, error code = %x", ret);
        return;
    }

    ret = esp_ble_gatts_app_register(PROFILE_A_APP_ID);
    if (ret){
        ESP_LOGE(GATTS_TAG, "gatts app register error, error code = %x", ret);
        return;
    }

    ret = esp_ble_gatts_app_register(PROFILE_B_APP_ID);
    if (ret){
        ESP_LOGE(GATTS_TAG, "gatts app register error, error code = %x", ret);
        return;
    }

    esp_err_t local_mtu_ret = esp_ble_gatt_set_local_mtu(500);
    if (local_mtu_ret){
        ESP_LOGE(GATTS_TAG, "set local  MTU failed, error code = %x", local_mtu_ret);
    }

    app_init();
    adc_init(AppData.refresh_time);
    xTaskCreate(&send_task, "send_task", 2048, NULL, 5, NULL);
}
