#include <PinChangeInt.h>
#include <PinChangeIntConfig.h>
#define PIN1 6
#define PIN2 A0
#define PIN3 4
int encoder1PhaseA = 6;
int encoder1PhaseB = 7;
int encoder1Position = 0;
int encoder2PhaseA = A0;
int encoder2PhaseB = A1;
int encoder2Position = 0;
int encoder3PhaseA = 4;
int encoder3PhaseB = 5;
int encoder3Position = 0;
int n,m,o = LOW;
void setup() {
 pinMode (encoder1PhaseA,INPUT);
 pinMode (encoder1PhaseB,INPUT);
 pinMode (encoder2PhaseA,INPUT);
 pinMode (encoder2PhaseB,INPUT);
 pinMode (encoder3PhaseA,INPUT);
 pinMode (encoder3PhaseB,INPUT);
 PCintPort::attachInterrupt(PIN1, readEncoder1,RISING);
 PCintPort::attachInterrupt(PIN2, readEncoder2,RISING);
 PCintPort::attachInterrupt(PIN3, readEncoder3,RISING);
 Serial.begin(9600);
}
void loop(){
 Serial.print ("Enc1=");
 Serial.print (encoder1Position);
 Serial.print ("\t");
 Serial.print ("Enc2=");
 Serial.print (encoder2Position);
 Serial.print ("\t");
 Serial.print ("Enc3=");
 Serial.println (encoder3Position);
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
void readEncoder3()
{
 o = digitalRead(encoder3PhaseA);
 if (o == HIGH) {
 if (digitalRead(encoder3PhaseB) == LOW) {
 encoder3Position--;
 } else {
 encoder3Position++;
 }
 }
}

