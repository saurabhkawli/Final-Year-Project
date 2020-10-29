#include <SoftwareSerial.h>

SoftwareSerial BT(2, 8);

String readvoice;

//LED
int red = A0;
int frontled = A1;
int rightled = A2;
int leftled = A3;

void setup() {

pinMode(red, OUTPUT);  
  pinMode(frontled, OUTPUT);
  pinMode(rightled, OUTPUT);
  pinMode(leftled, OUTPUT);

  BT.begin(9600);
  Serial.begin(9600);
}

void loop() {
  Serial.println("in loop");
  while (BT.available())
  {
    delay(10); //Delay added to make thing stable
    char c = BT.read(); //Conduct a serial read
    readvoice += c; //build the string- "forward", "reverse", "left" and "right"
    Serial.println("Here");
  }
  if (readvoice.length() > 0)
  {
    Serial.println(readvoice);
    if (readvoice == "*system check#")
    {
      glowlights();
      delay(500);
      closelights();
      
      delay(500);
      glowlights();
      delay(500);
      closelights();
      delay(500);
      
    }

    else if(readvoice == "*frontlight#" ||readvoice == "*front light#" )
    {
      delay(50);
      glowfront();
    }
    else if(readvoice == "*close front#" ||readvoice == "*close light#" )
    {
      delay(50);
      closefront();
    }
     else if (readvoice == "*night#")
    {
      glowlights();
    }

    else if (readvoice == "*morning#")
    {
      closelights();
    }
    readvoice = "";
  }

}

//LED
void glowlights()
{
  digitalWrite(frontled, HIGH);
  digitalWrite(red, HIGH);
  digitalWrite(rightled, HIGH);
  digitalWrite(leftled, HIGH);
}

void closelights()
{
  digitalWrite(frontled, LOW);
  digitalWrite(red,LOW);
  digitalWrite(rightled, LOW);
  digitalWrite(leftled, LOW);
}

void glowfront()
{
  digitalWrite(frontled, HIGH);
}

void closefront()
{
  digitalWrite(frontled, LOW);
}
