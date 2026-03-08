#ifndef CMD_H
#define CMD_H

#include "cmsis_os.h"

const byte numChars = 24;
 
struct CMD_Data {
  char  Cmd[numChars];
  char  Obj[numChars];
};

void CMD_Init(TaskHandle_t* green, TaskHandle_t* red, TaskHandle_t* blue);
void CMD_Exec(void *pvParameter);
void CMD_Parse(void *pvParameter);

#endif