#ifndef State_H
#define State_H
class State {
  public:
    float lastHum = 0;
    float lastTemp = 0;
    int mode = 0; // mode
    int modeB = 0; // border mode
    int si = 0;
    int sb = 0; // global border iterator
    int localTime[4];
    int lastMin =-1;
    String storedText = "ABC123";
    int lenX = 8;
    int lenY = 8;
    bool buttonState = 0;
    String weatherCondition = "None";
};
#endif