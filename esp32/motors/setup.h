#include <Arduino.h>

#ifndef SETUP_FUNCTIONS
#define SETUP_FUNCTIONS
void setup_access_point_start();
const char* setup_mqtt_server_get();
int setup_mqtt_port_get();
const char* setup_mqtt_topic_get();
const char* setup_mqtt_user_get();
const char* setup_mqtt_pass_get();
const char* setup_wifi_ssid_get();
const char* setup_wifi_pass_get();
bool setup_wifi_ssid_exists();
String setup_api_url_get();
void handle_connect();
void handle_home();
void setup_start();
void setup_end();
void setup_handle_client();
#endif // SETUP_FUNCTIONS
