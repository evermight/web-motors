#include <Arduino.h>
#ifndef MQTT_FUNCTIONS
#define MQTT_FUNCTIONS

String mqtt_message_get();
void mqtt_callback(char* topic, byte* message, unsigned int length);
void mqtt_configure(const char* mqtt_server, int mqtt_port);
void mqtt_connect(const char* mqtt_topic, const char* mqtt_user, const char* mqtt_pass);
bool mqtt_is_connected();
void mqtt_client_loop();

#endif // MQTT_FUNCTIONS
