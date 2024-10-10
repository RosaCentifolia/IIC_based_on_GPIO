/*DOC Encode Type: UTF-8*/
/*
*FileName:GPIO_IIC.c
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


#include "GPIO_IIC.h"

uint8_t g_GPIOI2C_recvBuf[stack_length_GPIOI2C_Recv_buf]; /*IIC Recv buff*/
uint8_t g_GPIOI2C_recvBufLength=0;
uint8_t g_GPIOI2C_sendBuf[stack_length_GPIOI2C_Send_buf];/*IIC Send buff*/
uint8_t g_GPIOI2C_send_bufLength=0;

/*debug test variable*/
#ifdef  GPIO_IIC_DEBUG_MODE
volatile uint16_t    countNACK_repeat=0,
                     countACK_repeat=0,
                     countWaitACK=0,
                     countACKsend=0,
                     countNACKsend=0;
#endif

/*
*Function: I2C_Puts(uint8_t SlaveAddr, uint8_t * sendQueue, uint8_t sendLength )
*Value: SlaveAddr: slave chip address,
        sendQueue: message queue
        sendlength:message length
*Description: Using in send a queue which length is sendlegth to SlaveAddr device by GPIO IIC
*Return: ACKstatus: ACK_repeat: sending successful
                    NACK_repeat:sended had error 

*Error:
*Author: RosaCentifolia
*/
ACK_REPORT GPIO_I2C_Puts(uint8_t SlaveAddr, uint8_t * sendQueue, uint8_t sendLength )
{
	uint8_t cursor;
    ACK_REPORT ACKstatus;
    
	/*prepare slave address and writing symbol */
	uint8_t DeviceSelect = ( SlaveAddr<<1 )&0xFE; 
	
	GPIO_IIC_Start();
    /*Send slave address and writing symbol */
	GPIO_IIC_Send_Byte(DeviceSelect);
    ACKstatus=GPIO_IIC_Wait_ACK();  /*Waitting ACK*/
    
	if( ACKstatus==ACK_repeat ){/*if ACK, start transmit*/
		for(cursor=0; cursor<sendLength; cursor++){
			GPIO_IIC_Send_Byte( sendQueue[cursor] );
			ACKstatus=GPIO_IIC_Wait_ACK();   /*ACK check*/
            if( ACKstatus!=ACK_repeat ){
                break;      /*if NACK, abroad transmit*/
            }
		}
	}
	GPIO_IIC_Stop();
	return ACKstatus;
}

/*
*Function: I2C_Gets(uint8_t SlaveAddr, uint8_t * recvQueue, uint8_t recvLength )
*Value: SlaveAddr: slave chip address,
        recvQueue: message queue
        recvLength:recv message length
*Description: Using in receive a queue which length is recvlength from SlaveAddr device by GPIO IIC
*Return:  ACKstatus: ACK_repeat: initiate receiving successful
                     NACK_repeat:initiated received had error 
*Error:
*Author: RosaCentifolia
*/
ACK_REPORT GPIO_I2C_Gets(uint8_t SlaveAddr, uint8_t * recvQueue, uint8_t recvLength )
{
	uint8_t cursor;
    ACK_REPORT ACKstatus;
    
	/*prepare slave address and reading symbol */
	uint8_t DeviceSelect = ( SlaveAddr<<1 )|0x01;

	GPIO_IIC_Start();
    /*Send slave address and  reading symbol */
	GPIO_IIC_Send_Byte( DeviceSelect );
    ACKstatus=GPIO_IIC_Wait_ACK();  /*Waiting ACK*/
    
	if( ACKstatus==ACK_repeat ){ /*if ACK, start receive*/
		for(cursor=0; cursor<recvLength; cursor++){
			if( recvLength==cursor+1 ){
            /*Last recv byte NACK, ready to stop*/
            recvQueue[cursor]=GPIO_IIC_Read_Byte(NACK_repeat);
            }else{
            recvQueue[cursor]=GPIO_IIC_Read_Byte(ACK_repeat);
            }
		}
	}
	GPIO_IIC_Stop();
	return  ACKstatus;
}

/*
*Function: I2C_ReadSlavReg(uint8_t SlaveAddr, uint8_t *sendQueue, uint8_t sendLength, uint8_t * recvQueue, uint8_t recvLength )
*Value: SlaveAddr: slave chip address,
        *sendQueue: message queue, such as regsiter&command
        sendLength: message length
        *recvQueue: message queue,
        recvLength:recv message length
*Description: reading register value from SlaveAddr device by GPIO IIC
*Return:   ACKstatus: ACK_repeat: read slave register successful
                      NACK_repeat: sended register and command had error 
                      NACK_repeatType2:writing register and command successful, but sended reading symbol error.
*Error:
*Author: RosaCentifolia
*/
ACK_REPORT GPIO_I2C_ReadSlavReg(uint8_t SlaveAddr, uint8_t *sendQueue, uint8_t sendLength, uint8_t *recvQueue, uint8_t recvLength ){
    
    uint8_t cursor;
    ACK_REPORT ACKstatus;
    
    /*prepare slave address and writing symbol */
    uint8_t DeviceSelect = ( SlaveAddr<<1 )&0xFE;
    
        GPIO_IIC_Start();
        /*Send slave address and writing symbol */
        GPIO_IIC_Send_Byte( DeviceSelect );
        /*Send register and commands*/
        ACKstatus=GPIO_IIC_Wait_ACK();  /*Waiting ACK*/
    
        if( ACKstatus==ACK_repeat ){/*if ACK, start transmit*/
            for(cursor=0;cursor<sendLength;cursor++){
                GPIO_IIC_Send_Byte( sendQueue[cursor] );
                ACKstatus=GPIO_IIC_Wait_ACK();  /*ACK check*/
                if( ACKstatus!=ACK_repeat ){
                    GPIO_IIC_Stop();      /*if NACK, abroad transmit*/
                    return ACKstatus;     /*runing here,should be return NACK_repeat*/
                }
            }
            /*prepare slave address and reading symbol */
            DeviceSelect = ( SlaveAddr<<1 )|0x01;
            GPIO_IIC_Start();
                
            /*Send slave address and reading symbol */
            GPIO_IIC_Send_Byte( DeviceSelect );
            ACKstatus=GPIO_IIC_Wait_ACK();  /*Waiting ACK*/
            if( ACKstatus==ACK_repeat ){ /*if ACK, start receive*/
                for(cursor=0; cursor<recvLength; cursor++){
                    if( recvLength==cursor+1 ){
                        /*Last recv byte NACK, ready to stop*/
                        recvQueue[cursor]=GPIO_IIC_Read_Byte(NACK_repeat);
                    }else{
                        recvQueue[cursor]=GPIO_IIC_Read_Byte(ACK_repeat);
                    }
                }
            }else{
                GPIO_IIC_Stop();
                ACKstatus=NACK_repeatType2;
                return ACKstatus;   /*runing here,should be return NACK_repeatType2*/
            }
    }
    GPIO_IIC_Stop();
    return ACKstatus;
}

/*
*Function: GPIO_I2C_RESET( void )
*Value: 
*Description: reset GPIO SDA pin to output mode, pull up SDA&SCL
*Return: 
*Error:
*Author: RosaCentifolia
*/
void GPIO_I2C_RESET( void ){
    GPIO_IIC_SDA_OUTPUT_MODE;
    GPIO_IIC_SCL_PIN_Set_to_Low;
    GPIO_IIC_SDA_PIN_Set_to_Low;
    /*Waiting for SMBUS mode timeout*/
    CPUdelay_10us(20);
    GPIO_IIC_SDA_PIN_Set_to_High;
    CPUdelay_10us(20);
    GPIO_IIC_SCL_PIN_Set_to_High;
    CPUdelay_10us(20);
}

/*
*Function: IIC_Start(void)
*Value: 
*Description: GPIO IIC running
*Return: 
*Error:
*Author: RosaCentifolia
*/
void GPIO_IIC_Start( void )
{
    /*step of restart:*/
    CPUdelay_10us(1);
	GPIO_IIC_SDA_PIN_Set_to_High;
    CPUdelay_10us(1);
	GPIO_IIC_SCL_PIN_Set_to_High;
    /*step of start:*/
	CPUdelay_10us(1);
    GPIO_IIC_SDA_PIN_Set_to_Low;
    CPUdelay_10us(1);
    GPIO_IIC_SCL_PIN_Set_to_Low;
    
	
}

/*
*Function: IIC_Stop(void)
*Value: 
*Description: GPIO IIC Stop
*Return: 
*Error:
*Author: RosaCentifolia
*/
void GPIO_IIC_Stop(void)
{
    /*STOP:when SCL to high, SDA set to high*/
    GPIO_IIC_SDA_OUTPUT_MODE;
    GPIO_IIC_SCL_PIN_Set_to_Low;
    GPIO_IIC_SDA_PIN_Set_to_Low;  
    /*Preliminary work to ensure shutdown finished*/
	CPUdelay_10us(1);
    GPIO_IIC_SCL_PIN_Set_to_High;
    CPUdelay_10us(1);
	GPIO_IIC_SDA_PIN_Set_to_High;
	CPUdelay_10us(1);							   	
}

/*
*Function: IIC_Send_Byte(uint8_t txDataByte )
*Value: 
*Description: GPIO IIC Send one byte
*Return: 
*Error:
*Author: RosaCentifolia
*/
void GPIO_IIC_Send_Byte(uint8_t txDataByte )
{                        
    uint8_t cursor,sendBit;

    for(cursor=0;cursor<8;cursor++){
        sendBit = txDataByte&0x80;
		CPUdelay_10us(1);
        if( sendBit==0x80 ){
            GPIO_IIC_SDA_PIN_Set_to_High;
        }else{
            GPIO_IIC_SDA_PIN_Set_to_Low;
        }
		txDataByte<<=1;
		CPUdelay_10us(1);
		GPIO_IIC_SCL_PIN_Set_to_High;
		CPUdelay_10us(1); 
		GPIO_IIC_SCL_PIN_Set_to_Low;
    }
}

/*
*Function: IIC_Read_Byte( uint8_t ackEn )
*Value: ACK_repeat:making an ACK by master
        NACK_repeat:don,t making an ACK by master
*Description: GPIO IIC Read one byte
*Return: recvByte
*Error:
*Author: RosaCentifolia
*/
uint8_t  GPIO_IIC_Read_Byte( ACK_REPORT ACK_status )
{
	uint8_t cursor, recvByte=0;
    
	GPIO_IIC_SDA_INPUT_MODE;    /*switch SDA to input mode*/

    for( cursor=0; cursor<8; cursor++ ){
        CPUdelay_10us(1);
		GPIO_IIC_SCL_PIN_Set_to_High;
        CPUdelay_10us(1);
        recvByte<<=1;
        if( GPIO_IIC_SDA_PIN_Input_High ){
            recvByte|=0x01;
        }else{
            recvByte&=0xFE;
        }
        GPIO_IIC_SCL_PIN_Set_to_Low;
    }

    GPIO_IIC_SDA_OUTPUT_MODE;   /*switch SDA to output mode*/
    CPUdelay_10us(1);
    /*making ACK or NACK*/
    if ( ACK_status==ACK_repeat ){
        GPIO_IIC_SDA_PIN_Set_to_Low;
        #ifdef  GPIO_IIC_DEBUG_MODE
        countACKsend+=1;
        #endif
    }else{
        GPIO_IIC_SDA_PIN_Set_to_High;
        #ifdef  GPIO_IIC_DEBUG_MODE
        countNACKsend+=1;
        #endif
    }
    CPUdelay_10us(1);
    GPIO_IIC_SCL_PIN_Set_to_High;
	CPUdelay_10us(1);
	GPIO_IIC_SCL_PIN_Set_to_Low;
    
    return recvByte;
}

/*
*Function: IIC_Wait_Ack(void)
*Value:
*Description: waitting ACK when get slave device massage
*Return: NACK_repeat: IIC slave device errror
         ACK_repeat: IIC slave device ready to send
*Error:
*Author: RosaCentifolia
*/

ACK_REPORT GPIO_IIC_Wait_ACK(void)
{
	uint16_t countErrTime=0;
    #ifdef  GPIO_IIC_DEBUG_MODE
    countWaitACK+=1;
    #endif

	GPIO_IIC_SDA_INPUT_MODE;       /*switch SDA to input mode*/
	CPUdelay_10us(1);
	GPIO_IIC_SCL_PIN_Set_to_High;
	CPUdelay_10us(1);	 
    
    for(countErrTime=0; countErrTime<MAXMUIN_ACK_Error; countErrTime++){  /*wating ACK*/
        if( GPIO_IIC_SDA_PIN_Input_Low ){   /*if recv ACK*/
            GPIO_IIC_SCL_PIN_Set_to_Low;
            GPIO_IIC_SDA_OUTPUT_MODE;   /*switch SDA to output mode*/
            #ifdef  GPIO_IIC_DEBUG_MODE
            countACK_repeat+=1;
            #endif
            return ACK_repeat;
        }
    }
    /*if recvn't ACK*/
    GPIO_IIC_SCL_PIN_Set_to_Low;
    GPIO_IIC_SDA_OUTPUT_MODE;   /*switch SDA to output mode*/
    GPIO_IIC_Stop();
    #ifdef  GPIO_IIC_DEBUG_MODE
    countNACK_repeat+=1;
    #endif
    return NACK_repeat;
}

/*
*Function: void CPUdelay_us( uint16_t )
*Value: delay_Countdown: number of software delays
*Description: software delay
*Return: 
*Error:
*Author: RosaCentifolia
*/
#if ( DLY_SYSTEM_CLOCK_MHz*10 < 8 )
#warning  "CPUdelay_10us mayben't be use"
#endif
__WEAK void CPUdelay_10us( uint16_t delay_Countdown ){
    
    uint16_t Count_10us = ( DLY_SYSTEM_CLOCK_MHz*10 )/8;
    
    Count_10us *= delay_Countdown;
    
    for(;Count_10us;Count_10us--)  ;
}


#ifdef  GPIO_IIC_DEBUG_MODE
/*
*Function: Oscilloscope_IO_Speed_Test(void)
*Value:
*Description: Used for oscilloscope testing the switching speed of SCL and SDA pins
*             Suggestion: Use rising edge trigger
*             Special notes: Hardware debugging method, no other intention
*Return: 
*Error:
*Author: RosaCentifolia
*/
void Oscilloscope_IO_Speed_Test(void){
    /*Shutdown communication*/
    GPIO_IIC_Stop();
    
    /*Function main body, start*/
    /*make a ready sign*/
    GPIO_IIC_SCL_PIN_Set_to_Low;
    GPIO_IIC_SDA_PIN_Set_to_Low;
    CPUdelay_10us(100);
    /*runing SDA pin check*/
    GPIO_IIC_SDA_PIN_Set_to_High;
    CPUdelay_10us(1);
    GPIO_IIC_SDA_PIN_Set_to_Low;
    CPUdelay_10us(1);
    GPIO_IIC_SDA_PIN_Set_to_High;
    CPUdelay_10us(1);
    GPIO_IIC_SDA_PIN_Set_to_Low;
    /*runing SCL pin check*/
    GPIO_IIC_SCL_PIN_Set_to_High;
    CPUdelay_10us(1);
    GPIO_IIC_SCL_PIN_Set_to_Low;
    CPUdelay_10us(1);
    GPIO_IIC_SCL_PIN_Set_to_High;
    CPUdelay_10us(1);
    GPIO_IIC_SCL_PIN_Set_to_Low;
    /*make a finished sign*/
    CPUdelay_10us(100);
    /*Function main body, over*/

    /*restore communication*/
    GPIO_IIC_Stop();
    }
#endif


