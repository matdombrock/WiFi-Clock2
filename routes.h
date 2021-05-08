#include <ESPAsyncWebServer.h>
#include <TimeLib.h>//https://github.com/PaulStoffregen/Time

#include "WiFi.h"
#include <MatrixGL.h>

extern State st;
extern MatrixGL matrix;

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
		if(cmd == "clock"){
			st.lastMin = -1;//Trigger clock
		}
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
	if(!request->hasParam("hour")){
		request->send(200, "text/plain", "Missing Hour");
		return;
	}
	if(!request->hasParam("minute")){
		request->send(200, "text/plain", "Missing Minute");
		return;
	}
	if(!request->hasParam("second")){
		request->send(200, "text/plain", "Missing Second");
		return;
	}
	matrix.drawString("SYNC  ",6);
	String hourVal = request->getParam("hour")->value();
	String minVal = request->getParam("minute")->value();
	String secVal = request->getParam("second")->value();
	// setTime(hr,min,sec,day,mnth,yr);
	setTime(hourVal.toInt(),minVal.toInt(),secVal.toInt(),1,1,2021);
	String message;
	message += hour();
	message += ".";
	message += minute();
	message += ".";
	message += second();
	request->send(200, "text/plain", message);
	st.lastMin = -1;// Refresh clock
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

void r_app(AsyncWebServerRequest *request){
	// Remove all comments
	// Make deviceURL an empty string
	// Minify to one line https://www.willpeavy.com/tools/minifier/
	// Replace all quotes with \" (escape)
  const char index_html[] PROGMEM = 
	"<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><div class=\"header\"> <h1>WIFI CLOCK<sup>2</sup></h1> <div class=\"status\" id=\"loading\"></div></div><br><br><br><br><div class=\"app-wrap\"> <select id=\"mode\"> <option value=\"clock\">CLOCK</option> <option value=\"demo\">DEMO</option> <option value=\"dht\">DHT</option> <option value=\"say\">SAY</option> </select> <div class=\"btn\" onclick=\"setMode()\">SET MODE</div><br><br><select id=\"border\"> <option value=\"0\">NONE</option> <option value=\"1\">LINES</option> <option value=\"2\">PHOTONS</option> <option value=\"3\">NOISE</option> </select> <div class=\"btn\" onclick=\"setBorder()\">SET BORDER</div><br><br><input type=\"text\" id=\"storedText\"> <div class=\"btn\" onclick=\"setText()\">SET TEXT</div><br><br><input type=\"range\" class=\"full\" id=\"brightness\" min=\"0\" max=\"15\" value=\"1\"> <br><div class=\"btn full\" onclick=\"setBrightness()\">SET BRIGHTNESS</div><br><br><div class=\"btn\" onclick=\"syncTime()\">SYNC TIME</div><div class=\"btn\" onclick=\"getState()\">SYNC STATE</div><br><br><div class=\"localTime\" id=\"localTime\">...</div><br><br><div class=\"footer\"> GPL <a href=\"https://matdombrock.com\">MATHIEU DOMBROCK</a> 2021 <a href=\"https://github.com\">GITHUB</a> </div></div><script>const deviceURL=''; const loading=document.getElementById('loading'); const mode=document.getElementById('mode'); const border=document.getElementById('border'); const storedText=document.getElementById('storedText'); const brightness=document.getElementById('brightness'); const localTime=document.getElementById('localTime'); let state; getState(); setInterval(()=>{const d=new Date(); localTime.innerText=d.toLocaleString().split(',')[1];}, 500); function updateUI(){mode.value=state.mode; border.value=state.border; storedText.value=state.storedText; brightness.value=state.intensity;}function getState(){const xhttp=new XMLHttpRequest(); xhttp.onreadystatechange=function(){if (this.readyState==4 && this.status==200){state=JSON.parse(xhttp.responseText); console.log('Synced State'); console.log(JSON.stringify(state, null, 2)); updateUI(); endLoad();}}; xhttp.open(\"GET\", deviceURL + \"/state\", true); xhttp.send(); startLoad();}function setState(cmd, val){const xhttp=new XMLHttpRequest(); xhttp.onreadystatechange=function(){if (this.readyState==4 && this.status==200){const resp=xhttp.responseText; console.log(resp); endLoad();}}; xhttp.open(\"GET\", deviceURL + '/'+cmd+'?set='+encodeURIComponent(val), true); xhttp.send(); startLoad();}function startLoad(){loading.classList.add(\"loading\");}function endLoad(){setTimeout(function(){loading.classList.remove(\"loading\");},300);}function setMode(){setState('mode', mode.value);}function setBorder(){setState('border', border.value);}function setText(){setState('say', storedText.value.toUpperCase());}function setBrightness(){setState('intensity', brightness.value);}function syncTime(){const xhttp=new XMLHttpRequest(); xhttp.onreadystatechange=function(){if (this.readyState==4 && this.status==200){const resp=xhttp.responseText; console.log(resp); endLoad();}}; const d=new Date(); const hour=d.getHours(); const minute=d.getHours(); const second=d.getSeconds(); xhttp.open(\"GET\", deviceURL + '/syncTime?hour='+hour+'&minute='+minute+'&second='+second, true); xhttp.send(); startLoad();}</script><style>:root{--fsize: 3vh; --iwidth: 45%; --iwidthFull: 92%; --accent:rgb(185, 118, 11); --accent2:#0075fb; --headerHeight:4.3rem;}body{font-family: Tahoma, sans-serif; padding:0; margin:0; background:rgb(33, 33, 33); color:rgb(228, 228, 228); text-align:center; font-size:var(--fisize);}a{color:white;}.header{text-align: left; background:rgb(114, 114, 114);}h1{padding:0; margin:0; font-size:3rem; height:var(--headerHeight); line-height:3rem; display:inline-block;}.status{width:10vw; background:var(--accent2); float:right; height:var(--headerHeight); text-align:right; padding-right:2rem; line-height: var(--headerHeight); clip-path: polygon(20% 0, 100% 0, 100% 100%, 0% 100%);}.app-wrap{max-width:50vw; margin:0 auto;}@media only screen and (max-width: 1000px){.app-wrap{max-width:100vw; margin:0 auto;}}select, input{padding:0.75rem; font-size:var(--fisize); min-width:var(--iwidth); max-width:var(--iwidth); width:var(--iwidth);}.btn{display:inline-block; background:rgb(75, 75, 75); padding-top:1rem; padding-bottom:1rem; cursor: pointer; min-width:var(--iwidth); max-width:var(--iwidth); width:var(--iwidth); transition: all 0.2s;}.btn:hover{background:var(--accent)}.full{min-width:var(--iwidthFull); max-width:var(--iwidthFull); width:var(--iwidthFull);}.loading{background: var(--accent);}.localTime{}.footer, .footer a{color:grey;}</style>"
	;
  request->send_P(200, "text/html", index_html);
}
