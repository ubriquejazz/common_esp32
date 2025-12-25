#include "command.h"
#include <string.h>

// define mutex object handle
SemaphoreHandle_t printMutex;

// define the queue handle for the queCmd queue
QueueHandle_t queCmd;

// handle used to pause, restart, or stop running tasks
TaskHandle_t taskCmd = NULL; 
TaskHandle_t* taskGreen, taskRed, taskBlue;

// command and object
CMD_Data valueToSend;

const char* cmdList = "kill...pause...resume...speed"; // list of accepted values for command
const char* objListLED = "red...green...blue";   // list of accepted values 
const char* objListSpeed = "faster...slower";

// define global variables to hold the parsed input data
char cmdFromPC[numChars] = {0};
char objFromPC[numChars] = {0};

BaseType_t newData = pdFALSE;
char receivedChars[numChars]; // update by recvWithEndMarker()
char tempChars[numChars]; // temporary array when parsing

// protypes
void parseData(void); // split the data into its parts
void recvWithEndMarker(void); // populate receivedChars[]
void checkParsedData(void); // cmdFromPC and objFromPC

void CMD_Init(TaskHandle_t* green, TaskHandle_t* red, TaskHandle_t* blue) {
    // start printer mutex access
    printMutex = xSemaphoreCreateMutex();
    if (printMutex != NULL) Serial.println("printMutex created");

    // initialize queue for commands
    queCmd = xQueueCreate( 5, sizeof(CMD_Data) );
    if( queCmd != NULL ) Serial.println("command queue created");

    taskGreen = green;
    taskRed = red;
    taskBlue = blue;
    
    strcpy(valueToSend.Cmd, "");
    strcpy(valueToSend.Obj, "");
}

void CMD_Exec(void *pvParameters) {
  CMD_Data receivedValue;
  BaseType_t xStatus;
  const TickType_t xTicksToWait = 100;
  char nameObj[8];

  for(;;) {
    xStatus = xQueueReceive( queCmd, &receivedValue, xTicksToWait );
    if( xStatus == pdPASS ) {
      xSemaphoreTake(printMutex, portMAX_DELAY);  // to use of the printer

      // check which led color to modify and set approriate task
      if (strstr("red",receivedValue.Obj)) {
        strcpy(nameObj,"red");
        taskCmd = *taskRed;
      }
      else if (strstr("green",receivedValue.Obj)) {
        strcpy(nameObj,"green");
        taskCmd = *taskGreen;
      }
      else if (strstr("blue",receivedValue.Obj)) {
        strcpy(nameObj,"blue");
        taskCmd = *taskBlue;
      }

      // check which command is sent and respond accordingly
      if (strstr("pause",receivedValue.Cmd)) {
        vTaskSuspend(taskCmd);
        Serial.print(nameObj);
        Serial.println(" paused");
      }
      else if (strstr("resume",receivedValue.Cmd)) {
        vTaskResume(taskCmd);
        Serial.print(nameObj);
        Serial.println(" resumed");
      }  
      else if (strstr("kill",receivedValue.Cmd)) {
        vTaskDelete(taskCmd);
        Serial.print(nameObj);
        Serial.println(" killed");
      }

      // check the speed
      else if (strstr("speed" , receivedValue.Cmd) ) {
        if (strstr ( "slower" , receivedValue.Obj)) {
          speedMult *= 1.5;
          Serial.println("speed is slower");
        }
        else if (strstr("faster" , receivedValue.Obj)) {
          speedMult *= 0.67;
          Serial.println("speed is faster");
        } 
      }
      Serial.flush(); 
      vTaskDelay(5000); 
      xSemaphoreGive(printMutex);   
    } 
    else {
      /* Do nothing here - Wait for a new entry to be added into the command queue */
    }
  }
}

void CMD_Parse(void *pvParameters) {
  BaseType_t xStatus; 

  // This uses non-blocking input routines to read and check user input
  // If values are acceptable the command is sent to the command processor (queue)
  // The input format is "command object" where command and object must conform
  // to values in lists.  If either is not valid, the user is notified. 

  for(;;)  
  {
    recvWithEndMarker();
    if (newData == pdTRUE) {
      strcpy(tempChars, receivedChars);
      parseData();
      checkParsedData();
      newData = pdFALSE;
      strcpy(valueToSend.Cmd, cmdFromPC);
      strcpy(valueToSend.Obj, objFromPC);
      // add the input values to the back of the queue
      xStatus = xQueueSendToBack( queCmd, &valueToSend, 0 );
      if( xStatus != pdPASS ) Serial.println("queue send failed!");
    } 
  }
}

void recvWithEndMarker() {
  static byte ndx = 0;
  char endMarker = '\n';
  
  while (Serial.available() > 0 && newData == pdFALSE) {
    char rc = Serial.read();
    if (rc != endMarker) {
      receivedChars[ndx] = rc;
      ndx++;
      if (ndx >= numChars) ndx = numChars - 1;
    }
    else {
      receivedChars[ndx] = '\0'; // terminate the string
      ndx = 0;
      newData = pdTRUE;
    }
  }
}

void parseData() {
    char * strtokIndx; 
    strtokIndx = strtok(tempChars," "); // get the first part - the string
    strcpy(cmdFromPC, strtokIndx); // copy it to cmdFromPC
    strtokIndx = strtok(NULL, " "); // this continues where the previous call left off
    strcpy(objFromPC, strtokIndx);  // copy it to objFromPC
}

void checkParsedData() {
  char * cmd;
  char * obj;
  int validRequest = 0;

  // *** 3 *** take the printer mutex
  xSemaphoreTake(printMutex, portMAX_DELAY);
  cmd = strstr(cmdList, cmdFromPC);
  if (cmd){
    validRequest += 1;
  } else {
    Serial.println("rejected - unrecognized command");
    validRequest -= 1;
  }

  if (strstr("speed",cmdFromPC)){
    obj = strstr(objListSpeed, objFromPC);
    if (obj)    {
      validRequest += 1;
    } else {
      Serial.println("rejected - unrecognized request");
      validRequest -= 1;
    }
  } else {
    obj = strstr(objListLED, objFromPC);
    if (obj)  {
      validRequest += 1;
    } else {
      Serial.println("rejected - unrecognized request");
      validRequest -= 1;
    }
  }

  if (validRequest == 2){
    Serial.println("command accepted");
    Serial.println(String(cmdFromPC) + "  " + String(objFromPC));
  }
  Serial.flush();
  vTaskDelay(3000);  // *** 4 *** flush the print data and wait for the user to read the response
  xSemaphoreGive(printMutex);
}
