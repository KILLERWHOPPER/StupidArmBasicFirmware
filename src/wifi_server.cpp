#include "wifi_server.h"

#include "stepper_motor.h"

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
  server->on("/test_connection", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "Connected!");
  });
//   server->on("/rotate/left", HTTP_GET, [](AsyncWebServerRequest *request) {
//     request->send(200, "text/plain", "Rotating left");
//     start_moving(&rotate_stepper, Left);
//   });
//   server->on("/rotate/right", HTTP_GET, [](AsyncWebServerRequest *request) {
//     request->send(200, "text/plain", "Rotating right");
//     start_moving(&rotate_stepper, Right);
//   });
//   server->on("/rotate/stop", HTTP_GET, [](AsyncWebServerRequest *request) {
//     request->send(200, "text/plain", "Stopping");
//     stop_moving(&rotate_stepper);
//   });
  server->on("/pitch/up", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "Pitching up");
    Serial.println("Pitching up");
    start_moving(&pitch_stepper, Up);
  });
  server->on("/pitch/down", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "Pitching down");
    Serial.println("Pitching down");
    start_moving(&pitch_stepper, Down);
  });
  server->on("/pitch/stop", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "Stopping");
    Serial.println("Stopping");
    stop_moving(&pitch_stepper);
  });
  server->on("/second_pitch/up", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "Second pitch up");
    Serial.println("Second pitch up");
    start_moving(&second_pitch_stepper, Up);
  });
  server->on("/second_pitch/down", HTTP_GET,
             [](AsyncWebServerRequest *request) {
               request->send(200, "text/plain", "Second pitch down");
               Serial.println("Second pitch down");
               start_moving(&second_pitch_stepper, Down);
             });
  server->on("/second_pitch/stop", HTTP_GET,
             [](AsyncWebServerRequest *request) {
               request->send(200, "text/plain", "Stopping");
               Serial.println("Stopping");
               stop_moving(&second_pitch_stepper);
             });
  server->begin();
}
