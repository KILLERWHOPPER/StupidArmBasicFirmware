#ifndef WIFI_SERVER_H
#define WIFI_SERVER_H

#include <Arduino.h>
#include <AsyncTCP.h>
#include <DNSServer.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <WiFi.h>
#include "ArduinoJson.h"
#include "stepper/stepper_motor.h"
#include "servo/servo_driver.h"

extern AsyncWebServer *server;

void connect_wifi(String ssid, String password);

void start_server();

#endif