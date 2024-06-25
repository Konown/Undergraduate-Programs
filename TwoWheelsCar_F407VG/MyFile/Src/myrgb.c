//
// Created by chenh on 2024/4/24.
//

#include "myrgb.h"

uint8_t RGB_BYTE_Buffer[PIXEL_NUM*24] = {0};

void RGB_Update(void){
    for (int j = 0; j < PIXEL_NUM*24; ++j) {
        for (int i = 0; i < Period_MX; ++i) {
            for (int k = 0; k < RGB_BYTE_Buffer[j]; ++k) {
                if (RGB_BYTE_Buffer[j] == TIM_ZERO) {
                    HAL_GPIO_WritePin(RGB_GPIO_Port, RGB_Pin, GPIO_PIN_RESET);
                }
                else if (RGB_BYTE_Buffer[j] == TIM_ONE){
                    HAL_GPIO_WritePin(RGB_GPIO_Port, RGB_Pin, GPIO_PIN_SET);
                }
            }
        }
    }
    HAL_GPIO_WritePin(RGB_GPIO_Port, RGB_Pin, GPIO_PIN_RESET);
}

void AX_RGB_SetFullColor( uint8_t r, uint8_t g, uint8_t b)
{
    for(uint8_t j=0;j<8;j++)
    {
        RGB_BYTE_Buffer[j] = ((g<<j) & 0x0080) ? TIM_ONE:TIM_ZERO;
        RGB_BYTE_Buffer[j+8] = ((r<<j) & 0x0080) ? TIM_ONE:TIM_ZERO;
        RGB_BYTE_Buffer[j+16] = ((b<<j) & 0x0080) ? TIM_ONE:TIM_ZERO;
    }

    for(uint8_t i=1; i<PIXEL_NUM; i++ )
    {
        for(uint8_t j=0;j<24;j++)
        {
            RGB_BYTE_Buffer[(24*i)+j] = RGB_BYTE_Buffer[j];
        }
    }

    RGB_Update();
    //RGB彩灯更新数据
}

