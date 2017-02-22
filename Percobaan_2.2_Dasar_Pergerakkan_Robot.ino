boolean M1=8; //DIR
int E1=9; //PWM
boolean M2=11; //DIR
int E2=10; //PWM
void setup(){
TCCR1B=TCCR1B&0xf8|0x01; // Pin9,Pin10 PWM 31250Hz
pinMode(M1, OUTPUT);
pinMode(E1, OUTPUT);
pinMode(M2, OUTPUT);
pinMode(E2, OUTPUT);
}
void loop(){
digitalWrite(M1,1);
analogWrite(E1,30);
digitalWrite(M2,0);
analogWrite(E2,30);
}
