#include <PinChangeInt.h>
#include <PinChangeIntConfig.h>
#include <math.h>
#define PIN1 6
#define PIN2 A0
#define PIN3 4
boolean M1=8; //DIR
int E1=9; //PWM
boolean M2=11; //DIR
int E2=10; //PWM
boolean M3=2; //DIR
int E3=3; //PWM
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
float phi=3.14;
int tickPerRev=775;
int pulse1, pulse2, pulse3;
float rps1, rps2, rps3;
float XL, YL, thetaDot, theta;
float phiDot1, phiDot2, phiDot3;
float r = 50; //mm
float R = 125; //mm
float a1 = 30;
float a2 = 150;
float a3 = 270;
float x1,x2,x3,y1,y2,y3;
//PID 1
float Kp1=4; // osilasi di 15, set setengahnya
float Kd1=0.001;
float Ki1=0.1; // mengurangi sse
float dt=1;//0.016;
float setPoint1, PV1;
float outPID1, Sum1;
float minPID1 = -2.42;
float maxPID1 = 2.42;
float error1 = 0;
float error1_1 =0;
// PID 2
float Kp2=4; // osilasi di 15, set setengahnya
float Kd2=0.001;
float Ki2=0.1; // mengurangi sse
float setPoint2, PV2;
float outPID2, Sum2;
float minPID2 = -2.42;
float maxPID2 = 2.42;
float error2 = 0;
float error2_1 =0;
// PID 3
float Kp3=4; // osilasi di 15, set setengahnya
float Kd3=0.001;
float Ki3=0.1; // mengurangi sse
float setPoint3, PV3;
float outPID3, Sum3;
float minPID3 = -2.42;
float maxPID3 = 2.42;
float error3 = 0;
float error3_1 =0;
void setup() {
 //Setup Timer1 as PWM
 TCCR1B=TCCR1B&0xf8|0x01; // Pin9,Pin10 PWM 31250Hz
 TCCR2B=TCCR2B&0xf8|0x01; // Pin3,Pin11 PWM 31250Hz
 pinMode(M1, OUTPUT);
 pinMode(E1, OUTPUT);
 pinMode(M2, OUTPUT);
 pinMode(E2, OUTPUT);
 pinMode(M3, OUTPUT);
 pinMode(E3, OUTPUT);

TCCR0A = 0x00;
TCNT0 = 6;
TIFR0 = 0x00;
TIMSK0 = 0x01;
TCCR0A = 0x00;
TCCR0B = 0x07;
 pinMode (encoder1PhaseA,INPUT);
 pinMode (encoder1PhaseB,INPUT);
 pinMode (encoder2PhaseA,INPUT);
 pinMode (encoder2PhaseB,INPUT);
 pinMode (encoder3PhaseA,INPUT);
 pinMode (encoder3PhaseB,INPUT);
 PCintPort::attachInterrupt(PIN1, readEncoder1,RISING);
 PCintPort::attachInterrupt(PIN2, readEncoder2,RISING);
 PCintPort::attachInterrupt(PIN3, readEncoder3,RISING);

 Serial.begin(115200);
}
void loop(){
 XL = 80; YL = 80; thetaDot = 0; inverseKinematic(); 
 }
void inverseKinematic(){
 phiDot1 = (((-sin((theta+a1)*M_PI/180)*
 cos(theta*M_PI/180)*XL)+
 (cos((theta+a1)*M_PI/180)*
 cos(theta*M_PI/180)*YL)+
 (R*thetaDot))/r);
 phiDot2 = (((-sin((theta+a2)*M_PI/180)*
 cos(theta*M_PI/180)*XL)+
 (cos((theta+a2)*M_PI/180)*
 cos(theta*M_PI/180)*YL)+
 (R*thetaDot))/r);
 phiDot3 = (((-sin((theta+a3)*M_PI/180)*
 cos(theta*M_PI/180)*XL)+
 (cos((theta+a3)*M_PI/180)*
 cos(theta*M_PI/180)*YL)+
 (R*thetaDot))/r);
 theta = theta + thetaDot;

 if (phiDot1<0){ digitalWrite(M1,1);} else {digitalWrite(M1,0);}
 if (phiDot2<0){ digitalWrite(M2,1);} else {digitalWrite(M2,0);}
 if (phiDot3<0){ digitalWrite(M3,1);} else {digitalWrite(M3,0);}
 x1 = abs(phiDot1);
 x2 = abs(phiDot2);
 x3 = abs(phiDot3);
y1 = (21.26*x1*x1*x1*x1*x1)-(92.68*x1*x1*x1*x1)+(151.1*x1*x1*x1)-
(102.5*x1*x1)+(49.68*x1)+5.047;
y2 = (21.26*x2*x2*x2*x2*x2)-(92.68*x2*x2*x2*x2)+(151.1*x2*x2*x2)-
(102.5*x2*x2)+(49.68*x2)+5.047;
y3 = (21.26*x3*x3*x3*x3*x3)-(92.68*x3*x3*x3*x3)+(151.1*x3*x3*x3)-
(102.5*x3*x3)+(49.68*x3)+5.047;
 analogWrite(E1,y1);
 analogWrite(E2,y2);
 analogWrite(E3,y3);
 Serial.print(phiDot1); Serial.print(" ");
 Serial.print(phiDot2); Serial.print(" ");
 Serial.print(phiDot3); Serial.print(" ");
 Serial.print(y1); Serial.print(" ");
 Serial.print(y2); Serial.print(" ");
 Serial.println(y3);
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
void readEncoder3()
{
 o = digitalRead(encoder3PhaseA);
 if (o == HIGH) {
 if (digitalRead(encoder3PhaseB) == LOW) {
 encoder3Position--;
 pulse3--;
 } else {
 encoder3Position++;
 pulse3++;
 }
 }
}
ISR(TIMERO_OVF_vect)
{
 TCNT0 = 6;
 rps1 = (pulse1* (1 / 0.016))/tickPerRev;
 rps2 = (pulse2* (1 / 0.016))/tickPerRev;
 rps3 = (pulse3* (1 / 0.016))/tickPerRev;
 pulse1=0;
 pulse2=0;
 pulse3=0;
}

