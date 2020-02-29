#include "ldr.h"

LDR::LDR(uint8_t pin){
	pinMode(pin, INPUT);
	this->ldrPin = pin;
}

int LDR::read(){
	int val = analogRead(this->ldrPin);

	int newVal = map(val, 0, 1024, 1024, 0);

	return newVal;
}