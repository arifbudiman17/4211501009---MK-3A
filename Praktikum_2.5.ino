/**************************************************************
                 ARIF BUDIMAN (4211501009)
                      MEKATRONIKA-3A
    PRAKTIKUM 2.5 FUNGSI DELAY PADA BUZZER WITH SWITCH
                   KONFIGURASI REGISTER
***************************************************************/
void setup(){
  DDRC=0x00;
  PORTC=0x01;
  DDRB=0x10;
}

void loop(){
  if(bit_is_clear(PINC,0)){
    PORTB=0x10;
  }
  else{
    PORTB=0x00;
  }
}

