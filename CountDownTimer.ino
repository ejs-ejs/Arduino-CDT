//Modified Countdown Timer Sketch

#include <EEPROM.h>
#include "pitches.h"

#include "settings.h"



UVLightBox cLightBox; //Variable to store UVLightBox object read from EEPROM.

unsigned long value = 20; // Countdown value: MMSSS



unsigned long valueUs = value*1000;

unsigned long timer = value;

unsigned long tStart;
unsigned long tPause;
unsigned long tElapsed;


// notes in the melody:
int end_melody[] = {
  NOTE_C5, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_G4, 0, NOTE_B4, NOTE_C5
};

int tick[] = {
  NOTE_C4, NOTE_G3,
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int end_noteDurations[] = {
  6, 10, 10, 6, 6, 6, 6, 6
};

int tick_Durations[] = {
  16, 16
};


//function to display value on 4x7 segment display


void displayNumber(int toDisplay) {

unsigned long beginTime = millis();



  for(int digit = 3 ; digit >= 0 ; digit--) {

    //Turn on a digit for a short amount of time
    switch(digit) {
    case 0:
      digitalWrite(Dig1, DIGIT_ON);
      digitalWrite(DOT, LOW);
//      lightNumber(d1);
      break;
    case 1:
      digitalWrite(Dig2, DIGIT_ON);
      digitalWrite(DOT, LOW);
//      lightNumber(d2);
      break;
    case 2:
      digitalWrite(Dig3, DIGIT_ON);
      if (cLightBox.timeMode)
      {digitalWrite(DOT, HIGH);}
//      lightNumber(d3);
      break;
    case 3:
      digitalWrite(Dig4, DIGIT_ON);
      if (cLightBox.timeMode)
      {digitalWrite(DOT, HIGH);}
//      lightNumber(d4);
      break;
    }

//    digitalWrite(Dig1, DIGIT_ON);
//    lightNumber(toDisplay);

    //Turn on the right segments for this digit
    lightNumber(toDisplay % 10);
    toDisplay /= 10;

    delay(DISPLAY_BRIGHTNESS); 
    //Display digit for fraction of a second (1us to 5000us, 500 is pretty good)

    //Turn off all segments
    lightNumber(10); 
  
    //Turn off all digits
    digitalWrite(Dig1, DIGIT_OFF);
    digitalWrite(Dig2, DIGIT_OFF);
    digitalWrite(Dig3, DIGIT_OFF);
    digitalWrite(Dig4, DIGIT_OFF);
}

  while( (millis() - beginTime) < 1) ; 
  //Wait for 20ms to pass before we paint the display again
}



//Given a number, turns on those segments
//If number == 10, then turn off number
void lightNumber(int numberToDisplay) {

  switch (numberToDisplay){

  case 0:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_OFF);
    break;

  case 1:
    digitalWrite(segA, SEGMENT_OFF);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_OFF);
    break;

  case 2:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_OFF);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 3:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 4:
    digitalWrite(segA, SEGMENT_OFF);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 5:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_OFF);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 6:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_OFF);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 7:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_OFF);
    break;

  case 8:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 9:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 10:
    digitalWrite(segA, SEGMENT_OFF);
    digitalWrite(segB, SEGMENT_OFF);
    digitalWrite(segC, SEGMENT_OFF);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_OFF);
    break;

    case 20:
    digitalWrite(segA, SEGMENT_OFF);
    digitalWrite(segB, SEGMENT_OFF);
    digitalWrite(segC, SEGMENT_OFF);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_ON);
    break;
  }
}


 
void setup() {
  Serial.begin(9600);
  Serial.println(F("The time is ticking"));

  int eeAddress = 0;
  
  EEPROM.get(eeAddress, cLightBox);

  Serial.print(F("Device signature:\t\t"));
  Serial.println(cLightBox.signature, HEX);
//  Serial.print("\n");
  
  Serial.print(F("Number of runs:\t\t\t"));
  Serial.println(cLightBox.numRuns);
//  Serial.print("\n");

  Serial.print(F("Number of values stored:\t"));
  Serial.println(cLightBox.numValues);
//  unsigned int timings[];
  
//  Serial.print("\n");
// for (int i=0; i<cLightBox.numValues; i++ )
// {
//  
//  }

  
  Serial.print(F("Current time value #:\t\t"));
  Serial.println(cLightBox.cValue);
  Serial.print(F("Current time mode #:\t\t"));
  cLightBox.timeMode?Serial.println("seconds"):Serial.println("mm:ss");

//  value = cTimings[cLightBox.cValue-1];

//  if (cLightBox.numRuns >10) {
    unsigned int timings[] = {  10, 20, 30, 40, 50, 60, 50, 60,70};
    cLightBox.cValue =1;
    cLightBox.timeMode = 0;
    cLightBox.numValues = sizeof(timings) / 2; // warum? 
    cLightBox.numRuns = 1;
    cLightBox.signature = 66;
    eeAddress = 0;
    EEPROM.put(eeAddress, cLightBox);
    eeAddress += 1;
    for (int i=1; i<cLightBox.numValues; i++ ){
      EEPROM.write(eeAddress, timings[i]);
      eeAddress += 1;
      }
//    } else {
      cLightBox.numRuns += 1;
      eeAddress = 0;
    EEPROM.put(eeAddress, cLightBox);
//      }
 
  pinMode(BUZZ, OUTPUT);
  pinMode(LED,  OUTPUT);
   pinMode(LOAD,  OUTPUT);
 
  pinMode(BUTTON_START, INPUT_PULLUP);
  pinMode(BUTTON_PAUSE, INPUT_PULLUP);
  pinMode(BUTTON_ADVANCE, INPUT_PULLUP);
  
//  digitalWrite(LATCH, HIGH); //Wake Up Display 
  digitalWrite(BUZZ, LOW);  //Buzzer Off
  digitalWrite(BUTTON_START, HIGH); // Button Low  
  delay(1000);  //delay for 1 second

  pinMode(segA, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segE, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segG, OUTPUT);
  pinMode(DOT, OUTPUT);

  pinMode(Dig1, OUTPUT);
  pinMode(Dig2, OUTPUT);
  pinMode(Dig3, OUTPUT);
  pinMode(Dig4, OUTPUT);
  
}


 void beep() {
  
    tone(BUZZ, NOTE_A4, 50);
    delay(70);
    noTone(BUZZ);
  
 
 }

 void wakeup () {

 for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / end_noteDurations[thisNote];
    tone(BUZZ, end_melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(BUZZ);
  }
 }


 void check_state() {
  
  
  if (state_running) {
    state_pause = digitalRead(BUTTON_PAUSE)?0:1;
    if (state_pause) {
  //    state_running=0;
       switch_load(LOW);
       state_running =0;
//       tElapsed = millis() - tStart - tPause;
       
       state_start = digitalRead(BUTTON_START)?0:1;
         if (state_start) {
//           state_pause =0;
            state_running =1;
           switch_load(HIGH);
          }
      
      } // end check for pause
      
      
    } // end if state running
    else 
      {
        state_start = digitalRead(BUTTON_START)?0:1;
           if (state_start) {
//              timer = value;
        tStart=state_pause?tStart:millis();
            switch_load(HIGH);
            state_running =1;
           }
        }
 
 }

 

//void check_state() {
//
// if (!state_running) {
//    state_start = digitalRead(BUTTON_START)?0:1;
//    if (state_start) {
//      if (!state_pause) {
////      timer = value;
//         tStart=millis();
//       }
//      state_running =1;
//      switch_load(HIGH);
//     } else {
//      state_pause = 0;
////      switch_load(HIGH);
//     }
// }
//
// 
// if (state_running) {
//    state_pause = digitalRead(BUTTON_PAUSE)?0:1;
//    if (state_pause) {
//      state_running=0;
//      switch_load(LOW);
//      }
// }
//
// if (state_pause) {
//  state_start = digitalRead(BUTTON_START)?0:1;
////  if (state_start) {
////      state_running =1;
////  }
// }
//
// if (state_pause && state_start) {
//  state_running = 1;
//  switch_load(HIGH);
//  state_pause = 0;
// }
//
//
//
//  }

void switch_load(int state) {
   digitalWrite(LOAD, state);
}

void check_time() {
  unsigned int now = millis();
  tPause = state_pause?now:0;
  tElapsed = (state_running && !state_pause)?now-tStart:tElapsed;
  
 if (state_running) {
   
     if (state_beep) {
      beep();
     }

      long oTimer = timer;
            
       timer = value - (tElapsed /1000);
       tPause = 0;
       
       state_beep=(timer-oTimer)?1:0;
        

    // Countdown is Finished? Sound Alarm
    if (timer <= 0) {
       digitalWrite(LED, HIGH); 
       switch_load(LOW);
      wakeup(); 
      state_start = 0;
      state_running = 0;
      state_pause = 0;
      timer = value;
    }

}

}

void report_state() {
  if (state_beep) {
//      Serial.print(F("Set value\t Started \t Remaining \t estimation\n"));
Serial.print(F("Set value\t Started \t Elapsed \t Remaining\n"));
      Serial.print(value);
      Serial.print("\t\t");
      Serial.print(tStart);
      Serial.print("\t\t");
       Serial.print(tElapsed);
      Serial.print("\t\t");
      Serial.print(timer);
      Serial.print("\t\t");
     
      
//      Serial.print(tPause);
//      Serial.print("\t\t");
//      Serial.print(valueUs - millis() - tStart);
      Serial.print("\n");
      if (state_pause) {
        Serial.print(F("\t\tCounter paused\n"));
      }
  }
}
  
  
void loop(){ 

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

      
   displayNumber(timer);  //display the Countdown Start value
   check_time();
   
   if (state_pause || state_start) {
    report_state();
    }  
}
