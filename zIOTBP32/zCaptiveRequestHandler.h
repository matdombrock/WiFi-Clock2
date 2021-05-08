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
    message += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
    if(WiFi.localIP()){
      message += "WiFi is connected.<br>";
      message += "Rejoin your regular WiFi and go to:<br><h1>";
      message += WiFi.localIP().toString().c_str();
      message += "/app</h1>";
      message += "<hr>";
    }
    message += "<h1>SETUP WIFI:</h1>";
    message += "<form action=\"http://";
    message += WiFi.softAPIP().toString().c_str();
    message += "/setupWIFI\" method=\"POST\">";
    message += "<input type=\"text\" name=\"ssid\" value=\"HERSHEL\" placeholder=\"ssid\"><br>";
    message += "<input type=\"text\" name=\"pass\" value=\"meowmeow\" placeholder=\"passkey\"><br>";
    message += "<button>CONNECT</button>";
    message += 
    "<style>"
    "body{background:rgb(33,33,33); color:rgb(233,233,233);}"
    "input, button{font-size:2rem;width:100%;max-width:800px}"
    "</style>"
    ;
    request->send(200, "text/html", message);    
  }
};
#endif