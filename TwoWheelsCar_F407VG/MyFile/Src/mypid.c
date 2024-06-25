//
// Created by chenh on 2024/4/12.
//

#include "mypid.h"
#include "motor.h"

PID LeftSpeedPid, RightSpeedPid;

void SpeedPid_Init(PID* pid, uint16_t Sv, float Kp, float Ki, float Kd){
    pid->Sv = Sv;
    pid->Pv = 0;
    pid->Pv_1 = 0;

    pid->Kp = Kp;
    pid->Ki = Ki;
    pid->Kd = Kd;

    pid->Error = 0;
    pid->Error_1 = 0;
    pid->Error_2 = 0;
    pid->SEk = 0;
    pid->DEk = 0;
    pid->Out = 0;
    pid->Out_1 = 0;
}

void Calc_SpeedPid(PID* pid){

    pid->Error = pid->Sv - pid->Pv;
    if (pid->Sv * pid->Sv_1 < 0){
        RightSpeedPid.SEk = 0;
        LeftSpeedPid.SEk = 0;
    }
    if ( (pid->Error<300&&pid->Error>0) || (pid->Error>-300&&pid->Error<0) ){
        pid->SEk += pid->Error;
    }

    if (pid->SEk > 1800){
        pid->SEk = 1800;
    }
    else if (pid->SEk < -1800){
        pid->SEk = -1800;
    }

    pid->DEk = pid->Pv - pid->Pv_1;
    pid->Out = (int16_t)(pid->Kp*pid->Error + pid->Ki*pid->SEk +pid->Kd*pid->DEk);

//    pid->Out += pid->Out_1;
    pid->Out = LimitSpeed(pid->Out);


//    pid->Out_1 = pid->Out;
    pid->Sv_1 = pid->Sv;
    pid->Pv_1 = pid->Pv;
    pid->Error_1 = pid->Error;
}

int16_t LimitSpeed(int16_t pwm){
    if (pwm > 5000)
        pwm = 5000;
    else if (pwm < -5000)
        pwm = -5000;

    return pwm;
}


