int led = 13;

void setup() {
pinMode(led, OUTPUT);
Serial.begin(9600);
}
void loop() {
digitalWrite(led,HIGH);
delay(100);
digitalWrite(led,LOW);
delay(100);
}


