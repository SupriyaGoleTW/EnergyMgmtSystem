int input_for_automate_button = 4; //number of input pin from which your button is connected
int input_for_manual_button  = 2;

int ledPin = 13;
int relayOut = 12;
int input_pin_of_pir = 2;
int pirState = LOW;
int val_of_automate = 0;
int val_of_manual = 0;
int counter = 0;
int timer;
int val = 0;

void setup(){
  pinMode(ledPin,OUTPUT);
  pinMode(input_for_automate_button,INPUT);
  pinMode(input_for_manual_button,INPUT);
  pinMode(relayOut,OUTPUT);
  Serial.begin(9600);
}

void loop(){
  delay(500);
  val_of_automate = digitalRead(input_for_automate_button);
  val_of_manual = digitalRead(input_for_manual_button);
  Serial.println("val_of_automate");
  Serial.println(val_of_automate);
  Serial.println("val_of_manual");
  Serial.println(val_of_manual);
  delay(500);
  
  if(val_of_automate == HIGH){
    set_automation();
  }
  if(val_of_manual == HIGH){
    set_manual();
  }
}

void set_automation(){
  int timeLimit = 250;
  val = digitalRead(input_for_automate_button);
  Serial.println("val");
  Serial.println(val);
 
  if(val == HIGH){
    // turn the led on
    digitalWrite(ledPin,HIGH);
    digitalWrite(relayOut,LOW);
    counter = 0; // after every motion it will reset the counter
  }

  Serial.println("In Automatic mode");

  while(counter < timeLimit){    // turn led on till some limit
    digitalWrite(ledPin,HIGH);
//  digitalWrite(relayOut,HIGH);
    counter = counter + 1;
    Serial.println("counter");
    Serial.println(counter);
  }
  if(counter == timeLimit){   // make LED low once time elapse
    Serial.println("end counter");
    Serial.println(counter);
    digitalWrite(ledPin,LOW);
    return;
  }
}
