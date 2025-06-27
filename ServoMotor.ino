#include <Servo.h>
#define SERVO 9

Servo s;
int pos;

void setup() {
  s.attach(SERVO);
  Serial.begin(9600);
  s.write(0); // servo motocomeca em 0 graus
}

void loop() {
  for(pos = 0; pos < 180; pos++){
    s.write(pos); //dentro do objeto s, escreva pos
    delay(30);
  }
    for(pos = 180; pos >= 0; pos--){
    s.write(pos);
    delay(30);
    }
}
