#include <Arduino.h>

#include "networkTime.h"

#include "zIOTBP32/zsetupBP.h"// Required

#include "State.h"
#include "weather.h"
#include "setupMatrix.h"
#include "matrixBorders.h"
#include "modes.h"
#include "routes.h"

#define BTNPIN 15

State st;

// void checkBtn(){
//   int modeLength = 3;
//   String modeList[] = {
//     "clock",
//     "demo",
//     "say",
//     "dht"
//   };
//   int modeIndex;
//   for(int i=0; i<=modeLength;i++){
//     if(st.mode == modeList[i]){
//       modeIndex = i;
//     }
//   }
//   st.buttonState = digitalRead(15);
//   if(st.buttonState){
//     Serial.println("BTN CHANGE MODE");
//     modeIndex++;
//     if(modeIndex>modeLength){
//       modeIndex = 0;
//     }
//     if(modeIndex==0){
//       //Trigger clock
//       st.lastMin = -1;
//     }
//     st.mode = modeList[modeIndex];
//     runMode(matrix, st);
//     delay(500);
//   }
// }

void setup() {
    Serial.begin(115200);
    /*
    * void setupBP(const char *apName="ESP SETUP", const char *ssid=NULL, const char *pkey=NULL)
    */
    setupBP("WiFiClock", "HERSHEL", "meowmeow");// Required

    st.lenX = matrix.lenX()-1;
    st.lenY =  matrix.lenY()-1;
    //Setup DHT
    dht.begin();
    //Setup btn
    pinMode(BTNPIN, INPUT);

    server.on("/localTime", HTTP_GET, r_localTime);
    //server.on("/cmd", HTTP_GET, r_handleCommand);
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