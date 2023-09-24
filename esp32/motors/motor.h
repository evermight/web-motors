#ifndef MOTOR_FUNCTIONS
#define MOTOR_FUNCTIONS

struct MotorDetails {
  byte motor1Pin1;
  byte motor1Pin2;
  byte enable1Pin;
  
  byte motor2Pin1;
  byte motor2Pin2;
  byte enable2Pin;
};

struct PwmDetails {
  byte channel1;
  byte channel2;
  int freq;
  byte resolution;
  byte dutyCycle;
  byte dutyCycleSlow;
};

void move_motors(String motion, MotorDetails motor, PwmDetails pwm);

void initialize_motors(MotorDetails motor, PwmDetails pwm);

#endif // MOTOR_FUNCTIONS
