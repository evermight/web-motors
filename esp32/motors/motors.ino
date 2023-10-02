#include "config.h"
#include "motor.h"
#include "wireless-network.h"
#include "api.h";

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

const char* ssids[] = SSID_NAMES;
const char* passes[] = SSID_PASSES;
const int ssid_len = SSID_LEN;
void setup() {
  Serial.begin(115200);
  initialize_motors(motor, pwm);
  
  // Connect to internet
  delay(1000);
  connect_network(ssids, passes, ssid_len);
  get_network_info();
  delay(1000);
}

void loop() {
  delay(LOOP_SPEED);
  
  if(!connected_to_network()) {
    // Stop the motor
    move_motors("ss", motor, pwm);
    
    // Try to reconnect
    connect_network(ssids, passes, ssid_len);
    get_network_info();
    delay(5000);
    return;
  }

  ApiResponse response = api_get(API_URL);
  if(response.httpResponseCode <= 0)
    return;

  move_motors(response.motion, motor, pwm);
}
