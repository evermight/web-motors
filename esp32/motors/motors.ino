#include <WiFi.h>
#include <HTTPClient.h>
#include "config.h"
#include "motor.h"
#include "wireless-network.h"

void setup() {
  initialize_motors();

  Serial.begin(115200);

  // Connect to internet
  delay(1000);
  connect_network(SSID, SSID_PASS);
  get_network_info();
}

void loop() {

  if(WiFi.status() != WL_CONNECTED)
    return;

  HTTPClient http;

  String apiUrl = API_URL;
  http.begin(apiUrl.c_str());
  
  // If you need Node-RED/server authentication, insert user and password below
  //http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");
  
  // Send HTTP GET request
  int httpResponseCode = http.GET();
  if(httpResponseCode <= 0)
    return;

  String motion = http.getString();
  motion.trim();
  move_motors(motion);
}
