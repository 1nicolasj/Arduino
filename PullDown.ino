byte i = 0;

void setup(){
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
}

void loop(){
  i = digitalRead(2);
  if(i == HIGH){
    digitalWrite(3, HIGH);
  }else{
    digitalWrite(3, LOW); 
  }
}

