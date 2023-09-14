import paho.mqtt.client as mqtt
import json
import random
import time

# Configuracoes MQTT
broker_address = "localhost"
port = 8883
cafile = "/mnt/mqttserver_cert.pem"
keyfile = "/mnt/mqttserver_key.pem"
certfile = "/mnt/mqttserver_cert.pem"
topic = "v1/devices/me/telemetry"

# Dados a serem enviados
data = {"temperature": 18}

def temperature_value(min, max):
    random_temp = round(random.uniform(min, max), 2)
    return {"temperature": random_temp}

def humidity_value(min, max):
    random_humi =  round(random.uniform(min, max), 2)
    return {"humidity": random_humi}


# Funca de callback para quando a conexao MQTT eh estabelecida
def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Conexao estabelecida com sucesso")
    else:
        print("Erro na conexao (Codigo: " + str(rc) + ")")

# Cria um cliente MQTT
client = mqtt.Client()

# Define as funcoes de callback
client.on_connect = on_connect

# Configura as opcoes de TLS/SSL
client.tls_set(ca_certs=cafile, certfile=certfile, keyfile=keyfile)

# Conecta-se ao broker MQTT
client.connect(broker_address, port)

# Loop principal
try:
    while True:
        # Gera dados de temperatura e umidade
        temp = temperature_value(10, 30)
        humi = humidity_value(50, 60)

        # Cria um único payload JSON com temperatura e umidade
        payload = json.dumps({"temperature": temp["temperature"], "humidity": humi["humidity"]})

        # Publica os dados no tópico MQTT
        client.publish(topic, payload, qos=1)
        print("Dados publicados: " + payload)

        time.sleep(5)  # Aguarda 5 segundos antes de enviar novamente


except KeyboardInterrupt:
    print("Programa encerrado pelo usuario")
    client.disconnect()