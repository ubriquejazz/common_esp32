# Beginners Guide To The Paho MQTT Python Client 
# 

import paho.mqtt.client as mqtt
import time

#broker_address = "test.mosquitto.org" 
broker_address = "127.0.0.1"
topic = "sensor_tmp"
valor = "23.7"

client = mqtt.Client() 
print(f"Conectando al broker: {broker_address}")
client.connect(broker_address) 

print(f"Publicando mensaje '{valor}' en el tópico '{topic}'")
client.publish(topic, valor)

# Mantener el cliente activo un momento para asegurar el envío
client.loop_start()
time.sleep(2) # Pausa para que el hilo de red procese el envío
client.loop_stop()

client.disconnect()
print("Desconectado.")