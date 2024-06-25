//
// Created by chenh on 2024/2/21.
//

#ifndef TWOWHEELSCAR_F407VG_ENCODER_H
#define TWOWHEELSCAR_F407VG_ENCODER_H

#include "main.h"

#define ec_back 0
#define ec_forward 1

#define pulse2per 1000/470

//两轮差速机器人参数
#define  M_PI           3.1416     //圆周率PI
#define  PID_RATE     50         //PID频率

#define  TWD_WHEEL_DIAMETER	      0.0724	 //轮子直径
#define  TWD_WHEEL_BASE           0.206	     //轮距，左右轮的距离
#define  TWD_WHEEL_RESOLUTION     1560.0      //编码器分辨率(13线),减速比30, 13x30x4=1560
#define  TWD_WHEEL_SCALE          (M_PI*TWD_WHEEL_DIAMETER*PID_RATE/TWD_WHEEL_RESOLUTION)  //轮子速度m/s与编码器转换系数

#define R_VX_LIMIT  1300   //X轴速度限值 m/s*1000
#define R_VW_LIMIT  6000   //W旋转角速度限值 rad/s*1000


typedef struct{
    uint8_t direction;
    int16_t enc;
}_encoder;

typedef struct
{
    int16_t TG_IX;     //目标X轴速度（16位整数）
    int16_t TG_IW;     //目标Yaw旋转轴速度（16位整数）

    int16_t RT_IX;     //实时X轴速度（16位整数）
    int16_t RT_IW;     //实时Yaw旋转轴速度（16位整数）
}ROBOT_Velocity;



extern _encoder ecR, ecL;
extern ROBOT_Velocity R_Vel;


void getTIMx_DetaCnt(_encoder* ec, TIM_TypeDef* TIMx);
void MY_ROBOT_Kinematics(void);

#endif //TWOWHEELSCAR_F407VG_ENCODER_H
