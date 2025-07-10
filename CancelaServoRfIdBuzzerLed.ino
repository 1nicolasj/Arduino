#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define SS_PIN 10
#define RST_PIN 9
#define LED_VERDE 5
#define LED_VERMELHO 4
#define BUZZER 2

MFRC522 rfid(SS_PIN, RST_PIN);
Servo servo;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  servo.attach(3);
  servo.write(0);
  
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  
  digitalWrite(LED_VERMELHO, HIGH);
  
  Serial.println("Aproxime o cartao");
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent()) {
    return;
  }
  
  if (!rfid.PICC_ReadCardSerial()) {
    return;
  }
  
  String uid = "";
  for (int i = 0; i < rfid.uid.size; i++) {
    if (rfid.uid.uidByte[i] < 16) {
      uid += "0";
    }
    uid += String(rfid.uid.uidByte[i], HEX);
  }
  uid.toUpperCase();
  
  Serial.print("Cartao: ");
  Serial.println(uid);
  
  if (uid == "72ECC705") {
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
}