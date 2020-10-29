const int ledPin = A1;
const int ldrPin = A4;


void setup() {

  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);  //initialize the LED pin as an output
  pinMode(ldrPin, INPUT);   //initialize the LDR pin as an input
}

void loop() {

  int ldrStatus = analogRead(ldrPin);   //read the status of the LDR value

  //check if the LDR status is <= 300
  //if it is, the LED is HIGH

   if (ldrStatus <=400) {

    digitalWrite(ledPin, HIGH);               //turn LED on
    Serial.println("LDR is DARK, LED is ON");
    
   }
  else {

    digitalWrite(ledPin, LOW);          //turn LED off
    Serial.println("---------------");
  }
}
