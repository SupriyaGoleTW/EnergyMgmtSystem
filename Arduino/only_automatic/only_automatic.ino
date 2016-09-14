int autoInput = 2; //number of input pin from which your button is connected
int ledPin = 13;
int relayOut = 12;

void setup(){
  pinMode(ledPin,OUTPUT);
  pinMode(autoInput,INPUT);
  pinMode(relayOut,OUTPUT);
  Serial.begin(9600);
}

void loop(){
  delay(500);
  int sensorStatus = digitalRead(autoInput);
  Serial.println(sensorStatus);
  if(sensorStatus != HIGH){
    turnOff();  
  }
  else{
    turnOn(sensorStatus);
  }
}


int generateBuffer(int time){
  int counter = 0;
  while(counter < time){// turn led on till some limit take input from sensor -> need to work on that
    int value_of_pir_sensor = digitalRead(2);
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

void turnOn(int value){
  int timeLimit = 3900 * 0.1;
  
  Serial.println("In Automatic mode");
  while(value == HIGH){
    Serial.println("Motion Sensed");
    int maxLimit = generateBuffer(timeLimit);
    
    if(maxLimit == timeLimit){   // make LED low once time elapse
      delay(1000);
      turnOff();
    }
    return;
  }
}


void turnOff(){
//  Serial.println("OFF LED");
  digitalWrite(ledPin,LOW);
  digitalWrite(relayOut,LOW);
}

