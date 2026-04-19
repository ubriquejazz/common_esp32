#include "adc.h"
#include "gatts_table_creat_demo.h"

static uint16_t Refresh_Time = 1;
TickType_t Record_Time = 0;
static esp_adc_cal_characteristics_t *adc_chars;

#define ADC_OFFSET      2048
#define HYSTERESIS      50    // Prevents noise from causing ghost RPM
#define TIMEOUT_MS      2000  // Reset to 0 RPM after 2 seconds of inactivity
#define MAX_SAMPLES     32

int adc_GetRPM(int adc_reading) {
    static float filt = 0;
    float oldf = filt;
    filt = (float)adc_reading - ADC_OFFSET;

    static int cadence_buffer[MAX_SAMPLES] = {0};
    static int write_idx = 0;
    static int samples_count = 0;
    
    // Zero-cross detection with improved logic
    if ((filt > HYSTERESIS && oldf < -HYSTERESIS) || (filt < -HYSTERESIS && oldf > HYSTERESIS)) {
        TickType_t now = xTaskGetTickCount();
        uint32_t delta_ms = (now - Record_Time) * portTICK_PERIOD_MS;
        Record_Time = now;

        if (delta_ms > 0) {
            cadence_buffer[write_idx] = 30000 / delta_ms; // 30k for half-rotation pulses
            write_idx = (write_idx + 1) % MAX_SAMPLES;
            if (samples_count < MAX_SAMPLES) samples_count++;
        }
    }

    // Stop condition
    if ((xTaskGetTickCount() - Record_Time) * portTICK_PERIOD_MS > TIMEOUT_MS) {
        return 0; 
    }

    if (samples_count == 0) return 0;
    
    long sum = 0;
    for (int i = 0; i < samples_count; i++) sum += cadence_buffer[i];
    return (int)(sum / samples_count);
}

void adc_task(void *pvParameter) {
    while(1) {
        int raw = adc1_get_raw((adc1_channel_t)ADC_CHANNEL_6);
        AppData.rpm = adc_GetRPM(raw);
        vTaskDelay(pdMS_TO_TICKS(ADC_SAMPL_TIME));
    }
}