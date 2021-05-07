/* 
Simple abstraction for the boilerplate loop.
Very simple but helps avoid confusion determining 
what is boilerplate code and what is app code.
Note: You probably don't want to change this file.
*/


#include <DNSServer.h>
extern DNSServer dnsServer;
void loopBP(){
  dnsServer.processNextRequest();
}