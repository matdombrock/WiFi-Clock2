EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Wifi Clock 2"
Date "2021-05-13"
Rev ""
Comp "Mathieu Dombrock"
Comment1 "GPL3"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Sensor:DHT11 U1
U 1 1 609E2237
P 7250 2900
F 0 "U1" H 7006 2946 50  0000 R CNN
F 1 "DHT11" H 7006 2855 50  0000 R CNN
F 2 "Sensor:Aosong_DHT11_5.5x12.0_P2.54mm" H 7250 2500 50  0001 C CNN
F 3 "http://akizukidenshi.com/download/ds/aosong/DHT11.pdf" H 7400 3150 50  0001 C CNN
	1    7250 2900
	1    0    0    -1  
$EndComp
$Comp
L RF_Module:ESP32-WROOM-32 U1
U 1 1 609E5658
P 6150 4000
F 0 "U1" H 6150 5581 50  0000 C CNN
F 1 "ESP32-WROOM-32" H 6150 5490 50  0000 C CNN
F 2 "RF_Module:ESP32-WROOM-32" H 6150 2500 50  0001 C CNN
F 3 "https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32_datasheet_en.pdf" H 5850 4050 50  0001 C CNN
	1    6150 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	6150 5500 6150 5400
Wire Wire Line
	6150 2600 7250 2600
Wire Wire Line
	7250 5500 6150 5500
Wire Wire Line
	6750 4000 7300 4000
Wire Wire Line
	7300 4000 7300 4850
Wire Wire Line
	7300 4850 7450 4850
Wire Wire Line
	6750 4400 7200 4400
Wire Wire Line
	7200 4400 7200 4950
Wire Wire Line
	7200 4950 7450 4950
Wire Wire Line
	6750 3300 7350 3300
Wire Wire Line
	7350 3300 7350 4750
Wire Wire Line
	7350 4750 7450 4750
Text Label 7550 4700 0    50   ~ 0
LOAD=CS
Wire Wire Line
	7850 5150 7850 5500
Wire Wire Line
	7850 5500 7250 5500
Connection ~ 7250 5500
Wire Wire Line
	7550 2900 7550 3150
Wire Wire Line
	7550 3150 7400 3150
Wire Wire Line
	7400 3150 7400 3900
Wire Wire Line
	6750 3900 7400 3900
Wire Wire Line
	7250 3200 7250 5500
Text Notes 8150 6950 0    50   ~ 0
ESP32: Pin 18 (or SCK) -> Matrix: CLK\nESP32: Pin 23 (or MOSI) -> Matrix: DATA\nESP32: Pin 5 (or SS) -> Matrix: CS\nESP32: Pin 17 -> DHT: Out
$Comp
L Driver_LED:MAX7219 U1
U 1 1 609E39A4
P 7850 4150
F 0 "U1" H 7850 5331 50  0000 C CNN
F 1 "MAX7219" H 7850 5240 50  0000 C CNN
F 2 "" H 7800 4200 50  0001 C CNN
F 3 "https://datasheets.maximintegrated.com/en/ds/MAX7219-MAX7221.pdf" H 7900 4000 50  0001 C CNN
	1    7850 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	6150 2600 6150 2550
Wire Wire Line
	6150 2550 7850 2550
Wire Wire Line
	7850 2550 7850 3150
Connection ~ 6150 2600
$EndSCHEMATC
