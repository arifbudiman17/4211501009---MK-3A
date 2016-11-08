#include<LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);
unsigned int jam, menit, detik;
/*unsigned int jam = 14;
  unsigned int menit = 36;
  unsigned int detik = 00;
*/boolean led=0;

ISR(TIMER1_OVF_vect){
  TCNT1H=0xC2;
  TCNT1L=0xf7;
  detik++;
  if(detik>=60){
    detik=0;
    menit++;
    if(menit>=60){
      menit=0;
      jam++;
      if(jam>=24){
        jam=0;
      }
    }
  }
}
void initTimer1(){
  TCCR1A=0x00;
  TCCR1B=0x05;
  TCNT1H=0xC2;
  TCNT1L=0xF7;
  ICR1H=0x00;
  ICR1L=0x00;
  OCR1AH=0x00;
  OCR1AL=0x00;
  OCR1BH=0x00;
  OCR1BL=0x00;
  TIMSK1=0x01;
  sei();
}
void setup(){
  lcd.begin(16,2);
  lcd.clear();
  initTimer1();
}
void loop(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("jam Digital");
  lcd.setCursor(0,1);
  lcd.print(jam,DEC);
  lcd.print(":");
  lcd.print(menit,DEC);
  lcd.print(":");
  lcd.print(detik,DEC);
  delay(500);
}
