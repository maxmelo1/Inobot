#include <ldr.h>

const int motorA0 = 16;
const int motorA1 = 17;
const int speedA = 5;

const int motorB0 = 18;
const int motorB1 = 19;
const int speedB = 3;

void forward(int =255, int =255);
void backward(int =255, int= 255);

LDR ldr(A0);

void setup() {
  // set the digital pin as output:
  pinMode(motorA0, OUTPUT);
  pinMode(motorA1, OUTPUT);
  pinMode(speedA, OUTPUT);

  pinMode(motorB0, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(speedB, OUTPUT);
  
  pinMode(9, OUTPUT);

  Serial.begin(9600);
  delay(6000);
}

void loop()
{
  
  forward(65, 50);
  Serial.println(ldr.read());

  //delay(1000);
  //stopMotor();

  
    
  //digitalWrite(9, HIGH);
  //delay(100);
  //digitalWrite(9, LOW);
}

void forward(int sA, int sB){
  /*Serial.print("sa: ");
  Serial.println(sA);
  Serial.print("sb: ");
  Serial.println(sB);*/

  digitalWrite(motorA0, HIGH);
  digitalWrite(motorA1, LOW);
  digitalWrite(motorB0, HIGH);
  digitalWrite(motorB1, LOW);

  analogWrite(speedA, sA);
  analogWrite(speedB, sB);
}

void backward(int sA, int sB){
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA0, LOW);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB0, LOW);
  
  analogWrite(speedA, sA);
  analogWrite(speedB, sB);
}

void stopMotor(){
  digitalWrite(motorA0, LOW);
  digitalWrite(motorA1, LOW);
  digitalWrite(motorB0, LOW);
  digitalWrite(motorB1, LOW);
}

void brake(){
  digitalWrite(motorA0, HIGH);
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorB0, HIGH);
  digitalWrite(motorB1, HIGH);
}

void rotate(){
  //Serial.println(sA);
  digitalWrite(motorA0, HIGH);
  digitalWrite(motorA1, LOW);
  digitalWrite(motorB0, HIGH);
  digitalWrite(motorB1, HIGH);

  analogWrite(speedA, 255);
  analogWrite(speedB, 255);


  delay(1000);

  digitalWrite(motorA0, HIGH);
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorB0, HIGH);
  digitalWrite(motorB1, LOW);

  analogWrite(speedA, 255);
  analogWrite(speedB, 255);

  delay(1000);
}
