void setup() { 
Serial.begin(9600);
Serial.println ("========== Fungsi Matematika ========== =");
Serial.print("cos(90) = ");	Serial.println(cos(90*0.01745329));
Serial.print("sin(45) = ");	Serial.println(sin(45*0.01745329));
Serial.print("tan(90) = ");	Serial.println(tan(90*0.01745329));
Serial.print("atan(90) = ");	Serial.println(atan(90*0.01745329));
Serial.print("atan2(90,10) = ");	Serial.println(atan2(90,10*0.01745329));
Serial.print("sqrt(9) = ");	Serial.println(sqrt(9));
Serial.print("exp(9) = ");	Serial.println(exp(9));
Serial.print("log(100) = ");	Serial.println(log(100));
Serial.print("log10(100) = ");	Serial.println(log10(100));
Serial.print("pow(9,2) = ");	Serial.println(pow(9,2));
Serial.print("square(9) = ");	Serial.println(sqrt(9));
Serial.print("fabs(-1.5) = ");	Serial.println(fabs(-1.5));
Serial.print("fmod(1.2334,2) = ");	Serial.println(fmod(1.2334,2));
}

void loop() 
{
}




