

/* LOAD CELL */
//#include <HX711.h>
//#define DOUT  3
//#define CLK  2
//
//float calibrationFactor = -7050;
//HX711 scale(DOUT, CLK);
//
//void setup() {
//  Serial.begin(9600);
//  scale.set_scale();
//  scale.tare();
//  long zeroFactor;
//  do {
//    zeroFactor = scale.read_average();
//  } while (zeroFactor != -1);
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
//  pinMode(outPin, OUTPUT);
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
