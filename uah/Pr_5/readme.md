# MQTT con SSL/TSL

En esta práctica se introducen las comunicaciones MQTT con seguridad (autenticación).

El método más simple consiste en añadir una autenticación de usuario mediante un par usuariopassword. Como se verá más adelante, esto ofrece una autenticación pobre ya que con las herramientas adecuadas es sencillo obtener el password.

Lo que en realidad se utiliza en la práctica es la autenticación SSL/TSL. Se verá cómo crear los diferentes ficheros de autenticación y cómo utilizarlos con el software usado en prácticas anteriores (mosquitto, MQTT.fx, MQTTbox, Node-RED).

**EJERCICIO 2.**

Capturar el paquete de conexión para ver user y password. Utilizar diferentes topic, user y password..

![](../fig/whiresharck.png)

**EJERCICIO 2.**

Instalar Node.js y node-RED en Windows:

- Node.js: https://nodejs.org/es (o https://nodejs.org/en) 

- Node-RED: https://nodered.org/docs/getting-started/windows

Crear en Node-RED un flow con nodos MQTT-in y MQTT-out, con seguridad user/password y capturar la comunicación entre ambos nodos.

**EJERCICIO 3.**

Instalar OpenSSL y crear los diferentes certificados y keys. Arrancar mosquitto broker con seguridad SSL/TSL y comunicar los clientes mosquitto_pub y mosquitto_sub. Capturar la comunicación con Wireshark e interpretar los paquetes obtenidos.

**EJERCICIO 4.**

Modificar el flow del ejercicio 2 y comprobar su correcto funcionamiento con SSL/TSL. Capturar la pantalla de debug de Node-RED para añadir evidencia de funcionamiento a la memoria de esta práctica.