/****************************************************************
                  ARIF BUDIMAN(4211501009)
                      MEKATRONIKA 3A
                  POLITEKNIK NEGERI BATAM
        PRAKTIKUM 3.3 Analog Input dengan Tegangan   
               Referensi Eksternal (1,1 Volt)
****************************************************************/
#include <LiquidCrystal.h> 
LiquidCrystal lcd(2,3,4,5,6,7);
 
void setup() {  
  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(0,0);  
  lcd.print("ADC Example on A0");
  analogReference(EXTERNAL);
  } 
 
void loop() {   
  unsigned int dataADC = analogRead(A0); 
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("Value = ");
  lcd.print(dataADC);
  delay(500); 
} 
