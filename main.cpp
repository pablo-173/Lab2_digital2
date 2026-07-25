#include <Arduino.h>
#include <driver/gpio.h>
#include <stdio.h>
#define t0 25000
#define led_g 4
#define b_1 34
#define b_2 35
#define touch 15


int s1=0;
int s2=0;
int l1=0;
int l2=0;

const byte ps[4]={
  5,18,19,21
};
const byte le[4]={
  13,14,26,33
};

byte bin[16][4]={
  {0,0,0,0},
  {0,0,0,1},
  {0,0,1,0},
  {0,0,1,1},
  {0,1,0,0},
  {0,1,0,1},
  {0,1,1,0},
  {0,1,1,1},
  {1,0,0,0},
  {1,0,0,1},
  {1,0,1,0},
  {1,0,1,1},
  {1,1,0,0},
  {1,1,0,1},
  {1,1,1,0},
  {1,1,1,1}
};

volatile int contadorT=0;
volatile int contadorB=0;

void Timer(void);
void IRAM_ATTR onTimer();

void IRAM_ATTR onButton_1();
void IRAM_ATTR onButton_2();

hw_timer_t * timer = NULL;



void setup() {
  Timer();
  attachInterrupt(b_1, onButton_1, HIGH);
  attachInterrupt(b_2, onButton_2, HIGH);

  pinMode(b_1,INPUT);
  pinMode(b_2,INPUT);
  pinMode(led_g,OUTPUT);
  for (int i = 0; i<4; i++){
    pinMode(ps[i],OUTPUT);
  }
  for(int i = 0; i<4; i++){
    pinMode(le[i],OUTPUT);
  }

  }

  void loop(){
  touchRead(touch);
  if (touchRead(touch)<40){
    contadorT=0;

  }
  if (contadorT>15){
    contadorT=0;
  }
  for(int i=0; i<4; i++){
    digitalWrite(ps[i],bin[contadorT][i]);
  }
  if (contadorB>15){
    contadorB=0;
  }
  else if (contadorB<0){
    contadorB=15;
  }
  for(int i=0; i<4; i++){
    digitalWrite(le[i],bin[contadorB][i]);

  }
  if (contadorB+1==contadorT){
    if (digitalRead(led_g)==LOW){
      digitalWrite(led_g,HIGH);
    }
    else{
      digitalWrite(led_g,LOW);
    }
    contadorT=0;
  }
  }
  

  
void Timer(void){
  timer = timerBegin(0, 800, true);
  timerAttachInterrupt(timer, &onTimer, true);

  timerAlarmWrite(timer, t0 , true);

  timerAlarmEnable(timer);
}
void IRAM_ATTR onTimer(){
  contadorT++;

}
void IRAM_ATTR onButton_1(){
  contadorB++;
}
void IRAM_ATTR onButton_2(){
  contadorB--;
}