#include "config.h"
#include "motor.h"
#include "server.h"
#include "wireless-network.h"
//#include "api.h"
#include "mqtt.h"

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
  .dutyCycle = PWM_DUTY_CYCLE,
  .dutyCycleSlow = PWM_DUTY_CYCLE_SLOW
};

void setup() {
  Serial.begin(115200);
  initialize_motors(motor, pwm);
  access_point_start();
  server_start();
  mqtt_configure();
  delay(5000);
}

void loop() {
  
  if(!ssid_exists()) {
    server_handle_client();
    return;
  }
  //delay(LOOP_SPEED);

  if(!mqtt_is_connected()) {
    mqtt_connect();
    delay(5000);
    return;
  }
  mqtt_client_loop();
/*
  if(!connected_to_network()) {
    // Stop the motor
    move_motors("ss", motor, pwm);
    
    // Try to reconnect
    connect_network(get_ssid(), get_pass());
    get_network_info();
    delay(5000);
    return;
  }

  ApiResponse response = api_get(get_api_url());
  if(response.httpResponseCode <= 0)
    return;

  move_motors(response.motion, motor, pwm);
*/
}
