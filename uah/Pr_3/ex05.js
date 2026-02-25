{
    Gpio = global.get('gpio');
    var LED = new Gpio(18, 'out'); 
    LED.writeSync(1); 
    if (LED.readSync() === 0) 
        msg.payload = 0; 
    else 
        msg.payload = 1; 

    msg.value = 'w'; 
    return msg;
}    
