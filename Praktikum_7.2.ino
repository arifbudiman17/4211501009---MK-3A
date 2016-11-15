int setCycles;
void set(int cycles){
char oldSREG;
int dutyCycle = cycles * 0.5;
if (dutyCycle < 6) {
dutyCycle = 6;
}
if (dutyCycle > 1015) {
dutyCycle = 1015;
}
if (cycles < 50) {
cycles = 50;
}
oldSREG = SREG;
cli();
ICR1 = cycles;
OCR1A = dutyCycle;
SREG = oldSREG;
}
void setup() {
TCCR1A = 0;
TCCR1B = _BV(WGM13);
TCCR1B &= ~(_BV(CS10) | _BV(CS11) | _BV(CS12));
TCCR1B |= _BV(CS10);
DDRB |= _BV(PORTB1);
TCCR1A |= _BV(COM1A1);
}
void loop() {
int temp_cycles = analogRead(A0);
if (temp_cycles != setCycles ) {
setCycles = temp_cycles;
set(setCycles);
}
}
