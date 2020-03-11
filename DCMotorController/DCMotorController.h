#ifndef DCMotorController_h
#define DCMotorController_h
 
#include <Arduino.h>

#include <stdlib.h> 


class DCMotorController{
	public:
		DCMotorController(uint8_t l0, uint8_t l1, uint8_t r0, uint8_t r1, uint8_t spl, uint8_t spr);
		void forward(uint8_t powerLeft =255, uint8_t powerRight =255);
		void backward(uint8_t powerLeft =255, uint8_t powerRight =255);
		void stop();
		void brake();
	private:
		uint8_t ml0, ml1, mr0, mr1, mspl, mspr;
};

#endif