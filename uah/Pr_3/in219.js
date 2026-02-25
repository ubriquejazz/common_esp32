'use strict';

const i2c = require('i2c-bus'); 
const INA219_ADDR = 0x40; 

var buf = Buffer.from([0,0,0,0]); 
var i2cRx = Buffer.from([0,0,0,0]); 

const i2c1 = i2c.openSync(1); 
i2c1.readI2cBlockSync(INA219_ADDR, 0, 2, i2cRx);

console.log('INA219 Config reg: 0x' + i2cRx[0].toString(16) + i2cRx[1].toString(16));

buf[0]=2; // VBUS 

i2c1.i2cWriteSync(INA219_ADDR, 1, buf);
i2c1.i2cReadSync(INA219_ADDR, 2, i2cRx); 

console.log('voltage reg raw: 0x' + i2cRx[0].toString(16) + i2cRx[1].toString(16));

var volt = i2cRx[0]<<5 | (i2cRx[1]>>3)&7;
console.log('voltage reg (only voltage): 0x' + volt.toString(16)); 

volt *= 4E-3;
console.log('INA219 Vbus float:' + volt); 

i2c1.closeSync();