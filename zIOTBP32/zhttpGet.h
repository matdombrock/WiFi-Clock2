/* 
Handles outgoing HTTP GET requests
Note: You probably don't want to change this file.
*/
#ifndef HTTPGET_H
#define HTTPGET_H
#include <HTTPClient.h>

void HTTPGET(String url, int &code, String &pay){
  HTTPClient http;
 
  http.begin(url); //Specify the URL
  int httpCode = http.GET();                                        //Make the request

  if (httpCode > 0) { //Check for the returning code
    String payload = http.getString();
    code = httpCode;
    pay = payload;
  }
  else {
    Serial.println("Error on HTTP request");
    code = httpCode;
    pay = "null";
  }

  http.end(); //Free the resources
}
#endif