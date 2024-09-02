#ifndef STEPPER_MOTOR_H
#define STEPPER_MOTOR_H

#include "A4988.h"
#include "MultiDriver.h"
#include "SyncDriver.h"
#include "util/enums.h"

#define DIR_rotate 25
#define STEP_rotate 26

#define DIR_pitch 18
#define STEP_pitch 19

#define DIR_second_pitch 32
#define STEP_second_pitch 33

#define STEPS 200
#define RPM 300
#define ACCEL 1000
#define DECEL 1000

#define MICROSTEPS 16

extern TaskHandle_t TASK_Handle_single;
extern TaskHandle_t TASK_Handle_combined;
extern A4988 rotate_stepper;
extern A4988 pitch_stepper;
extern A4988 second_pitch_stepper;

extern SyncDriver controller;

void init_steppers();

void start_moving(A4988 stepper, float angle);

void stop_moving(A4988 stepper);

void combined_moving(float rotate_angle, float pitch_angle, float second_pitch_angle);

#endif