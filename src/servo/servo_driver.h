#ifndef SERVO_DRIVER_H
#define SERVO_DRIVER_H

#include <ESP32Servo.h>

#define CLAW_SERVO_L 22
#define CLAW_SERVO_R 23
#define PITCH_SERVO 21

#define PITCH_OFFSET 0
#define LEFT_OFFSET 0
#define RIGHT_OFFSET 0

extern Servo claw_servo_L;
extern Servo claw_servo_R;
extern Servo pitch_servo;



void init_servos();
void move_servo(Servo servo, int angle);

#endif