/****************************************************************
                    ARIF BUDIMAN (4211501009)
                      MEKATRONIKA -3A
                   POLITEKNIK NEGERI BATAM
                   TUGAS 3.2 MIKROKONTROLLER
****************************************************************/
int ledPin[] ={8,9,10,11};
int maxCount = 256;
int delayInterval = 1000;

void setup() {
  // put your setup code here, to run once:
  for (int i=8 ; i<12 ; i++)
  {
    pinMode(ledPin[i], OUTPUT);
  }
digitalWrite(A0, HIGH);
digitalWrite(A1, HIGH);
digitalWrite(A2, HIGH);

}

void loop() {
  // put your main code here, to run repeatedly:
  
  //for (int counter = 0; counter < maxCount;counter++)
  int counter =0;
while(counter < maxCount){
  if(digitalRead(A0)==LOW)
  {
    counter++;
    displayBinary(counter);
    delay(delayInterval);
    
  }
  if(digitalRead(A1)==LOW)
  {
    counter--;
    displayBinaryReverse(counter);
    delay(delayInterval);
    
  }
  }
}

void displayBinary(byte numToShow)
{
  for (int i=0; i < 8 ;i++)
  {
  if (bitRead(numToShow, i)==1)
  {
    digitalWrite(ledPin[i], HIGH);
  }
    else
    {
      digitalWrite(ledPin[i], LOW);
    }
}
}

void displayBinaryReverse(byte numToShow)
{
  for (int i=8; i >=0 ;i--)
  {
  if (bitRead(numToShow, i)==1)
  {
    digitalWrite(ledPin[i], HIGH);
  }
    else
    {
      digitalWrite(ledPin[i], LOW);
    }
}
}
