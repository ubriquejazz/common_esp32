# MQTT

- MQTT tres QoS, brokers publicos
- CoAP (Constraint App Protocol) opcion OBSERVE asincrona
- piggyback protocol - data on the ack

**EJERCICIO**

Instalar MQTT.fx en dos PCs. Configurar el broker con test.mosquitto.org en ambos. En el PC1 suscribirse a un topic. En el PC2 publicar en ese mismo topic. Experimentar con diferentes topic/subtopic y con los wildcard (+ y #).

Utilizar Wireshark para capturar y analizar la petición de suscripción y los mensajes publicados y los recibidos por el subscriber.

**EJERCICIO**

Instalar Mosquitto (broker y clientes) en dos PCs. En el PC1 arrancar el broker y en otro PowerShell suscribirse a un topic en la dirección loopback. En el PC2 publicar en ese mismo topic mensajes ASCII o JSON.

Utilizar Wireshark para capturar y analizar la petición de suscripción y los mensajes publicados y los recibidos por el subscriber.

**EJERCICIO**

En n Python3 instalar el módulo paho-mqtt. Crear el programa anterior y ejecutarlo con Python.

Para ver los resultados es necesario tener un subscriber suscrito al topic en el correspondiente broker; para ello se puede usar cualquiera de los vistos a lo largo de la práctica.
