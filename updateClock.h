#include <TimeLib.h>//https://github.com/PaulStoffregen/Time
#include <WiFi.h>
#include "State.h"

void updateClock(State &st){
  int thour = hour();
  int tmin = minute();
  int h1 = 0;
  int h2 = 0;
  int m1 = 0;
  int m2 = 0;
  // 24hr time
  if(thour>9){
    h1 = 1;
    h2 = thour - 10;
  }else{
    h2 = thour;
  }
  if(thour>19){
    h1 = 2;
    h2 = thour - 20;
  }
  if(tmin > 9){
    m1 = 1;
    m2 = tmin - 10;
  }else{
    m2 = tmin;
  }
  if(tmin > 19){
    m1 = 2;
    m2 = tmin - 20;
  }
  if(tmin > 29){
    m1 = 3;
    m2 = tmin - 30;
  }
  if(tmin > 39){
    m1 = 4;
    m2 = tmin - 40;
  }
  if(tmin > 49){
    m1 = 5;
    m2 = tmin - 50;
  }
  st.localTime[0] = h1;
  st.localTime[1] = h2;
  st.localTime[2] = m1;
  st.localTime[3] = m2;
}