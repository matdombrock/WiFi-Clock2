/* 
Handles the captive portal feature 
*/

#ifndef CaptiveRequestHandler_H
#define CaptiveRequestHandler_H
#include "Arduino.h"
#include <ESPAsyncWebServer.h>

class CaptiveRequestHandler : public AsyncWebHandler {
public:
  CaptiveRequestHandler() {}
  virtual ~CaptiveRequestHandler() {}

  bool canHandle(AsyncWebServerRequest *request){
    //request->addInterestingHeader("ANY");
    return true;
  }

  void handleRequest(AsyncWebServerRequest *request) {
    String message;
    message += "<form action=\"http://";
    message += WiFi.softAPIP().toString().c_str();
    message += "/setupWIFI\" method=\"POST\">";
    message += "<input type=\"text\" name=\"ssid\" value=\"HERSHEL\"><br>";
    message += "<input type=\"text\" name=\"pass\" value=\"meowmeow\"><br>";
    message += "<button>SETUP</button>";
    request->send(200, "text/html", message);    
  }
};
#endif