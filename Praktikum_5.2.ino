/****************************************************************
                  ARIF BUDIMAN(4211501009)
                      MEKATRONIKA 3A
                  POLITEKNIK NEGERI BATAM
              PRAKTIKUM 5.2 Mengirim Data Byte
****************************************************************/
void setup() {
Serial.begin(115200);
}
void loop() {
Serial.write(0x00);
Serial.write(0x01);
Serial.write(0xF0);
Serial.write(0x1F);
Serial.write(0x2F);
delay(2000);
}
