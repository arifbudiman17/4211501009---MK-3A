#include <PinChangeInt.h>
#include <PinChangeIntConfig.h>
#define PIN1 4
#define PIN2 6
int encoder1PhaseA = 4;
int encoder1PhaseB = 5;
int encoder1Position = 0;
int encoder2PhaseA = 6;
int encoder2PhaseB = 7;
int encoder2Position = 0;
int n,m = LOW;
void setup() {
pinMode (encoder1PhaseA,INPUT);
pinMode (encoder1PhaseB,INPUT);
pinMode (encoder2PhaseA,INPUT);
pinMode (encoder2PhaseB,INPUT);
PCintPort::attachInterrupt(PIN1, readEncoder1,RISING);
PCintPort::attachInterrupt(PIN2, readEncoder2,RISING);
Serial.begin(9600);
}
void loop(){
Serial.print ("Enc1=");
Serial.print (encoder1Position);
Serial.print ("\t");
Serial.print ("Enc2=");
Serial.print (encoder2Position);
Serial.println ("\t");
}
void readEncoder1()
{
n = digitalRead(encoder1PhaseA);
if (n == HIGH) {
if (digitalRead(encoder1PhaseB) == LOW) {
  encoder1Position--;
} else {
encoder1Position++;
}
}
}
void readEncoder2()
{
m = digitalRead(encoder2PhaseA);
if (m == HIGH) {
if (digitalRead(encoder2PhaseB) == LOW) {
encoder2Position--;
} else {
encoder2Position++;
}
}
}


