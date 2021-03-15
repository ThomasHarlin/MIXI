//Fun animation on power on
void wakeUp() {

  //put on a little make up

  //starts out dim
  strip.setBrightness(75);
  //initial color splash
  strip.setPixelColor(0, 68, 50, 170);
  delay(500);
  strip.show();
  strip.setPixelColor(6, 43, 150, 190);
  delay(400);
  strip.show();
  strip.setPixelColor(4, 168, 250, 17);
  delay(300);
  strip.show();
  strip.setPixelColor(3, 255, 10, 60);
  delay(200);
  strip.show();
  strip.setPixelColor(7, 20, 100, 160);
  delay(175);
  strip.show();
  strip.setPixelColor(2, 200, 200, 70);
  delay(150);
  strip.show();
  strip.setPixelColor(5, 75, 6, 140);
  delay(125);
  strip.show();
  strip.setPixelColor(1, 125, 87, 96);
  delay(100);
  strip.show();
  //increases brightness for step 2
  strip.setBrightness(150);
  strip.setPixelColor(5, 168, 5, 98);
  delay(100);
  strip.show();
  strip.setPixelColor(0, 243, 15, 19);
  delay(100);
  strip.show();
  strip.setPixelColor(1, 18, 250, 174);
  delay(100);
  strip.show();
  strip.setPixelColor(7, 55, 100, 16);
  delay(100);
  strip.show();
  strip.setPixelColor(2, 220, 70, 54);
  delay(100);
  strip.show();
  strip.setPixelColor(4, 20, 200, 70);
  delay(100);
  strip.show();
  strip.setPixelColor(6, 111, 46, 148);
  delay(100);
  strip.show();
  strip.setPixelColor(3, 25, 87, 209);
  delay(100);
  strip.show();
  //full brightness for the rest of the sketch
  strip.setBrightness(255);
  strip.setPixelColor(3, 68, 50, 170);
  delay(50);
  strip.show();
  strip.setPixelColor(7, 68, 50, 170);
  delay(50);
  strip.show();
  strip.setPixelColor(1, 68, 50, 170);
  delay(50);
  strip.show();
  strip.setPixelColor(5, 68, 50, 170);
  delay(50);
  strip.show();
  strip.setPixelColor(0, 250, 22, 216);
  delay(50);
  strip.show();
  strip.setPixelColor(2, 68, 50, 170);
  delay(50);
  strip.show();
  strip.setPixelColor(6, 68, 50, 170);
  delay(50);
  strip.show();
  strip.setPixelColor(4, 245, 158, 42);
  delay(50);
  strip.show();


  //sends it into the drum screen
  drumLights = true;
  screen = 1;
}

///////////////////////////////////////////////////////////////

void initializeButtons() {
  for (int i = 0; i < 8; i++) {
    buttons[i].attach(buttonPins[i] , INPUT_PULLUP  );
    buttons[i].interval(15);
  }
}
//////////////////////////////////////////////////////////////////
void updateButtons() {
  for (int i = 0; i < 8; i++) {
    buttons[i].update();
    if (buttons[i].rose()) {
      buttonStates[i] = 1;
    }
    else {
      buttonStates[i] = 0;
    }
  }
}
////////////////////////////////////////////////////////////////
void updatePots() {
  for (int i = 0; i < 4; i++) {
    int thisPot = analogRead(potPins[i]);
    int mapPot = map(thisPot, 0, 1023, 0, 127);

    if (i != 4) {
      mapPot = 127 - mapPot;
    }

    potStates[i] = mapPot;
  }
}
