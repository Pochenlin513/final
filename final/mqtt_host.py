import paho.mqtt.client as paho
import time

mqttc = paho.Client()

host = "localhost"
topic = "BBcar"

port = 1883


# Callbacks
def on_connect(self, mosq, obj, rc):
    print("Connected rc: " + str(rc))

def on_message(mosq, obj, msg):
    print("[Received] Topic: " + msg.topic + ", Message: " + str(msg.payload) + "\n");
    if msg.topic == "AccX":
        x.append(float(msg.payload))
    elif msg.topic == "AccY":
        y.append(float(msg.payload))
    elif msg.topic == "AccZ":
        z.append(float(msg.payload))
    elif msg.topic == "tilt":
        tilt.append(float(msg.payload))
def on_subscribe(mosq, obj, mid, granted_qos):
    print("Subscribed OK")

def on_unsubscribe(mosq, obj, mid, granted_qos):
    print("Unsubscribed OK")

# Set callbacks
mqttc.on_message = on_message
mqttc.on_connect = on_connect
mqttc.on_subscribe = on_subscribe
mqttc.on_unsubscribe = on_unsubscribe

# Connect and subscribe
print("Connecting to " + host + "/" + topic)
mqttc.connect(host, port=1883, keepalive=60)
mqttc.subscribe(topic, 0)

while True:
    mqttc.loop()