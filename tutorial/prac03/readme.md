# Prac05

Now we are ready to add the command processor. We’re going to add this in two parts.

- Command Parser to read the keyboard entry and validate that is a correct command.
- Command Executor to take the validated input entry and perform the requested command.

We will use a queue to pass the validated command from the command parser to the command executor. Why separate the two tasks? 

In the future we  may want to add the ability to enter commands from a web interface, or through some other input method. We  would simply have the new input device send commands to the same command queue as the command parser and avoid writing additional processing  code. 

## Struct

First add a code to create global variables to hold the command data and a struct:

    // define structure for data in the cmdQueue
    const byte numChars = 24;
    struct cmdData {
    char  Cmd[numChars];
    char  Obj[numChars];
    };

For this tutorial, all of our commands will have two parts — a command name (Cmd variable) and an Object field (Obj variable). The permitted values for the command and object fields are

- pause (red, green, blue)
- resume (red, green, blue)
- kill (red, green, blue)
- speed (slower, faster)

## Queue

The function **xQueueCreate** is used to create a queue called queCmd that contains space for 5 entries, where each entry is the size of the struct.

The command parser will enter values to the back of the queue and the command executor will read entries from the front, so that commands will be processed in the order they were entered.

The command parser will validate that the keyboard entry matches one of the values above and then add an entry into queCmd queue that points to  the contents of cmdData structure. 
