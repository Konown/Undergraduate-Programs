//
// Created by chenh on 2024/2/21.
//

#ifndef TWOWHEELSCAR_F407VG_MOTOR_H
#define TWOWHEELSCAR_F407VG_MOTOR_H

#include "main.h"

#define pwm_max 5000
#define RightWheel 1
#define LeftWheel 2


void Forward_Slow(uint8_t id, uint16_t pwm);
void Back_Slow(uint8_t id, uint16_t pwm);

void Forward(uint16_t pwm);
void Back(uint16_t pwm);
void Stop();



#endif //TWOWHEELSCAR_F407VG_MOTOR_H
