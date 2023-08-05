#include <WiFi.h>
#include <HTTPClient.h>
#include "config.h"
#include "motor.h"

void get_network_info(){
    if(WiFi.status() == WL_CONNECTED) {
        Serial.print("[*] Network information for ");
        Serial.println(SSID);

        Serial.println("[+] BSSID : " + WiFi.BSSIDstr());
        Serial.print("[+] Gateway IP : ");
        Serial.println(WiFi.gatewayIP());
        Serial.print("[+] Subnet Mask : ");
        Serial.println(WiFi.subnetMask());
        Serial.println((String)"[+] RSSI : " + WiFi.RSSI() + " dB");
        Serial.print("[+] ESP32 IP : ");
        Serial.println(WiFi.localIP());
    }
}

void setup() {
  initialize_motors();

  Serial.begin(115200);

  // Connect to internet
  delay(1000);
  WiFi.mode(WIFI_STA); //Optional
  WiFi.begin(SSID, SSID_PASS);
  Serial.println("\nConnecting");

  while(WiFi.status() != WL_CONNECTED){
      Serial.print(".");
      delay(100);
  }

  Serial.println("\nConnected to the WiFi network");
  Serial.print("Local ESP32 IP: ");
  Serial.println(WiFi.localIP());
  
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
