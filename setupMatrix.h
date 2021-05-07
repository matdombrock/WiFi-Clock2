/*
* SETUP LED MATRIX
*/
#include <MatrixGL.h>
#define CLK_PIN   18  // or SCK//13
#define DATA_PIN  23  // or MOSI//11
#define CS_PIN 5 // or SS//10
#define MAX_DEVICES 4
#define LENGTHX 32
#define LENGTHY 8
MatrixGL matrix(CLK_PIN,DATA_PIN,CS_PIN,MAX_DEVICES);
