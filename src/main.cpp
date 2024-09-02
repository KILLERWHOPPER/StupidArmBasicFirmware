#include "network/wifi_server.h"
#include "stepper/stepper_motor.h"

#define USE_MULTCORE 1
void setup() {
  Serial.begin(9600);
  init_steppers();
  connect_wifi("KILLERWHOPPER_2.4", "84639188");
  start_server();
}

void loop() { delay(1000); }