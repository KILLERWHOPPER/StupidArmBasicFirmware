#include "stepper_motor.h"

TaskHandle_t TASK_Handle_single = NULL;
TaskHandle_t TASK_Handle_combined = NULL;

A4988 rotate_stepper(STEPS, DIR_rotate, STEP_rotate);
A4988 pitch_stepper(STEPS, DIR_pitch, STEP_pitch);
A4988 second_pitch_stepper(STEPS, DIR_second_pitch, STEP_second_pitch);

SyncDriver controller(rotate_stepper, pitch_stepper, second_pitch_stepper);

void init_steppers() {
  rotate_stepper.begin(RPM, MICROSTEPS);
  pitch_stepper.begin(RPM, MICROSTEPS);
  second_pitch_stepper.begin(RPM, MICROSTEPS);
  rotate_stepper.setSpeedProfile(rotate_stepper.LINEAR_SPEED, ACCEL, DECEL);
  pitch_stepper.setSpeedProfile(pitch_stepper.LINEAR_SPEED, ACCEL, DECEL);
  second_pitch_stepper.setSpeedProfile(second_pitch_stepper.LINEAR_SPEED, ACCEL,
                                       DECEL);
  Serial.println("Steppers initialized");
};


// void task_move_single(void* parameter) {
//   moving_info* info = (moving_info*)parameter;
//   A4988 stepper = info->stepper;
// //   int preset_cycles = info->preset_cycles;
// //   stepper.move(preset_cycles);
//   while(stepper.nextAction())
//   Serial.println("Single motor move finished");
//   vTaskDelete(NULL);
// }

// void task_move_combined(void* parameter) {
//   int* numArray;
//   numArray = (int*)parameter;
//   controller.move(numArray[0], numArray[1]);
//   vTaskDelete(NULL);
// }

void start_moving(A4988 stepper, float angle) {
  // moving_info moving_info{stepper, preset_cycles * 16};
  stepper.move((angle / 1.8) * MICROSTEPS);
  Serial.printf("Move %f degrees finished\n", angle);
};

void stop_moving(A4988 stepper) { stepper.startBrake(); };

void combined_moving(float rotate_angle, float pitch_angle,
                     float second_pitch_angle) {
  controller.move((rotate_angle / 1.8) * MICROSTEPS,
                  (pitch_angle / 1.8) * MICROSTEPS,
                  (second_pitch_angle / 1.8) * MICROSTEPS);
  Serial.printf(
      "Combined motor move finished\n rotate: %2f, pitch: %2f, second_pitch: "
      "%2f\n",
      rotate_angle, pitch_angle, second_pitch_angle);
}