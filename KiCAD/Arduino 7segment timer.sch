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
LIBS:w_connectors
LIBS:arduino
LIBS:displays-7seg
LIBS:switch-enc
LIBS:w_device
LIBS:sx02s02
LIBS:Arduino 7segment timer-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 3
Title "Count down timer with 4x7 scrapped LED display (common cathode) "
Date "2016-07-24"
Rev "0.1b"
Comp "TxTn"
Comment1 "ejs, 2016"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Sheet
S 5450 1750 1200 1400
U 578DA969
F0 "Control" 79
F1 "Control.sch" 79
F2 "Ctrl" I L 5450 1950 60 
F3 "Vcc" U L 5450 2700 60 
F4 "GND1" U L 5450 2900 60 
$EndSheet
$Sheet
S 4000 1750 700  1400
U 578DB8E5
F0 "Power" 79
F1 "power.sch" 79
F2 "Ctrl" I R 4700 1950 60 
F3 "Vcc" U R 4700 2700 60 
F4 "GND" U R 4700 2900 60 
$EndSheet
Wire Wire Line
	4700 2900 5450 2900
Wire Wire Line
	4700 2700 5450 2700
Wire Wire Line
	4700 1950 5450 1950
$EndSCHEMATC
