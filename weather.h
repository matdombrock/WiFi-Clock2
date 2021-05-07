#include "zIOTBP32/zhttpGet.h"

#include "State.h"

//extern void HTTPGET(String url, int &code, String &pay);
extern State st;

void getWeather(){
    int httpCode;
    String payload;
    //https://github.com/chubin/wttr.in
    //http://wttr.in/98367?format=%C,%p,%t,%f,%w
    HTTPGET("http://wttr.in/?format=%C",httpCode, payload);
    Serial.println(httpCode);
    Serial.println(payload);
    st.weatherCondition = payload;
}