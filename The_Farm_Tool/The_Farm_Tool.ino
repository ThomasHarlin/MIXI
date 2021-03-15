#include <Bounce2.h>
int buttonPins[] = {5, 6, 7, 8, 9, 10, 11, 12};
int buttonStates[] = {0, 0, 0, 0, 0, 0, 0, 0};
Bounce * buttons = new Bounce[8];

int potPins[] = {A0, A1, A2, A3};
int potStates[] = {0, 0, 0, 0};

#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel strip(8, 4, NEO_RGB + NEO_KHZ800);


//state variable
int screen = 0;

//bools to track when lights should be what colors
bool drumLights = false;
bool synthLights = false;
bool pedalLights = false;



void setup() {
  Serial.begin(9600);
  strip.begin();
  strip.clear();
  initializeButtons();
  wakeUp();
}

void loop() {
  updateButtons();
//  printButtons();
  updatePots();
 // printPots();

  //state machine of control which "screen" im on
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
