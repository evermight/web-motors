#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <WebServer.h>
#include <ArduinoJson.h>
#include "config.h"
#include "html.h"

WebServer server(80);
String new_ssid = "";
String new_pass = "";
String api_url = "";
String mqtt_server = "";
String mqtt_port = "";
String mqtt_topic = "";
String mqtt_user = "";
String mqtt_pass = "";

// Set these to your desired credentials.
const char *ssid = SSID_NAME;
const char *password = SSID_PASS;

void access_point_start() {
  // You can remove the password parameter if you want the AP to be open.
  // a valid password must have more than 7 characters
  if (!WiFi.softAP(ssid, password)) {
    log_e("Soft AP creation failed.");
    while(1);
  }
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
}
const char* get_pass() {
  return new_pass.c_str();
}
const char* get_ssid() {
  return new_ssid.c_str();
}
String get_api_url() {
  return api_url;
}
bool ssid_exists() {
  return new_ssid != "";
}
const char* get_mqtt_server() {
  return mqtt_server.c_str();
}
int get_mqtt_port() {
  return mqtt_port.toInt();
}
const char* get_mqtt_topic() {
  return mqtt_topic.c_str();
}
const char* get_mqtt_user() {
  return mqtt_user.c_str();
}
const char* get_mqtt_pass() {
  return mqtt_pass.c_str();
}
void handle_connect() {
  String body = server.arg("plain");
  StaticJsonDocument<250> jsonDocument;
  deserializeJson(jsonDocument, body);
  new_ssid = jsonDocument["ss_id"].as<String>();
  new_pass = jsonDocument["ss_pass"].as<String>();
  api_url = jsonDocument["api_url"].as<String>();
  mqtt_server = jsonDocument["mqtt_server"].as<String>();
  mqtt_port = jsonDocument["mqtt_port"].as<String>();
  mqtt_topic = jsonDocument["mqtt_topic"].as<String>();
  mqtt_user = jsonDocument["mqtt_user"].as<String>();
  mqtt_pass = jsonDocument["mqtt_pass"].as<String>();

  String json = "{\"ss_id\":\""+new_ssid+"\"";
  json += ",\"ss_pass\":\""+new_pass+"\"";
  json += ",\"api_url\":\""+api_url+"\"";
  json += ",\"mqtt_server\":\""+mqtt_server+"\"";
  json += ",\"mqtt_port\":\""+mqtt_port+"\"";
  json += ",\"mqtt_topic\":\""+mqtt_topic+"\"";
  json += ",\"mqtt_user\":\""+mqtt_user+"\"";
  json += ",\"mqtt_pass\":\""+mqtt_pass+"\"";
  json += "}";
  server.send(200, "application/json", json);
  server.stop();
}

void handle_home() {

  server.send(200,"text/html",html());
}

void server_start() {
  server.on("/", handle_home);
  server.on("/connect", HTTP_POST, handle_connect);
  server.begin();
}
void server_stop() {
  server.stop();
}
void server_handle_client() {
  server.handleClient();
}
