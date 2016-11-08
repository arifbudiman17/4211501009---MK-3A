void setup(){
  Serial.begin(9600);
  TCCR1A=0x00;
  TCCR1B=0x06;
  TCNT1H=0x00;
  TCNT1L=0x00;
  ICR1H=0x00;
  ICR1L=0x00;
  OCR1AH=0x00;
  OCR1AL=0x00;
  OCR1BH=0x00;
  OCR1BL=0x00;
}

void loop(){
  Serial.print("Nilai TCNT1 = ");
  Serial.println(TCNT1,DEC);
  delay(100);
}
