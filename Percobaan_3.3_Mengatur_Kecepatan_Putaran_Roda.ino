#include <PinChangeInt.h>
#include <PinChangeIntConfig.h>
#define PIN1 4
#define PIN2 6
boolean M1=8; //DIR
int E1=9; //PWM
boolean M2=11; //DIR
int E2=10; //PWM
int encoder1PhaseA = 4;
int encoder1PhaseB = 5;
int encoder1Position = 0;
int encoder2PhaseA = 6;
int encoder2PhaseB = 7;
int encoder2Position = 0;
int n,m = LOW;
int tickPerRev=775;
int pulse1, pulse2;
float rps1, rps2;
float x,y;
float Kp=6; // osilasi di 15, set setengahnya
float Kd=0.01;
float Ki=1; // mengurangi sse
float dt=0.016;
float setPoint, PV;
float outPID, Sum;
float minPID = 0;
float maxPID = 2.42;
float error = 0;
float error_1 =0;
void setup() {
//Setup Timer1 as PWM output
TCCR1B=TCCR1B&0xf8|0x01; // Pin9,Pin10 PWM 31250Hz
pinMode(M1, OUTPUT);
pinMode(E1, OUTPUT);
pinMode(M2, OUTPUT);
pinMode(E2, OUTPUT);
//Setup Timer2 to fire every 16 ms
TCCR2B = 0x00; //Disbale Timer2 while we set it up
TCNT2 = 6; //256-((16MHz*16 ms)/1024)
TIFR2 = 0x00; //Timer2 INT Flag Reg: Clear Timer Overflow Flag
TIMSK2 = 0x01; //Timer2 INT Reg: Timer2 Overflow Interrupt Enable
TCCR2A = 0x00; //Timer2 Control Reg A: Wave Gen Mode normal
TCCR2B = 0x07;
pinMode (encoder1PhaseA,INPUT);
pinMode (encoder1PhaseB,INPUT);
pinMode (encoder2PhaseA,INPUT);
pinMode (encoder2PhaseB,INPUT);
PCintPort::attachInterrupt(PIN1, readEncoder1,RISING);
PCintPort::attachInterrupt(PIN2, readEncoder2,RISING);
Serial.begin(19200);
}
void loop(){
setPoint = 0.5; //rps
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
TCNT2 = 6;
rps1 = (pulse1* (1 / 0.016))/tickPerRev;
rps2 = -(pulse2* (1 / 0.016))/tickPerRev;
pulse1=0;
pulse2=0;
PV = rps1;
error = setPoint - PV;
Sum = Sum + error;
outPID = Kp*error + Ki*Sum*dt + ((Kd/dt)*(error - error_1));
if (outPID > maxPID) { outPID = maxPID;}
if (outPID < minPID) { outPID = minPID;}
error_1 = error;
x=outPID;
y=(21.26*x*x*x*x*x)-(92.68*x*x*x*x)+(151.1*x*x*x)-
(102.5*x*x)+(49.68*x)+5.047;
digitalWrite(M1,1);
analogWrite(E1,y);
Serial.print (setPoint); Serial.print (" ");
Serial.print (PV); Serial.print (" ");
Serial.print (outPID); Serial.print (" ");
Serial.println (y);
}
