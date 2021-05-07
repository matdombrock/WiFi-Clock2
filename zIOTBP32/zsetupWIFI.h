/* 
Handles setting up the WiFi connection
Note: You probably don't want to change this file.
*/

#include <WiFi.h>
bool setupWIFI(const char *ssid, const char *password){
  Serial.println("SETUP SERVER:");
  Serial.println(ssid);
  Serial.println(password);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
      Serial.printf("WiFi Failed!\n");
      return false;
  }else{
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    return true;
  }
}