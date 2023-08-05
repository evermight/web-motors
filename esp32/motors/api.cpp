#include <Arduino.h>
#include <HTTPClient.h>
#include "api.h"

ApiResponse api_get(String apiUrl) {
  ApiResponse response;
  HTTPClient http;

  response.httpResponseCode = -1;
  response.motion = "";

  http.begin(apiUrl);
  // If you need Node-RED/server authentication, insert user and password below
  //http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");

  // Send HTTP GET request
  response.httpResponseCode = http.GET();
  if(response.httpResponseCode <= 0)
    return response;

  String motion = http.getString();
  motion.trim();
  response.motion = motion;

  return response;
}
