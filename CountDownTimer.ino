//Modified Countdown Timer Sketch


#include <EEPROM.h>
#include "pitches.h"
#include "settings.h"

//#define EEPROM_INIT
//#define DEBUG


void setup(void);
void report_state(void);
void check_time(void);
void check_state(void);

void displayNumber(int);
void lightNumber(int);



void switch_load(int);
void beep(void);


void wakeup (void);

 unsigned int bAdvance = 1;
  unsigned int bsAdvance = 1;
  unsigned int lbsAdvance = 1;
  unsigned long bDebounceTime;
  unsigned long debounceTime = 10;
  int counter = 0;
  static int debounceCount = 10;



UVLightBox cLightBox; //Variable to store UVLightBox object read from EEPROM.

//unsigned int value = 20; // Countdown value: MMSSS


unsigned long oTimer;

//unsigned long valueUs = value*1000;

unsigned int timer;

unsigned int cTimers[MAX_TIMER_VALUES];

unsigned long tStart;
unsigned long tPause;
unsigned long tElapsed;



void loop() {

unsigned int mm;
unsigned int sec;

  //   blink dot leds
  digitalWrite(LED, HIGH);

  check_state();

  digitalWrite(LED, LOW);
  //   digitalWrite(Dig3, HIGH);
  //   digitalWrite(Dig3, HIGH);
  //   digitalWrite(DOT, LOW);

  //   digitalWrite(Dig4, HIGH);
  //   digitalWrite(Dig3, HIGH);
  //      digitalWrite(Dig2, HIGH);
  //      digitalWrite(Dig1, HIGH);

  check_time();

 if (cLightBox.timeMode) {

  mm = timer / 60;
  sec = timer % 60;
  displayNumber(mm*100+sec);  //display the mm:ss
  
 } else {

  displayNumber(timer);  //display the current value
  
 }
  
#ifdef DEBUG
  if (state_pause || state_start) {
    report_state();
  }
#endif
}
