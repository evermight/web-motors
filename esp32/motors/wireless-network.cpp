#include <Arduino.h>
#include <WiFi.h>
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

void connect_network(const char* ssid[], const char* pass[]) {
  WiFi.mode(WIFI_STA); //Optional
  WiFi.disconnect();

  int n = WiFi.scanNetworks();
  Serial.println(String(n) + " networks found");
  if (n == 0) {
    return;
  }
  
  bool found = false;
  for (int i = 0; i < n && !found; ++i) {
    for (int j = 0; j < sizeof(ssid) && !found; j++) {
      if(WiFi.SSID(i) == String(ssid[j])){
        WiFi.begin(ssid[j], pass[j]);
        found = true;
      }
    }
  }

  if(!found) {
    Serial.println("Unable to connect to internet");
    return;
  }
  Serial.println("\nConnecting");

  while(WiFi.status() != WL_CONNECTED){
      Serial.print(".");
      delay(100);
  }

  Serial.println("\nConnected to the WiFi network");
  Serial.print("Local ESP32 IP: ");
  Serial.println(WiFi.localIP());
}
