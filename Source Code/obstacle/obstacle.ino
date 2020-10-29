#include <Servo.h>


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

int distance, duration;

Servo servo;  //servo

void setup() {
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

  Serial.begin(9600);
}

void loop() {

  
  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);
  
  distance = readPing();
  delay(500);
  Serial.print("Distance ");
  Serial.print(distance);
  Serial.println(" cm");

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
      delay(1000);
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
