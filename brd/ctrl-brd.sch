EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:stm8
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "28 feb 2015"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L STM8S003F3P IC?
U 1 1 54F1BFDA
P 5850 3650
F 0 "IC?" H 4700 4450 50  0000 L CNN
F 1 "STM8S003F3P" H 4700 4350 50  0000 L CNN
F 2 "TSSOP-20" H 4700 2850 50  0000 L CIN
F 3 "" H 5800 3250 60  0000 C CNN
	1    5850 3650
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X03 P?
U 1 1 54F1C00D
P 7700 3950
F 0 "P?" H 7700 4150 50  0000 C CNN
F 1 "LCD" V 7800 3950 50  0000 C CNN
F 2 "" H 7700 3950 60  0000 C CNN
F 3 "" H 7700 3950 60  0000 C CNN
	1    7700 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	7150 3850 7500 3850
Wire Wire Line
	7150 3950 7500 3950
Wire Wire Line
	7150 4050 7500 4050
$Comp
L CONN_01X01 P?
U 1 1 54F1C327
P 5850 2450
F 0 "P?" H 5850 2550 50  0000 C CNN
F 1 "VDD" V 5950 2450 50  0000 C CNN
F 2 "" H 5850 2450 60  0000 C CNN
F 3 "" H 5850 2450 60  0000 C CNN
	1    5850 2450
	0    -1   -1   0   
$EndComp
$Comp
L VDD #PWR?
U 1 1 54F1C340
P 6100 2600
F 0 "#PWR?" H 6100 2450 60  0001 C CNN
F 1 "VDD" H 6100 2750 60  0000 C CNN
F 2 "" H 6100 2600 60  0000 C CNN
F 3 "" H 6100 2600 60  0000 C CNN
	1    6100 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	5850 2850 5850 2650
Wire Wire Line
	5750 2750 6100 2750
Wire Wire Line
	6100 2750 6100 2600
Connection ~ 5850 2750
$Comp
L GND #PWR?
U 1 1 54F1C364
P 5850 4800
F 0 "#PWR?" H 5850 4550 60  0001 C CNN
F 1 "GND" H 5850 4650 60  0000 C CNN
F 2 "" H 5850 4800 60  0000 C CNN
F 3 "" H 5850 4800 60  0000 C CNN
	1    5850 4800
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X01 P?
U 1 1 54F1C373
P 6150 4700
F 0 "P?" H 6150 4800 50  0000 C CNN
F 1 "GND" V 6250 4700 50  0000 C CNN
F 2 "" H 6150 4700 60  0000 C CNN
F 3 "" H 6150 4700 60  0000 C CNN
	1    6150 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	5950 4700 5850 4700
Wire Wire Line
	5850 4550 5850 4800
Connection ~ 5850 4700
$Comp
L CONN_01X01 P?
U 1 1 54F1C3AD
P 4050 3450
F 0 "P?" H 4050 3550 50  0000 C CNN
F 1 "SWIM" V 4150 3450 50  0000 C CNN
F 2 "" H 4050 3450 60  0000 C CNN
F 3 "" H 4050 3450 60  0000 C CNN
	1    4050 3450
	-1   0    0    1   
$EndComp
Wire Wire Line
	4550 3450 4250 3450
$Comp
L CONN_01X01 P?
U 1 1 54F1C460
P 4050 3850
F 0 "P?" H 4050 3950 50  0000 C CNN
F 1 "UART_TX" V 4150 3850 50  0000 C CNN
F 2 "" H 4050 3850 60  0000 C CNN
F 3 "" H 4050 3850 60  0000 C CNN
	1    4050 3850
	-1   0    0    1   
$EndComp
Wire Wire Line
	4250 3850 4550 3850
$Comp
L CONN_01X01 P?
U 1 1 54F1C486
P 5200 2450
F 0 "P?" H 5200 2550 50  0000 C CNN
F 1 "UART_VDD" V 5300 2450 50  0000 C CNN
F 2 "" H 5200 2450 60  0000 C CNN
F 3 "" H 5200 2450 60  0000 C CNN
	1    5200 2450
	0    -1   -1   0   
$EndComp
$Comp
L R R?
U 1 1 54F1C4A4
P 5500 2750
F 0 "R?" V 5580 2750 50  0000 C CNN
F 1 "10" V 5507 2751 50  0000 C CNN
F 2 "" V 5430 2750 30  0000 C CNN
F 3 "" H 5500 2750 30  0000 C CNN
	1    5500 2750
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5250 2750 5200 2750
Wire Wire Line
	5200 2750 5200 2650
$Comp
L CONN_01X01 P?
U 1 1 54F1C51D
P 3700 3650
F 0 "P?" H 3700 3750 50  0000 C CNN
F 1 "ZERO" V 3800 3650 50  0000 C CNN
F 2 "" H 3700 3650 60  0000 C CNN
F 3 "" H 3700 3650 60  0000 C CNN
	1    3700 3650
	-1   0    0    1   
$EndComp
Wire Wire Line
	3900 3650 4550 3650
$Comp
L CONN_01X01 P?
U 1 1 54F1C562
P 7700 4250
F 0 "P?" H 7700 4350 50  0000 C CNN
F 1 "X" V 7800 4250 50  0000 C CNN
F 2 "" H 7700 4250 60  0000 C CNN
F 3 "" H 7700 4250 60  0000 C CNN
	1    7700 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	7150 4250 7500 4250
$Comp
L CONN_01X01 P?
U 1 1 54F1C5B7
P 8050 4150
F 0 "P?" H 8050 4250 50  0000 C CNN
F 1 "SW" V 8150 4150 50  0000 C CNN
F 2 "" H 8050 4150 60  0000 C CNN
F 3 "" H 8050 4150 60  0000 C CNN
	1    8050 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	7150 4150 7850 4150
$Comp
L CONN_01X01 P?
U 1 1 54F1C62E
P 3200 3550
F 0 "P?" H 3200 3650 50  0000 C CNN
F 1 "SENSE" V 3300 3550 50  0000 C CNN
F 2 "" H 3200 3550 60  0000 C CNN
F 3 "" H 3200 3550 60  0000 C CNN
	1    3200 3550
	-1   0    0    1   
$EndComp
Wire Wire Line
	3400 3550 4550 3550
$Comp
L CONN_01X01 P?
U 1 1 54F1C69B
P 3400 3900
F 0 "P?" H 3400 4000 50  0000 C CNN
F 1 "HEAT" V 3500 3900 50  0000 C CNN
F 2 "" H 3400 3900 60  0000 C CNN
F 3 "" H 3400 3900 60  0000 C CNN
	1    3400 3900
	-1   0    0    1   
$EndComp
Wire Wire Line
	4550 3750 3850 3750
Wire Wire Line
	3850 3750 3850 3900
Wire Wire Line
	3850 3900 3600 3900
$Comp
L R R?
U 1 1 54F1CEB6
P 4450 2800
F 0 "R?" V 4530 2800 50  0000 C CNN
F 1 "10k" V 4457 2801 50  0000 C CNN
F 2 "" V 4380 2800 30  0000 C CNN
F 3 "" H 4450 2800 30  0000 C CNN
	1    4450 2800
	-1   0    0    1   
$EndComp
$Comp
L VDD #PWR?
U 1 1 54F1CEBC
P 4450 2450
F 0 "#PWR?" H 4450 2300 60  0001 C CNN
F 1 "VDD" H 4450 2600 60  0000 C CNN
F 2 "" H 4450 2450 60  0000 C CNN
F 3 "" H 4450 2450 60  0000 C CNN
	1    4450 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 3050 4450 3150
Connection ~ 4450 3150
Wire Wire Line
	4450 2550 4450 2450
$Comp
L C C?
U 1 1 54F1CF4D
P 3600 4850
F 0 "C?" H 3650 4950 50  0000 L CNN
F 1 "C" H 3650 4750 50  0000 L CNN
F 2 "" H 3638 4700 30  0000 C CNN
F 3 "" H 3600 4850 60  0000 C CNN
	1    3600 4850
	-1   0    0    1   
$EndComp
$Comp
L C C?
U 1 1 54F1CF5B
P 3900 4850
F 0 "C?" H 3950 4950 50  0000 L CNN
F 1 "C" H 3950 4750 50  0000 L CNN
F 2 "" H 3938 4700 30  0000 C CNN
F 3 "" H 3900 4850 60  0000 C CNN
	1    3900 4850
	-1   0    0    1   
$EndComp
$Comp
L VDD #PWR?
U 1 1 54F1CF61
P 3900 4500
F 0 "#PWR?" H 3900 4350 60  0001 C CNN
F 1 "VDD" H 3900 4650 60  0000 C CNN
F 2 "" H 3900 4500 60  0000 C CNN
F 3 "" H 3900 4500 60  0000 C CNN
	1    3900 4500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 54F1CF67
P 3900 5200
F 0 "#PWR?" H 3900 4950 60  0001 C CNN
F 1 "GND" H 3900 5050 60  0000 C CNN
F 2 "" H 3900 5200 60  0000 C CNN
F 3 "" H 3900 5200 60  0000 C CNN
	1    3900 5200
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X01 P?
U 1 1 54F1CF79
P 3850 3150
F 0 "P?" H 3850 3250 50  0000 C CNN
F 1 "NRST" V 3950 3150 50  0000 C CNN
F 2 "" H 3850 3150 60  0000 C CNN
F 3 "" H 3850 3150 60  0000 C CNN
	1    3850 3150
	-1   0    0    1   
$EndComp
$Comp
L C C?
U 1 1 54F1CF99
P 4250 4850
F 0 "C?" H 4300 4950 50  0000 L CNN
F 1 "C" H 4300 4750 50  0000 L CNN
F 2 "" H 4288 4700 30  0000 C CNN
F 3 "" H 4250 4850 60  0000 C CNN
	1    4250 4850
	-1   0    0    1   
$EndComp
Wire Wire Line
	4250 4650 4250 4250
Wire Wire Line
	4250 4250 4550 4250
Wire Wire Line
	4250 5150 4250 5050
Wire Wire Line
	3600 5150 4250 5150
Wire Wire Line
	3900 5050 3900 5200
Connection ~ 3900 5150
Wire Wire Line
	3600 5150 3600 5050
Wire Wire Line
	3900 4650 3900 4500
Wire Wire Line
	3600 4650 3600 4250
Wire Wire Line
	3600 4250 3300 4250
Text Label 3350 4250 0    60   ~ 0
RST
Text Label 4200 3150 0    60   ~ 0
RST
Wire Wire Line
	4050 3150 4550 3150
$EndSCHEMATC
