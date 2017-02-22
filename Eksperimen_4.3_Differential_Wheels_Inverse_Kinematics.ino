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

float sL,sR,s;
float r=143/2; //wheel radius
float phi=3.14;
int tickPerRev=775;
float PHI;
float d=290;

int timer2_counter;
int pulse1, pulse2;
float rpm1, rpm2;
float rps1, rps2;

float v,w;
void setup() 
{
 //Setup Timer2 to fire every 1.6ms
 TCCR2B = 0x00; //Disable Timer2 while we set it up
 TCNT2 = 6; //Reset Timer Count to 6 out of 255
 TIFR2 = 0x00; //Timer2 INT Flag Reg: Clear Timer Overflow Flag
 TIMSK2 = 0x01; //Timer2 INT Reg: Timer2 Overflow Interrupt Enable
 TCCR2A = 0x00; //Timer2 Control Reg A: Wave Gen Mode normal
 TCCR2B = 0x07; // N=1024
 pinMode (encoder1PhaseA,INPUT);
 pinMode (encoder1PhaseB,INPUT);
 pinMode (encoder2PhaseA,INPUT);
 pinMode (encoder2PhaseB,INPUT);
 PCintPort::attachInterrupt(PIN1, readEncoder1,RISING);
 PCintPort::attachInterrupt(PIN2, readEncoder2,RISING);
 Serial.begin(19200);
}

void loop()
{
  v = 2*phi*r*((rps1/2)+(rps2/2));
 w = 2*phi*r*(-(rps1/d)+(rps2/d));
 Serial.print (rps1); Serial.print (" ");
 Serial.print (rps2); Serial.print (" ");
 Serial.print (v); Serial.print (" ");
 Serial.println (w);   
}

void readEncoder1()
{
 n = digitalRead(encoder1PhaseA);
 if (n == HIGH) {
 if (digitalRead(encoder1PhaseB) == LOW) {
 encoder1Position--;
 pulse1--;
 } else {
 encoder1Position++;
 pulse1++;
 }
 }
}

void readEncoder2()
{
 m = digitalRead(encoder2PhaseA);
 if (m == HIGH) {
 if (digitalRead(encoder2PhaseB) == LOW) {
 encoder2Position--;
 pulse2--;
 } else {
 encoder2Position++;
 pulse2++;
 }
 }
}

ISR(TIMER2_OVF_vect) // interrupt service routine
{
 TCNT2 = 6; // 0.016s;
 rps1 = (pulse1* (1 / 0.016))/775;
 rps2 = -(pulse2* (1 / 0.016))/775;
 rpm1 = 60*rps1;
 rpm2 = 60*rps2;
 pulse1=0;
 pulse2=0; 
 
}
