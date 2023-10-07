#include <WiFi.h>
#include <PubSubClient.h>
#include "config.h"


// Add your MQTT Broker IP address, example:
const char* mqtt_server = MQTT_SERVER;
const char* mqtt_topic = MQTT_TOPIC;
int mqtt_port = MQTT_PORT;
const char* mqtt_user = MQTT_USER;
const char* mqtt_pass = MQTT_PASS;

WiFiClient espClient;
PubSubClient client(espClient);


void mqtt_callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }

  // If a message is received on the topic esp32/output, you check if the message is either "on" or "off". 
  // Changes the output state according to the message
  if (String(topic) == mqtt_topic) {
    Serial.println(messageTemp);
  }
}

void mqtt_configure() {
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(mqtt_callback);
}
void mqtt_connect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client", mqtt_user, mqtt_pass)) {
      Serial.println("connected, subscribing to");
      Serial.println(mqtt_topic);
      // Subscribe
      client.setCallback(mqtt_callback);
      client.subscribe(mqtt_topic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

bool mqtt_is_connected() {
  return client.connected();
}
void mqtt_client_loop() {
  client.loop();
}
