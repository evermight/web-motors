#include <Arduino.h>
#ifndef MQTT_FUNCTIONS
#define MQTT_FUNCTIONS

String mqtt_get_message();
void mqtt_callback(char* topic, byte* message, unsigned int length);
void mqtt_configure();
void mqtt_connect();
bool mqtt_is_connected();
void mqtt_client_loop();

#endif // MQTT_FUNCTIONS
