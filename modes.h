#include <MatrixGL.h>
#include "State.h"
#include "zDHT.h"

void println(MatrixGL &matrix, String str){
  char buf[6];
  str.toCharArray(buf, 7);
  matrix.lock();
  matrix.clear();
  for(int i = 0; i<6; i++){
    if(buf[i]==NULL){
      buf[i] = ' ';
    }
    matrix.drawChar(buf[i],1+(i*5),1);  
  }
  matrix.unlock();
}

void say(MatrixGL matrix, State st){
  println(matrix, st.storedText);
}
void drawDHT(MatrixGL matrix, State st){
  updateDHT(st);
  String DHTString = String(st.lastTemp).substring(0,2) + "C" + String(st.lastHum).substring(0,2) + "H";
  println(matrix, DHTString);
}

void demoRandomNoise(MatrixGL &matrix){
  // Generate random noise
  int X = matrix.lenX();
  int Y = matrix.lenY();
  matrix.lock();
  matrix.clear();
  for(int i = 0; i<(X*Y); i++){
    matrix.drawPoint(random(X), random(Y)); 
  }
  matrix.unlock();
  matrix.delayF();
}

void drawClock(MatrixGL &matrix, State &st){
  // Skip if time has not changed
  if(st.localTime[3] != st.lastMin){
    matrix.lock();
    matrix.clear();
    matrix.drawNum(st.localTime[0],5,1);
    matrix.drawNum(st.localTime[1],10,1);
    matrix.drawChar(':',14,1);
    matrix.drawNum(st.localTime[2],18,1);
    matrix.drawNum(st.localTime[3],23,1);  
    matrix.unlock(); 
  }
  st.lastMin = st.localTime[3];
}

/*
* RUN CURRENT MODE
*/
void runMode(MatrixGL &matrix, State &st){
   switch(st.mode){
    case 0:
      drawClock(matrix, st);
      break;
    case 1:
      demoRandomNoise(matrix);
      break;
    case 2:
      say(matrix, st);
      break;
    case 3:
      drawDHT(matrix, st);
      break;
    default:
      drawClock(matrix, st);
      break;
   }
}