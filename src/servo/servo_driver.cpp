#include "servo/servo_driver.h"

Servo claw_servo_L;
Servo claw_servo_R;
Servo pitch_servo;


void init_servos() {
    ESP32PWM::allocateTimer(0);
    ESP32PWM::allocateTimer(1);
    ESP32PWM::allocateTimer(2);
    ESP32PWM::allocateTimer(3);
    claw_servo_L.setPeriodHertz(50);
    claw_servo_L.attach(CLAW_SERVO_L, 500, 2400);
    claw_servo_R.setPeriodHertz(50);
    claw_servo_R.attach(CLAW_SERVO_R, 500, 2400);
    pitch_servo.setPeriodHertz(50);
    pitch_servo.attach(PITCH_SERVO, 500, 2400);
}

void moce_servo(Servo servo, int angle) {
    servo.write(angle);
}