#include <Servo.h>

const int botaoEsquerda = 8; 
const int botaoDireita  = 7;

Servo s;

int posicao = 90; //POS INICIAL

void setup() {
  pinMode(botaoEsquerda, INPUT_PULLUP);
  pinMode(botaoDireita, INPUT_PULLUP);
  
  s.attach(9); 
  s.write(posicao); 

  Serial.begin(9600);
}

void loop() {
  if (digitalRead(botaoEsquerda) == LOW) {
    Serial.println("Girando para a ESQUERDA");
    if(posicao < 180){
      posicao += 1;
      s.write(posicao);
    }
  }

  if (digitalRead(botaoDireita) == LOW) {
    Serial.println("Girando para a DIREITA");
    if(posicao > 0){
      posicao -= 1;
      s.write(posicao);
    }
  }
}

