///////SYNTHS///////

boolean synthButtons[] = {false, false, false, false, false, false};

int synthPots[] = {0, 0, 0, 0};
int synthPotTol = 10;

int synthOffset = 40;
int synthOffset2 = (8 + synthOffset);

///////////////////////////////////////////////////////////////////////////////
void synthBoard() {
  if (synthLights) {
    for (int i = 0; i < strip.numPixels(); i++) {
        //synth color
        strip.setPixelColor(i, 250, 22, 216);
        if (i == 0) {
          //pedal color
          strip.setPixelColor(i, 245, 158, 42);
        }
        if (i == 4) {
          //drum color
          strip.setPixelColor(i, 68, 50, 170);
        }
      }
      strip.show();
      pedalLights = false;
    }


    for (int i = 0; i < 8; i++) {
      int curSynth = buttonStates[i];

      if (curSynth == 1 && i != 0 && 1 != 4) {
        synthButtons[i] = !synthButtons[i];
        if (synthButtons[i]) {
          usbMIDI.sendControlChange(i + synthOffset, 127, 1);
        }
        else {
          usbMIDI.sendControlChange(i + synthOffset, 0, 1);
        }
      }

      if (curSynth == 1 && i == 0) {
        strip.clear(); synthLights = false; pedalLights = true; screen = 3;
        Serial.println("synth to pedal");
      }
      if (curSynth == 1 && i == 4) {
        strip.clear(); synthLights = false; drumLights = true; screen = 1;
        Serial.println("synth to drums");
      }
    }

    //storing the pots//
    for (int i = 0; i < 4; i++) {
      int thisPot = potStates[i];
      if (abs(thisPot - synthPots[i]) > synthPotTol) {
        usbMIDI.sendControlChange(i + synthOffset2, thisPot, 1);
        synthPots[i] = thisPot;
      }

    }
  }
