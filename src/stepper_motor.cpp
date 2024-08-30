#include "stepper_motor.h"

// A4988 rotate_stepper(STEPS, DIR_rotate, STEP_rotate);
A4988 pitch_stepper(STEPS, DIR_pitch, STEP_pitch);
A4988 second_pitch_stepper(STEPS, DIR_second_pitch, STEP_second_pitch);

void init_steppers() {
//   rotate_stepper.begin(RPM, MICROSTEPS);
  pitch_stepper.begin(RPM, MICROSTEPS);
  second_pitch_stepper.begin(RPM, MICROSTEPS);
//   rotate_stepper.setSpeedProfile(rotate_stepper.LINEAR_SPEED, ACCEL, DECEL);
  pitch_stepper.setSpeedProfile(pitch_stepper.LINEAR_SPEED, ACCEL, DECEL);
  second_pitch_stepper.setSpeedProfile(second_pitch_stepper.LINEAR_SPEED, ACCEL,
                                       DECEL);
  Serial.println("Steppers initialized");
};

void start_moving(A4988* stepper, Direction dir) {
  int preset_cycles = 100;
  if (dir == Right || dir == Down) {
    preset_cycles = -preset_cycles;
  }
  stepper->startMove(16 * preset_cycles);
};

void stop_moving(A4988* stepper) { stepper->startBrake(); };