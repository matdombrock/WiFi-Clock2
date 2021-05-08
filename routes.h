#include <ESPAsyncWebServer.h>
#include <TimeLib.h>//https://github.com/PaulStoffregen/Time

#include "WiFi.h"
#include <MatrixGL.h>

extern State st;
extern MatrixGL matrix;
extern void setupTime();

int startTime = millis();

void r_localTime(AsyncWebServerRequest *request){
	String message;
	message += hour();
	message += ":";
	message += minute();
	message += ":";
	message += second();
	request->send(200, "text/plain", message);
}

void r_border(AsyncWebServerRequest *request){
	String message;
	if(request->hasParam("set")){
		String cmd = request->getParam("set")->value();
		if(cmd == "none"){
			st.modeB = 0;
		}
		st.modeB = cmd.toInt();
		message = "Set: "+cmd;
	}else{
		message = st.modeB;
	}
	request->send(200, "text/plain", message);
}

void r_mode(AsyncWebServerRequest *request){
	String message;
	if(request->hasParam("set")){
		String cmd = request->getParam("set")->value();
		st.mode = cmd;
		message = "Set: "+cmd;
	}else{
		message = st.mode;
	}
	request->send(200, "text/plain", message);
}

void r_intensity(AsyncWebServerRequest *request){
	String message;
	if(request->hasParam("set")){
		String cmd = request->getParam("set")->value();
		st.intensity = cmd.toInt();
		if(st.intensity>15){
			st.intensity=15;
		}
		if(st.intensity<0){
			st.intensity=0;
		}
		message = "Set: "+cmd;
		matrix.setIntensity(st.intensity);
	}else{
		message = st.intensity;
	}
	request->send(200, "text/plain", message);
}

void r_say(AsyncWebServerRequest *request){
	String message;
	if(request->hasParam("set")){
		String cmd = request->getParam("set")->value();
		st.storedText = cmd;
		message = "Set: "+st.storedText;
	}else{
		message = st.storedText;
	}
	st.mode = "say";
	request->send(200, "text/plain", message);
}

void r_syncTime(AsyncWebServerRequest *request){
	setupTime();
	String message;
	message += hour();
	message += ".";
	message += minute();
	message += ".";
	message += second();
	request->send(200, "text/plain", message);
}

void r_state(AsyncWebServerRequest *request){
	String message = "{";
	message += "\"mode\":\""+st.mode+"\",";
	message += "\"border\":\""+String(st.modeB)+"\",";
	message += "\"intensity\":\""+String(st.intensity)+"\",";
	message += "\"storedText\":\""+st.storedText+"\",";
	message += "\"weatherCondition\":\""+st.weatherCondition+"\",";
	message += "\"lastHum\":\""+String(st.lastHum)+"\",";
	message += "\"lastTemp\":\""+String(st.lastTemp)+"\",";
	message += "\"hour\":\""+String(hour())+"\",";
	message += "\"minute\":\""+String(minute())+"\",";
	message += "\"second\":\""+String(second())+"\",";
	message += "\"isPM\":\""+String(isPM())+"\",";
	message += "\"sys_heapSize\":\""+String(esp_get_free_heap_size())+"\",";
	message += "\"sys_minHeapSize\":\""+String(esp_get_minimum_free_heap_size())+"\",";
	message += "\"sys_uptime\":\""+String(int((millis() - startTime)/1000))+"\"";
	message += "}";
	request->send(200, "text/json", message);
}

// void r_handleCommand(AsyncWebServerRequest *request){
// 	String message;
// 	if(request->hasParam("mode")){
// 		String cmd = request->getParam("mode")->value();
// 		if(cmd == "clock"){
// 			Serial.println("MODE: CLOCK");
//       st.mode = "clock";
//       // Reset lastMin so clock updates instantly
//       st.lastMin = -1;
// 		}
// 		else if(cmd == "demo"){
// 			Serial.println("MODE: DEMO");
//       st.mode = "demo";
// 		}
// 		else if(cmd == "dht"){
// 			Serial.println("MODE: DHT");
//       st.mode = "dht";
// 		}
// 	}
// 	if(request->hasParam("intensity")){
// 		String cmd = request->getParam("intensity")->value();
// 		matrix.setIntensity(cmd.toInt());
// 	}
// 	if(request->hasParam("say")){
// 		String cmd = request->getParam("say")->value();
// 		st.storedText = cmd;
//     Serial.print("Set saved text to:");
//     Serial.println(st.storedText);
//     st.mode = 2;
// 	}
// 	if(request->hasParam("border")){
// 		String cmd = request->getParam("border")->value();
// 		if(cmd == "none"){
// 			st.modeB = 0;
// 		}
// 		st.modeB = cmd.toInt();
// 	}
// 	message += "ok: ";
// 	message += st.mode;
// 	Serial.println(st.mode);
// 	request->send(200, "text/plain", message);
// }