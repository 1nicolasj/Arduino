/*
 * codigo verifica cada indice (char) do array (string)
 */
const unsigned int MAX_MESSAGE_LENGTH = 12;
void setup() {
  Serial.begin(9600);
}
void loop() {
  while(Serial.available() > 0){
    static char message[MAX_MESSAGE_LENGTH];
    static unsigned int message_pos = 0;
    char inByte = Serial.read();
    if(inByte != '\n' && (message_pos < MAX_MESSAGE_LENGTH - 1)){
      message[message_pos] = inByte;
      message_pos++;
    }else{
      message[message_pos] = '\0';
      Serial.println(message);
      message_pos = 0;
    }
  }
}


