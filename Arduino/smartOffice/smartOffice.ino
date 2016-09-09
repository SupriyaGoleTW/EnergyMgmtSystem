int input_from_automate_button = 4; //number of input pin from which your button is connected
int input_from_manual_button = 2;
int input_from_pir_sensor  = 6;

int ledPin = 13;
int val_of_automate = 0;
int val_of_manual = 0;
int counter = 0;

void setup(){
  pinMode(ledPin,OUTPUT);
  pinMode(input_from_automate_button,INPUT);
  pinMode(input_from_manual_button,INPUT);
  pinMode(input_from_pir_sensor,INPUT);
  pinMode(relayOut,OUTPUT);
  Serial.begin(9600);
}
 
void loop(){
  val_of_automate = digitalRead(input_from_automate_button);
  val_of_manual = digitalRead(input_from_manual_button);
  
  if(val_of_manual == HIGH){
    jumpToManualMode();
  }

  jumpToAutomaticMode();
}

void jumpToAutomaticMode(){
  int timeLimit = 3900 * 5;
  counter = 0;
  int value_of_pir_sensor = digitalRead(input_from_pir_sensor);
  Serial.println("In Automatic mode");
  if(value_of_pir_sensor == HIGH){
    
    while(counter < timeLimit){// turn led on till some limit take input from sensor -> need to work on that
      value_of_pir_sensor = digitalRead(input_from_pir_sensor);
      if(value_of_pir_sensor == HIGH){
        counter = 0;
      }
      
      digitalWrite(ledPin,HIGH);
      counter++;
    }
    
    if(counter == timeLimit){   // make LED low once time elapse
      digitalWrite(ledPin,LOW);
      return;
    }
  }
  else{
      digitalWrite(ledPin,LOW);
      return;
  }
}

void jumpToManualMode(){
  int value_of_automate_button = digitalRead(input_from_automate_button);
  while(value_of_automate_button == LOW){
    value_of_automate_button = digitalRead(input_from_automate_button);
    digitalWrite(ledPin, HIGH);  // turn LED ON
  }
  while(value_of_automate_button == HIGH){
    jumpToAutomaticMode();
  }
  return;
}
