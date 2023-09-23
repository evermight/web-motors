#include <Arduino.h>
#include "motor.h"

void initialize_motors(MotorDetails motor, PwmDetails pwm) {
  // sets the pins as outputs:
  pinMode(motor.motor1Pin1, OUTPUT);
  pinMode(motor.motor1Pin2, OUTPUT);
  pinMode(motor.enable1Pin, OUTPUT);
  pinMode(motor.motor2Pin1, OUTPUT);
  pinMode(motor.motor2Pin2, OUTPUT);
  pinMode(motor.enable2Pin, OUTPUT);

  // configure LED PWM functionalitites
  ledcSetup(pwm.channel1, pwm.freq, pwm.resolution);
  ledcSetup(pwm.channel2, pwm.freq, pwm.resolution);

  // attach the channel to the GPIO to be controlled
  ledcAttachPin(motor.enable1Pin, pwm.channel1);
  ledcAttachPin(motor.enable2Pin, pwm.channel2);
}
void move_motors(String motion, MotorDetails motor, PwmDetails pwm) {
  ledcWrite(pwm.channel1, pwm.dutyCycle);
  ledcWrite(pwm.channel2, pwm.dutyCycle);
  int slowcycle = 200;
  if(motion == "ff") {
    // Move both motors forwards at maximum speed
    digitalWrite(motor.motor1Pin1, LOW);
    digitalWrite(motor.motor1Pin2, HIGH);
    digitalWrite(motor.motor2Pin1, LOW);
    digitalWrite(motor.motor2Pin2, HIGH);
  } else if(motion == "fs") {
    // Move motor 1 forwards and motor 2 backwards at slow speed
    digitalWrite(motor.motor1Pin1, LOW);
    digitalWrite(motor.motor1Pin2, HIGH);
    digitalWrite(motor.motor2Pin1, HIGH);
    digitalWrite(motor.motor2Pin2, LOW);
    ledcWrite(pwm.channel1, slowcycle);
    ledcWrite(pwm.channel2, slowcycle);
  } else if(motion == "sf") {
    // Move motor 1 backwards and motor 2 forwards at slow speed
    digitalWrite(motor.motor1Pin1, HIGH);
    digitalWrite(motor.motor1Pin2, LOW);
    digitalWrite(motor.motor2Pin1, LOW);
    digitalWrite(motor.motor2Pin2, HIGH);
    ledcWrite(pwm.channel1, slowcycle);
    ledcWrite(pwm.channel2, slowcycle);
  } else if(motion == "bf") {
    // Move motor 1 backwards and motor 2 forwards at maximum speed
    digitalWrite(motor.motor1Pin1, HIGH);
    digitalWrite(motor.motor1Pin2, LOW);
    digitalWrite(motor.motor2Pin1, LOW);
    digitalWrite(motor.motor2Pin2, HIGH);
  } else if(motion == "fb") {
    // Move motor 1 forwards and motor 2 backwards at maximum speed
    digitalWrite(motor.motor1Pin1, LOW);
    digitalWrite(motor.motor1Pin2, HIGH);
    digitalWrite(motor.motor2Pin1, HIGH);
    digitalWrite(motor.motor2Pin2, LOW);
  } else if(motion == "bb") {
    // Move both motors backwards at maximum speed
    digitalWrite(motor.motor1Pin1, HIGH);
    digitalWrite(motor.motor1Pin2, LOW);
    digitalWrite(motor.motor2Pin1, HIGH);
    digitalWrite(motor.motor2Pin2, LOW);
  } else {
    // Stop both motors
    digitalWrite(motor.motor1Pin1, LOW);
    digitalWrite(motor.motor1Pin2, LOW);
    digitalWrite(motor.motor2Pin1, LOW);
    digitalWrite(motor.motor2Pin2, LOW);
  }
}
