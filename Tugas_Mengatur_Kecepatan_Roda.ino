#include <PinChangeInt.h>
#include <PinChangeIntConfig.h>

#define PIN1 4
#define PIN2 6
  boolean M1=8; //DIR
  int E1=9; //PWM
  boolean M2=11; //DIR
  int E2=10; //PWM
  
int encoder1PhaseA =4;
int encoder1PhaseB =5;
int encoder1Position =0;

int encoder2PhaseA =6;
int encoder2PhaseB =7;
int encoder2Position =0;
int n,m =LOW;
int tickPerRev=775;
int pulse1,pulse2;
float rpm1,rpm2;
float rps1,rps2;
float x1,y1,x2,y2;
float Kp=6; // osilasi di 15, set setengahnya
float Kd=0.01;
float Ki=1; // mengurangi sse
float dt=0.016;
float setPoint,setPoint2, PV1,PV2;
float outPID1, Sum1;
float outPID2,Sum2;
float minPID = 0;
float maxPID = 2.42;
float error = 0;
float error_1 =0;
float error2 = 0;
float error_2 =0;
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
  Serial.begin(115200);
}


void loop() {
 setPoint = 0.5; //rps
 setPoint2=0.3;
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
ISR(TIMER2_OVF_vect)        // interrupt service routine 
{  TCNT2 = 6;
  rps1 = (pulse1* (1 / 0.016))/tickPerRev;
  rps2 = -(pulse2* (1 / 0.016))/tickPerRev;
  pulse1=0;
  pulse2=0;
PV1 = rps1;
PV2=rps2;
error = setPoint -PV1;
error2 = setPoint2 -PV2;
Sum1 = Sum1 + error;
Sum2 = Sum2 + error2;
outPID1 = Kp*error + Ki*Sum1*dt + ((Kd/dt)*(error -error_1));
outPID2=Kp*error2 + Ki*Sum2*dt + ((Kd/dt)*(error2 -error_2));

if (outPID1 > maxPID) { outPID1 = maxPID;}
if (outPID1 < minPID) { outPID1 = minPID;}
if (outPID2 > maxPID) { outPID2 = maxPID;}
if (outPID2 < minPID) { outPID2 = minPID;}
error_1 = error;
error_2 = error2;
x1=outPID1;
x2=outPID2;
y1=(21.26*x1*x1*x1*x1*x1)-(92.68*x1*x1*x1*x1)+(151.1*x1*x1*x1)-(102.5*x1*x1)+(49.68*x1)+5.047;
y2=(21.26*x2*x2*x2*x2*x2)-(92.68*x2*x2*x2*x2)+(151.1*x2*x2*x2)-(102.5*x2*x2)+(49.68*x2)+5.047;
digitalWrite(M1,1);
analogWrite(E1,y1);
digitalWrite(M2,0);
analogWrite(E2,y2);
Serial.print (setPoint); Serial.print (" ");
  Serial.print (PV1); Serial.print (" ");
  Serial.print (outPID1); Serial.print (" ");
   Serial.print (y1); Serial.print (" ");
      Serial.print (setPoint2); Serial.print (" ");
  Serial.print (PV2); Serial.print (" ");
  Serial.print (outPID2); Serial.print (" ");
  Serial.println (y2);
}
