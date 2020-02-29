#include <DCMotorController.h>

const int MOTOR_A0 = 16;
const int MOTOR_A1 = 17;
const int SPEED_A = 5;

const int MOTOR_B0 = 18;
const int MOTOR_B1 = 19;
const int SPEED_B = 3;

float MIDPOINT; 
const float black = 80;
const float white = 31;

const float KP = 0.5;
const float KD = 0;
const float KI = 0.0;

const uint8_t VL_REF = 30;
const uint8_t VR_REF = 20;

const float THRESHOLD_MAX = 180;
const float THRESHOLD_MIN = 10;

float lastError;
float accError;

unsigned long current, previous,elapsedTime;


//Pinos de conexao do modulo TCS230  
//const int s0 = 8;  
//const int s1 = 9;  
const int s2 = 12;  
const int s3 = 13;  
const int out = 10;  
const int oe = 8;


//Variaveis que armazenam o valor das cores
int red = 0;  
int green = 0; 
int blue = 0;  

float vl, vr;

unsigned long tf;

DCMotorController motor(MOTOR_A0, MOTOR_A1, MOTOR_B0, MOTOR_B1, SPEED_A, SPEED_B);

void setup()   
{  
  //pinMode(s0, OUTPUT);  
  //pinMode(s1, OUTPUT);  
  pinMode(s2, OUTPUT);  
  pinMode(s3, OUTPUT);  
  pinMode(out, INPUT);  
  pinMode(oe, INPUT);  
  Serial.begin(9600);  
  //digitalWrite(s0, HIGH);  
  //digitalWrite(s1, LOW);  
  digitalWrite(oe, LOW);

  MIDPOINT = (black+white)/2.0;
  //MIDPOINT = 48;
  accError = lastError = 0;

  
  delay(6000);
  
  tf = millis()+3000;  

  previous = current = 0;
}  



float computePID(float obtido)
{
  

  current = millis();
  elapsedTime = (double)((current-previous)/1000.0);

  float erro = MIDPOINT - obtido;

  accError += erro*elapsedTime;

  float p = KP*erro;
  float d = KD*(erro-lastError)/elapsedTime;
  float i = KI*(accError);
  
  float u = p + i + d;


  vl =   VL_REF+u;
  vr =   VR_REF-u;

  vl = vl < THRESHOLD_MAX?vl:THRESHOLD_MAX;
  vr = vr < THRESHOLD_MAX?vr:THRESHOLD_MAX;
  
  vl = vl > THRESHOLD_MIN? vl: THRESHOLD_MIN;
  vr = vr > THRESHOLD_MIN? vr: THRESHOLD_MIN;   
  
  
  lastError = erro;
  previous = current;
  
  
  
  return erro;
  
 }

 void loop(){
    color(); //Chama a rotina que le as cores
    //Mostra no serial monitor os valores detectados
    //Serial.print("Vermelho :");  
    //Serial.print(red, DEC);
    //Serial.print(" Verde : ");
    //Serial.print(green, DEC);
    //Serial.print(" Azul : ");
    //Serial.print(blue, DEC);
    float erro = computePID(red);

    if( millis() < tf  ){
      
      //Serial.println(erro[1]);
      //Serial.print("p: ");
      //Serial.println(u);
      /*Serial.print("vl: ");
      Serial.println(vl);
      Serial.print("vr: ");
      Serial.println(vr);
      Serial.print("p: ");*/
      Serial.println(erro);
    
      motor.forward(255, 255);
    }
    else{
      Serial.println('f');
      motor.stop();
    }
    //Aguarda 2 segundos, apaga os leds e reinicia o processo  
    //delay(2000);   
    //digitalWrite(pinoledverm, LOW);
    //digitalWrite(pinoledverd, LOW);  
    //digitalWrite(pinoledazul, LOW);  
    //delay(100);
    //motor.forward(110, 90);
 }
    
void color()  
{  
  int i, val;
  //Rotina que le o valor das cores  
  digitalWrite(s2, LOW);  
  //digitalWrite(s2, HIGH);  
  digitalWrite(s3, LOW);  
  //count OUT, pRed, RED  
  for(i=0, val=0; i< 50; i++){
    val += pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
  }
  red = val/i;
  
  //digitalWrite(s3, HIGH);  
  //count OUT, pBLUE, BLUE  
  //blue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
  
  //digitalWrite(s2, HIGH);  
  //count OUT, pGreen, GREEN  
  //green = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
}
