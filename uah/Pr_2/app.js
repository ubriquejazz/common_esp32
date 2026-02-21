const mqtt = require('mqtt');
const client = mqtt.connect('mqtt://localhost');
const TOPIC_SENSOR = 'sensor_en_MQTTfx';

// Al conectarse...
client.on('connect', function () {
    console.log('Conectado al broker con éxito');
    client.subscribe(TOPIC_SENSOR, function (err) {

        if (!err) {
            console.log('Suscrito a:' + TOPIC_SENSOR);
            setInterval(() => {
                const tempSimulada = (20 + Math.random() * 10).toFixed(1);
                client.publish(TOPIC_SENSOR, tempSimulada);
            }, 5000);
            //client.publish('sensor_tmp', '30.4');
            console.log('Mensaje enviado a:' + TOPIC_SENSOR);
        }
    });
});

// Al recibir un mensaje de los tópicos suscritos
client.on('message', function (topic, message) {
    // message es un Buffer, usamos .toString() para leerlo
    console.log(`Mensaje recibido en [${topic}]: ${message.toString()}`);

    // Nota: client.end() cierra la conexión inmediatamente. 
    // Si esperas recibir más mensajes, 
    client.end(); 
});