#include <ESPAsyncWebServer.h>
#include <TimeLib.h>//https://github.com/PaulStoffregen/Time

#include "WiFi.h"

extern State st;

void r_localTime(AsyncWebServerRequest *request){
	String message;
	message += hour();
	message += ":";
	message += minute();
	message += ":";
	message += second();
	request->send(200, "text/plain", message);
}

void r_handleCommand(AsyncWebServerRequest *request){
	String message;
	if(request->hasParam("mode")){
		String cmd = request->getParam("mode")->value();
		if(cmd == "clock"){
			
		}
	}
}