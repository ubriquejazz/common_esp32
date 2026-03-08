#include "blink.h"

//define semaphore object handle
SemaphoreHandle_t syncFlag;

BaseType_t Blink_Init() {
  BaseType_t retVal = pdTRUE;
  syncFlag = xSemaphoreCreateBinary();
  if (syncFlag != NULL){
    retVal = pdFALSE;
  }
  // make the semaphore available to start sequential processing    
  xSemaphoreGive(syncFlag);
  return retVal;
}

void TaskBlink(void *pvParameters) {
  BlinkData *data = (BlinkData *)pvParameters; 
  float *mult = data->speedMult;
  int *status = data->status;
  pinMode(data->pin, OUTPUT);
  for(;;){
    int delayInt = (data->delay * (*mult)); // get new delay time (ms)
    *status = 1;  
    digitalWrite(data->pin, HIGH); 
    vTaskDelay(delayInt);  // unblock delay for on cycle
    *status = 0; 
    digitalWrite(data->pin, LOW);
    vTaskDelay(delayInt); // unblock delay for off cycle                
  }
}

void TaskBlinkSeq(void *pvParameters) {
  BlinkData *data = (BlinkData *)pvParameters; 
  float *mult = data->speedMult;
  int *status = data->status;
  pinMode(data->pin, OUTPUT);
  for(;;){
    xSemaphoreTake(syncFlag, portMAX_DELAY);
    int delayInt = (data->delay * (*mult)); // get new delay time (ms)
    *status = 1;  
    digitalWrite(data->pin, HIGH); 
    vTaskDelay(delayInt);  // unblock delay for on cycle
    *status = 0; 
    digitalWrite(data->pin, LOW);
    vTaskDelay(delayInt); // unblock delay for off cycle

    xSemaphoreGive(syncFlag);
    vTaskDelay(100);          
  }
}