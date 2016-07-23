void check_time(void) {
  static unsigned long duration = 1000; // 1 second

  //  unsigned long cTimer = timer*1000;


  //  tPause = state_pause?now:0;
  //  tElapsed = (state_running && !state_pause)?now-tStart:tElapsed;
  //
  if (state_running) {

    if (state_beep) {
      beep();
    }

    unsigned long now = millis();
    unsigned int tDelta = now - oTimer;
    //if (now - oTimer - duration) {
    if (tDelta > duration) {
#ifdef DEBUG
      Serial.print(F("Time elapsed, ms:\t"));
      Serial.print(millis());
      Serial.print(F("\tOld timer, ms:\t"));
      Serial.print(oTimer);
      Serial.print(F("\tTime delta, ms:\t"));
      Serial.println(tDelta);
#endif
      timer -= 1;
      //        tPause = 0;
      state_beep = 1;
      oTimer = now;
    }
    else {
      state_beep = 0;
    }


    // Countdown is Finished? Sound Alarm
    if (timer <= 0) {
      digitalWrite(LED, HIGH);
      switch_load(LOW);
      wakeup();
      state_start = 0;
      state_running = 0;
      state_pause = 0;
      timer = cTimers[cLightBox.cValue];
    }

  }
 
}


