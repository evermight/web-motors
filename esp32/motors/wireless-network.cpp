#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "wireless-network.h"

boolean connected_to_network() {
  return WiFi.status() == WL_CONNECTED;
}

void get_network_info(){
  if(WiFi.status() == WL_CONNECTED) {
    Serial.println("[+] SSID : " + WiFi.SSID());
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

void connect_network(const char* ssid[], const char* pass[], const int len) {
  WiFi.disconnect();
  WiFi.mode(WIFI_STA); //Optional

  int n = WiFi.scanNetworks();
  Serial.println(String(n) + " networks found");
  if (n == 0) {
    return;
  }
  
  bool found = false;
  for (int i = 0; i < n && !found; ++i) {
    for (int j = 0; j < len && !found; j++) {
      if(WiFi.SSID(i) == String(ssid[j])){
        Serial.println("\nConnecting to " + String(ssid[j]));
        WiFi.begin(ssid[j], pass[j]);
        found = true;
      }
    }
  }

  if(!found) {
    Serial.println("Unable to connect to internet");
    return;
  }

  int dl = 1000;
  int dl_limit = 15*dl;
  int dl_count = 0;
  while(WiFi.status() != WL_CONNECTED && dl_count < dl_limit){
      Serial.println(".");
      delay(dl);
      dl_count = dl_count + dl;
  }
  if(WiFi.status() != WL_CONNECTED) {
    Serial.println("Unable to connect to network");
    return;
  }

  Serial.println("\nConnected to the WiFi network");
  Serial.print("Local ESP32 IP: ");
  Serial.println(WiFi.localIP());
}
