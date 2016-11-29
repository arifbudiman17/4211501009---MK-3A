/* Projek Ohm Meter
 Arif Budiman
 4211501009
 MK - 3A
 */

const int pinADC = A0;
float nilaiADC = 0; 
float Vin = 5; //volt
float Vout = 0;//volt
float R1 = 56; //ohm
float R2 = 0; //ohm

void setup ()
{
  Serial.begin(9600);
}

void loop ()
{
  
  nilaiADC = analogRead(pinADC);  // baca Vout pada analog input pin A0
  Vout = (Vin*nilaiADC)/1023;    // konversi Vout ke volt
  R2 = ((Vin/Vout)-1) * R1;
  Serial.print("Nilai ADC =  ");
  Serial.println(nilaiADC);
  Serial.print("Vout =  "); //volt
  Serial.println(Vout);
  Serial.print("R2 =  "); //ohm                  
  Serial.println(R2); 
    Serial.print("\n");
  delay(1500);    
     
}
