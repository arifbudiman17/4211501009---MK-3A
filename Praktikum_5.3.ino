/****************************************************************
                  ARIF BUDIMAN(4211501009)
                      MEKATRONIKA 3A
                  POLITEKNIK NEGERI BATAM
   PRAKTIKUM 5.3 Menerima Data dari UART dengan Sistem Pooling
       UART (Universal Asynchronous Receiver-Transmitter)
****************************************************************/
#include<LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);
String textFromSerial ="";
void setup() {
lcd.begin(16,2);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Data From Serial");
Serial.begin(9600);
}
void loop() {
while(Serial.available()>0) {
char data = Serial.read();
if(data == '\n'){
lcd.setCursor(0,1);
lcd.print(textFromSerial);
textFromSerial="";
}
else{
if(data!='\r'){
textFromSerial += data;
   }
  }
 }
}
