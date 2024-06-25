//
// Created by chenh on 2024/2/21.
//

#include "motor.h"
#include "tim.h"

void Forward_Slow(uint8_t id, uint16_t pwm){
    if (id == 1){
        __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, pwm_max-1);
        __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, pwm_max-pwm+1);
    }
    else if (id == 2){
        __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, pwm_max-1);
        __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, pwm_max-pwm+1);
    }
}

void Back_Slow(uint8_t id, uint16_t pwm){
    if (id == 1){
        __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, pwm_max-pwm+1);
        __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, pwm_max-1);
    }
    else if (id == 2){
        __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, pwm_max-pwm+1);
        __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, pwm_max-1);
    }
}


void Forward(uint16_t pwm){
    Forward_Slow(1, pwm);
    Forward_Slow(2, pwm);
}


void Back(uint16_t pwm){
    Back_Slow(1, pwm);
    Back_Slow(2, pwm);
}

void Stop(){
    Forward_Slow(1, 0);
    Forward_Slow(2, 0);
}