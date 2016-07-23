void adjust_timing(void) {

    if (millis() != bDebounceTime ) {
      bAdvance = digitalRead(BUTTON_ADVANCE) ? 0 : 1;
      #ifdef DEBUG
      Serial.print(F("bAdvance state: "));
      Serial.print(bAdvance);
      Serial.print(F("\t bsAdvance: "));
      Serial.print(bsAdvance);
      Serial.print(F("\t @: "));
      Serial.print(bDebounceTime);
      Serial.print(F("\t count: "));
      Serial.println(counter);
#endif
      if (bAdvance == !bsAdvance && counter > 0)  {
        counter--;
      }

      if (bAdvance == bsAdvance ) {
        counter++;
      }
      if (counter >= debounceCount) {
        counter = 0;
        bAdvance = 0;
      }
      bDebounceTime = millis();
    }

    //    if (bAdvance == !lbsAdvance) {
    //      bDebounceTime = millis();
    //    }
    //    if ((millis() - bDebounceTime) > debounceTime) {
    //      if (bAdvance != bsAdvance) {
    //        bsAdvance = bAdvance;
    //      }
    //    }
    //

    

  if (bAdvance) {
    unsigned int tmp = cLightBox.cValue + 1;
    if (tmp > cLightBox.numValues) {
      tmp = 0;
    }
    cLightBox.cValue = tmp;
    timer = cTimers[cLightBox.cValue];
    int eeAddress = 0;
     EEPROM.put(eeAddress, cLightBox);
    delay(400);
    bAdvance = 0;
    bsAdvance = 1;
  }


}
