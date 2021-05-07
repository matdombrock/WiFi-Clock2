/* 
Contains the standard routes for the application.
Note: You probably don't want to change this file.
*/

#include <ESPAsyncWebServer.h>
#include "WiFi.h"

extern bool setupWIFI(const char *ssid, const char *password);

void r_root(AsyncWebServerRequest *request){
  request->send(200, "text/plain", "Hello, worlds");
}

void r_setupWIFI(AsyncWebServerRequest *request){
  Serial.println("ATTEMPT NEW WIFI SETUP");
  int args = request->args();
  for(int i=0;i<args;i++){
    Serial.printf("ARG[%s]: %s\n", request->argName(i).c_str(), request->arg(i).c_str());
  }
  // Use hasArg, required here
  // No idea why
  if (request->hasArg("ssid") && request->hasArg("pass")) {
    const char* nssid = request->arg("ssid").c_str();
    const char* npass = request->arg("pass").c_str();
    Serial.println("NEW CREDS:");
    Serial.println(nssid);
    Serial.println(npass);
    bool running = setupWIFI(nssid, npass);
    if(running){
      String message = "SERVER STARTED: ";
      message += WiFi.softAPIP().toString().c_str();
      message += "\r You can now disconnect and access the server from your main network.";
      request->send(200, "text/plain", message);
    }else{
      request->send(200, "text/plain", "CANT CONNECT");
    }
  }
  request->send(200, "text/plain", "MISSING ARGS");
}

void r_notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}

void setupStandardRoutes(AsyncWebServer &server){
  server.on("/", HTTP_GET, r_root);
  server.on("/setupWIFI", HTTP_POST, r_setupWIFI);
  server.onNotFound(r_notFound);
}


