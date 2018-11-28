/*  
 *   Boston University
 *   EK 210 Section E1
 *   Team Bronze: Trash Compactor
 *   Written By: Ben Livney
*/

#include <HX711.h>
const int motorPin = 5;
const int valvePin = 6;
const int lockPin = 9;
const int distPin = A0;
const int switchOut = A1;
const int switchIn = A2;
const int led = A3;
HX711 scale(3, 2);

int distance;
bool switched;
unsigned long timer;
unsigned long zeroTimer;

void poll();
void compact();
void reset();

void setup() {
  Serial.begin(9600);
  switched = false;
  distance = -1;
  pinMode(motorPin, OUTPUT);
  pinMode(valvePin, OUTPUT);
  pinMode(lockPin, OUTPUT);
  scale.set_scale();
  scale.tare();
}

void loop() {
  timer = millis();
  analogWrite(switchOut, 255);
  poll();
  while (switched && (timer - zeroTimer) > (1000 * 60 * 2.5)) {
    timer = millis();
    analogWrite(switchOut, 255);
    analogWrite(led, 255);
    compact();
  }
  reset();
}

void poll() {
  scale.set_scale(7050);
  Serial.println(scale.get_units(), 1);
  distance = analogRead(distPin);
  if (distance > 350) {
    analogWrite(led, 255);
  }
  if (analogRead(switchIn) > 200) {
    switched = true;
    zeroTimer = timer;
  }
}

void compact() {
  digitalWrite(motorPin, HIGH);
  digitalWrite(lockPin, HIGH);
  if (analogRead(switchIn) < 200) {
    switched = false;
  }
}

void reset() {
  digitalWrite(motorPin, LOW);
  digitalWrite(valvePin, HIGH);
  delay(1000 * 60 * 2.5);
  while(switched);
  digitalWrite(lockPin, LOW);
}



/* MOTOR */
//const int motorPin = 3;
//const int valvePin = 5;
//const int lockPin = 6;
//
//void setup() {
//  pinMode(motorPin, OUTPUT);
//  pinMode(valvePin, OUTPUT);
//  pinMode(lockPin, OUTPUT);
//
//  pinMode(LED_BUILTIN, OUTPUT);
//  Serial.begin(9600);
//}
//
//void loop() {
//  digitalWrite(motorPin, HIGH);
//  digitalWrite(valvePin, HIGH);
//  digitalWrite(lockPin, HIGH);
//  digitalWrite(LED_BUILTIN, HIGH);
//  delay(500);
//  digitalWrite(motorPin, LOW);
//  digitalWrite(valvePin, LOW);
//  digitalWrite(lockPin, LOW);
//  digitalWrite(LED_BUILTIN, LOW);
//  delay(1500);
//}


/* LOAD CELL */
//#include <HX711.h>
//#define DOUT  3
//#define CLK  2
//
//float calibrationFactor = 70.5;
//HX711 scale(DOUT, CLK);
//
//void setup() {
//  Serial.begin(9600);
//  scale.set_scale();
//  scale.tare();
//  long zeroFactor;
//  zeroFactor = scale.read_average();
//  Serial.println(zeroFactor);
//}
//
//void loop() {
//  scale.set_scale(calibrationFactor);
//  Serial.println(scale.get_units(), 1);
//}


/* IR SENSOR */
//const int distPin = A0;
//
//void setup() {
//  Serial.begin(9600);
//}
//
//void loop() {
//  int distance = analogRead(distPin);
//  if (distance <= 75) distance = 0;
//  if (distance > 400) {
//    Serial.println("Compact");
//  } else {
//    Serial.println(distance);
//  }
//}
