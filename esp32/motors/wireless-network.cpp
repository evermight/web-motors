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

void connect_network(const char* ssid, const char* pass, const char* ssid2, const char* pass2) {
  WiFi.mode(WIFI_STA); //Optional
  bool found = false;
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0)
  {
    Serial.println("no networks found");
    return;
  }
  else
  {
    for (int i = 0; i < n && !found; ++i)
    {
      if(WiFi.SSID(i) == String(ssid)){
        WiFi.begin(ssid, pass);
        found = true;
      }
    }
    for (int i = 0; i < n && !found; ++i)
    {
      if(WiFi.SSID(i) == String(ssid2)){
        WiFi.begin(ssid2, pass2);
        found = true;
      }
    }
  }
  if(!found) {
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
