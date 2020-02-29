#include <DCMotorController.h>
#include <ldr.h>

const int MOTOR_A0 = 16;
const int MOTOR_A1 = 17;
const int SPEED_A = 5;

const int MOTOR_B0 = 18;
const int MOTOR_B1 = 19;
const int SPEED_B = 3;

const uint8_t PIN_LDR = A0;


float MIDPOINT; 
const float black = 220.986607;
const float white = 393.334821;

const float KP = 1;
const float KD = 0.;
const float KI = 0.;

const uint8_t VL_REF = 70;
const uint8_t VR_REF = 65;

const uint8_t THRESHOLD_MAX = 150;
const uint8_t THRESHOLD_MIN = 40;

float lastError;
float accError;

DCMotorController motor(MOTOR_A0, MOTOR_A1, MOTOR_B0, MOTOR_B1, SPEED_A, SPEED_B);
LDR ldr(PIN_LDR);

float vl, vr;

unsigned long tf;

void setup() {
  Serial.begin(9600);
  
  
  MIDPOINT = (black+white)/2.0;
  //MIDPOINT = 0.5;
  accError = lastError = 0;

  
  delay(6000);
  
  tf = millis()+2000;
  
}

float norm(int val){
  return ((val-MIDPOINT)/(white-MIDPOINT));
}

void loop()
{
  int obtido = ldr.read();
  
  float erro = norm(MIDPOINT - obtido);
  //float erro = (VL_REF-vl) + VR_REF-vr;
  //float erro[2];
  //erro[0] = VL_REF-vl;
  //erro[1] = VR_REF-vr;

  //float p = KP*erro[0] + KP*erro[1];
  float p = KP*erro;
  float d = 0;//KD*(erro-lastError);
  float i = KI*(accError);
  
  int u = p + i + d;
  //int u[2];
  //u[0] = KP*erro[0];
  //u[1] = KP*erro[1];

  //vl = (VL_REF + u) < THRESHOLD_MAX?(VL_REF + u):THRESHOLD_MAX;
  //vr = (VR_REF - u) < THRESHOLD_MAX?(VR_REF - u):THRESHOLD_MAX;
  vl +=   u;
  vr -=   u;

  vl = (vl) < THRESHOLD_MAX?(vl):THRESHOLD_MAX;
  vr = (vr) < THRESHOLD_MAX?(vr):THRESHOLD_MAX;
  
  vl = vl > THRESHOLD_MIN? vl: THRESHOLD_MIN;
  vr = vr > THRESHOLD_MIN? vr: THRESHOLD_MIN;

  if( millis() < tf  ){
    //Serial.print("vl: ");
    //Serial.println(vl);
    //Serial.print("vr: ");
    //Serial.println(vr);
    //Serial.print("erro: ");
    Serial.println(erro);
    //Serial.println(erro[1]);
    //Serial.print("p: ");
    //Serial.println(u);
  
  
    motor.forward(vl, vr);
  }
  else{
    Serial.println('f');
    motor.stop();
  }
  
  //lastError = erro;
  //accError += erro;

  /*delay(2000);
  motor.brake();
  delay(20);
  motor.backward(127, 127);
  delay(2000);
  motor.brake();
  delay(20);


  motor.forward(100,50);
  delay(2000);
  motor.brake();
  delay(20);
  */
  
}

