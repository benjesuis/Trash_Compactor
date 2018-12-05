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
const int switchOut = A1;
const int switchIn = A2;
const int led = A3;
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
  scale.set_scale();
  scale.tare();
}

void loop() {
  analogWrite(switchOut, 255);
  //Serial.println(analogRead(switchIn));
  if(analogRead(switchIn) > 900) {
    switched = true;
  } else {
    switched = false;
  }
  //checkDistance();
  while(switched) {
    digitalWrite(lockPin, HIGH);
    Serial.println(analogRead(switchIn));
    if(analogRead(switchIn) > 900) {
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
    delay(1000);
    digitalWrite(lockPin, LOW);
    digitalWrite(valvePin, LOW);
    analogWrite(led, 0);
    justCompacted = false;
  }
}

void checkSwitch() {
  //Serial.println(analogRead(switchIn));
  switched = analogRead(switchIn > 1010) ? true : false;
  //Serial.println(switched);
}

void checkDistance() {
  distance = analogRead(distPin);
  if (distance > 350) {
    analogWrite(led, 255);
  } else {
    analogWrite(led, 0);
  }
}

void checkTension() {
  scale.set_scale(7050);
  Serial.println(scale.get_units(), 1);
}
