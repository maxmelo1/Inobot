
#include <ldr.h>

LDR ldr(A0);


void setup() {
  Serial.begin(9600);
}

void loop()
{
  int val = ldr.read();
  
  Serial.println(val);
  delay(50);
}


