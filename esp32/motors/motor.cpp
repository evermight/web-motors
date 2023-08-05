#include <Arduino.h>
#include "config.h"
#include "motor.h"
void initialize_motors() {
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
