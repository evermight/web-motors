#include <Arduino.h>
#ifndef HTML_FUNCTIONS
#define HTML_FUNCTIONS
String html_foot();
String html_css();
String html_script();
String html_form();
String html_current_connection(String new_ssid, String new_pass, String api_url, String mqtt_server, String mqtt_port, String mqtt_topic, String mqtt_user, String mqtt_pass);
String html_head();
#endif // HTML_FUNCTIONS
