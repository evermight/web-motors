//#include "BluetoothSerial.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include "config.h"
#include "motor.h"
#include "wireless-network.h"
#include "api.h";
/*
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
*/
boolean connecting = false;

/*
const char* SSID_NAME = "";
const char* SSID_PASS = "";
const char* API_URL = "";
*/
//BluetoothSerial SerialBT;

MotorDetails motor = {
  .motor1Pin1 = MOTOR1_PIN1,
  .motor1Pin2 = MOTOR1_PIN2,
  .enable1Pin = ENABLE1_PIN,
  .motor2Pin1 = MOTOR2_PIN1,
  .motor2Pin2 = MOTOR2_PIN2,
  .enable2Pin = ENABLE2_PIN
};

PwmDetails pwm = {
  .channel1 = PWM_CHANNEL_1,
  .channel2 = PWM_CHANNEL_2,
  .freq = PWM_FREQ,
  .resolution = PWM_RESOLUTION,
  .dutyCycle = PWM_DUTY_CYCLE
};

void setup() {
  Serial.begin(115200);

  //SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("Device started, pair with bluetooth!");
 
  initialize_motors(motor, pwm);

  // Connect to internet
  delay(1000);
  connect_network(SSID_NAME, SSID_PASS);

}

void loop() {
  /*
  if(Serial.available()) {
    SerialBT.write(Serial.read());
    delay(20);
  }
  if (SerialBT.available()) {
    String payload = SerialBT.readStringUntil('\n');
    payload.trim();
    if(payload == "connect") {
      connecting = true;
      
    } else if (strncmp(payload.c_str(), "SSID_NAME=", 5) == 0) {
      SSID_NAME = payload.substring(5).c_str();
      
    } else if (strncmp(payload.c_str(), "SSID_PASS=", 5) == 0) {
      SSID_PASS = payload.substring(5).c_str();
      
    } else if (strncmp(payload.c_str(), "API_URL=", 4) == 0) {
      API_URL = payload.substring(4).c_str();

    }
    delay(20);
  }

  if(connecting) {
    delay(1000);
    connect_network(SSID_NAME, SSID_PASS);
    connecting = false;
  }
*/
  delay(100);  
  if(WiFi.status() != WL_CONNECTED)
    return;
  
  ApiResponse response = api_get(API_URL);
  if(response.httpResponseCode <= 0)
    return;
  //Serial.println(response.motion);
  move_motors(response.motion, motor);

}
