#include <Arduino.h>
#define CH1 A0
#define CH3 A1
#define CH4 A2
#define RrPWM 6
#define RlPWM 9
#define LrPWM 10
#define LlPWM 11
#define Reve 12
// Read the number of a given channel and convert to the range provided.
// If the channel is off, return the default value
int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue){
  int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}

// Red the channel and return a boolean value
bool redSwitch(byte channelInput, bool defaultValue){
  int intDefaultValue = (defaultValue)? 100: 0;
  int ch = readChannel(channelInput, 0, 100, intDefaultValue);
  return (ch > 50);
}

void setup(){
  Serial.begin(9600);
  pinMode(CH1, INPUT);
  pinMode(CH3, INPUT);
  pinMode(CH4, INPUT);
  pinMode(Reve, INPUT);
  pinMode(RrPWM, OUTPUT);
  pinMode(RlPWM, OUTPUT);
  pinMode(LrPWM, OUTPUT);
  pinMode(LlPWM, OUTPUT);
}

int ch1Value,ch3Value, ch4Value;
bool Rev;

void loop() {
  ch1Value = readChannel(CH1, -255,255, 0);
  ch3Value = readChannel(CH3, 0, 255, 0);
  ch4Value = readChannel(CH4, -255, 255, 0);
  Rev = redSwitch(Reve,0);
  
  Serial.print("Ch1:");
  Serial.print(ch1Value);
  Serial.print(" Ch3:");
  Serial.print(ch3Value);
  Serial.print(" Ch4:");
  Serial.print(ch4Value);
  Serial.print(" Rev:");
  Serial.print(Rev);
  Serial.print("\n");
  //Forward and reverse
  if (Rev>0){
  analogWrite(RrPWM,ch3Value);
  analogWrite(RlPWM,LOW);
  digitalWrite(7,HIGH);
  digitalWrite(8,HIGH);
  digitalWrite(2,HIGH);
  digitalWrite(4,HIGH);
  analogWrite(LrPWM,ch3Value);
  analogWrite(LlPWM,LOW);
  }
  else{
  analogWrite(RlPWM,ch3Value);
  analogWrite(RrPWM,LOW);
  digitalWrite(7,HIGH);
  digitalWrite(8,HIGH);
  digitalWrite(2,HIGH);
  digitalWrite(4,HIGH);
  analogWrite(LlPWM,ch3Value);
  analogWrite(LrPWM,LOW);
  } 
  //Right and left
  if(ch1Value >5 || ch1Value <-5){
  if (ch1Value>0){
  analogWrite(RrPWM,ch1Value);
  analogWrite(RlPWM,LOW);
  digitalWrite(7,HIGH);
  digitalWrite(8,HIGH);
  }
  else{
  analogWrite(LrPWM,-ch1Value);
  analogWrite(LlPWM,LOW);
  digitalWrite(2,HIGH);
  digitalWrite(4,HIGH);
  }
  }
  //Tank turns
  if(ch4Value >15 || ch4Value <-15){
  if (ch4Value>0){
  analogWrite(RrPWM,ch4Value);
  analogWrite(RlPWM,LOW);
  digitalWrite(7,HIGH);
  digitalWrite(8,HIGH);
  analogWrite(LlPWM,ch4Value);
  analogWrite(LrPWM,LOW);
  }
  else{
  analogWrite(LrPWM,-ch4Value);
  analogWrite(LlPWM,LOW);
  digitalWrite(7,HIGH);
  digitalWrite(8,HIGH);
  analogWrite(RlPWM,-ch4Value);
  analogWrite(RrPWM,LOW);
  }
  }
 
 }
