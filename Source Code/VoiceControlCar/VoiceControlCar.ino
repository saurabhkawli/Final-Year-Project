#include <Servo.h>
#include <SoftwareSerial.h>

SoftwareSerial BT(0, 1);

String readvoice;

//L298N
const int In1 = 7;
const int In2 = 6;
const int In3 = 4;
const int In4 = 5;

//sensor pins
#define trigPin 11
#define echoPin 12

//LED
int red = A0;
int frontled = A1;
int rightled = A2;
int leftled = A3;

const int ldr = A4;  // LDR pin

int distance, duration;

Servo servo;  //servo

void setup()
{
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(red, OUTPUT);  
  pinMode(frontled, OUTPUT);
  pinMode(rightled, OUTPUT);
  pinMode(leftled, OUTPUT);

  pinMode(ldr, INPUT);   //initialize the LDR pin as an input

  servo.attach(10);
  servo.write(90);
  delay(1000);
  
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  
  BT.begin(9600);
  Serial.begin(9600);
}

void loop()
{
  
  while (BT.available())
  {
    delay(10); //Delay added to make thing stable
    char c = BT.read(); //Conduct a serial read
    readvoice += c; //build the string- "forward", "reverse", "left" and "right"
    //Serial.print("Available!!");
  }
  
  int stat = analogRead(ldr);   //read the status of the LDR value
  if (stat <=400) 
  {
    glowfront(); //turn LED on
    Serial.println("Lights are off, LED is ON");
  }
  else 
  {
    closefront();//turn LED off
    Serial.println("Lights are on");
  }
  
  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);

  distance = readPing();
  delay(100);
  Serial.print("Distance ");
  Serial.print(distance);
  Serial.println(" cm");

  //Code for Voice Commands
  if (readvoice.length() > 0)
  {
    //Serial.print("Here "+readvoice);
    Serial.println(readvoice);
    if (readvoice == "*go#")
    {
      ahead();
      again:
      while (BT.available())
      {
        delay(50);
        char c = BT.read();
        readvoice += c;
      }
      distance = readPing();
      delay(50);
      Serial.print("Distance in go ");
      Serial.print(distance);
      Serial.println(" cm");
      delay(50);
      if (distance <= 20 || readvoice == "*stop#")
      {
        moveStop();
        delay(100);
      }
      else
      {
        readvoice = "";
        goto again;
      }
    }
    
    else if (readvoice == "*go back#")
    {
      back();
      
    }
    else if (readvoice == "*back#" || readvoice == "*backup#")
    {
      back();
      delay(5000);
      moveStop();
    }
    
    else if (readvoice == "*left#")
    {
      digitalWrite(leftled, HIGH);
      distanceLeft = lookLeft();
      delay(300);
      if (distanceLeft <= 20)
      {
        digitalWrite(red, HIGH);
        delay(500);
        digitalWrite(red, LOW);
        delay(500);
        digitalWrite(red, HIGH);
        delay(500);
        digitalWrite(red, LOW);
        delay(500);
        digitalWrite(red, HIGH);
        delay(500);
        digitalWrite(red, LOW);
        delay(50);
      }
      else
      {
        left();
      }
      digitalWrite(leftled, LOW);
    }

    else if (readvoice == "*right#")
    {
      digitalWrite(rightled, HIGH);
      distanceRight = lookRight();
      delay(300);
      if (distanceRight <= 20)
      {
        digitalWrite(red, HIGH);
        delay(500);
        digitalWrite(red, LOW);
        delay(500);
        digitalWrite(red, HIGH);
        delay(500);
        digitalWrite(red, LOW);
        delay(500);
        digitalWrite(red, HIGH);
        delay(500);
        digitalWrite(red, LOW);
        delay(50);
      }
      else
      {
        right();
      }
      digitalWrite(rightled, LOW);
    }
    
    else if(readvoice == "*keep watch#" || readvoice == "*keepwatch#")
    {
      anotheragain:
      while (BT.available())
      {
        delay(50);
        char c = BT.read();
        readvoice += c;
      }
      if (distance <= 20)
      {
        moveStop();
        delay(300);
        back();
        delay(400);
        moveStop();
        delay(300);
        distanceRight = lookRight();
        delay(300);
        distanceLeft = lookLeft();
        delay(300);
        if (distance >= distanceLeft)
        {
          right();
          moveStop();
        }
        else
        {
          left();
          moveStop();
        }
      }
      else
      {
        ahead(); 
      }
      distance = readPing();
      Serial.print("I'm Watching ");
      Serial.print(distance);
      Serial.println(" cm");
      delay(100);
      if (readvoice == "*stop#")
      {
        moveStop();
        delay(100);
      }
      else
      {
        readvoice = "";
        goto anotheragain;
        
      }
    }
    
    else if (readvoice == "*round#")
    {
      circle();
    }

    //LIGHTS
    else if(readvoice == "*frontlight#" || readvoice == "*front light#" )
    {
      delay(50);
      glowfront();
    }
    else if(readvoice == "*close front#" || readvoice == "*close light#" )
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

    else if (readvoice == "*red on#" || readvoice == "*redon#")
    {
      digitalWrite(red, HIGH);
    }

    else if(readvoice == "*red of#" || readvoice == "*redoff#" || readvoice == "*red off#" || readvoice == "*redof#")
    {
      digitalWrite(red, LOW);
    }

    else if (readvoice == "*systemcheck#" || readvoice == "*system check#")
    {
      ahead();
      delay(1000);
      moveStop();
      delay(200);
      back();
      delay(1000);
      moveStop();
      delay(50);
      lookRight();
      delay(500);
      lookLeft();
      delay(500);
      digitalWrite(frontled, HIGH);
      delay(500);
      digitalWrite(frontled, LOW);
      delay(200);
      digitalWrite(red, HIGH);
      delay(500);
      digitalWrite(red,LOW);
      delay(200);
      digitalWrite(rightled, HIGH);
      delay(500);
      digitalWrite(rightled, LOW);
      delay(200);
      digitalWrite(leftled, HIGH);
      delay(500);
      digitalWrite(leftled, LOW);
      delay(200);
      glowlights();
      delay(1000);
      closelights();
      delay(200);
      glowlights();
      delay(1000);
      closelights();
      delay(200);
      glowlights();
      delay(1000);
      closelights();
      delay(200);
      glowlights();
      delay(1000);
      closelights();
      delay(200);
      
    }
  
    //STOP
    else if (readvoice == "*stop#")
    {
      moveStop();
    }
    readvoice = "";
  }
}

int lookRight()
{
  servo.write(0);
  delay(500);
  int distance = readPing();
  delay(100);
  servo.write(90);
  Serial.print("Right Distance ");
  Serial.print(distance);
  Serial.println(" cm");
  return distance;
  delay(100);
}

int lookLeft()
{
  servo.write(180);
  delay(500);
  int distance = readPing();
  delay(100);
  servo.write(90);
  Serial.print("Left Distance ");
  Serial.print(distance);
  Serial.println(" cm");
  return distance;
  delay(100);
}

float readPing()
{
  delay(70);

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, HIGH);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) * 0.0343;
  //distance = distance + 10;
  return distance;
}

void ahead()
{
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
  delay(100);
}

void back()
{
  digitalWrite (In1, LOW);
  digitalWrite (In2, HIGH);
  digitalWrite (In3, LOW);
  digitalWrite (In4, HIGH);
  delay (100);
}

void circle()
{
  digitalWrite (In1, HIGH);
  digitalWrite (In2, LOW);
  digitalWrite (In3, LOW);
  digitalWrite (In4, LOW);
  delay (100);
}

//LED LGHTS
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

void right()
{
  delay(500);
  digitalWrite (In1, HIGH);
  digitalWrite (In2, LOW);
  digitalWrite (In3, LOW);
  digitalWrite (In4, HIGH);
  delay (1100);
  digitalWrite (In1, LOW);
  digitalWrite (In4, LOW);
  delay (100);
}


void left()
{
  delay(1000);
  digitalWrite (In1, LOW);
  digitalWrite (In2, HIGH);
  digitalWrite (In3, HIGH);
  digitalWrite (In4, LOW);
  delay (1100);
  digitalWrite (In2, LOW);
  digitalWrite (In3, LOW);
  delay (100);
}

void moveStop()
{
  digitalWrite(red, HIGH);
  digitalWrite (In1, LOW);
  digitalWrite (In2, LOW);
  digitalWrite (In3, LOW);
  digitalWrite (In4, LOW);
  delay (500);
  digitalWrite(red, LOW);
}
