/* 
Setup custom server routes
Note: These do not need to go here 
if you would rather put them somewhere else.
*/
#include <ESPAsyncWebServer.h>
// EXAMPLE ROUTES BELOW
// CAN BE REMOVED
#include "WiFi.h"

extern int timer;

void r_test(AsyncWebServerRequest *request){
  const char index_html[] PROGMEM = "<h1>HELLO POOP</h1>";
  request->send_P(200, "text/html", index_html);
}



void r_get(AsyncWebServerRequest *request){
  String message;
  if (request->hasParam("message")) {
      message = request->getParam("message")->value();
  }
  else if(request->hasParam("test")){
    message = "You passed the test!";
  }
  else {
      message = "No message sent";
  }
  Serial.println(message);
  request->send(200, "text/plain", "Hello, GET: " + message);
}

void r_uptime(AsyncWebServerRequest *request){
  String message = String(int((millis() - timer)/1000));
  request->send(200, "text/plain", message);
}

void r_post(AsyncWebServerRequest *request){
  String message;
  if (request->hasParam("message", true)) {
      message = request->getParam("message", true)->value();
  } else {
      message = "No message sent";
  }
  request->send(200, "text/plain", "Hello, POST: " + message);
}

void r_scan(AsyncWebServerRequest *request){
  int n = WiFi.scanNetworks();
  if(n== 0){
    request->send(200, "text/html", "NO NETWORKS FOUND");
  }else{
    String message;
    for (int i = 0; i < n; ++i) {
      // Print SSID and RSSI for each network found
      message += i + 1;
      message += ": ";
      message += WiFi.SSID(i);
      message += " (";
      message +=WiFi.RSSI(i);
      message +=")";
      message +=(WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*";
      message +='\r';      
    }
    request->send(200, "text/plain", message);
  }
}

void r_status(AsyncWebServerRequest *request){
  String message = "RESET REASON: "+String(esp_reset_reason()) +'\r';
  message += "HEAP SIZE: "+String(esp_get_free_heap_size()) +'\r';
  message += "MIN HEAP SIZE: "+String(esp_get_minimum_free_heap_size())+'\r';
  message += "UPTIME: "+String(int((millis() - timer)/1000));
  request->send(200, "text/plain", message);
}
