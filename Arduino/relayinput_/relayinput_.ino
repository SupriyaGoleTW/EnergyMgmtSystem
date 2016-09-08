int pirSensor = 8;
int relayInput = 7;
int count = 0;
void setup() {
  pinMode(pirSensor, INPUT);
  pinMode(relayInput, OUTPUT);  
  Serial.begin(9600);
}
void loop() {
  delay(100);
  int sensorValue = digitalRead(pirSensor);
  if (sensorValue == 1) {
    Serial.println("detects");
    digitalWrite(relayInput,LOW); // The Relay Input works Inversly
  }else{
    Serial.println("ended");
    digitalWrite(relayInput,HIGH); // The Relay Input works Inversly    
  }
}
