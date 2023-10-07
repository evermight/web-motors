#include <WiFi.h>
#include <PubSubClient.h>
#include "config.h"

/*
// Add your MQTT Broker IP address, example:
const char* mqtt_server = MQTT_SERVER;
const char* mqtt_topic = MQTT_TOPIC;
int mqtt_port = MQTT_PORT;
const char* mqtt_user = MQTT_USER;
const char* mqtt_pass = MQTT_PASS;
*/
String msg = "";
String listening_topic = "";
WiFiClient espClient;
PubSubClient client(espClient);


String mqtt_get_message() {
  return msg;
}

void mqtt_callback(char* topic, byte* message, unsigned int length) {
  if (String(topic) == listening_topic) {
    msg = "";
    for (int i = 0; i < length; i++) {
      msg += (char)message[i];
    }
    Serial.println(msg);
  }
}

void mqtt_configure(const char* mqtt_server, int mqtt_port) {
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(mqtt_callback);
}
void mqtt_connect(const char* mqtt_topic, const char* mqtt_user, const char* mqtt_pass) {
  listening_topic = String(mqtt_topic);
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP32Client", mqtt_user, mqtt_pass)) {
      Serial.println("connected, subscribing to");
      Serial.println(mqtt_topic);
      // Subscribe
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
