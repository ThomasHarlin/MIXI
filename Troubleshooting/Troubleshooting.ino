#include <Bounce2.h>
int buttonPins[] = {5, 6, 7, 8, 9, 10, 11, 12};
int buttonStates[] = {0, 0, 0, 0, 0, 0, 0, 0};
Bounce * buttons = new Bounce[8];


#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel strip(8, 4, NEO_RGB + NEO_KHZ800);

int mode = 0;

//bools to track when lights should be what colors
bool drumLights = false;
bool synthLights = false;
bool pedalLights = false;



//button 1
boolean drumButtons[] = {false, false, false, false, false, false};

int drumPots[] = {0, 0, 0, 0};
int drumPotTol = 10;

//button 2
boolean pedalButtons[] = {false, false, false, false, false, false};

int pedalPots[] = {0, 0, 0, 0};
int pedalPotTol = 10;

int pedalOffset = 20;
int pedalOffset2 = (8 + pedalOffset);
//button 3
boolean synthButtons[] = {false, false, false, false, false, false};

int synthPots[] = {0, 0, 0, 0};
int synthPotTol = 10;

int synthOffset = 40;
int synthOffset2 = (8 + synthOffset);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  strip.begin();
  strip.clear();
  initializeButtons();
  wakeUp();
}

void loop() {
  // put your main code here, to run repeatedly:

  updateButtons();
  updatePots();

  switch (screen) {
    case 0:
      wakeUp();
      break;
    case 1:
      drumBoard();
      break;
    case 2:
      synthBoard();
      break;
    case 3:
      pedalBoard();
      break;
  }

}
////////////////////////////////////////////////////////
void wakeUp() {
  //Fun animation on power on

  int x = 0;
  for (int j = 0; j < 255; j++) {
    for (int i = 0; i < strip.numPixels(); i++) {
      x = (16 + j) % 255;
      strip.setPixelColor(i, Wheel(x));
    }
    strip.show();
    delay(15);
  }
  strip.clear();
  drumLights = true;
  screen = 1;
}
////////////////////////////////////////////////////////////
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
////////////////////////////////////////////////////////////////
void initializeButtons() {
  for (int i = 0; i < 8; i++) {
    buttons[i].attach(buttonPins[i] , INPUT_PULLUP  );
    buttons[i].interval(15);
  }
}
////////////////////////////////////////////////////////////
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
    potStates[i] = mapPot;
  }
}
////////////////////////////////////////////////////////////////
void buttons1() {
  if (drumLights) {
    for (int i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, 68, 50, 170);
      if (i == 0) {
        strip.setPixelColor(i, 245, 158, 42);
      }
      if (i == 4) {
        strip.setPixelColor(i, 250, 22, 216);
      }
    }
    strip.show();
    drumLights = false;
  }


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

    if (curDrum == 1 && i == 0) {
      screen = 2; drumLights = false; synthLights = true;
    }
    if (curDrum == 1 && i == 4) {
      screen = 3; drumLights = false; pedalLights = true;
    }
  }
}
/////////////////////////////////////////////////////////////////////////
void buttons2() {
  if (pedalLights) {
    for (int i = 0; i < strip.numPixels(); i++) {

      //pedal color
      strip.setPixelColor(i, 250, 22, 216);
      if (i == 0) {
        //synth color
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
      screen = 2; pedalLights = false; drumLights = true;
    }
    if (curPedal == 1 && i == 4) {
      screen = 1; pedalLights = false; synthLights = true;
    }
  }
}
////////////////////////////////////////////////////////////////////////////
void buttons3() {
  if (synthLights) {
    for (int i = 0; i < strip.numPixels(); i++) {

      //synth color
      strip.setPixelColor(i, 245, 158, 42);
      if (i == 0) {
        //drum color
        strip.setPixelColor(i, 68, 50, 170);
      }
      if (i == 4) {
        //pedal color
        strip.setPixelColor(i, 250, 22, 216);
      }
    }
    strip.show();
    synthLights = false;
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
      screen = 2; synthLights = false; drumLights = true;
    }
    if (curSynth == 1 && i == 4) {
      screen = 1; synthLights = false; pedalLights = true;
    }
  }
}
