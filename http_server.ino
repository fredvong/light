#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "html.h"

const char* PARAM_INPUT = "value";

// Replaces placeholder with button section in your web page
String processor(const String& var){
  //Serial.println(var);
  if (var == "LEDSLIDERVALUE"){
    return ledSliderValue;
  }
  if (var == "FANSLIDERVALUE"){
    return fanSliderValue;
  }
  if (var == "FANSPEED") {
    return fanSpeed;
  }
  return String();
}

// Replaces placeholder with button section in your web page
String configProcessor(const String& var){
  //Serial.println(var);
  if (var == "VERSION"){
    
    return String(globalConfig.majorVersion) + "." + String(globalConfig.minorVersion) + "." + String(globalConfig.revision);
  }
  if (var == "FANSPEED") {
    return fanSpeed;
  }
  return String();
}


void runAP() {
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);  
}

void runWebServer() {
    // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });

  // Send a GET request to <ESP_IP>/slider?value=<inputMessage>
  server.on("/led", HTTP_PUT, [] (AsyncWebServerRequest *request) {
    String inputMessage;
    // in order to have this work, the client should set the "Content-Type"
    // to "application/x-www-form-urlencoded"
    if (request->hasParam(PARAM_INPUT, true)) {
      inputMessage = request->getParam(PARAM_INPUT, true)->value();
      ledSliderValue = inputMessage;
      ledcWrite(ledChannel, inputMessage.toInt());
    }
    else {
      inputMessage = "No message sent";
    }
    Serial.println("LED: "+inputMessage);
    request->send(200, "text/plain", "OK");
  });

  // Send a GET request to <ESP_IP>/slider?value=<inputMessage>
  server.on("/fan", HTTP_PUT, [] (AsyncWebServerRequest *request) {
    String inputMessage;
    // in order to have this work, the client should set the "Content-Type"
    // to "application/x-www-form-urlencoded"
    if (request->hasParam(PARAM_INPUT, true)) {
      inputMessage = request->getParam(PARAM_INPUT, true)->value();
      fanSliderValue = inputMessage;
      setFan(fanSliderValue);
    }
    else {
      inputMessage = "No message sent";
    }
    Serial.println("Fan: "+inputMessage);
    request->send(200, "text/plain", "OK");
  });
  server.on("/fanspeed", HTTP_GET, [] (AsyncWebServerRequest *request) {
    request->send(200, "text/plain", fanSpeed);
  });

  server.on("/config", HTTP_GET, [] (AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", config_html, configProcessor);
  });

  // Start server
  server.begin();
}

void runWebServerWithAP( void * parameter) {
  configLED();
  runAP();
  runWebServer();
}
