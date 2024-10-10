/*DOC Encode Type: UTF-8*/
/*
*FileName:GPIO_IIC.h
*Description: use GPIO accomplish IIC
*Author: RosaCentifolia 
*Version: V1.0
*Fixed record: 
*/

/*
*正常情况下不需要修改此文件
*Normally, you do not need to modify this file.
*使用前，应配置GPIO_IIC_CONFIG.h中的宏定义
*Before use, the macro definition in GPIO_IIC_CONFIG.h should be configured
*/

#ifndef __GPIO_IIC_H
#define __GPIO_IIC_H

#include <stdint.h>
#include "GPIO_IIC_CONFIG.h"


/*Gobal variable declaration*/
extern uint8_t g_GPIOI2C_recvBuf[]; /*IIC Recv buff*/
extern uint8_t g_GPIOI2C_recvBufLength;
extern uint8_t g_GPIOI2C_sendBuf[];/*IIC Sending buff*/
extern uint8_t g_GPIOI2C_send_bufLength;
/*Debug test variable*/
#ifdef  GPIO_IIC_DEBUG_MODE
extern volatile uint16_t    countNACK_repeat,
                            countACK_repeat,
                            countWaitACK,
                            countACKsend,
                            countNACKsend;
#endif
/*Typedef declaration*/
typedef enum{
    Restart = 0u,
    Start
}START_STATUS;
typedef enum{
    ACK_repeat = 0u,
    NACK_repeat,
    NACK_repeatType2
}ACK_REPORT;
/*Function declaration */
void GPIO_I2C_RESET(void);
ACK_REPORT GPIO_I2C_Puts(uint8_t SlaveAddr, uint8_t * sendQueue, uint8_t sendLength );
ACK_REPORT GPIO_I2C_Gets(uint8_t SlaveAddr, uint8_t * recvQueue, uint8_t recvLength );
ACK_REPORT GPIO_I2C_ReadSlavReg(uint8_t SlaveAddr, uint8_t * sendQueue, uint8_t sendLength, uint8_t * recvQueue, uint8_t recvLength );
void GPIO_IIC_Start(void);
void GPIO_IIC_Stop(void);
void GPIO_IIC_Send_Byte( uint8_t txDataByte );
uint8_t  GPIO_IIC_Read_Byte( ACK_REPORT ACK_status );
ACK_REPORT GPIO_IIC_Wait_ACK(void);
__WEAK void CPUdelay_10us( uint16_t delay_Countdown );

#ifdef  GPIO_IIC_DEBUG_MODE
void Oscilloscope_IO_Speed_Test(void);
#endif


#endif
