//
// Created by chenh on 2024/2/21.
//

#include "encoder.h"
#include "tim.h"
#include "gpio.h"
#include "usart.h"
#include "mypid.h"
#include "motor.h"

_encoder ecR={0, 0}, ecL={0, 0};
ROBOT_Velocity R_Vel={0, 0, 0, 0};


void getTIMx_DetaCnt(_encoder* ec, TIM_TypeDef* TIMx) //读取单位时间内脉冲变化值
{
    int16_t cnt;
    cnt = TIMx->CNT-0x5fff;
    TIMx->CNT = 0x5fff;
//    if (cnt < 0){
//        ec->direction = ec_back;
//        ec->enc = -cnt;
//    } else{
//        ec->direction = ec_forward;
//        ec->enc = cnt;
//    }
    ec->enc = cnt;
}

void MY_ROBOT_Kinematics(void){
    getTIMx_DetaCnt(&ecL, TIM3);
    LeftSpeedPid.Pv = ecL.enc * TWD_WHEEL_SCALE * 1000;    // mm/s
    getTIMx_DetaCnt(&ecR, TIM2);
    RightSpeedPid.Pv = - ecR.enc * TWD_WHEEL_SCALE * 1000;    // mm/s

    // Positive kinematics
    R_Vel.RT_IX = (int16_t)((LeftSpeedPid.Pv + RightSpeedPid.Pv)/2);
    R_Vel.RT_IW = (int16_t)((-LeftSpeedPid.Pv + RightSpeedPid.Pv)/TWD_WHEEL_BASE);

    Uart2_Str.Analysis_function();

    if( R_Vel.TG_IX > R_VX_LIMIT )    R_Vel.TG_IX = R_VX_LIMIT;
    if( R_Vel.TG_IX < (-R_VX_LIMIT))  R_Vel.TG_IX = (-R_VX_LIMIT);
    if( R_Vel.TG_IW > R_VW_LIMIT)     R_Vel.TG_IW = R_VW_LIMIT;
    if( R_Vel.TG_IW < (-R_VW_LIMIT))  R_Vel.TG_IW = (-R_VW_LIMIT);

    // Inverse kinematics
    LeftSpeedPid.Sv = (int16_t)(R_Vel.TG_IX - R_Vel.TG_IW*(TWD_WHEEL_BASE/2));
    RightSpeedPid.Sv = (int16_t)(R_Vel.TG_IX + R_Vel.TG_IW*(TWD_WHEEL_BASE/2));

    if (RightSpeedPid.Sv){
        Calc_SpeedPid(&RightSpeedPid);
        if (RightSpeedPid.Out >= 0) {
            Forward_Slow(RightWheel, RightSpeedPid.Out);
        }
        else if (RightSpeedPid.Out < 0){
            Back_Slow(RightWheel, -RightSpeedPid.Out);
        }
    }
    else{
        Forward_Slow(RightWheel, 0);
    }

    if (LeftSpeedPid.Sv){
        Calc_SpeedPid(&LeftSpeedPid);
        if (LeftSpeedPid.Out >= 0){
            Forward_Slow(LeftWheel, LeftSpeedPid.Out);
        }
        else if (LeftSpeedPid.Out < 0){
            Back_Slow(LeftWheel, -LeftSpeedPid.Out);
        }
    }
    else{
        Forward_Slow(LeftWheel, 0);
    }

}

