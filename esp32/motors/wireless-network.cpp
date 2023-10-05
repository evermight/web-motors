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

void connect_network(const char* ssid, const char* pass) {
  WiFi.disconnect();
  WiFi.mode(WIFI_STA); //Optional
  WiFi.begin(ssid, pass);
  
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
