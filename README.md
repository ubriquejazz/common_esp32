# common_esp32

## Stmas e ifaces web

Desplegar soluciones IoT para apl de control distribuido, comenzando por los ESP32 de bajo coste, pero con capacidades de gestión de energía, comunicaciones, protección ...

Protocolos necesarios para transmitir la información a servicios en la nube. Una vez los datos en la nube se estudia el desarrollo de las interfaces web para interactuar con los datos y con los elementos IoT.

**Introduccion**

- Conceptos básicos. Internet
- Protocolos utilizados en IoT
- Comunicaciones inalámbricas
- Seguridad en comunicaciones

**ESP32: uC adaptados para aplicaciones distribuidas**

• 3 + 3 horas

**AWS: Plataformas de procesado en la nube**

• 4 + 2 horas

## Arquitectura Nodos en IoT

UPM [practicas](https://miot-rpi.github.io/practicas/ANIOT/P1/)

- e_1 -> Uso de `i2ctools`

- e_2 -> Lectura de temperatura

- e_3 -> Uso de CRC en sensor

- e_4 -> Aplicación con FSM

---

e_1 -> Lectura de fuente de tensión variable

e_2 -> Lectura de distancias

## Tutorial with three phases

1. Three LED lights blinking on and off, task increase the speed with a button. Add a semaphore to give some order (template task called **TaskBlink**)
1. Two new tasks: one to show the number of LEDs lit via an OLED display and other to show the watermark of each tasks at the begining (serial).
1. Serial parse and executer (semaphore and queue)

For more info, see this tutorial

![img](https://miro.medium.com/v2/resize:fit:1400/1*Ium5nL6kGjRzAcKUvPTjFQ.jpeg)

**References**

- ESP32 [tutorial](https://medium.com/@tomw3115/implementing-freertos-solutions-on-esp-32-devices-using-arduino-114e05f7138a)
- Hardware: ESP32 Dev (WROOM), ESP-CAM
