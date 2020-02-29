#ifndef LDR_h
#define LDR_h
 
#include <Arduino.h>

class LDR{
	public:
		LDR(uint8_t pin);
		int read();
	private:
		uint8_t ldrPin;
};

#endif