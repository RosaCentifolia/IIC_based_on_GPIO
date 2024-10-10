/*DOC Encode Type: UTF-8*/
/*
*FileName:GPIO_IIC_CONFIG.h
*Description: Initialization settings for configuring GPIO accomplish IIC
*用途：配置GPIO模拟IIC通讯的初始化设置
*Author: RosaCentifolia 
*Version: V1.0
*Fixed record: 
*/

#ifndef __GPIO_IIC_CONFIG_H
#define __GPIO_IIC_CONFIG_H

/*Configuration start
**配置开始
**Preset 13 #define, 1 required #include and 1 optional #include
**预先设置13个#define、1个必须的#include和一个可选的#include
*/

/*Include GPIO Pin IO control headfile
**包含GPIO pin控制的的头文件*/
//#include "empty.h"  

/*Includes an optional header to override the software delay mode
**包含一个可选的覆写软件延迟方式的头文件
**Default state used:
**缺省状态下将使用：
*   __WEAK void CPUdelay_10us( uint16_t delay_Countdown )
***/

//#include  "empty.h"

/*Include the optional header file above
*在上方包含可选的头文件
*/

/*Configure the system clock of __WEAK void CPUdelay_10us( uint16_t delay_Countdown )
*配置__WEAK void CPUdelay_10us( uint16_t delay_Countdown ) 的系统时钟
*Override can be default
*覆写时可以缺省
****#define DLY_SYSTEM_CLOCK_MHz
*/
#define DLY_SYSTEM_CLOCK_MHz  72 

/*
*If don't need debug mode based on statistical ACK and NACK, 
*and function Oscilloscope_IO_Speed_Test(void)
*如果不需要基于ACK和NACK统计的debug模式和函数 Oscilloscope_IO_Speed_Test(void)
*Please comment this define
*请注释这条宏定义
****#define GPIO_IIC_DEBUG_MODE
*/
#define GPIO_IIC_DEBUG_MODE


/*Config Macro*/
/*配置宏定义*/

/*send&recv stack size, word size=uint8_t
*#define  stack_length_GPIOI2C_Recv_buf
*#define  stack_length_GPIOI2C_Send_buf
*发送和接收堆栈长度，字长=uint8_t*/

#define  stack_length_GPIOI2C_Recv_buf  3    /*Define it yourself*/
#define  stack_length_GPIOI2C_Send_buf  3    /*Define it yourself*/


/*ACK waitting limited period
*#define  MAXMUIN_ACK_Error
*等待ACK应答的最大周期*/
#define  MAXMUIN_ACK_Error      255


/*GPIO Pin ctrl
*#define  GPIO_IIC_SDA_OUTPUT_MODE
*#define  GPIO_IIC_SDA_INPUT_MODE
*#define  GPIO_IIC_SDA_PIN_Input_High
*#define  GPIO_IIC_SDA_PIN_Input_Low
*#define  GPIO_IIC_SDA_PIN_Set_to_High
*#define  GPIO_IIC_SDA_PIN_Set_to_Low
*#define  GPIO_IIC_SCL_PIN_Set_to_High
*#define  GPIO_IIC_SCL_PIN_Set_to_Low
*GPIO Pin 控制*/
#define  GPIO_IIC_SDA_OUTPUT_MODE        
#define  GPIO_IIC_SDA_INPUT_MODE         
#define  GPIO_IIC_SDA_PIN_Input_High     
#define  GPIO_IIC_SDA_PIN_Input_Low      
#define  GPIO_IIC_SDA_PIN_Set_to_High    
#define  GPIO_IIC_SDA_PIN_Set_to_Low     
#define  GPIO_IIC_SCL_PIN_Set_to_High    
#define  GPIO_IIC_SCL_PIN_Set_to_Low     


/*Configuration completed
**配置结束
**A total of 13 #define, 1 required #include and one optional #include
**总计13个#define、1个必须的#include和一个可选的#include
*/



#endif

