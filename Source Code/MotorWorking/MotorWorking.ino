int In1=7;
int In2=6;
int In3=4;
int In4=5;
void setup() 
{
  pinMode(In1,OUTPUT);
  pinMode(In2,OUTPUT);
  pinMode(In3,OUTPUT);
  pinMode(In4,OUTPUT);
}
void loop()
{
    digitalWrite(In1,HIGH);
    digitalWrite(In2,LOW);
    digitalWrite(In3,HIGH);
    digitalWrite(In4,LOW);
    delay(5000);
    digitalWrite (In1, LOW);
    digitalWrite (In2, LOW);
    digitalWrite (In3, LOW);
    digitalWrite (In4, LOW);
    delay (100);
}
