var Gpio = require('onoff').Gpio; 

// use GPIO pin 18, and specify that it is ouput
var LED = new Gpio(530, 'out'); 

//run the blinkLED function every 250ms
var blinkInterval = setInterval(blinkLED, 250); 

//stop blinking after 5 seconds
setTimeout(endBlink, 5000);

//function to start blinking
function blinkLED() { 
    // check the pin state, if the state is 0 (or off)
    if (LED.readSync() === 0) { 
        LED.writeSync(1); 
    } else { 
        LED.writeSync(0); // set pin state to 0 (turn LED off)
    } 
} 
     
//function to stop blinking
function endBlink() { 
    clearInterval(blinkInterval); 
    LED.writeSync(0); 
    LED.unexport(); // to free resources
} 


