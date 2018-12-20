#include"direction.h"
#include<Arduino.h>
#include "motor.h"
#define M_left_forward 1
#define M_left_back  2
#define M_right_forward  3
 #define M_right_back  4
#define M_left_stop  5
#define M_right_stop  6
const int High=145;
 const int Low=127;
const int velocity=500;
//int cross_flag=0;
int T=0;
int flag_draw=0;
enum Direction_State{Left_state,Right_state,common_state,Left_second_state,Right_second_state};
 Direction_State direction_state=common_state;
void sensor_load(int* sensor_state){ 
     
//sensor_state[0]=digitalRead(48);//0是白色，1是黑色
//sensor_state[1]=digitalRead(49);
sensor_state[1]=0;
sensor_state[4]=0;

sensor_state[2]=digitalRead(50);
sensor_state[3]=digitalRead(51);
//sensor_state[4]=digitalRead(52);
//sensor_state[5]=digitalRead(53);
  sensor_state[0]=digitalRead(49);
  sensor_state[5]=digitalRead(52);
  sensor_state[6]=digitalRead(47);
  sensor_state[7]=digitalRead(37);//左边后方的管子
  sensor_state[8]=digitalRead(36);//右边后方的管子





  
  }
void decision (int* sensor_state){
  switch (direction_state)
  
  {case Left_second_state:
     motor_control(M_left_back,velocity);
    motor_control(M_right_forward,velocity);
     if(sensor_state[2]==1)//(左前）中间是黑色
    {
      direction_state=common_state;
      return 0;
    }
      if(sensor_state[8]==1)//右边后边那个是黑色
  {
    direction_state=common_state;
    return 0;
  }
  break;
   case Right_second_state:
    motor_control(M_right_back,velocity);
    motor_control(M_left_forward,velocity); 
     if(sensor_state[3]==1)//（右前）中间是黑色
    {
      direction_state=common_state;
      return 0;
    }
      if(sensor_state[7]==1)//左边后边那个是黑色
  {
    direction_state=common_state;
    return 0;
  }
  break;
    case Left_state:
  /*  if(sensor_state[6]==0)
    {motor_control(M_left_stop,0);
    motor_control(M_right_forward,velocity); 
    return 0;
    }
    else
   { direction_state=common_state;
    return 0;
   }
   */
   motor_control(M_left_stop,velocity);
    motor_control(M_right_forward,velocity);
     if(sensor_state[6]==1)//中间是黑色
    {
      direction_state=common_state;
      return 0;
    }
  if(sensor_state[5]==1)//右边第一个是黑色
  {
    direction_state=common_state;
    return 0;
  }
 
  break;
  case Right_state:
    motor_control(M_right_stop,velocity);
    motor_control(M_left_forward,velocity);
     if(sensor_state[6]==1)//中间是黑色
    {
      direction_state=common_state;
      return 0;
    }
  if(sensor_state[0]==1)//左边第一个是黑色
  {
    direction_state=common_state;
    return 0;
  }
  break;
  case common_state:
 
  
    if(sensor_state[6]==1)
  //gogogo,这时候不给转弯
  {
   motor_control(M_left_forward,velocity);
    motor_control(M_right_forward,velocity);
    
    return 0;
  }
   if((sensor_state[0]==1&&sensor_state[5]==1)||(sensor_state[1]==1&&sensor_state[4]==1)||(sensor_state[2]==1&&sensor_state[3]==1))
  //交叉弯，车直行
  {
    motor_control(M_left_forward,velocity);
    motor_control(M_right_forward,velocity);   
    
    return 0;
  }
  
  if(sensor_state[0]==1&&sensor_state[5]==0)
 //车右大偏，左满舵
  {
  //if(cross_flag==0)
   direction_state=Left_state;
   return 0;
   
   
     /*motor_control(M_left_forward,velocity);
    motor_control(M_right_forward,velocity);
    cross_flag=0;
    delay(100);
    return 0;
   */
  }
 
   if(sensor_state[0]==0&&sensor_state[5]==1)
  //车左大偏，右满舵
  {
    //if(cross_flag==0)
   direction_state=Right_state;
   return 0;
   /*
   else
   {
    motor_control(M_left_forward,velocity);
    motor_control(M_right_forward,velocity);
    cross_flag=0;
    delay(100);
    return 0;
   }
   */
  }
   
  
  if(sensor_state[0]==0&&sensor_state[5]==0&&sensor_state[1]==1&&sensor_state[4]==0)
  //车右中偏，左半舵
  {
   motor_control(M_left_back,velocity);
    motor_control(M_right_forward,velocity);
    
    return 0;
  }
   if(sensor_state[0]==0&&sensor_state[5]==0&&sensor_state[1]==0&&sensor_state[4]==1)
  //车左中偏，右半舵
  {
   motor_control(M_right_back,velocity);
    motor_control(M_left_forward,velocity);
   
    return 0;
  }
  if(sensor_state[0]==0&&sensor_state[5]==0&&sensor_state[1]==0&&sensor_state[4]==0&&sensor_state[2]==1&&sensor_state[3]==0)
  //车右小偏，左轻舵
  {
   motor_control(M_left_stop,0);
    motor_control(M_right_forward,velocity);
    
    return 0;
  }
  if(sensor_state[0]==0&&sensor_state[5]==0&&sensor_state[1]==0&&sensor_state[4]==0&&sensor_state[2]==0&&sensor_state[3]==1)
  //车左小偏，右轻舵
  {
   motor_control(M_right_stop,0);
    motor_control(M_left_forward,velocity);
    
    return 0;
  }
 
  if(sensor_state[0]==0&&sensor_state[5]==0&&sensor_state[1]==0&&sensor_state[4]==0&&sensor_state[2]==0&&sensor_state[3]==0&&sensor_state[7]==1&&sensor_state[8]==0)
  //左后方管子发力
  {
     direction_state=Left_second_state;
    
    return 0;
  }
   if(sensor_state[0]==0&&sensor_state[5]==0&&sensor_state[1]==0&&sensor_state[4]==0&&sensor_state[2]==0&&sensor_state[3]==0&&sensor_state[8]==1&&sensor_state[7]==0)
  //右后方管子发力
  {
     direction_state=Right_second_state;
    
    return 0;
  }
 
   
   /* if(sensor_state[0]==0&&sensor_state[5]==0&&sensor_state[1]==0&&sensor_state[4]==0&&sensor_state[2]==0&&sensor_state[3]==0&&sensor_state[6]==0)
  //前面没路了，倒车
  { if(T>10000&&flag_draw==1)//开始倒车，持续50ms
   {motor_control(M_left_back,velocity);
    motor_control(M_right_back,velocity);
    delay(50);
    flag_draw=0;
    return 0;
   }
   else
   {if(flag_draw==0)//倒车态启动
   {
    flag_draw=1;
    T=0;
    return 0;
   }
   else//满足倒车条件，但是时间没到
   {
    T=T+1;
   return 0; 
   }
   
   
  }
  
  }
  */
}
}

