# MQTT

**EJERCICIO**

Instalar MQTT.fx en dos PCs. Configurar el broker con **test.mosquitto.org** en ambos. En el PC1 suscribirse a un topic. En el PC2 publicar en ese mismo topic. Experimentar con diferentes topic/subtopic y con los wildcard (+ y #).

**EJERCICIO**

Instalar **mosquitto** (broker y clientes) en dos PCs. En la RPi arrancar el broker y en otro PowerShell suscribirse a un topic en la dirección loopback. En el PC2 publicar en ese mismo topic mensajes ASCII o JSON.

**EJERCICIO**

En Python3 instalar el módulo paho-mqtt. Crear el programa anterior y ejecutarlo con Python. Para ver los resultados es necesario tener un subscriber suscrito al topic en el correspondiente broker; para ello se puede usar cualquiera de los vistos a lo largo de la práctica.

On Window #2 publish a message:

```
mosquitto_pub -d -h 127.0.0.1 -t sensor_temp -m "20.5"
```

Open a new terminal Window #3 and run this command to subscribe to **testTopic** topic:

```
mosquitto_sub -d -h 127.0.0.1 -t sensor_temp
```

**EJERCICIO**

Ejecutar el ejemplo en JavaScript. Para ello es necesario tener instalado Node.js (https://nodejs.org/en/) y el cliente para protocolo MQTT (https://www.npmjs.com/package/mqtt)

```
sudo apt install -y mosquitto mosquitto-clients nodejs npm
```

Instalar el complemento para MQTT:

```
npm install mqt
```

Resultado

```
$ node app.js
Conectado al broker con éxito
Suscrito a: sensor_temp
Mensaje enviado!

Mensaje recibido en [sensor_temp]: 31.5
```