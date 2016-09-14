int input_for_automate_button = 2; //number of input pin from which your button is connected
int ledPin = 13;
int relayOut = 12;

void setup(){
  pinMode(ledPin,OUTPUT);
  pinMode(input_for_automate_button,INPUT);
  pinMode(relayOut,OUTPUT);
  Serial.begin(9600);
}

void loop(){
  delay(500);
  int value_of_pir_sensor = digitalRead(input_for_automate_button);
  jumpToAutomaticMode(value_of_pir_sensor);
}


int bufferLight(int counter,int time,int inputValue){
  while(counter < time){// turn led on till some limit take input from sensor -> need to work on that
    int value_of_pir_sensor = digitalRead(inputValue);
    if(value_of_pir_sensor == HIGH){
      Serial.println("resetted- again motion detected");
      counter = 0;
    }
    
    digitalWrite(ledPin,HIGH);
    digitalWrite(relayOut,HIGH);
    Serial.println("LED is glowing");
    counter++;
  } 
  return counter;
}

void jumpToAutomaticMode(int value){
  int timeLimit = 3900 * 0.1;
  int counter = 0;
  
  Serial.println("In Automatic mode");
  while(value == HIGH){
    Serial.println("Motion Sensed");
    int maxLimitReached = bufferLight(counter,timeLimit,input_for_automate_button);
    
    if(maxLimitReached == timeLimit){   // make LED low once time elapse
      delay(1000);
      Serial.println("OFF LED");
      digitalWrite(ledPin,LOW);
      digitalWrite(relayOut,LOW);
    }
    return;
  }
 digitalWrite(ledPin,LOW);
 Serial.println("LED is Off");
 digitalWrite(relayOut,LOW);
 return;
}

