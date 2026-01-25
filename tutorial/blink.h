#ifndef BLINK_H
#define BLINK_H

#include "cmsis_os.h"

// define structure for data to pass to each task
struct BlinkData {
  int pin;
  int delay;
  float *speedMult;
  int *status;
};

BaseType_t Blink_Init();
void TaskBlink(void *pvParameters);
void TaskBlinkSeq(void *pvParameters);

#endif