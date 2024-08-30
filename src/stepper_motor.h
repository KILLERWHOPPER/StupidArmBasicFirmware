#ifndef STEPPER_MOTOR_H
#define STEPPER_MOTOR_H

#include "A4988.h"
#include "enums.h"

// #define DIR_rotate 18
// #define STEP_rotate 19

#define DIR_pitch 18
#define STEP_pitch 19

#define DIR_second_pitch 23
#define STEP_second_pitch 22

#define STEPS 200
#define RPM 200
#define ACCEL 1000
#define DECEL 1000

#define MICROSTEPS 16

// extern A4988 rotate_stepper;
extern A4988 pitch_stepper;
extern A4988 second_pitch_stepper;

void init_steppers();

void start_moving(A4988* stepper, Direction dir);

void stop_moving(A4988* stepper);

#endif