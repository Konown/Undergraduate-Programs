//
// Created by chenh on 2024/4/12.
//

#ifndef TWOWHEELSCAR_F407VG_MYPID_H
#define TWOWHEELSCAR_F407VG_MYPID_H

#include "main.h"

typedef struct pid{
    int16_t Sv;
    int16_t Sv_1;
    int16_t Pv;
    int16_t Pv_1;
    int16_t Error;
    int16_t Error_1;
    int16_t Error_2;
    int16_t SEk;
    int16_t DEk;
    float Kp;
    float Ki;
    float Kd;
    int16_t Out;
    int16_t Out_1;
}PID;


extern PID LeftSpeedPid, RightSpeedPid;
extern uint8_t flag_speed;

void SpeedPid_Init(PID* pid, uint16_t Sv, float Kp, float Ki, float Kd);
void Calc_SpeedPid(PID* pid);
int16_t LimitSpeed(int16_t pwm);

#endif //TWOWHEELSCAR_F407VG_MYPID_H
