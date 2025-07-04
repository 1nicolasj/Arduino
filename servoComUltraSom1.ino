#include <HCSR04.h>
#include <Servo.h>
#define TRIGGER 9
#define ECHO 8
#define SERVO 7
UltraSonicDistanceSensor distanceSensor(TRIGGER,ECHO);
Servo s;
int pos = 90;

void setup(){
  s.attach(SERVO);
  Serial.begin(9600);
  s.write(pos);
}

void loop(){
  int distancia = 0;
  distancia = distanceSensor.measureDistanceCm();
  Serial.println(distancia);
  
  if(distancia > pos){
    pos +=1;
    s.write(pos);
  }else if(distancia < pos){
    pos -=1;
    s.write(pos);
  }  
  delay(10);
}

