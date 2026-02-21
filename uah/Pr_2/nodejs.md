# NodeJS y MQTT

### Ejercicio 5

Run the following command to install MQTT Mosquitto Client:

```
sudo apt install -y mosquitto mosquitto-clients nodejs npm
```

Run Mosquitto in the background as a daemon:

```
node -v
sudo systemctl enable mosquitto
mosquitto -d
```

On Window #2 publish a message:

```
mosquitto_pub -d -h 127.0.0.1 -t sensor_temp -m "20.5"
```

Open a new terminal Window #3 and run this command to subscribe to **testTopic** topic:

```
mosquitto_sub -d -h 127.0.0.1 -t sensor_temp
```

### Ejercicio 6

En este apartado se presenta un ejemplo simple en JavaScript. 

Para ejecutarlo es necesario tener instalado Node.js (https://nodejs.org/en/) y el cliente para protocolo MQTT (https://www.npmjs.com/package/mqtt)

```
$ node prac2_mqqt.js
Conectado al broker con éxito
Suscrito a: sensor_en_MQTTfx
Mensaje enviado a: sensor_tmp

Mensaje recibido en [sensor_en_MQTTfx]: 31.5
```

Esta figura muestra la ejecución del script. Se puede observar la respuesta del topic 'sensor_en_MQTTfx'

---





### Instalar Node-RED

**Node-RED** es la navaja suiza de la domótica y el complemento perfecto para MQTT en una Raspberry Pi. Te ahorra horas de código para hacer cosas visuales.

Aunque a veces viene preinstalado, lo mejor es usar el script oficial para asegurarte de tener la última versión y que funcione como un servicio del sistema:

Bash

```
bash <(curl -sL https://raw.githubusercontent.com/node-red/linux-installers/master/deb/update-nodejs-and-nodered)
```

*Di que **sí (y)** cuando te pregunte si quieres instalar los nodos específicos de Raspberry Pi.*

Igual que hicimos con tu script, queremos que Node-RED se encienda con la Raspberry:

Bash

```
sudo systemctl enable nodered.service
sudo systemctl start nodered.service
```

### Entrar al panel de control

Ahora, desde cualquier ordenador o tablet de tu casa, abre el navegador y escribe la IP de tu Raspberry seguida del puerto `1880`. Una vez dentro de Node-RED, crear un visualizador es tan fácil como arrastrar bloques:

1. **Nodo `mqtt in`:** Arrástralo al lienzo. Haz doble clic y configúralo con el broker (ej. `localhost` si instalaste Mosquitto o `test.mosquitto.org`) y el tópico `sensor_tmp`.
2. **Nodo `debug`:** Conéctalo a la salida del nodo MQTT. Dale al botón **Deploy** (arriba a la derecha).
   - *¡Magia!* En la pestaña de la derecha (el icono del bicho) empezarás a ver llegar el "30.4" que envía tu script.

Para ver una **gráfica o un termómetro** de aguja, necesitamos instalar el módulo de interfaz...¿Quieres que te pase el código "JSON" de un flujo ya hecho para que solo tengas que importarlo y ver una gráfica funcionando al instante?

```json
[
  {
    "wires": [
      []
    ]
  }
]
```

Este flujo recibirá el valor de tu script de Node.js y lo mostrará simultáneamente en un indicador de aguja (Gauge) y en una gráfica histórica (Chart). 

1. Abre tu editor de Node-RED (`http://tu-ip:1880`).
2. Haz clic en el **menú de las tres rayas** (esquina superior derecha).
3. Selecciona **Import**.
4. Pega el código anterior en el cuadro de texto y dale al botón **Import**.
5. **Configura el Broker:** Haz doble clic en el nodo azul de la izquierda (`mqtt in`) y asegúrate de que esté conectado a `test.mosquitto.org` o a tu `localhost`.
6. Pulsa el botón rojo **Deploy**.

------

**Un último detalle...**

Si quieres que la gráfica se mueva más rápido para probarla, puedes modificar tu script de Node.js (el `app.js`) para que envíe un valor aleatorio cada 5 segundos en lugar de uno fijo:

JavaScript

```
setInterval(() => {
    const tempSimulada = (20 + Math.random() * 10).toFixed(1);
    client.publish('sensor_tmp', tempSimulada);
}, 5000);
```



## Boton

Vamos a añadir un **botón interactivo** en tu Dashboard de Node-RED para controlar algo en la Raspberry (por ahora, simularemos que enciende una luz o un relé enviando un mensaje MQTT).

### El flujo en Node-RED (frontend)

Sigue estos pasos en tu editor de Node-RED:

1. Busca en la paleta de la izquierda el nodo **`switch`** (del grupo *dashboard*, de color azul).
2. Arrástralo al lienzo.
3. Busca el nodo **`mqtt out`** (de color rosa) y arrástralo también.
4. Conéctalos: la salida del `switch` a la entrada del `mqtt out`.

**Configuración:**

- **Doble clic en el `switch`:**
  - **Group:** Selecciona el mismo donde está tu gráfica.
  - **On Payload:** Pon un String que diga `ON`.
  - **Off Payload:** Pon un String que diga `OFF`.
  - **Topic:** Escribe `actuador/luz`.
- **Doble clic en el `mqtt out`:**
  - Asegúrate de que use el mismo **Broker** que los demás nodos.
  - Deja el campo *Topic* vacío (tomará el que configuraste en el switch).

**Dale a "Deploy"** (arriba a la derecha).

------

### El código en Node.js (backend)

Ahora vamos a crear tu script de Node.js (`boton.js`) para que "escuche" ese botón y haga algo:

```javascript
const mqtt = require('mqtt');

client.on('message', (topic, message) => {
    if (topic === TOPIC_BOTON) {
        const estado = message.toString();
        
        if (estado === 'ON') {
            console.log('--- ¡Luz ENCENDIDA! ---');
            // Aquí iría el código para activar un pin GPIO
        } else {
            console.log('--- Luz APAGADA ---');
            // Aquí iría el código para desactivar el pin
        }
    }
});
```



1. Abre el Dashboard en tu navegador: `http://tu-ip:1880/ui`.
2. Verás un interruptor nuevo junto a tu gráfica de temperatura.
3. Abre la terminal de tu Raspberry donde corre el script (puedes usar `pm2 logs`).
4. **Toca el interruptor en tu móvil:** Verás cómo aparece el mensaje instantáneamente en la terminal.