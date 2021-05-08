#ifndef State_H
#define State_H
class State {
  public:
    float lastHum = 0;
    float lastTemp = 0;
    String mode = "clock"; // mode
    int modeB = 2; // border mode
    int si = 0;
    int sb = 0; // global border iterator
    int localTime[4];
    int lastMin =-1;
    int intensity = 1;
    String storedText = "ABC123";
    int lenX = 8;
    int lenY = 8;
    bool buttonState = 0;
    String weatherCondition = "None";
};
#endif