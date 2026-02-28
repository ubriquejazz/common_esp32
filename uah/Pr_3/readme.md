# RPi, JavaScript y Node-RED

    $ ifconfig eth0 130.233.120.77 netmask 255.255.255.0 up
    $ route add default gw 130.233.120.254



**Ejercico 02. Counter**

Programar el JS anterior en la Raspberry y ejecutarlo.

```
$ node count.js 
Hola desde Node.js 
Suma :1234 + 1.234 = 1235.234
Execution 1  
Execution 2  
Execution 3  
Execution 4  
Execution 5  
Interval stopped after 5 executions! 
```

**Ejercicio 3. LED Blinking**

Conectar un LED al pin 18 (530), programar el JS anterior y ejecutarlo. Leer la documentación sobre los métodos **setInterval**, clearInterval, **setTimeout** y comentar brevemente cómo funcionan.

```
~$ grep GPIO18 | cat /sys/kernel/debug/gpio
...
~/.node-red$ npm install onoff
~/.node-red$ npm list
```

Leer la documentación sobre la palabra clave ‘require’ y comentar brevemente para qué sirve.

```
~/repo/uah$  ./copiar.sh Pr_3
~/repo/uah$  cd ~/.node-red
~/.node-red$ node Pr_3/blink.js

~/.node-red$ 
```

**Ejercicio 4. I2C Sensor** 

Conectar al bus I2C de la Raspberry un [INA219](https://www.ti.com/lit/ds/symlink/ina219.pdf) y un resistor variable. Programar el JS anterior y ejecutarlo tomando varias medidas según posición del potenciómetro.

```
~/.node-red$ node Pr_3/ina219.js
```

Modificar el programa anterior añadiendo un setInterval para que se tomen medidas del INA219 cada 2s.

- Grabar un video de unos pocos segundos en el que se muestre como se varía el potenciómetro y a la vez la salida por consola (MobaXterm) de los valores del INA219.

![](fig/bulb.gif)



