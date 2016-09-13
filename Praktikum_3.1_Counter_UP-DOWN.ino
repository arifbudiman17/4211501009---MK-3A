/****************************************************************
                    ARIF BUDIMAN (4211501009)
                        MEKATRONIKA -3A
                     POLITEKNIK NEGERI BATAM
                    TUGAS 3.1 MIKROKONTROLLER
****************************************************************/
//int i=8;
void setup() {
  // put your setup code here, to run once:
pinMode(8, OUTPUT);
pinMode(9, OUTPUT);
pinMode(10, OUTPUT);
pinMode(11, OUTPUT);
pinMode(A0, OUTPUT);
pinMode(A1, OUTPUT);
pinMode(A2, OUTPUT);
digitalWrite(A0, HIGH);
digitalWrite(A1, HIGH);
digitalWrite(A2, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int x=0;x<16;x++){
  int i=7;
while(i<12){
if(digitalRead(A0)==LOW){
  i++;
  digitalWrite(i, HIGH);      
  delay(500);
  digitalWrite(i, LOW);      
  delay(500);
  }
   else if(digitalRead(A1)==LOW){
    i--;
    digitalWrite(i,HIGH);
    delay(500);
  digitalWrite(i, LOW);      
  delay(500);
    }}}
   
}        
