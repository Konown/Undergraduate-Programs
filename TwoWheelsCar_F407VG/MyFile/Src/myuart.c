//
// Created by chenh on 2024/2/21.
//

#include "myuart.h"
#include "stm32f4xx.h"
#include "encoder.h"

IMU_Data acle={0, 0, 0}, gyro={0, 0, 0}, angle={0, 0, 0};


void Send_User_Data(uint8_t num, uint8_t* address, uint8_t data_id){
    static uint8_t _data_to_send[70]={0};
    uint8_t _cnt=0;

    _data_to_send[_cnt++] = 0xAA;
    _data_to_send[_cnt++] = 0xFF;
    _data_to_send[_cnt++] = data_id;
    _data_to_send[_cnt++] = num;

    for (uint8_t i = 0; i < num; ++i) {
        _data_to_send[_cnt++] = *(address+i);
    }

    _data_to_send[3] = _cnt-4;

    uint8_t _sumcheck=0, _addcheck=0;
    for (uint8_t i = 0; i < (num+4); ++i) {
        _sumcheck += _data_to_send[i];
        _addcheck += _sumcheck;
    }
    _data_to_send[_cnt++] = _sumcheck;
    _data_to_send[_cnt++] = _addcheck;

    HAL_UART_Transmit_DMA(&huart1, _data_to_send, _cnt);
}

void mydebug_send_motor(int16_t speed, int16_t out, uint8_t id){
    static uint8_t _data_to_send[50]={0};
    uint8_t _cnt=0;

    _data_to_send[_cnt++] = BYTE0(speed);
    _data_to_send[_cnt++] = BYTE1(speed);
    _data_to_send[_cnt++] = BYTE0(out);
    _data_to_send[_cnt++] = BYTE1(out);

    Send_User_Data(_cnt, _data_to_send, id);
}


void IMU_DataAnalysis(void){
    static uint8_t state=1;
    static uint8_t receive_buf[11]={0};
    static uint8_t receive_num=0;
    uint8_t data = Uart3_Str.Uart_RecvBuff[0];
    if (state == 1) {
        receive_num = 0;
        if (data == 0x55){
            state = 0;
            receive_buf[receive_num++] = data;
        }
    } else{
        receive_buf[receive_num++] = data;
    }

    if (receive_num == 11){
        switch (receive_buf[1]) {
            case 0x51:  // acceleration
                acle.x = (int16_t)((receive_buf[3] << 8) | receive_buf[2]);
                acle.y = (int16_t)((receive_buf[5] << 8) | receive_buf[4]);
                acle.z = (int16_t)((receive_buf[7] << 8) | receive_buf[6]);
                break;
            case 0x52:
                gyro.x = (int16_t)((receive_buf[3] << 8) | receive_buf[2]);
                gyro.y = (int16_t)((receive_buf[5] << 8) | receive_buf[4]);
                gyro.z = (int16_t)((receive_buf[7] << 8) | receive_buf[6]);
                break;
            case 0x53:
                angle.x = (int16_t)((receive_buf[3] << 8) | receive_buf[2]);
                angle.y = (int16_t)((receive_buf[5] << 8) | receive_buf[4]);
                angle.z = (int16_t)((receive_buf[7] << 8) | receive_buf[6]);
//                HAL_UART_Transmit_DMA(&huart1, &receive_num, 1);
                break;
            default:
                break;
        }
        receive_num = 0;
        state = 1;
    }
}

void ROS_DataAnalysis(void){
    if (Uart2_Str.Uart_RecvBuff[0]==HeadFrame1 && Uart2_Str.Uart_RecvBuff[1]==HeadFrame2 && Uart2_Str.flag_new){
        uint8_t checksum=0;
        for (uint8_t i = 0; i < Uart2_Str.Uart_RecvBuff[3]+4; ++i) {
            checksum += Uart2_Str.Uart_RecvBuff[i];
        }
        if (Uart2_Str.Uart_RecvBuff[Uart2_Str.Uart_RecvLens-1] == checksum){
            switch (Uart2_Str.Uart_RecvBuff[2]) {
                case ID_ROS2CTR_VEL:
                    R_Vel.TG_IX = (int16_t)((Uart2_Str.Uart_RecvBuff[5]<<8) | Uart2_Str.Uart_RecvBuff[4]);
                    R_Vel.TG_IW = (int16_t)((Uart2_Str.Uart_RecvBuff[7]<<8) | Uart2_Str.Uart_RecvBuff[6]);
                    break;
                default:
                    break;
            }
        }

        Uart2_Str.flag_new = 0;
    }
}


void ROBOT_SendDataToRos(void){
    static uint8_t _data_to_send[70]={0};
    uint8_t _cnt=0;

    _data_to_send[_cnt++] = HeadFrame1;
    _data_to_send[_cnt++] = HeadFrame2;
    _data_to_send[_cnt++] = ID_CTR2ROS_DATA;
    _data_to_send[_cnt++] = 0;

    _data_to_send[_cnt++] = R_Vel.RT_IX;
    _data_to_send[_cnt++] = (uint8_t)(R_Vel.RT_IX >> 8);
    _data_to_send[_cnt++] = R_Vel.RT_IW;
    _data_to_send[_cnt++] = (uint8_t)(R_Vel.RT_IW >> 8);

    _data_to_send[_cnt++] = acle.x;
    _data_to_send[_cnt++] = (uint8_t)(acle.x >> 8);
    _data_to_send[_cnt++] = acle.y;
    _data_to_send[_cnt++] = (uint8_t)(acle.y >> 8);
    _data_to_send[_cnt++] = acle.z;
    _data_to_send[_cnt++] = (uint8_t)(acle.z >> 8);
    _data_to_send[_cnt++] = gyro.x;
    _data_to_send[_cnt++] = (uint8_t)(gyro.x >> 8);
    _data_to_send[_cnt++] = gyro.y;
    _data_to_send[_cnt++] = (uint8_t)(gyro.y >> 8);
    _data_to_send[_cnt++] = gyro.z;
    _data_to_send[_cnt++] = (uint8_t)(gyro.z >> 8);
    _data_to_send[_cnt++] = angle.x;
    _data_to_send[_cnt++] = (uint8_t)(angle.x >> 8);
    _data_to_send[_cnt++] = angle.y;
    _data_to_send[_cnt++] = (uint8_t)(angle.y >> 8);
    _data_to_send[_cnt++] = angle.z;
    _data_to_send[_cnt++] = (uint8_t)(angle.z >> 8);

    _data_to_send[3] = _cnt - 4;

    uint8_t checksum = 0;
    for (uint8_t i = 0; i < _cnt; ++i) {
        checksum += _data_to_send[i];
    }
    _data_to_send[_cnt++] = checksum;

    HAL_UART_Transmit_DMA(&huart2, _data_to_send, _cnt);
}


