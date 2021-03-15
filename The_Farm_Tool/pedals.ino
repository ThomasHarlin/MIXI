///////PEDALS///////

boolean pedalButtons[] = {false, false, false, false, false, false};

int pedalPots[] = {0, 0, 0, 0};
int pedalPotTol = 10;

int pedalOffset = 20;
int pedalOffset2 = (8 + pedalOffset);

///////////////////////////////////////////////////////////////////////////////
void pedalBoard() {
  if (pedalLights) {
    for (int i = 0; i < strip.numPixels(); i++) {
      //pedal color
      strip.setPixelColor(i, 245, 158, 42);
      if (i == 4) {
        //synth color
        strip.setPixelColor(i, 250, 22, 216);
      }
      if (i == 0) {
        //drum color
        strip.setPixelColor(i, 68, 50, 170);
      }
    }
    strip.show();
    pedalLights = false;
  }


  for (int i = 0; i < 8; i++) {
    int curPedal = buttonStates[i];

    if (curPedal == 1 && i != 0 && 1 != 4) {
      pedalButtons[i] = !pedalButtons[i];
      if (pedalButtons[i]) {
        usbMIDI.sendControlChange(i + pedalOffset, 127, 1);
      }
      else {
        usbMIDI.sendControlChange(i + pedalOffset, 0, 1);
      }
    }

    if (curPedal == 1 && i == 0) {
      strip.clear(); pedalLights = false; drumLights = true; screen = 1;
           Serial.println("pedal to drums");
    }
    if (curPedal == 1 && i == 4) {
      strip.clear(); pedalLights = false; synthLights = true; screen = 2;
      Serial.println("pedal to synth");
    }
  }

  //storing the pots//
  for (int i = 0; i < 4; i++) {
    int thisPot = potStates[i];
    if (abs(thisPot - pedalPots[i]) > pedalPotTol) {
      usbMIDI.sendControlChange(i + pedalOffset2, thisPot, 1);
      pedalPots[i] = thisPot;
    }

  }
}
