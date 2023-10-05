#include <Arduino.h>

#ifndef SERVER_FUNCTIONS
#define SERVER_FUNCTIONS
void access_point_start();
String get_api_url();
bool get_connection_status();
void handle_connect();
void handle_home();
void server_start();
void server_end();
void server_handle_client();
#endif // SERVER_FUNCTIONS
