# NodeJS y Node-RED

**Node-RED** es la navaja suiza de la domótica y el complemento perfecto para MQTT. Te ahorra horas de código para hacer cosas visuales.

Aunque a veces viene preinstalado, lo mejor es usar el script oficial para asegurarte de tener la última versión y que funcione como un servicio del sistema:

```
bash <(curl -sL https://raw.githubusercontent.com/node-red/linux-installers/master/deb/update-nodejs-and-nodered)
```

Igual que hicimos con tu script, queremos que Node-RED se encienda con la Raspberry:

```
sudo systemctl enable nodered.service
sudo systemctl start nodered.service
```

### Entrar al panel de control

Ahora, desde cualquier ordenador o tablet de tu casa, abre el navegador y escribe la IP de tu Raspberry seguida del puerto `1880`. Una vez dentro de Node-RED, crear un visualizador es tan fácil como arrastrar bloques:

1. **Nodo `mqtt in`:** Arrástralo al lienzo. Haz doble clic y configúralo con el broker (ej. `localhost` si instalaste Mosquitto o `test.mosquitto.org`) y el tópico `sensor_temp`.
2. **Nodo `debug`:** Conéctalo a la salida del nodo MQTT. Dale al botón **Deploy** (arriba a la derecha).

Para ver una **gráfica o un termómetro** de aguja, necesitamos instalar el módulo de interfaz:

1. Ve al menú (tres rayas arriba a la derecha) -> **Manage palette**.
2. En la pestaña **Install**, busca: `node-red-dashboard`.
3. Instálalo. Ahora tendrás nuevos nodos de color azul (Gauge, Chart, Text).
4. Arrastra un nodo **Gauge** (indicador), conéctalo a tu nodo MQTT y vuelve a dar a **Deploy**.

Para ver tu panel de control, entra en: `http://192.168.1.XX:1880/ui`

**Un último detalle sobre la frecuencia...**

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
4. **Toca el interruptor en tu navegador:** Verás cómo aparece el mensaje instantáneamente en la terminal.