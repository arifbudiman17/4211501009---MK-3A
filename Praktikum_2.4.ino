/**************************************************************
                 ARIF BUDIMAN (4211501009)
                      MEKATRONIKA-3A
    PRAKTIKUM 2.4 FUNGSI DELAY PADA BUZZER WITH SWITCH
***************************************************************/
void setup(){
  pinMode(A0, INPUT);
  digitalWrite(A0, HIGH);
  pinMode(12, OUTPUT);
}
void loop(){
  if(digitalRead(A0)==LOW){
    digitalWrite(12, 1);
  }
  else{
    digitalWrite(12, LOW);
  }
}

