//Leonardo de Oliveira / Nicolas Jose
//Trabalho final de Sistemas Embarcados

#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define SS_PIN 10
#define RST_PIN 9
#define LED_VERDE 5
#define LED_VERMELHO 4
#define BUZZER 2
#define SERVO_PIN 3
#define TRIG_PIN 6
#define ECHO_PIN 7

MFRC522 rfid(SS_PIN, RST_PIN);
Servo servo;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();

    Serial.println("Testando sensor...");
  long teste = medirDistancia();
  Serial.print("Distância: ");
  Serial.println(teste);

  servo.attach(SERVO_PIN);
  servo.write(90); // inicia aberto

  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  digitalWrite(LED_VERDE, HIGH);
  digitalWrite(LED_VERMELHO, LOW);

  Serial.println("Sistema iniciado. Aguardando veículo...");
}

void loop() {
  long distancia = medirDistancia();

  if (distancia > 0 && distancia < 30) {
    servo.write(0);
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_VERMELHO, HIGH);
    Serial.println("Veículo detectado. Aguardando cartão...");

    if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
      String uid = "";
      for (int i = 0; i < rfid.uid.size; i++) {
        if (rfid.uid.uidByte[i] < 16) uid += "0";
        uid += String(rfid.uid.uidByte[i], HEX);
      }
      uid.toUpperCase();

      Serial.print("Cartão: ");
      Serial.println(uid);

      if (uid == "72ECC705") {  // UID do nosso cartao
        Serial.println("Acesso liberado");

        digitalWrite(LED_VERMELHO, LOW);
        digitalWrite(LED_VERDE, HIGH);
        tone(BUZZER, 1000);
        delay(500);
        noTone(BUZZER);

        servo.write(90); 
        delay(6000);
        servo.write(0);  

        digitalWrite(LED_VERDE, LOW);
        digitalWrite(LED_VERMELHO, HIGH);
      } else {
        Serial.println("Acesso negado");
        tone(BUZZER, 300);
        delay(1000);
        noTone(BUZZER);
      }

      rfid.PICC_HaltA(); 
    }
  } else {
    servo.write(90);
    digitalWrite(LED_VERDE, HIGH);
    digitalWrite(LED_VERMELHO, LOW);
  }

  delay(200);
}

long medirDistancia() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duracao = pulseIn(ECHO_PIN, HIGH);
  long distancia = duracao * 0.034 / 2;
  return distancia;
}