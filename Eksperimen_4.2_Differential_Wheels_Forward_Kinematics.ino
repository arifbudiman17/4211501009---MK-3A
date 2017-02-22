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
float r=143/2; //wheel radius
float phi=3.14;
int tickPerRev=775;
float d=290;
int timer2_counter;
int pulse1, pulse2;
float rpm1, rpm2;
float rps1, rps2;
float v,w;
float thetaDotL, thetaDotR;
float x1,x2,y1,y2;

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
void setup() {
 //Setup Timer1 as PWM output
 TCCR1B=TCCR1B&0xf8|0x01; // Pin9,Pin10 PWM 31250Hz
 pinMode(M1, OUTPUT);
 pinMode(E1, OUTPUT);
 pinMode(M2, OUTPUT);
 pinMode(E2, OUTPUT);

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
void loop(){
 v=100; //mm per second
 w=0; //deg per second
 w=w*(phi/180);
 thetaDotL = (1/(2*phi*r))*(v-(w*d/2));
 thetaDotR = (1/(2*phi*r))*(v+(w*d/2));
 setPoint1 = thetaDotL;
 setPoint2 = thetaDotR;

 // PID 1 Calculation
 PV1 = rps1;
 error1 = setPoint1 - PV1;
 Sum1 = Sum1 + error1;
 outPID1 = Kp1*error1 + Ki1*Sum1*dt + ((Kd1/dt)*(error1 -
 error1_1));
 if (outPID1 > maxPID1) { outPID1 = maxPID1;}
 if (outPID1 < minPID1) { outPID1 = minPID1;}
 error1_1 = error1;

 // PID 2 Calculation
 PV2 = rps2;
 error2 = setPoint2 - PV2;
 Sum2 = Sum2 + error2;
 outPID2 = Kp2*error2 + Ki2*Sum2*dt + ((Kd2/dt)*(error2 –
 error2_1));
 if (outPID2 > maxPID2) { outPID2 = maxPID2;}
 if (outPID2 < minPID2) { outPID2 = minPID2;}
 error2_1 = error2;

 x1=abs(outPID1);
 x2=abs(outPID2);
 y1=(21.26*x1*x1*x1*x1*x1)-(92.68*x1*x1*x1*x1)+(151.1*x1*x1*x1)-
 (102.5*x1*x1)+(49.68*x1)+5.047;
 y2=(21.26*x2*x2*x2*x2*x2)-(92.68*x2*x2*x2*x2)+(151.1*x2*x2*x2)-
 (102.5*x2*x2)+(49.68*x2)+5.047;

 if (outPID1<0){ digitalWrite(M1,0);} else {digitalWrite(M1,1);}
 if (outPID2<0){ digitalWrite(M2,1);} else {digitalWrite(M2,0);}
 analogWrite(E1,y1);
 analogWrite(E2,y2);

 Serial.print (v); Serial.print (" ");
 Serial.print (w); Serial.print (" ");
 Serial.print (thetaDotL); Serial.print (" ");
 Serial.print (thetaDotR); Serial.print (" ");
 Serial.print (outPID1); Serial.print (" ");
 Serial.print (outPID2); Serial.print (" ");
 Serial.print (y1); Serial.print (" ");
 Serial.println (y2);
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
 }

