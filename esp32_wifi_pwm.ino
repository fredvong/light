#include <ESPAsyncWebServer.h>
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"

/* Put your SSID & Password */
const char* ssid = "ESP32";  // Enter SSID here
const char* password = "12345678";  //Enter Password here


/* Put IP Address details */
IPAddress local_ip(192,168,10,1);
IPAddress gateway(192,168,10,1);
IPAddress subnet(255,255,255,0);

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// Timer related variables

int id = 1;
byte myCount;
//TaskHandle_t pulseCountTask;
//TaskHandle_t webServerTask;


void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);

  initFanPin();

  configHardware();
  runAP();
  runWebServer();
  
//    xTaskCreatePinnedToCore(
//      runWebServerWithAP, /* Function to implement the task */
//      "webServer", /* Name of the task */
//      10000,  /* Stack size in words */
//      NULL,  /* Task input parameter */
//      0,  /* Priority of the task */
//      &pulseCountTask,  /* Task handle. */
//      1); /* Core where the task should run */
//
//  xTaskCreatePinnedToCore(
//      countPulse, /* Function to implement the task */
//      "pulseCount", /* Name of the task */
//      10000,  /* Stack size in words */
//      NULL,  /* Task input parameter */
//      0,  /* Priority of the task */
//      &pulseCountTask,  /* Task handle. */
//      1); /* Core where the task should run */
}
  
void loop() {
  countPulse();
}
