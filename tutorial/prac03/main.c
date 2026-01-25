#include "../command.h"

TaskHandle_t taskGreen, taskRed, taskBlue;
TaskHandle_t taskCmdParse, taskCmdExec;

void main() {

  
  CMD_Init(&taskGreen, &taskRed, &taskBlue);

  // Run this in core separate from LED tasks if there are two cores. Still priority 2
  xTaskCreate( CMD_Parse, "Command Parser", 4096, NULL, 2, &taskCmdParse);  
  xTaskCreate( CMD_Exec, "Execute Commands From Queue", 4096, NULL, 2, &taskCmdExec);

}