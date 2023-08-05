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
  ledcWrite(pwm.channel1, pwm.dutyCycle);
  ledcWrite(pwm.channel2, pwm.dutyCycle);
}
void move_motors(char motion[2], MotorDetails motor) {
  if(motion[0] == 'f' && motion[1] == 'f') {
    // Move both motors forwards at maximum speed
    digitalWrite(motor.motor1Pin1, LOW);
    digitalWrite(motor.motor1Pin2, HIGH);
    digitalWrite(motor.motor2Pin1, LOW);
    digitalWrite(motor.motor2Pin2, HIGH);
  } else if(motion[0] == 'f' && motion[1] == 's') {
    // Move motor 1 forwards at maximum speed
    digitalWrite(motor.motor1Pin1, LOW);
    digitalWrite(motor.motor1Pin2, HIGH);
    digitalWrite(motor.motor2Pin1, LOW);
    digitalWrite(motor.motor2Pin2, LOW);
  } else if(motion[0] == 's' && motion[1] == 'f') {
    // Move motor 2 forwards at maximum speed
    digitalWrite(motor.motor1Pin1, LOW);
    digitalWrite(motor.motor1Pin2, LOW);
    digitalWrite(motor.motor2Pin1, LOW);
    digitalWrite(motor.motor2Pin2, HIGH);
  } else if(motion[0] == 'b' && motion[1] == 'f') {
    // Move motor 1 backwards and motor 2 forwards at maximum speed
    digitalWrite(motor.motor1Pin1, HIGH);
    digitalWrite(motor.motor1Pin2, LOW);
    digitalWrite(motor.motor2Pin1, LOW);
    digitalWrite(motor.motor2Pin2, HIGH);
  } else if(motion[0] == 'f' && motion[1] == 'b') {
    // Move motor 1 backwards and motor 2 forwards at maximum speed
    digitalWrite(motor.motor1Pin1, LOW);
    digitalWrite(motor.motor1Pin2, HIGH);
    digitalWrite(motor.motor2Pin1, HIGH);
    digitalWrite(motor.motor2Pin2, LOW);
  } else if(motion[0] == 'b' && motion[1] == 'b') {
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
