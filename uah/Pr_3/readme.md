# RPi, JavaScript y Node-RED

    $ ifconfig eth0 130.233.120.77 netmask 255.255.255.0 up
    $ route add default gw 130.233.120.254



**Ejercico JS.**

Programar el JS anterior en la Raspberry y ejecutarlo.

```
$ node ex02.js 
Hola desde Node.js 
Suma :1234 + 1.234 = 1235.234
```

**Ejercicio LED**

Conectar un LED al pin 18, programar el JS anterior y ejecutarlo. Leer la documentación sobre los métodos setInterval, clearInterval, setTimeout y comentar brevemente cómo funcionan.

```
~$ cd .node-red 
~/.node-red$ npm install onoff
~/.node-red$ node oo.js
```

Leer la documentación sobre la palabra clave ‘require’ y comentar brevemente para qué sirve.

**Ejercicio I2C** 

Conectar al bus I2C de la Raspberry un [INA219](https://www.ti.com/lit/ds/symlink/ina219.pdf?ts=1615288223466&ref_url=https%253A%252F%2 2Fwww.ti.com%252Famplifier-circuit%252Fcurrent-sense%252Fpower-currentmonitors%252Fproducts.html ) y un resistor variable. Programar el JS anterior y ejecutarlo tomando varias medidas según posición del potenciómetro.

```
~/.node-red$ node ina219.js
```

Modificar el programa anterior añadiendo un setInterval para que se tomen medidas del INA219 cada 2 segundos. Grabar (con el móvil) un video de unos pocos segundos en el que se muestre como se varía el potenciómetro y a la vez la salida por consola (MobaXterm) de los valores del INA219.

**Ejercico 5A: Simple Dashboard**

Instalar el bróker Mosquitto en Raspberry y arrancarlo en una consola. Partiendo de las conexiones de los ejercicios anteriores (LED en GPIO18 y ADC INA219), crear un ‘flow’ en Node-RED de Raspberry que:

- Muestre un chart (dashboard chart) en el que se visualice el valor de tensión del INA219. Una gauge (dashboard) que visualice el valor de tensión del INA219.

- Un LED (instalar el paquete ‘node-red-contrib-ui-led’) que indique el estado del GPIO18. Dos button (dasshboard) que permitan poner el GPIO a 1 y a 0.

**Ejercico 5B: Publisher**

* Un nodo MQTT que publique el valor del ADC leído con la correspondiente función JS

Dentro de una función JS de Node-RED no se puede usar ‘require’. Es necesario añadir todos los ‘require’ que se necesiten en Node-RED al fichero **settings.js**.  A continuación se muestra el fragmento de ese fichero en donde se añaden los ‘require’:

```
$ cat /home/pi/.node-red/settings.js
functionGlobalContext: {
	gpio:require('onoff').Gpio,
	i2c:require('i2c-bus'),
	os:require('os'),
},
```

Así que dentro de un nodo function en Node-RED el código correspondiente al GPIO será:

```
~/.node-red$ node ex05.js
```



**Ejercico 5C: Subscriber**

- Un nodo MQTT que se suscriba a un topic ‘GPIO18’ y que modifica el valor de ese GPIO 18 cada vez que reciba un valor 1 o 0 de un Publisher remoto (se puede utilizar la extensión de Google, MQTT.fx, etc.). El Publisher usará el bróker Mosquitto instalado en Raspberry.

  