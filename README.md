# WIFI CLOCK 2
*A WiFi enabled smart-clock for ESP32 development boards.*

![gif](images/wifi-clock.gif)

This is a work in progress rewrite of my original [WiFi Clock](https://github.com/matdombrock/WIFI-Clock). It's being rewritten to use my [zIOTBP32 Biolerplate](https://github.com/matdombrock/zIOTBP32) which enabled a soft AP for confiuguring WiFi access as well as many other quality of life features. 

## Features
* Soft AP for configuring WiFi credentials.
* Serverless web based UI.
* Automatic [NTP](https://en.wikipedia.org/wiki/Network_Time_Protocol) time fetching. 
* Display local (indoor) temperature and humidity readings using an onboard sensor.
* Display external ([web based](https://github.com/chubin/wttr.in)) weather conditions.
* USB Powered.

## Required Libraries
* [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer)
* [Time](https://github.com/PaulStoffregen/Time)
* [MatrixGL](https://github.com/matdombrock/MatrixGL)

## Required Components
* ESP32 Dev Board
* 4x MAX72xx LED Matrix Displays
* DHT11
* Jumper cables and breadboards.  
* 3D Printer (optional)

## Wiring
* ESP32: Pin 18 (or SCK)  -> Matrix: CLK
* ESP32: Pin 23 (or MOSI) -> Matrix: DATA
* ESP32: Pin 5 (or SS)    -> Matrix: CS
 
* ESP32: Pin 17           -> DHT: Out

## Printing the housing
See the [Housing README](housing)
![housing-screenshot](housing/screenshot.png)

## UI Screenshots
![desktop-ui](images/ui-desktop.png)
![mobile-ui](images/ui-mobile.png)

## More Device Images
![clock](images/clock1.jpg)
![dht](images/clock-dht.jpg)
![wiring](images/clock-wiring.jpg)