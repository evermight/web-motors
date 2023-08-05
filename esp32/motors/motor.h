#ifndef MOTOR_FUNCTIONS
#define MOTOR_FUNCTIONS

struct MotorDetails {
  int motor1Pin1;
  int motor1Pin2;
  int enable1Pin;
  
  int motor2Pin1;
  int motor2Pin2;
  int enable2Pin;
};

struct PwmDetails {
  int channel1;
  int channel2;
  int freq;
  int resolution;
  int dutyCycle;
};

void move_motors(char motion[2], MotorDetails motor);

void initialize_motors(MotorDetails motor, PwmDetails pwm);

#endif // MOTOR_FUNCTIONS
