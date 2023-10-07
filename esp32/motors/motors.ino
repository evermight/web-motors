#include "config.h"
#include "motor.h"
#include "setup.h"
#include "wifi.h"
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
  motor_init(motor, pwm);
  setup_access_point_start();
  setup_start();
  delay(5000);
}

void loop() {

  // Ensure wifi credentials for internet
  if(!setup_wifi_ssid_exists()) {
    setup_handle_client();
    return;
  }

  // Ensure internet access
  if(!wifi_is_connected()) {
    // Stop the motor
    motor_move("ss", motor, pwm);

    // Try to reconnect
    wifi_connect(setup_wifi_ssid_get(), setup_wifi_pass_get());
    wifi_info_get();
    delay(5000);
    return;
  }

  // Ensure MQTT access
  if(!mqtt_is_connected()) {
    mqtt_configure(setup_mqtt_server_get(), setup_mqtt_port_get());
    mqtt_connect(setup_mqtt_topic_get(), setup_mqtt_user_get(), setup_mqtt_pass_get());
    delay(5000);
    return;
  }

  // Move motors
  motor_move(mqtt_message_get(), motor, pwm);
  mqtt_client_loop();

/*
  delay(LOOP_SPEED);
  ApiResponse response = api_get(setup_api_url_get());
  if(response.httpResponseCode <= 0)
    return;

  move_motors(response.motion, motor, pwm);
*/
}
