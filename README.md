# common_esp32
FreeRTOS tutorial for ESP32

Create function prototypes for the functions that will be used to create  tasks. 

- **Blinker Task** — to cycle an LED on and off.
- **OLED Task** — to display the current number of LEDs lit at any given time.
- **Highwater Task** — this will display a value at the serial console.
- **Speedup Task** — increase the cycle speed 50% each time the button is pushed.

The highwater mark describes the  amount of memory (in bytes) that has been allocated to the task but  never used. It can be used to adjust the allocation that is specified  when the task is initialized. You will see how this is used later.

Define a struct datatype called BlinkData to exchange information with  the tasks.

- the GPIO pin number and initial delay are entered as values  
- the speed multiplier and status variable are copied by reference, as they will change dynamically as the program runs.

Load up data for each LED task

    static BlinkData blinkGreen = { 15, 2500, &speedMult, &greenLED };
    static BlinkData blinkRed = { 4, 3300, &speedMult, &redLED };
    static BlinkData blinkBlue = { 16, 1800, &speedMult, &blueLED };

We create  BlinkData  variables for each LED with the  values to be used. Again note we are passing values for the pin and  delay, and pointers for the speed multiplier and the status.

Next we are ready to start executing the startup code…

1. Here we are setting up the GPIO pin 23 to create an interrupt called  **buttonPush** on a falling value. This will trigger the routine defined in ...

1. Finally, the arguments passed to the task creation function *xTaskCreate* include:

   - function to call to initiate the task

   - name to call the task (text)

   - memory allocation for the task (bytes). We can tweak this after reading the highwater mark on first execution.

   - variable passed to the function by reference (pointer to a BlinkData type)

   - task priority (higher gets processed first)

   - task handle name

Next is the most uninteresting section of code, a void loop. 

For more info, see this tutorial

![img](https://miro.medium.com/v2/resize:fit:1400/1*Ium5nL6kGjRzAcKUvPTjFQ.jpeg)

