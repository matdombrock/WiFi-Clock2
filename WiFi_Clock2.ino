#include <Arduino.h>

#include "networkTime.h"

#include "zIOTBP32/zsetupBP.h"// Required

#include "State.h"
#include "weather.h"
#include "setupMatrix.h"
#include "matrixBorders.h"
#include "modes.h"
#include "routes.h"

State st;


void setup() {
    Serial.begin(115200);
    /*
    * void setupBP(const char *apName="ESP SETUP", const char *ssid=NULL, const char *pkey=NULL)
    */
    setupBP("WiFiClock", "HERSHEL", "meowmeow");// Required

    st.lenX = matrix.lenX()-1;
    st.lenY =  matrix.lenY()-1;
    // Setup DHT
    dht.begin();
    // Setup Routes
    server.on("/localTime", HTTP_GET, r_localTime);
    server.on("/border", HTTP_GET, r_border);
    server.on("/mode", HTTP_GET, r_mode);
    server.on("/intensity", HTTP_GET, r_intensity);
    server.on("/say", HTTP_GET, r_say);
    server.on("/state", HTTP_GET, r_state);
    server.on("/syncTime", HTTP_GET, r_syncTime);
    server.on("/app", HTTP_GET, r_app);
    setupTime();
    getWeather();
}

void loop() {
  //
  loopBP();// Required
  //
  //checkBtn();
  runMode(matrix, st);
  runBorder(matrix, st);
  matrix.delayF();
}