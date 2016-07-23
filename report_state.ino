
void report_state(void) {
  if (state_beep) {
//      Serial.print(F("Set value\t Started \t Remaining \t estimation\n"));
Serial.print(F("Set value\t Started \t Elapsed \t Remaining\n"));
      Serial.print(timer);
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
  
