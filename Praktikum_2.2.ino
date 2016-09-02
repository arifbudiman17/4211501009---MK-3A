/**************************************************************
                 ARIF BUDIMAN (4211501009)
                      MEKATRONIKA-3A
    PRAKTIKUM 2.2 PEMROGRAMAN DIGITAL OUTPUT MENGGUNAKAN
                   KONFIGURASI REGISTER
***************************************************************/
void setup() {
  DDRB=0x3F;
}
void loop(){
  PORTB=0x07;
}

