//
// Created by chenh on 2024/2/21.
//

#ifndef TWOWHEELSCAR_F407VG_MYUART_H
#define TWOWHEELSCAR_F407VG_MYUART_H

#include "main.h"
#include "usart.h"

#define BYTE0(dwTemp) (*((char *)(&dwTemp)))
#define BYTE1(dwTemp) (*((char *)(&dwTemp)+1))
#define BYTE2(dwTemp) (*((char *)(&dwTemp)+2))
#define BYTE3(dwTemp) (*((char *)(&dwTemp)+3))

#define HeadFrame1 0xAA
#define HeadFrame2 0xBB
#define ID_CTR2ROS_DATA 0x10
#define ID_ROS2CTR_VEL 0x50


typedef struct{
    int16_t x;
    int16_t y;
    int16_t z;
}IMU_Data;


void ROBOT_SendDataToRos(void);

void Send_User_Data(uint8_t num, uint8_t* address, uint8_t data_id);
void mydebug_send_motor(int16_t speed, int16_t out, uint8_t id);

void ROS_DataAnalysis(void);
void IMU_DataAnalysis(void);

#endif //TWOWHEELSCAR_F407VG_MYUART_H
