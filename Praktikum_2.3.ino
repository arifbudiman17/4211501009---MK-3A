/**************************************************************
                 ARIF BUDIMAN (4211501009)
                      MEKATRONIKA-3A
           PRAKTIKUM 2.3 FUNGSI DELAY PADA BUZZER
***************************************************************/
void setup (){
  pinMode(12, OUTPUT);
}
void loop(){
  digitalWrite(12,HIGH);
  delay(1000);
  digitalWrite(12,LOW);
  delay(1000);
}

