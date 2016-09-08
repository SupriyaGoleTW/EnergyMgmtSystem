#include "Timer.h"


Timer t;
int pin = 13;
int ledEvent;
int inputPin = 2;
int pirState = LOW;
int val = 0;
int timeLimit =  1000;
int counter = 0;
int relayout = 12;

void setup()
{
  pinMode(inputPin,INPUT);
  Serial.begin(9600);
  pinMode(pin, OUTPUT);
//  ledEvent = t.oscillate(pin, 0.1, LOW);
}


void loop(){
  val = digitalRead(inputPin);
  Serial.println("sensed something");
  Serial.println(val);
  //int foo = get the sensor value
  if(val == HIGH){
//    do stuff here;
    digitalWrite(pin,HIGH);
    digitalWrite(relayout,LOW);
    Serial.println("Glowing LED");
    }
  if(counter >= timeLimit){
    Serial.println("batti bujhi");
    digitalWrite(pin,LOW);
    digitalWrite(relayout,HIGH);
    Serial.println("led turn off and program ended");
    counter = 0;
    return ;
    //turn of the led
  }else{
    counter = counter+1;
  }
//  t.every(1000,takeReading);
//  t.update();
//  t.stop(ledEvent);
}


void takeReading()
{
  Serial.println("Nice iDea !!");
  int output = t.oscillate(pin,0.1,HIGH);
  Serial.println(output);
//  t.stop(ledEvent);
//  Serial.println(analogRead(0));
}
