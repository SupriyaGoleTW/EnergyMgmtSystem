int pin = 13;
int inputPin = 2;
int val = 0;
int timeLimit =  250;
int counter = 0;
int relayout = 12;

void setup()
{
  pinMode(inputPin,INPUT);
  Serial.begin(9600);
  pinMode(pin, OUTPUT);
  pinMode(relayout,OUTPUT); 
}


void loop(){
  val = digitalRead(inputPin);
  Serial.println("sensed something");
  Serial.println(val);
  if(val == HIGH){
    // turn the led on
    digitalWrite(pin,HIGH);
    digitalWrite(relayout,LOW);
    Serial.println("Glowing LED");
    counter = 0; // after every motion it will reset the counter
    }
  if(counter >= timeLimit){
    // turn off the led after a specific time
    digitalWrite(pin,LOW);
    digitalWrite(relayout,HIGH);
    Serial.println("led turn off and program ended");
    counter = 0;
    return ;
    //turn off the led
  }else{
    // increase the counter 
    counter++;
  }
}

