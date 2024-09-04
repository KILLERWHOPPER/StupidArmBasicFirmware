#include "network/wifi_server.h"
#include "stepper/stepper_motor.h"
#include "servo/servo_driver.h"

#define USE_MULTCORE 1
void setup() {
  Serial.begin(9600);
  connect_wifi("KILLERWHOPPER_2.4", "84639188");
  init_steppers();
  init_servos();
  start_server();
}

void loop() { delay(1000); }