#include <Arduino.h>

#include "networkTime.h"

#include "zIOTBP32/zsetupBP.h"// Required

#include "State.h"
#include "weather.h"
#include "routes.h"

#include "setupMatrix.h"
#include "matrixBorders.h"
#include "modes.h"
#include "updateClock.h"

#define BTNPIN 15

State st;

void checkBtn(){
  st.buttonState = digitalRead(15);
  if(st.buttonState){
    Serial.println("BTN CHANGE MODE");
    st.mode++;
    if(st.mode>3){
      st.mode = 0;
    }
    if(st.mode==0){
      //Trigger clock
      st.lastMin = -1;
    }
    runMode(matrix, st);
    delay(500);
  }
}

void setup() {
    Serial.begin(115200);
    /*
    * void setupBP(const char *apName="ESP SETUP", const char *ssid=NULL, const char *pkey=NULL)
    */
    setupBP("ESP SETUP", "HERSHEL", "meowmeow");// Required
    // EXAMPLE ROUTES
    // Check system uptime
    server.on("/uptime", HTTP_GET, r_uptime);
    // Test reading content from PROGMEM
    server.on("/test", HTTP_GET, r_test);
    // Scan local WIFI networks
    server.on("/scan", HTTP_GET, r_scan);
    // Get system status info
    server.on("/status", HTTP_GET, r_status);
    // Send a GET request to <IP>/get?message=<message>
    server.on("/get", HTTP_GET, r_get);
    // Send a POST request to <IP>/post with a form field message set to <message>
    server.on("/post", HTTP_POST, r_post);
    //your other setup stuff...

    st.lenX = matrix.lenX()-1;
    st.lenY =  matrix.lenY()-1;
    //Setup DHT
    dht.begin();
    //Setup btn
    pinMode(BTNPIN, INPUT);

    server.on("/localTime", HTTP_GET, r_localTime);
    
    setupTime();
    getWeather();
}

void loop() {
  //
  loopBP();// Required
  //
  checkBtn();
  updateClock(st);
  runMode(matrix, st);
  runBorder(matrix, st);
  matrix.delayF();
}