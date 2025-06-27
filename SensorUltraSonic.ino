#include <HCSR04.h>
#define TRIGGER 9
#define ECHO 8
UltraSonicDistanceSensor distanceSensor(TRIGGER,ECHO);

void setup(){
  Serial.begin(9600);
}

void loop(){
  int distancia = 0;
  distancia = distanceSensor.measureDistanceCm();
  Serial.println(distancia);
  delay(100);
}