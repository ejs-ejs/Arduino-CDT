void beep(void) {

  tone(BUZZ, NOTE_A4, 50);
  delay(70);
  noTone(BUZZ);
}
