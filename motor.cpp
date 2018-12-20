#include "motor.h"
#include<Arduino.h>

extern const int sensor1;
extern const int sensor2;
extern const int sensor4 ;
extern const int sensor5 ;
extern const int sensor6;
extern const int sensor7 ;
extern const int High;
extern const int Low;
extern const int velocity;
extern int M_in_1;
extern int M_in_2;
extern int M_in_3;
extern int M_in_4;
#define M_left_forward 1
#define M_left_back  2
#define M_right_forward  3
 #define M_right_back  4
#define M_left_stop  5
#define M_right_stop  6
void motor_control( int motor_state,int M_velocity){
 
  switch (motor_state){
  case M_left_forward:
  constrain( M_velocity,High,255);
 analogWrite(M_in_1,M_velocity);
 analogWrite(M_in_2,0);
 break;
 case M_left_back:
  constrain( M_velocity,High,255);
 analogWrite(M_in_1,0);
 analogWrite(M_in_2,M_velocity);
 break;
 case M_left_stop:
 analogWrite(M_in_1,0);
 analogWrite(M_in_2,0);
 break;
 case M_right_forward:
  constrain( M_velocity,High,255);
 analogWrite(M_in_3,M_velocity);
 analogWrite(M_in_4,0);
 break;
  case M_right_back:
  constrain( M_velocity,High,255);
 analogWrite(M_in_3,0);
 analogWrite(M_in_4,M_velocity);
 break;
 case M_right_stop:
 analogWrite(M_in_3,0);
 analogWrite(M_in_4,0);
 break;
 }
}

