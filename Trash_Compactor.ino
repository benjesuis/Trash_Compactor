/*  
 *   Boston University
 *   EK 210 Section E1
 *   Team Bronze: Trash Compactor
 *   Written By: Ben Livney
*/

#include <HX711.h>
const int valvePin = 3;
const int lockPin = 6;
const int distPin = A0;
const int controlsSwitch = 10;
const int led = 2;
HX711 scale(3, 2);

int distance;
bool switched;
bool justCompacted;

void checkDistance();
void checkSwitch();
void checkTension();

void setup() {
  Serial.begin(9600);
  Serial.println("Initializing...");
  switched = false;
  justCompacted = false;
  distance = -1;
  pinMode(valvePin, OUTPUT);
  pinMode(lockPin, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(controlsSwitch, INPUT_PULLUP);
  scale.set_scale();
  scale.tare();
}

void loop() {
  //Serial.println(analogRead(switchIn));
  if(digitalRead(controlsSwitch) == HIGH) {
    switched = true;
  } else {
    switched = false;
  }
  //checkDistance();
  while(switched) {
    digitalWrite(lockPin, HIGH);
    if(digitalRead(controlsSwitch) == HIGH) {
      switched = true;
    } else {
      switched = false;
    }
    //checkTension();
    // motor gets turned on here externally
    justCompacted = true;
  }
  if (justCompacted) {
    digitalWrite(valvePin, HIGH);
    delay(1000 * 10);
    digitalWrite(lockPin, LOW);
    digitalWrite(valvePin, LOW);
    digitalWrite(led, LOW);
    justCompacted = false;
  }
}

void checkDistance() {
  distance = analogRead(distPin);
  if (distance > 350) {
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW);
  }
}

void checkTension() {
  scale.set_scale(7050);
  Serial.println(scale.get_units(), 1);
}
