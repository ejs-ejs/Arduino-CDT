void setup(void) {
  Serial.begin(115200);
  Serial.print(F("The time is ticking: \n\t"));
  Serial.println(F("Count-Down timer for anything\n\t\t ejs @ TxNx, 2016\n"));

  int eeAddress = 0;
  
  EEPROM.get(eeAddress, cLightBox);

  Serial.print(F("Device signature:\t\t"));
  Serial.println(cLightBox.signature, HEX);
  
  Serial.print(F("Number of runs:\t\t\t"));
  Serial.println(cLightBox.numRuns);

  Serial.print(F("Number of values stored:\t"));
  Serial.println(cLightBox.numValues);

  Serial.print(F("Current time value #:\t\t"));
  Serial.println(cLightBox.cValue);
  Serial.print(F("Current time mode #:\t\t"));
  cLightBox.timeMode?Serial.println(F("mm:ss")):Serial.println(F("seconds"));

//  value = cTimings[cLightBox.cValue-1];

#ifdef EEPROM_INIT
    unsigned int timings[] = { 30, 45, 60, 60+15, 60+30, 60+45, 2*60, 2*60+15, 2*60+30, 2*60+45, 3*60, 3*60+15, 3*60+30, 3*60+45, 4*60 , 4*60+15, 4*60+30, 4*60+45, 5*60 , 5*60+15, 5*60+30, 5*60+45, 6*60 , 6*60+15, 6*60+30, 6*60+45, 7*60 , 7*60+15, 7*60+30, 7*60+45};
    cLightBox.cValue =17; // current preset number
    cLightBox.timeMode = 1; // 0 - secs, 1 - mm:ss
    cLightBox.numValues = sizeof(timings) / 2; // warum? 
    cLightBox.numRuns = 1; // number of runs the Thing made
    cLightBox.signature = 66; // the signature of the Thing
    
 // write timings to EEPROM
    eeAddress = 0;
    EEPROM.put(eeAddress, cLightBox);
 
#ifdef DEBUG
Serial.print(F("INIT: Initial address:\t"));
Serial.println(eeAddress, HEX);
#endif

eeAddress += sizeof(cLightBox);

#ifdef DEBUG
Serial.print(F("INIT: Timing address:\t"));
Serial.println(eeAddress, HEX);
#endif
  
Serial.print(F("Storing timings, s:\n"));

    for (int i=0; i<cLightBox.numValues; i++ ){
      EEPROM.put(eeAddress, timings[i]);
      Serial.print(F("\t\t#"));
    Serial.print(i);
    Serial.print(F(":\t\t"));
    Serial.print(timings[i]);
    Serial.print(F("\t\t@0x"));
    Serial.println(eeAddress, HEX);
      eeAddress += sizeof(int);
      }
     
#endif

//     increment number of runs
      cLightBox.numRuns += 1;
      eeAddress = 0;
     EEPROM.put(eeAddress, cLightBox);

#ifdef DEBUG
Serial.print(F("Initial address:\t"));
Serial.println(eeAddress, HEX);
#endif

eeAddress += sizeof(cLightBox);

#ifdef DEBUG
Serial.print(F("Timing address:\t"));
Serial.println(eeAddress, HEX);
#endif


Serial.print(F("Stored timings, s:\n"));
  
 // read timers stored in EEPROM
   for (int i=0; i<cLightBox.numValues; i++ ){
    unsigned int tmp;
    EEPROM.get(eeAddress, tmp);
    cTimers[i]=(tmp == 666)?0:tmp;
    Serial.print(F("\t\t#"));
    Serial.print(i);
    Serial.print(F(":\t\t"));
    Serial.print(cTimers[i]);
    Serial.print(F("\t\t@0x"));
    Serial.println(eeAddress, HEX);
  
  
      eeAddress += sizeof(int);
   }

   timer = cTimers[cLightBox.cValue]; 


   
      
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


