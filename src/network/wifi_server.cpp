#include "wifi_server.h"

AsyncWebServer *server = new AsyncWebServer(80);

void connect_wifi(String ssid, String password) {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid.c_str(), password.c_str());
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}

void start_server() {
  server->on("/test_connection", HTTP_POST, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "Connected!");
  });
  server->on("/rotate", HTTP_POST, [](AsyncWebServerRequest *request) {
    float angle = request->getParam("angle")->value().toFloat() * 3.33;
    float rpm = request->getParam("rpm")->value().toFloat();
    rotate_stepper.setRPM(rpm);
    Serial.printf("Rotating %f degrees\n", angle);
    JsonDocument doc;
    doc["on_going"] = "rotate";
    doc["angle"] = angle;
    doc["rpm"] = rpm;
    request->send(200, "application/json", doc.as<String>());
    start_moving(rotate_stepper, angle);
    pitch_stepper.setRPM(RPM);
  });

  server->on("/pitch", HTTP_POST, [](AsyncWebServerRequest *request) {
    float angle = request->getParam("angle")->value().toFloat() * 9;
    float rpm = request->getParam("rpm")->value().toFloat();
    pitch_stepper.setRPM(rpm);
    Serial.printf("Pitching %f degrees\n", angle);
    JsonDocument doc;
    doc["on_going"] = "pitch";
    doc["angle"] = angle;
    doc["rpm"] = rpm;
    request->send(200, "application/json", doc.as<String>());
    start_moving(pitch_stepper, angle);
    pitch_stepper.setRPM(RPM);
  });

  server->on("/second_pitch", HTTP_POST, [](AsyncWebServerRequest *request) {
    float angle = request->getParam("angle")->value().toFloat() * 9;
    float rpm = request->getParam("rpm")->value().toFloat();
    second_pitch_stepper.setRPM(rpm);
    Serial.printf("Rotating %f degrees\n", angle);
    JsonDocument doc;
    doc["on_going"] = "second_pitch";
    doc["angle"] = angle;
    doc["rpm"] = rpm;
    request->send(200, "application/json", doc.as<String>());
    start_moving(second_pitch_stepper, angle);
    second_pitch_stepper.setRPM(RPM);
  });

  server->on("/combined", HTTP_POST, [](AsyncWebServerRequest *request) {
    float rotate = request->getParam("rotate")->value().toFloat() * 3.33;
    int rotate_rpm = request->getParam("rotate_rpm")->value().toInt();
    float pitch = request->getParam("pitch")->value().toFloat() * 9;
    int pitch_rpm = request->getParam("pitch_rpm")->value().toInt();
    float second_pitch = request->getParam("second_pitch")->value().toFloat();
    int second_pitch_rpm =
        request->getParam("second_pitch_rpm")->value().toInt() * 9;
    rotate_stepper.setRPM(rotate_rpm);
    pitch_stepper.setRPM(pitch_rpm);
    second_pitch_stepper.setRPM(second_pitch_rpm);
    Serial.printf("Combined moving:\nrotate: %f, pitch: %f, second_pitch: %f\n",
                  rotate, pitch, second_pitch);
    JsonDocument doc;
    doc["on_going"] = "combined_moving";
    doc["rotate"]["angle"] = rotate;
    doc["rotate"]["rpm"] = rotate_rpm;
    doc["pitch"]["angle"] = pitch;
    doc["pitch"]["rpm"] = pitch_rpm;
    doc["second_pitch"]["angle"] = second_pitch;
    doc["second_pitch"]["rpm"] = second_pitch_rpm;
    request->send(200, "application/json", doc.as<String>());
    combined_moving(rotate, pitch, second_pitch);
    rotate_stepper.setRPM(RPM);
    pitch_stepper.setRPM(RPM);
    second_pitch_stepper.setRPM(RPM);
  });

  server->on("/head_pitch", HTTP_POST, [](AsyncWebServerRequest *request) {
    int angle = request->getParam("angle")->value().toInt();
    pitch_servo.write(angle);
    Serial.printf("Servo angle: %d\n", angle);
    JsonDocument doc;
    doc["on_going"] = "servo";
    doc["angle"] = angle;
    request->send(200, "application/json", doc.as<String>());
  });

  server->on("/head_claw", HTTP_POST, [](AsyncWebServerRequest *request) {
    int angle = request->getParam("angle")->value().toInt();
    claw_servo.write(angle);
    Serial.printf("Servo angle: %d\n", angle);
    JsonDocument doc;
    doc["on_going"] = "servo";
    doc["angle"] = angle;
    request->send(200, "application/json", doc.as<String>());
  });
  server->begin();
}
