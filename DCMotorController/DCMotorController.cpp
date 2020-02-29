#include "DCMotorController.h"


DCMotorController::DCMotorController(uint8_t l0, uint8_t l1, uint8_t r0, uint8_t r1, uint8_t spl, uint8_t spr): 
ml0(l0), ml1(l1), mr0(r0), mr1(r1), mspl(spl), mspr(spr)
{
  pinMode(l0, OUTPUT);
  pinMode(l1, OUTPUT);
  pinMode(spl, OUTPUT);

  pinMode(r0, OUTPUT);
  pinMode(r1, OUTPUT);
  pinMode(spr, OUTPUT);
}

/********************************************************************************
*	Aciona os motores para a frente com a potência por parâmetro				*
*	@param powerLeft 0-255														*
*	@param powerRight 0-255														*
********************************************************************************/
void DCMotorController::forward(uint8_t powerLeft, uint8_t powerRight){  
  digitalWrite(ml0, HIGH);
  digitalWrite(ml1, LOW);
  digitalWrite(mr0, HIGH);
  digitalWrite(mr1, LOW);

  analogWrite(mspl, powerLeft);
  analogWrite(mspr, powerRight);
}

/********************************************************************************
*	Aciona os motores para a trás com a potência por parâmetro					*
*	@param powerLeft 0-255														*
*	@param powerRight 0-255														*
********************************************************************************/
void DCMotorController::backward(uint8_t powerLeft, uint8_t powerRight){
  digitalWrite(ml0, LOW);
  digitalWrite(ml1, HIGH);
  digitalWrite(mr0, LOW);
  digitalWrite(mr1, HIGH);
  
  analogWrite(mspl, powerLeft);
  analogWrite(mspr, powerRight);
}

/********************************************************************************
*	cessa o acionamento dos motores, sem travá-los								*
********************************************************************************/
void DCMotorController::stop(){
  digitalWrite(ml0, LOW);
  digitalWrite(ml1, LOW);
  digitalWrite(mr0, LOW);
  digitalWrite(mr1, LOW);
}

/********************************************************************************
*	trava os motores															*
********************************************************************************/
void DCMotorController::brake(){
  digitalWrite(ml0, HIGH);
  digitalWrite(ml1, HIGH);
  digitalWrite(mr0, HIGH);
  digitalWrite(mr1, HIGH);
}
