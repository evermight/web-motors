#include <WiFi.h>
#include <HTTPClient.h>
#include "config.h"

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

void move_motors(String motion) {
  if(motion == "ff") {
    // Move both motors forwards at maximum speed
    digitalWrite(MOTOR1_PIN1, LOW);
    digitalWrite(MOTOR1_PIN2, HIGH);
    digitalWrite(MOTOR2_PIN1, LOW);
    digitalWrite(MOTOR2_PIN2, HIGH);
  } else if(motion == "fs") {
    // Move motor 1 forwards at maximum speed
    digitalWrite(MOTOR1_PIN1, LOW);
    digitalWrite(MOTOR1_PIN2, HIGH);
    digitalWrite(MOTOR2_PIN1, LOW);
    digitalWrite(MOTOR2_PIN2, LOW);
  } else if(motion == "sf") {
    // Move motor 2 forwards at maximum speed
    digitalWrite(MOTOR1_PIN1, LOW);
    digitalWrite(MOTOR1_PIN2, LOW);
    digitalWrite(MOTOR2_PIN1, LOW);
    digitalWrite(MOTOR2_PIN2, HIGH);
  } else if(motion == "bf") {
    // Move motor 1 backwards and motor 2 forwards at maximum speed
    digitalWrite(MOTOR1_PIN1, HIGH);
    digitalWrite(MOTOR1_PIN2, LOW);
    digitalWrite(MOTOR2_PIN1, LOW);
    digitalWrite(MOTOR2_PIN2, HIGH);
  } else if(motion == "fb") {
    // Move motor 1 backwards and motor 2 forwards at maximum speed
    digitalWrite(MOTOR1_PIN1, LOW);
    digitalWrite(MOTOR1_PIN2, HIGH);
    digitalWrite(MOTOR2_PIN1, HIGH);
    digitalWrite(MOTOR2_PIN2, LOW);
  } else if(motion == "bb") {
    // Move both motors backwards at maximum speed
    digitalWrite(MOTOR1_PIN1, HIGH);
    digitalWrite(MOTOR1_PIN2, LOW);
    digitalWrite(MOTOR2_PIN1, HIGH);
    digitalWrite(MOTOR2_PIN2, LOW);
  } else {
    // Stop both motors
    digitalWrite(MOTOR1_PIN1, LOW);
    digitalWrite(MOTOR1_PIN2, LOW);
    digitalWrite(MOTOR2_PIN1, LOW);
    digitalWrite(MOTOR2_PIN2, LOW);
  }
  delay(100);
}

void setup() {
  // sets the pins as outputs:
  pinMode(MOTOR1_PIN1, OUTPUT);
  pinMode(MOTOR1_PIN2, OUTPUT);
  pinMode(ENABLE1_PIN, OUTPUT);
  pinMode(MOTOR2_PIN1, OUTPUT);
  pinMode(MOTOR2_PIN2, OUTPUT);
  pinMode(ENABLE2_PIN, OUTPUT);

  
  // configure LED PWM functionalitites
  ledcSetup(PWM_CHANNEL_1, PWM_FREQ, PWM_RESOLUTION);
  ledcSetup(PWM_CHANNEL_2, PWM_FREQ, PWM_RESOLUTION);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(ENABLE1_PIN, PWM_CHANNEL_1);
  ledcAttachPin(ENABLE2_PIN, PWM_CHANNEL_2);
  ledcWrite(PWM_CHANNEL_1, PWM_DUTY_CYCLE);
  ledcWrite(PWM_CHANNEL_2, PWM_DUTY_CYCLE);

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
