int input_from_manual_button = 2;
int input_from_pir_sensor  = 4;
int relay_output = 12;

int ledPin = 13;
int val_of_automate = 0;
int val_of_manual = 0;
int counter = 0;

void setup(){
  pinMode(ledPin,OUTPUT);
  pinMode(relay_output,OUTPUT);
  pinMode(input_from_manual_button,INPUT);
  pinMode(input_from_pir_sensor,INPUT);
  Serial.begin(9600);
}
 
void loop(){
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
      val_of_manual = digitalRead(input_from_manual_button);
      if(val_of_manual == HIGH){
        jumpToManualMode();
        return;
      }
      if(value_of_pir_sensor == HIGH){
        counter = 0;
      }
      
      digitalWrite(ledPin,HIGH);
      digitalWrite(relay_output,HIGH);
      counter++;
    }
    
    if(counter == timeLimit){   // make LED low once time elapse
      digitalWrite(ledPin,LOW);
      digitalWrite(relay_output,LOW);
      return;
    }
  }
  else{
      digitalWrite(ledPin,LOW);
      digitalWrite(relay_output,LOW);
      return;
  }
}

void jumpToManualMode(){
  val_of_manual = digitalRead(input_from_manual_button);
  int val_of_automate_button = digitalRead(input_from_pir_sensor);
  
  while(val_of_manual == HIGH){
    val_of_manual = digitalRead(input_from_manual_button);
    digitalWrite(ledPin, HIGH);  // turn LED ON
    digitalWrite(relay_output, HIGH);
  }

  
  while(val_of_manual == LOW){
    digitalWrite(ledPin, LOW);  // turn LED OFF
    digitalWrite(relay_output, LOW);
    jumpToAutomaticMode();
    return;
  }
}
