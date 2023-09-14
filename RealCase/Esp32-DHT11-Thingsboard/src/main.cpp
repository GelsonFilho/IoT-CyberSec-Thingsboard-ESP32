#include <Arduino.h>
/*
#include <Adafruit_Sensor.h>
#include <DHT.h>
#define DHT_SENSOR_PIN  10
#define DHT_SENSOR_TYPE DHT11
DHT dht(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);

#include <WiFi.h>
#include <PubSubClient.h>
const char* ssid         = "GELlllllllllSON FILHO";
const char* password     = "Mud@r$321";
const char* mqttServer   = "192.168.0.9";
const int   mqttPort     = 1883;
const char* TOKEN        = "0n9tbw9g3hkmjpil49rk";
//const char* mqttUser     = "usuario"; //User name
//const char* mqttPassword = "password"; //Password
//const char* mqttClient   = "id"; //ID
WiFiClient wifiClient;
PubSubClient client(wifiClient);
int status = WL_IDLE_STATUS;
unsigned long lastSend;

void InitWifi()
{
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("Iniciando conexao com a rede WiFi..");
  }
  Serial.println("Conectado na rede WiFi!");
}

void reconnect()
{
  while (!client.connected())
  {
    status = WiFi.status();
    if (status != WL_CONNECTED)
      InitWifi();
    
    Serial.print("Conectando a Thingsboard ...");

    if (client.connect("ESP32 Device", TOKEN, NULL))
    //if (client.connect(mqttClient, mqttUser, mqttPassword))
      Serial.println("[DONE]");
    else
    {
      Serial.print("[FAILED] [ rc = ]");
      Serial.println(client.state());
      delay(5000);
    }
  }
}

void get_send_temp_humid_data()
{
  Serial.println("Adquirindo valores.");

  float humi = dht.readHumidity();
  float temp = dht.readTemperature();

  if(isnan(humi) || isnan(temp))
  {
    Serial.println("Falha na leitura do sensor!");
    return;
  }

  String temperature = String(temp);
  String humidity = String(humi);

  String payload = "{";
  payload += "\"temperature\":";
  payload += temperature;
  payload += ",";
  payload += "\"humidity\":";
  payload += humidity; 
  payload += "}";

  char attributes[100];
  payload.toCharArray(attributes, 100);
  client.publish("v1/devices/me/telemetry", attributes);
  Serial.println(attributes);
}

void setup() 
{
  Serial.begin(115200);
  dht.begin(); // initialize the DHT sensor
  InitWifi();
  delay(2000);
  client.setServer(mqttServer, mqttPort);
  lastSend = 0;
}

void loop()
{
  if(!client.connected())
    reconnect();
  
  if(millis() - lastSend > 1000)
  {
    get_send_temp_humid_data();
    lastSend = millis();
  }

  client.loop();
}
*/

/*
#include <Adafruit_Sensor.h>
#include <DHT.h>
#define DHT_SENSOR_PIN  10
#define DHT_SENSOR_TYPE DHT11
DHT dht(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);

#include <WiFiClientSecure.h>
#include <PubSubClient.h>
const char* ssid         = "GELSON FILHO";
const char* password     = "Mud@r$321";
const char* mqttServer   = "192.168.0.9";
const int   mqttPort     = 8883;
//const char* TOKEN        = "gnr7okcwoawg8cpl9pq2";
const char* mqttUser     = "usuario"; //User name
const char* mqttPassword = "password"; //Password
const char* mqttClient   = "id"; //ID
WiFiClientSecure wifiClient;
PubSubClient client(wifiClient);
int status = WL_IDLE_STATUS;
unsigned long lastSend;

const char* test_client_key= \
    "-----BEGIN EC PARAMETERS-----\n" \
    "BggqhkjOPQMBBw==\n" \
    "-----END EC PARAMETERS-----\n" \
    "-----BEGIN EC PRIVATE KEY-----\n" \
    "MHcCAQEEIEX/OW+QNsnTZGM1N2Y1V137BYQ23dQxLEVMp7svm5proAoGCCqGSM49\n" \
    "AwEHoUQDQgAEK2bFZc/6kBxazr+8gkkC83/AWy/8sIdAbJGnv6qAfd9A/G27nLuE\n" \
    "Bfu/w3wLwYhrzlZTnkWvPCXVjz2R3xryaA==\n" \
    "-----END EC PRIVATE KEY-----\n";

const char* test_client_cert= \
    "-----BEGIN CERTIFICATE-----\n" \
    "MIIBfTCCASOgAwIBAgIUBFKsPeVgNGYpv+1T3mh6ZC6clKowCgYIKoZIzj0EAwIw\n" \
    "FDESMBAGA1UEAwwJbG9jYWxob3N0MB4XDTIzMDkwODIyMjcyMFoXDTI0MDkwNzIy\n" \
    "MjcyMFowFDESMBAGA1UEAwwJbG9jYWxob3N0MFkwEwYHKoZIzj0CAQYIKoZIzj0D\n" \
    "AQcDQgAEK2bFZc/6kBxazr+8gkkC83/AWy/8sIdAbJGnv6qAfd9A/G27nLuEBfu/\n" \
    "w3wLwYhrzlZTnkWvPCXVjz2R3xryaKNTMFEwHQYDVR0OBBYEFAI+kF3rS3KjE4VU\n" \
    "Xo2EugO5/mZgMB8GA1UdIwQYMBaAFAI+kF3rS3KjE4VUXo2EugO5/mZgMA8GA1Ud\n" \
    "EwEB/wQFMAMBAf8wCgYIKoZIzj0EAwIDSAAwRQIgV9cUAib2a+fgbkfl5VxUqCLE\n" \
    "uRHSkxd4RKho5TVUjqICIQC45BMnDVja1SIvO6/IUzq6qj+a6Vh+xPweHRZITMaa\n" \
    "Hg==\n" \
    "-----END CERTIFICATE-----\n";

void InitWifi()
{
  Serial.println();
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print("Iniciando conexao com a rede WiFi: ");
    Serial.println(ssid);
  }
  Serial.println("WiFi conectado com sucesso!");

  //wifiClient.setCACert(test_client_cert);
  wifiClient.setCertificate(test_client_cert); // for client verification
  //wifiClient.setPrivateKey(test_client_key);	// for client verification
  //wifiClient.setInsecure();


  Serial.println();
}

void reconnect()
{
  while (!client.connected())
  {
    status = WiFi.status();
    if (status != WL_CONNECTED)
      InitWifi();
    
    Serial.println();
    Serial.print("Conectando a Thingsboard ...");

    //if (client.connect("ESP32 Device", TOKEN, NULL))
    if (client.connect(mqttClient, mqttUser, mqttPassword))
    //if (client.connect("ESP32 Device"))
      Serial.println("[DONE]");
    else
    {
      Serial.print("[FAILED] [ rc = ]");
      Serial.println(client.state());
      delay(5000);
    }
    Serial.println();
  }
}

void get_send_temp_humid_data()
{
  Serial.println("Adquirindo valores.");

  float humi = dht.readHumidity();
  float temp = dht.readTemperature();

  if(isnan(humi) || isnan(temp))
  {
    Serial.println("Falha na leitura do sensor!");
    return;
  }

  String temperature = String(temp);
  String humidity = String(humi);

  String payload = "{";
  payload += "\"temperature\":";
  payload += temperature;
  payload += ",";
  payload += "\"humidity\":";
  payload += humidity; 
  payload += "}";

  char attributes[100];
  payload.toCharArray(attributes, 100);
  client.publish("v1/devices/me/telemetry", attributes);
  Serial.println(attributes);
}

void setup() 
{
  Serial.begin(115200);
  dht.begin(); // initialize the DHT sensor
  InitWifi();
  delay(2000);
  client.setServer(mqttServer, mqttPort);
  lastSend = 0;
}

void loop()
{
  if(!client.connected())
    reconnect();
  
  if(millis() - lastSend > 1000)
  {
    get_send_temp_humid_data();
    lastSend = millis();
  }

  client.loop();
}*/

#include <PubSubClient.h>
#include "dependencies/WiFiClientSecure/WiFiClientSecure.h"

const char* CA_cert = \
    "-----BEGIN CERTIFICATE-----\n" \
    "MIIBfTCCASOgAwIBAgIUBFKsPeVgNGYpv+1T3mh6ZC6clKowCgYIKoZIzj0EAwIw\n" \
    "FDESMBAGA1UEAwwJbG9jYWxob3N0MB4XDTIzMDkwODIyMjcyMFoXDTI0MDkwNzIy\n" \
    "MjcyMFowFDESMBAGA1UEAwwJbG9jYWxob3N0MFkwEwYHKoZIzj0CAQYIKoZIzj0D\n" \
    "AQcDQgAEK2bFZc/6kBxazr+8gkkC83/AWy/8sIdAbJGnv6qAfd9A/G27nLuEBfu/\n" \
    "w3wLwYhrzlZTnkWvPCXVjz2R3xryaKNTMFEwHQYDVR0OBBYEFAI+kF3rS3KjE4VU\n" \
    "Xo2EugO5/mZgMB8GA1UdIwQYMBaAFAI+kF3rS3KjE4VUXo2EugO5/mZgMA8GA1Ud\n" \
    "EwEB/wQFMAMBAf8wCgYIKoZIzj0EAwIDSAAwRQIgV9cUAib2a+fgbkfl5VxUqCLE\n" \
    "uRHSkxd4RKho5TVUjqICIQC45BMnDVja1SIvO6/IUzq6qj+a6Vh+xPweHRZITMaa\n" \
    "Hg==\n" \
    "-----END CERTIFICATE-----\n";

const char* ESP_CA_cert = \
    "-----BEGIN CERTIFICATE-----\n" \
    "MIIBfTCCASOgAwIBAgIUBFKsPeVgNGYpv+1T3mh6ZC6clKowCgYIKoZIzj0EAwIw\n" \
    "FDESMBAGA1UEAwwJbG9jYWxob3N0MB4XDTIzMDkwODIyMjcyMFoXDTI0MDkwNzIy\n" \
    "MjcyMFowFDESMBAGA1UEAwwJbG9jYWxob3N0MFkwEwYHKoZIzj0CAQYIKoZIzj0D\n" \
    "AQcDQgAEK2bFZc/6kBxazr+8gkkC83/AWy/8sIdAbJGnv6qAfd9A/G27nLuEBfu/\n" \
    "w3wLwYhrzlZTnkWvPCXVjz2R3xryaKNTMFEwHQYDVR0OBBYEFAI+kF3rS3KjE4VU\n" \
    "Xo2EugO5/mZgMB8GA1UdIwQYMBaAFAI+kF3rS3KjE4VUXo2EugO5/mZgMA8GA1Ud\n" \
    "EwEB/wQFMAMBAf8wCgYIKoZIzj0EAwIDSAAwRQIgV9cUAib2a+fgbkfl5VxUqCLE\n" \
    "uRHSkxd4RKho5TVUjqICIQC45BMnDVja1SIvO6/IUzq6qj+a6Vh+xPweHRZITMaa\n" \
    "Hg==\n" \
    "-----END CERTIFICATE-----\n";

const char* ESP_RSA_key= \
    "-----BEGIN EC PARAMETERS-----\n" \
    "BggqhkjOPQMBBw==\n" \
    "-----END EC PARAMETERS-----\n" \
    "-----BEGIN EC PRIVATE KEY-----\n" \
    "MHcCAQEEIEX/OW+QNsnTZGM1N2Y1V137BYQ23dQxLEVMp7svm5proAoGCCqGSM49\n" \
    "AwEHoUQDQgAEK2bFZc/6kBxazr+8gkkC83/AWy/8sIdAbJGnv6qAfd9A/G27nLuE\n" \
    "Bfu/w3wLwYhrzlZTnkWvPCXVjz2R3xryaA==\n" \
    "-----END EC PRIVATE KEY-----\n";

const char* ssid        = "GELSON FILHO";        // your network SSID (name of wifi network)
const char* password    = "Mud@r$321";   // your network password

const char* mqtt_server = "192.168.0.9";  //Adress for your Mosquitto broker server, it must be the same adress that you set in Mosquitto.csr CN field
int port                = 8883;             //Port to your Mosquitto broker server. Dont forget to forward it in your router for remote access
const char* mqtt_user   = "";           //Depends on Mosquitto configuration, if it is not set, you do not need it
const char* mqtt_pass   = "";  //Depends on Mosquitto configuration, if it is not set, you do not need it

WiFiClientSecure client;
PubSubClient mqtt_client(client); 

#include <Adafruit_Sensor.h>
#include <DHT.h>
#define DHT_SENSOR_PIN  10
#define DHT_SENSOR_TYPE DHT11
DHT dht(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);

void get_send_temp_humid_data()
{
  Serial.println("Adquirindo valores.");

  float humi = dht.readHumidity();
  float temp = dht.readTemperature();

  if(isnan(humi) || isnan(temp))
  {
    Serial.println("Falha na leitura do sensor!");
    return;
  }

  String temperature = String(temp);
  String humidity = String(humi);

  String payload = "{";
  payload += "\"temperature\":";
  payload += temperature;
  payload += ",";
  payload += "\"humidity\":";
  payload += humidity; 
  payload += "}";

  char attributes[100];
  payload.toCharArray(attributes, 100);
  mqtt_client.publish("v1/devices/me/telemetry", attributes);
  Serial.println(attributes);
}

void setup() {
  Serial.begin(115200);
  delay(100); 

  dht.begin();
  Serial.print("Attempting to connect to SSID: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  // attempt to connect to Wifi network:
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    // wait 1 second for re-trying
    delay(1000);
  }

  Serial.print("Connected to ");
  Serial.println(ssid);

  //Set up the certificates and keys
  client.setCACert(CA_cert);          //Root CA certificate
  client.setCertificate(ESP_CA_cert); //for client verification if the require_certificate is set to true in the mosquitto broker config
  client.setPrivateKey(ESP_RSA_key);  //for client verification if the require_certificate is set to true in the mosquitto broker config

  mqtt_client.setServer(mqtt_server, port);

  Serial.println("Saiu do void setup");

}

void loop() {  
  Serial.println("\nStarting connection to server...");
  //if you use password for Mosquitto broker
  //if (mqtt_client.connect("ESP32", mqtt_user , mqtt_pass)) {
  //if you dont use password for Mosquitto broker
  if (mqtt_client.connect("ESP32")) {                       
    Serial.print("Connected, mqtt_client state: ");
    Serial.println(mqtt_client.state());
    //Publsih a demo message to topic LivingRoom/TEMPERATURE with a value of 25
    //mqtt_client.publish("LivingRoom/TEMPERATURE", "25");
    get_send_temp_humid_data();
  }
  else {
    Serial.println("Connected failed!  mqtt_client state:");
    Serial.print(mqtt_client.state());
    Serial.println("WiFiClientSecure client state:");
    char lastError[100];
    //client.lastError(lastError,100);  //Get the last error for WiFiClientSecure
    Serial.print(lastError);
  }
  delay(10000);
}