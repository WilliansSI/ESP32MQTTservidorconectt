#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

const char *ssid = "senha";
const char *password = "nome";

// MQTT Broker

const char* Cliente = "esp32";
const char* Servidor = "kef41c2c.us-east-1.emqx.cloud";
const char* topico = "corrente";
const int Porta = 1313;
const char* Usuario_MQTT = "nome";
const char* Senha_MQTT = "senha";

WiFiClient espClient;
PubSubClient client(espClient);

void setup()
{
  Serial.begin(9600);
  // connecting to a WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  //client.setServer(mqtt_broker, mqtt_port);
  /* Conexão ao MQTT */
  client.setServer(Servidor, Porta);  
  while(!client.connected())
  {
    Serial.println("Conectando ao MQTT...");
    if(client.connect(Cliente, Usuario_MQTT, Senha_MQTT))
    {
      Serial.println("MQTT Conectado");
    }
    else
    {
      Serial.println("Falha na Conexão");
      Serial.print(client.state());
      delay(2000);
    }
  } 
  if(client.publish(topico, "willians na area")){
          Serial.print("Escreveu na area");
  }
  //client.setCallback(callback);
 
}

void callback(char *topic, byte *payload, unsigned int length) {
 Serial.print("Message arrived in topic: ");
 Serial.println(topic);
 Serial.print("Message:");
 for (int i = 0; i < length; i++) {
     Serial.print((char) payload[i]);
 }
 Serial.println();
 Serial.println("-----------------------");
}

void loop()
{
  // put your main code here, to run repeatedly:
  client.loop();
}