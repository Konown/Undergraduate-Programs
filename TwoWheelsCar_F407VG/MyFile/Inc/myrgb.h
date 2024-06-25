//
// Created by chenh on 2024/4/24.
//

#ifndef TWOWHEELSCAR_F407VG_MYRGB_H
#define TWOWHEELSCAR_F407VG_MYRGB_H

#include "main.h"

#define  PIXEL_NUM  8

#define Period_MX 210
#define TIM_ONE 143
#define TIM_ZERO 67

void RGB_Update(void);
void AX_RGB_SetFullColor( uint8_t r, uint8_t g, uint8_t b);

#endif //TWOWHEELSCAR_F407VG_MYRGB_H
