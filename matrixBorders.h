#include <MatrixGL.h>
#include "State.h"

void clearBorder(MatrixGL &matrix, State &st){
  int points[] = {0,0, st.lenX,0, st.lenX,st.lenY, 0,st.lenY, 0,0};
  matrix.drawPath(points,10, false);
  //matrix.drawLine(0,0, 8,8, false);
}


void border(MatrixGL &matrix, State &st){
  clearBorder(matrix, st);
  if(st.sb > 300){
    matrix.drawLine(0,0, 0,st.lenY);
  }else if(st.sb > 200){
    matrix.drawLine(st.lenX,0, 0,0);
  }else if(st.sb > 100){
    matrix.drawLine(st.lenX,st.lenY, st.lenX,0);
  }else{
    matrix.drawLine(0,st.lenY, st.lenX,st.lenY);
  }
  st.sb+=10;
  if(st.sb>400){
    st.sb=0;
  }
}

void border2(MatrixGL &matrix, State &st)
{
  clearBorder(matrix, st);
  if(st.sb>31){
    //reverse
    int sx = st.sb - 31;
    matrix.drawPoint(0,sx/4);
    matrix.drawPoint(st.lenX,st.lenY-sx/4);
    matrix.drawPoint(sx,0);
    matrix.drawPoint(st.lenX-sx,st.lenY);
  }else{
    matrix.drawPoint(0,st.lenY-st.sb/4);
    matrix.drawPoint(st.lenX,st.sb/4);
    matrix.drawPoint(st.lenX-st.sb,0);
    matrix.drawPoint(st.sb,st.lenY);
  }
  st.sb++;
  if(st.sb>63){
    st.sb=0;
  }
}
void border3(MatrixGL &matrix, State &st){
  clearBorder(matrix, st);
  matrix.drawPoint(random(st.lenX),0);
  matrix.drawPoint(random(st.lenX),st.lenY);
  matrix.drawPoint(0,random(st.lenY));
  matrix.drawPoint(st.lenX,random(st.lenY));
  matrix.drawPoint(random(st.lenX),0);
  matrix.drawPoint(random(st.lenX),st.lenY);
  matrix.drawPoint(0,random(st.lenY));
  matrix.drawPoint(st.lenX,random(st.lenY));
  matrix.drawPoint(random(st.lenX),0);
  matrix.drawPoint(random(st.lenX),st.lenY);
  matrix.drawPoint(0,random(st.lenY));
  matrix.drawPoint(st.lenX,random(st.lenY));
}


void runBorder(MatrixGL &matrix, State &st){
  switch (st.modeB){
    case 0:
      break;
    case 1:
      border(matrix, st);
      break;
    case 2:
      border2(matrix, st);
      break;
    case 3:
      border3(matrix, st);
      break;
    default:
      break;
  }
}