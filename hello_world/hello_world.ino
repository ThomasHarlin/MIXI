#include <Bounce2.h>

Bounce button1 = Bounce();

int knob = A0;
int lastKnob=0;   
int knobTol=10;

bool button1Toggle = false;


void setup() {
  Serial.begin(9600);
 button1.attach(15,INPUT);
 button1.interval(5);
}

void loop() {
button1.update();

if(button1.rose()){
  button1Toggle = !button1Toggle;
  if(button1Toggle){usbMIDI.sendControlChange(1,127,1);}
  else{usbMIDI.sendControlChange(1,0,1);}
}

int thisKnob = analogRead(knob);
if(abs(thisKnob-lastKnob)>knobTol){
  int knobOut = map(thisKnob, 0, 1023, 0, 127);
  usbMIDI.sendControlChange(2,knobOut,1);
  lastKnob = thisKnob;
}

while(usbMIDI.read()){}
delay(5);
}
