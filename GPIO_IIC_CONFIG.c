/*DOC Encode Type: UTF-8*/
/*
*FileName:GPIO_IIC.c
*Description: use GPIO accomplish IIC SWITCH IO mode in STM32F1xx
*Author: RosaCentifolia 
*Version: V1.1
*Fixed record: 
*/
#include "GPIO_IIC_CONFIG.h"


#ifdef STM32F1xx_HAL_GPIO_H
/*This code is only used for GPIO SDA Pin mode switching of STM32F1 HAL
*This code can be deleted when using other MCU*/
/*此段代码仅用于STM32F1 HAL库的GPIO SDA脚模式切换
*使用其它单片机可以删除此代码*/
/*
*Function: STM32HAL_IICSDA_MODE_SWITCH()
*Value: modeSelection:GPIO_OUTPUT_MODE:output mode
                      GPIO_INPUT_MODE:input mode
*Description: switch SDA pin input and output mode
*Return: 
*Error:
*Author: RosaCentifolia
*/
void STM32HAL_GPIO_IICSDA_MODE_SWITCH( GPIO_SWITCH_MODE modeSelection ){
    
    GPIO_InitTypeDef GPIO_InitStruct={0};
    
    HAL_GPIO_DeInit(GPIOB, IIC_SDA_Pin);
    
    GPIO_InitStruct.Pin = IIC_SDA_Pin;
    if ( modeSelection==GPIO_OUTPUT_MODE ){
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
    }else{
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    }
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}
#endif

