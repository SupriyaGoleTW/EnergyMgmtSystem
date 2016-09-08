/*
 * PIR sensor tester
 */
 
int ledPin = 13;  
int relayout=12;// choose the pin for the LED
int inputPin = 2;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status
int count = 0; 
void setup() {
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT);     // declare sensor as input
 pinMode(relayout,OUTPUT);          
  Serial.begin(9600);
}
 
void loop(){
  delay(500);
  val = digitalRead(inputPin);  // read input value
  if (val == HIGH) {            // check if the input is HIGH
    digitalWrite(ledPin, HIGH);  // turn LED ON
    digitalWrite(relayout,LOW);
    
    if (pirState == LOW) {
      // we have just turned on
      Serial.println("Motion detected!");
      // We only want to print on the output change, not state
      pirState = HIGH;
//      count++;
//      Serial.println(count);
    }
  } else {
    digitalWrite(ledPin, LOW); // turn LED OFF
    digitalWrite(relayout,HIGH);
    if (pirState == HIGH){
      // we have just turned of
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }
}
