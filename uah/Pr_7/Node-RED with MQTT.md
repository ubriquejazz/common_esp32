# Node-RED with MQTT (Publish and Subscribe)

Learn how to publish and subscribe to MQTT topics with the ESP8266  NodeMCU board. In this tutorial, we’ll use the Node-RED dashboard to  control the ESP8266 outputs and display sensor data from the ESP8266 on  its interface. The Node-RED software is running on a Raspberry Pi, and  the communication between the ESP8266 and the Node-RED software is done  via MQTT communication protocol. We’ll program the ESP8266 using Arduino IDE.

![ESP8266 and Node-RED with MQTT (Publish and Subscribe)](https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2017/08/ESP8266_Node-RED_MQTT_Publish_Subscribe.jpg?resize=828%2C466&quality=100&strip=all&ssl=1)


​                      ![img](data:image/svg+xml;base64,PHN2ZyB3aWR0aD0iMTIiIGhlaWdodD0iOCIgdmlld0JveD0iMCAwIDEyIDgiIGZpbGw9Im5vbmUiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyI+CjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgY2xpcC1ydWxlPSJldmVub2RkIiBkPSJNMTEuMjU5MiAwLjU4NjMwOUMxMC45NDk4IDAuNjc2MTIzIDEwLjM2OCAwLjg5ODU1NSAxMC4xNDE1IDEuMzQzNjJDOS45MjgxOSAxLjc2MjIxIDEwLjA2OSAyLjMzNzU0IDEwLjE5NzUgMi42N0MxMC41MDY3IDIuNTgwMjkgMTEuMDg5OSAyLjM1Nzg2IDExLjMxNjUgMS45MTIzOEMxMS41NDMyIDEuNDY3MzEgMTEuMzczMSAwLjg4MTIwOCAxMS4yNTkyIDAuNTg2MzA5VjAuNTg2MzA5Wk05LjkwMDYxIDMuMjU1OUw5LjgxMjMgMy4wODUyQzkuNzg4OTMgMy4wMzk3MyA5LjI0MjA5IDEuOTYyNzggOS42NzMwMyAxLjExNjg4QzEwLjEwMzYgMC4yNzA3NzggMTEuMzEzNiAwLjA0MzkzMjEgMTEuMzY0OCAwLjAzNDY5NEwxMS41NTc2IDBMMTEuNjQ1OSAwLjE3MDY5OUMxMS42NjkzIDAuMjE2MTcxIDEyLjIxNiAxLjI5MzAyIDExLjc4NDkgMi4xMzkxMkMxMS4zNTQ4IDIuOTg0ODIgMTAuMTQ0NyAzLjIxMTg3IDEwLjA5MzMgMy4yMjExMUw5LjkwMDYxIDMuMjU1OVoiIGZpbGw9IiM5MTkxOTEiLz4KPHBhdGggZmlsbC1ydWxlPSJldmVub2RkIiBjbGlwLXJ1bGU9ImV2ZW5vZGQiIGQ9Ik0yLjY0NDc1IDIuNjQ3NzlDMi41NzkxNyAxLjI4MzQzIDEuNDQwMjIgMC4xOTQ4NzggMC4wMzI5NTkgMC4xNjE2MjFWNS4zODI1NkMwLjAzNDAxMTYgNS4zODI1NiAwLjAzNTA2NDIgNS4zODI0NiAwLjAzNjExNjkgNS4zODIzNkMwLjEwMTY5NiA2Ljc0NjcyIDEuMjQwNjQgNy44MzUzNyAyLjY0NzkxIDcuODY4NTJWMi42NDc2OUMyLjY0Njg1IDIuNjQ3NjkgMi42NDU4IDIuNjQ3NzkgMi42NDQ3NSAyLjY0Nzc5IiBmaWxsPSIjOTE5MTkxIi8+CjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgY2xpcC1ydWxlPSJldmVub2RkIiBkPSJNNS43MTcyNiAyLjY0Nzc5QzUuNjUxNjggMS4yODM0MyA0LjUxMjczIDAuMTk0ODc4IDMuMTA1NDcgMC4xNjE2MjFWNS4zODI1NkMzLjEwNjUyIDUuMzgyNTYgMy4xMDc1NyA1LjM4MjQ2IDMuMTA4NzMgNS4zODIzNkMzLjE3NDIxIDYuNzQ2NzIgNC4zMTMxNSA3LjgzNTM3IDUuNzIwNTIgNy44Njg1MlYyLjY0NzY5QzUuNzE5NDcgMi42NDc2OSA1LjcxODMxIDIuNjQ3NzkgNS43MTcyNiAyLjY0Nzc5IiBmaWxsPSIjOTE5MTkxIi8+CjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgY2xpcC1ydWxlPSJldmVub2RkIiBkPSJNOC43OTAwMSAyLjY0Nzc5QzguNzI0MzMgMS4yODM0MyA3LjU4NTQ5IDAuMTk0ODc4IDYuMTc4MjIgMC4xNjE2MjFWNS4zODI1NkM2LjE3OTI4IDUuMzgyNTYgNi4xODAzMyA1LjM4MjQ2IDYuMTgxMzggNS4zODIzNkM2LjI0Njk2IDYuNzQ2NzIgNy4zODYwMSA3LjgzNTM3IDguNzkzMTcgNy44Njg1MlYyLjY0NzY5QzguNzkyMTIgMi42NDc2OSA4Ljc5MTA2IDIuNjQ3NzkgOC43OTAwMSAyLjY0Nzc5IiBmaWxsPSIjOTE5MTkxIi8+Cjwvc3ZnPgo=)

## Project Overview

The following figure shows an overview of what we’re going to do in this tutorial.

[![img](https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2017/08/MQTT-ESP8266-publish-and-subscribe-Node-RED.png?resize=828%2C459&quality=100&strip=all&ssl=1)](https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2017/08/MQTT-ESP8266-publish-and-subscribe-Node-RED.png?quality=100&strip=all&ssl=1)

## Node-RED and Node-RED Dashboard

To follow this tutorial, you need to have Node-RED and Node-RED Dashboard installed in your [Raspberry Pi](https://makeradvisor.com/raspberry-pi-board/).  Follow the next tutorials to install and get started with Node-RED and Node-RED dashboard:

- [Getting started with Node-RED on Raspberry Pi](https://randomnerdtutorials.com/getting-started-with-node-red-on-raspberry-pi/)
- [Getting Started with Node-RED Dashboard](https://randomnerdtutorials.com/getting-started-with-node-red-dashboard/)

## MQTT Protocol

In this tutorial, we’ll establish a communication between a Raspberry Pi running the Node-RED software and  an ESP8266 using MQTT.

MQTT stands for **MQ T**elemetry **T**ransport and it is a nice lightweight publish and subscribe system where you can publish and receive messages as a client. It is a simple messaging  protocol, designed for constrained devices and with low bandwidth. So,  it’s the perfect solution for Internet of Things applications.

If you want to learn more about MQTT, watch the video or read this blog post [What is MQTT and How It Works](https://randomnerdtutorials.com/what-is-mqtt-and-how-it-works/).

## Installing Mosquitto Broker

The MQTT broker is responsible for receiving all messages, filtering the messages, deciding who is interested in them, and then **publishing** the messages to all subscribed clients.

There are several brokers you can use. In this tutorial, we’re going to use the **Mosquitto Broker**.

You can install the Mosquitto MQTT broker locally on a Raspberry Pi, on your computer, or on the cloud. Follow **one** of the next tutorials to install Mosquitto broker:

- [Install Mosquitto MQTT Broker on a Raspberry Pi](https://randomnerdtutorials.com/how-to-install-mosquitto-broker-on-raspberry-pi/)
- [Install Mosquitto MQTT Broker on the Cloud (Digital Ocean)](https://randomnerdtutorials.com/cloud-mqtt-mosquitto-broker-access-anywhere-digital-ocean/)

To see if Mosquitto broker was successfully installed, run the next command:

```
pi@raspberry:~ $ mosquitto -v
```

This returns the Mosquitto version that is currently running on your Raspberry Pi. It should be 2.0.11 or above.

![Checking Mosquitto Version](https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2017/08/Checking-Mosquitto-Version.png?resize=621%2C418&quality=100&strip=all&ssl=1) 

![img](data:image/svg+xml;base64,PHN2ZyB3aWR0aD0iMTIiIGhlaWdodD0iOCIgdmlld0JveD0iMCAwIDEyIDgiIGZpbGw9Im5vbmUiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyI+CjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgY2xpcC1ydWxlPSJldmVub2RkIiBkPSJNMTEuMjU5MiAwLjU4NjMwOUMxMC45NDk4IDAuNjc2MTIzIDEwLjM2OCAwLjg5ODU1NSAxMC4xNDE1IDEuMzQzNjJDOS45MjgxOSAxLjc2MjIxIDEwLjA2OSAyLjMzNzU0IDEwLjE5NzUgMi42N0MxMC41MDY3IDIuNTgwMjkgMTEuMDg5OSAyLjM1Nzg2IDExLjMxNjUgMS45MTIzOEMxMS41NDMyIDEuNDY3MzEgMTEuMzczMSAwLjg4MTIwOCAxMS4yNTkyIDAuNTg2MzA5VjAuNTg2MzA5Wk05LjkwMDYxIDMuMjU1OUw5LjgxMjMgMy4wODUyQzkuNzg4OTMgMy4wMzk3MyA5LjI0MjA5IDEuOTYyNzggOS42NzMwMyAxLjExNjg4QzEwLjEwMzYgMC4yNzA3NzggMTEuMzEzNiAwLjA0MzkzMjEgMTEuMzY0OCAwLjAzNDY5NEwxMS41NTc2IDBMMTEuNjQ1OSAwLjE3MDY5OUMxMS42NjkzIDAuMjE2MTcxIDEyLjIxNiAxLjI5MzAyIDExLjc4NDkgMi4xMzkxMkMxMS4zNTQ4IDIuOTg0ODIgMTAuMTQ0NyAzLjIxMTg3IDEwLjA5MzMgMy4yMjExMUw5LjkwMDYxIDMuMjU1OVoiIGZpbGw9IiM5MTkxOTEiLz4KPHBhdGggZmlsbC1ydWxlPSJldmVub2RkIiBjbGlwLXJ1bGU9ImV2ZW5vZGQiIGQ9Ik0yLjY0NDc1IDIuNjQ3NzlDMi41NzkxNyAxLjI4MzQzIDEuNDQwMjIgMC4xOTQ4NzggMC4wMzI5NTkgMC4xNjE2MjFWNS4zODI1NkMwLjAzNDAxMTYgNS4zODI1NiAwLjAzNTA2NDIgNS4zODI0NiAwLjAzNjExNjkgNS4zODIzNkMwLjEwMTY5NiA2Ljc0NjcyIDEuMjQwNjQgNy44MzUzNyAyLjY0NzkxIDcuODY4NTJWMi42NDc2OUMyLjY0Njg1IDIuNjQ3NjkgMi42NDU4IDIuNjQ3NzkgMi42NDQ3NSAyLjY0Nzc5IiBmaWxsPSIjOTE5MTkxIi8+CjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgY2xpcC1ydWxlPSJldmVub2RkIiBkPSJNNS43MTcyNiAyLjY0Nzc5QzUuNjUxNjggMS4yODM0MyA0LjUxMjczIDAuMTk0ODc4IDMuMTA1NDcgMC4xNjE2MjFWNS4zODI1NkMzLjEwNjUyIDUuMzgyNTYgMy4xMDc1NyA1LjM4MjQ2IDMuMTA4NzMgNS4zODIzNkMzLjE3NDIxIDYuNzQ2NzIgNC4zMTMxNSA3LjgzNTM3IDUuNzIwNTIgNy44Njg1MlYyLjY0NzY5QzUuNzE5NDcgMi42NDc2OSA1LjcxODMxIDIuNjQ3NzkgNS43MTcyNiAyLjY0Nzc5IiBmaWxsPSIjOTE5MTkxIi8+CjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgY2xpcC1ydWxlPSJldmVub2RkIiBkPSJNOC43OTAwMSAyLjY0Nzc5QzguNzI0MzMgMS4yODM0MyA3LjU4NTQ5IDAuMTk0ODc4IDYuMTc4MjIgMC4xNjE2MjFWNS4zODI1NkM2LjE3OTI4IDUuMzgyNTYgNi4xODAzMyA1LjM4MjQ2IDYuMTgxMzggNS4zODIzNkM2LjI0Njk2IDYuNzQ2NzIgNy4zODYwMSA3LjgzNTM3IDguNzkzMTcgNy44Njg1MlYyLjY0NzY5QzguNzkyMTIgMi42NDc2OSA4Ljc5MTA2IDIuNjQ3NzkgOC43OTAwMSAyLjY0Nzc5IiBmaWxsPSIjOTE5MTkxIi8+Cjwvc3ZnPgo=)

**Note:** the Mosquitto command returns the Mosquitto  version that is currently installed, but it also tries to initialize  Mosquitto again. Since Mosquitto is already running it prompts an error  message. Don’t worry Mosquitto is properly installed and running if you  see a similar message.

## Establishing an MQTT communication with Node-RED

In this section, we’re going to establish an MQTT communication with Node-RED using the MQTT nodes.

...

The Node-RED application is ready. To see how your dashboard looks go to ***http://your-pi-ip-address:1880/ui***. Now, follow the next sections to prepare your ESP8266.

## Building the Circuit

The following sections show you the needed parts and schematics to build the circuit for this project.

## Parts required

These are the parts required to build the circuit (click the links below to find the best price at [Maker Advisor](https://makeradvisor.com/tools/)):

- [Raspberry Pi](https://makeradvisor.com/tools/raspberry-pi-board/) – [read Best Raspberry Pi 3 Starter Kits](https://makeradvisor.com/best-raspberry-pi-3-starter-kits/)
- [ESP8266 (ESP-12E nodemcu)](https://makeradvisor.com/tools/esp8266-esp-12e-nodemcu-wi-fi-development-board/) – [read Best ESP8266 Wi-Fi Development Boards](https://makeradvisor.com/best-esp8266-wi-fi-development-board/)
- [DHT11 temperature and humidity sensor ](https://makeradvisor.com/tools/dht11-temperature-humidity-sensor/)
- [Breadboard](https://makeradvisor.com/tools/mb-102-solderless-breadboard-830-points/)

You can use the preceding links or go directly to [MakerAdvisor.com/tools](https://makeradvisor.com/tools/?utm_source=rnt&utm_medium=post&utm_campaign=post) to find all the parts for your projects at the best price!

[![img](https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2017/10/header-200.png?w=828&quality=100&strip=all&ssl=1)](https://makeradvisor.com/tools/?utm_source=rnt&utm_medium=post&utm_campaign=post)

## Schematics

Here are the schematics for this project’s circuit.

![img](https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2017/08/ESP8266_MQTT_Node-RED_bb-1.png?resize=700%2C766&quality=100&strip=all&ssl=1)

## Preparing your Arduino IDE

We’ll program the ESP8266 using the Arduino IDE. In order to upload  code to your ESP8266 using the Arduino IDE, you need to install the  ESP8266 add-on ([How to Install the ESP8266 Board in Arduino IDE](https://randomnerdtutorials.com/how-to-install-esp8266-board-arduino-ide/)). You’ll also need to install two additional libraries to have everything ready for your ESP8266.

### Installing the PubSubClient Library

The [PubSubClient](https://github.com/knolleary/pubsubclient) library provides a client for doing simple publish/subscribe messaging  with a server that supports MQTT (basically allows your ESP8266 to talk  with Node-RED).

**1)** [Click here to download the PubSubClient library](https://github.com/knolleary/pubsubclient/archive/master.zip). You should have a *.zip* folder in your Downloads folder

**2)** In the Arduino IDE, go to Sketch > Include Library > Add .ZIP library and select the library *.zip* folder you’ve just downloaded.

**3)** Restart your Arduino IDE. 

The library comes with a number of examples. See File >Examples > PubSubClient within the Arduino IDE software.

### Installing the DHT Sensor Library

To read from the DHT sensor, we’ll use the [DHT library from Adafruit](https://github.com/adafruit/DHT-sensor-library). To use this library you also need to install the [Adafruit Unified Sensor library](https://github.com/adafruit/Adafruit_Sensor). Follow the next steps to install those libraries.

**1)** Open your Arduino IDE and go to **Sketch** > **Include Library** > **Manage Libraries**. The Library Manager should open.

**2)** Search for “**DHT**” on the Search box and install the DHT library from Adafruit.

![Installing Adafruit DHT library](https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2019/04/adafruit_dht_library.png?resize=750%2C422&quality=100&strip=all&ssl=1)

**3)** After installing the DHT library from Adafruit, type “**Adafruit Unified Sensor**” in the search box. Scroll all the way down to find the library and install it.

![Installing Adafruit Unified Sensor driver library](https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2019/04/adafruit_unified_sensor_library.png?resize=750%2C422&quality=100&strip=all&ssl=1)

**4)** After installing the libraries, restart your Arduino IDE.

For more information about the DHT11 sensor and the ESP8266, read [ESP8266 DHT11/DHT22 Temperature and Humidity Web Server with Arduino IDE](https://randomnerdtutorials.com/esp8266-dht11dht22-temperature-and-humidity-web-server-with-arduino-ide/).

### Selecting the right board on Arduino IDE

You also need to select the right board on Arduino IDE:

**1)** Go to **Tools** > **Board** and select the ESP8266 board you’re using.

**2)** Select the right COM port in **Tools** > **Port**.

## Uploading code

Now, you can upload the following code to your ESP8266. This code  publishes messages with the temperature and humidity from the DHT11  sensor on the **room/temperature** and **room/humidity** topics via MQTT protocol.

The ESP8266 is subscribed to the **room/lamp** topic to receive the messages published on that topic by the Node-RED application, to turn the lamp on or off.

The code is well commented on where you need to make changes. **You need to edit the code with your network credentials (SSID and  password), and broker details (Raspberry Pi IP address, mqtt broker  username and password.**

This code is also compatible with other DHT sensors – you just need  to uncomment and comment the right lines of code to choose your sensor. [code](https://github.com/RuiSantosdotme/Random-Nerd-Tutorials/raw/master/Projects/ESP8266_NodeRED_MQTT_LED_DHT.ino)

After uploading and with the Raspberry Pi running your Node-RED application and the Mosquitto broker, you can open the serial monitor at a baud rate of 115200 and see what’s happening in  real-time.

This is helpful to check if the ESP8266 has established a successful  connection to your router and to the Mosquitto broker. You can also see  the messages the ESP8266 is receiving and publishing.

![img](https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2017/08/serial-monitor-arduino-ide.png?resize=750%2C496&quality=100&strip=all&ssl=1)

## Demonstration

Congratulations! Your project is now completed.

Go to ***http://your-pi-ip-address/ui*** to control the ESP with the  Node-RED application. You can access your  application in any browser on the same network that your Pi (watch the  video demonstration below).

The application should look something the figure below.

![img](https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2017/08/Screenshot_2017-08-21-14-54-45.png?resize=700%2C504&quality=100&strip=all&ssl=1)

## Wrapping up

In this tutorial, we’ve shown you  the basic concepts that will allow you to turn on lights and monitor  sensors on your ESP8266 using Node-RED and MQTT communication protocol.  You can follow these basic steps to build more advanced projects.

We have other MQTT tutorials using other sensors that you may find useful:

- [ESP8266 NodeMCU MQTT – Publish **BME280** Sensor Readings (Arduino IDE)](https://randomnerdtutorials.com/esp8266-nodemcu-mqtt-publish-bme280-arduino/)
- [ESP8266 NodeMCU MQTT – Publish **DS18B20** Temperature Readings (Arduino IDE)](https://randomnerdtutorials.com/esp8266-nodemcu-mqtt-publish-ds18b20-arduino/)
- [ESP8266 NodeMCU MQTT – Publish **BME680** Temperature, Humidity, Pressure, and Gas Readings (Arduino IDE)](https://randomnerdtutorials.com/esp8266-nodemcu-mqtt-publish-bme680-arduino/)

We hope you’ve found this tutorial useful.

If you like this project and Home Automation make sure you check our eBook: [SMART HOME with Raspberry Pi, ESP32, and ESP8266](https://randomnerdtutorials.com/smart-home-ebook/). 

