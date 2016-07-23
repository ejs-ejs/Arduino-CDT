
void check_state(void) {

  unsigned int button_delay;

  if (state_running) {
    state_pause = digitalRead(BUTTON_PAUSE) ? 0 : 1;
    if (state_pause) {
      //    state_running=0;
      switch_load(LOW);
      state_running = 0;
      //       tElapsed = millis() - tStart - tPause;

      while (state_pause == 0) {
        button_delay++;
        if ( button_delay > 100) {
          state_pause = 0;
          state_start = 0;
          state_running = 0;
          switch_load(LOW);

        } else {
          delay(10);
          //        Serial.println("holding");
          state_pause = digitalRead(BUTTON_PAUSE) ? 0 : 1;
        }
      }

      state_start = digitalRead(BUTTON_START) ? 0 : 1;
      if (state_start) {
        //           state_pause =0;
        state_running = 1;
        switch_load(HIGH);
      }

    } // end check for pause


  } // end if state running
  else
  {
    state_start = digitalRead(BUTTON_START) ? 0 : 1;
    if (state_start) {
      //              timer = value;
      tStart = millis();
      oTimer = tStart;
      switch_load(HIGH);
      state_running = 1;
    }

    //    adjust timings from the presets
    adjust_timing();
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


