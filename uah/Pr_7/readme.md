# Motas



## Micropython

Modificar el ejemplo de comunicación MQTT disponible en https://github.com/RuiSantosdotme/ESPMicroPython/tree/master/code/MQTT/Node_RED_Client para simular el envío de datos simulados desde el ESP32 a un servidor Node-RED.

Observar que con lo visto anteriormente realmente se podrían enviar datos de sensores reales conectados al ESP32 a través de I2C, ADCs, UART, etc.

## ESP-IDF

Se simularán dos sensores en el ESP32 y se enviarán los datos a Node-RED cada 4 s.

## STM32L475E IOT01_GenericMQTT

1. Aplicación MQTT genérica

Compilar el proyecto con STM32CubeIDE. Es necesario convertirlo de SW4STM32.

- añadir una variable contador a los datos enviados por el Publisher que indique el número de paquetes enviados
- seguir las instrucciones del apartado 11 del manual de usuario.
- abrir el puerto serie a 115200 bps.
- introducir SSID y PASSWD del router WiF
- Suscribirse al broker y recibir todos los topics
- Presentar datos en NODE-RED
- Capturar resultados (flow y dashboard) y presentarlos como resultados de este ejercicios con explicacion.
 
2. Aplicación Grovestreams

Seguir paso a paso la configuración detallada en el apartado 17 del manual de usuario UM2347

Presentarán como resultados de este ejercicio las capturas de pantalla que muestren los resultados con una
breve explicación 
