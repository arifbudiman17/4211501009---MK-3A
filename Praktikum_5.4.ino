/****************************************************************
                  ARIF BUDIMAN(4211501009)
                      MEKATRONIKA 3A
                  POLITEKNIK NEGERI BATAM
      PRAKTIKUM 5.4 Menerima Data UART dengan Interupsi
****************************************************************/
#include <LiquidCrystal.h>
#define FOSC 16000000
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
String dataSerial;
void initSerial(int baudrate) {
int ubrr = FOSC/16/baudrate-1;
// Mengisi register UBRR0H dan UBRR0L untuk menentukan baudrate
UBRR0H |= ubrr>>8;
UBRR0L |= ubrr;
// Mengaktifkan saluran transmitter dan receiver
UCSR0B |= (1<<RXEN0)|(1<<TXEN0);
// Menggunakan format data 8 bit
UCSR0C |= (0<<UCSZ02)|(1<<UCSZ01)|(1<<UCSZ00);
// Menggunakan 1 stop bit
UCSR0C |= (0<<USBS0);
// No Parity
UCSR0C |= (0<<UPM01)|(0<<UPM00);
// Mengaktifkan RX interrupt
UCSR0B |= (1<<RXCIE0);
}

// Rutin yang akan dijalankan jika terjadi interupsi
ISR(USART_RX_vect){
 char data = UDR0;
 if(data=='\n') {
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("Incoming Data");
 lcd.setCursor(0,1);
 lcd.print(dataSerial);
 dataSerial = "";
}
else{
 if(data!='\r') {
  dataSerial += data;
  }
 }
}
void setup() {
 initSerial(9600);
 lcd.begin(16,2);
 //lcd.clear();
 sei();
}
void loop() {
}
