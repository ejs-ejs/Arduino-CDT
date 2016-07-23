

#include <avr/pgmspace.h>

//unsigned int cTimings[] PROGMEM;

 
#define LATCH  12  //pin 12 connect to RCK
#define CLOCK  11  //pin 11 connect to SCK
#define DATA   10  //pin 10 connect to DIO
#define BUZZ    A1  //pin A1  connect to Buzzer
#define BUTTON_START  12  //pin 11 connect to START Button
#define BUTTON_PAUSE  11
#define BUTTON_ADVANCE  10
#define LEFT   0  // define the value for left justify
#define RIGHT  1  // define the value for right justify
#define LED 13
#define LOAD A0

#define Dig1 A2
#define Dig2 A3
#define Dig3 A4
#define Dig4 A5


//Pin mapping from Arduino to the ATmega DIP28 if you need it
//http://www.arduino.cc/en/Hacking/PinMapping
#define segA 2 
#define segB 3 
#define segC 4 
#define segD 6 
#define segE 7 
#define segF 8 
#define segG 9 
#define DOT 5

unsigned int state_start = 0;
unsigned int state_pause = 0;
unsigned int state_running = 0;
int state_buzz = 9; //Trigger counter for Buzzer

unsigned int state_beep = 1;

long remaining;

struct UVLightBox {
  unsigned long numRuns;
  unsigned long signature;
  unsigned int timeMode;
  unsigned long numValues;
  unsigned long cValue;
};



#define DISPLAY_BRIGHTNESS  5

#define DIGIT_ON  LOW
#define DIGIT_OFF  HIGH

#define SEGMENT_ON  HIGH
#define SEGMENT_OFF LOW



