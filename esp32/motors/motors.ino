#include <WiFi.h>
#include <HTTPClient.h>
#include "config.h"
#include "motor.h"
#include "wireless-network.h"
#include "api.h";

MotorDetails get_motor_details() {
  MotorDetails motor;
  motor.motor1Pin1 = MOTOR1_PIN1;
  motor.motor1Pin2 = MOTOR1_PIN2;
  motor.enable1Pin = ENABLE1_PIN;
  motor.motor2Pin1 = MOTOR2_PIN1;
  motor.motor2Pin2 = MOTOR2_PIN2;
  motor.enable2Pin = ENABLE2_PIN;
  return motor;
}

PwmDetails get_pwm_details() {
  PwmDetails pwm;
  pwm.channel1 = PWM_CHANNEL_1;
  pwm.channel2 = PWM_CHANNEL_2;
  pwm.freq = PWM_FREQ;
  pwm.resolution = PWM_RESOLUTION;
  pwm.dutyCycle = PWM_DUTY_CYCLE;
  return pwm;
}

void setup() {

  initialize_motors(get_motor_details(), get_pwm_details());

  Serial.begin(115200);

  // Connect to internet
  delay(1000);
  connect_network(SSID, SSID_PASS);
  get_network_info();
}

void loop() {
  delay(100);
  if(WiFi.status() != WL_CONNECTED)
    return;
  
  ApiResponse response = api_get(API_URL);
  if(response.httpResponseCode <= 0)
    return;

  move_motors(response.motion, get_motor_details());
}
