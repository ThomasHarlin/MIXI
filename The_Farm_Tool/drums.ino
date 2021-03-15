///////DRUMS///////

boolean drumButtons[] = {false, false, false, false, false, false};

int drumPots[] = {0, 0, 0, 0};
int drumPotTol = 10;

void drumBoard() {

  //sets LED colors for the screen
  if (drumLights) {
    strip.clear();

    for (int i = 0; i < strip.numPixels(); i++) {
      //drum color
      strip.setPixelColor(i, 68, 50, 170);
      if (i == 4) {
        //pedal color
        strip.setPixelColor(i, 245, 158, 42);
      }
      if (i == 0) {
        //synth color
        strip.setPixelColor(i, 250, 22, 216);
      }
    }
    strip.show();
    drumLights = false;
  }

  //runs through the buttons to check if any have been pressed
  for (int i = 0; i < 8; i++) {
    int curDrum = buttonStates[i];

    if (curDrum == 1 && i != 0 && 1 != 4) {
      drumButtons[i] = !drumButtons[i];
      if (drumButtons[i]) {
        usbMIDI.sendControlChange(i, 127, 1);
      }
      else {
        usbMIDI.sendControlChange(i, 0, 1);
      }
    }

    //state change buttons
    if (curDrum == 1 && i == 0) {
      strip.clear(); drumLights = false; synthLights = true; screen = 2;
      Serial.println("drum to synth");
    }
    if (curDrum == 1 && i == 4) {
      strip.clear(); drumLights = false; pedalLights = true; screen = 3;
      Serial.println("drum to pedals");
    }
  }

  //storing the pots//
  for (int i = 0; i < 4; i++) {
    int thisPot = potStates[i];
    if (abs(thisPot - drumPots[i]) > drumPotTol) {
      usbMIDI.sendControlChange(i + 8, thisPot, 1);
      drumPots[i] = thisPot;
    }

  }
}
