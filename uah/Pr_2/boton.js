const mqtt = require('mqtt');
const client = mqtt.connect('mqtt://localhost');
const TOPIC_BOTON = 'actuador/luz';

// Al conectarse...
client.on('connect', () => {
    console.log('Conectado y esperando órdenes...');
    // Nos suscribimos al tópico del botón
    client.subscribe(TOPIC_BOTON);
});

// Al recibir un mensaje ...
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