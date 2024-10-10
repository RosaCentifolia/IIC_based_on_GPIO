1-10: 本说明书以中文说明为准，编码格式为UTF-8，基于冗余性考虑附注机器翻译英文说明。
1-10: This manual is based on the Chinese instructions, the encoding format is UTF-8, and machine-translated English instructions are attached for redundancy.

2-10: 使用时务必配置GPIO_IIC_CONFIG.h头文件。
2-10: Be sure to configure the GPIO_IIC_CONFIG.h header file when using.

3-10: 本文档涉及的所有IIC通讯地址均为7bit格式，不包含读写标志位。
3-10: All IIC communication addresses mentioned in this document are in 7-bit format, excluding the read/write flag bit.

*以下为主要功能函数说明。
*The following is a description of the main functions.

4-10: ACK_REPORT GPIO_I2C_Puts(uint8_t SlaveAddr, uint8_t * sendQueue, uint8_t sendLength )
       -a.用于向指定地址的从机连续发送一串 uint8_t 的指令。通常首字节是寄存器指针，后续为指令。
       -a.Used to continuously send a string of uint8_t instructions to the slave at the specified address. Usually the first byte is the register pointer, followed by the instruction.
       -b.返回值ACK_REPORT表示发送结果，若全部发送成功返回ACK_repeat，若任意字节（含从机地址）发送失败则立刻退出并返回NACK_repeat 。
       -b.The return value ACK_REPORT indicates the result of the transmission. If all transmissions are successful, ACK_repeat is returned. If any byte (including the slave address) fails to be transmitted, the system will exit immediately and return NACK_repeat.

5-10: ACK_REPORT GPIO_I2C_Gets(uint8_t SlaveAddr, uint8_t * recvQueue, uint8_t recvLength )
       -a.用于在指定地址的从机连续接收一串 uint8_t 的报文。必须由主机指定接受长度。
       -a.Used to continuously receive a string of uint8_t messages from the slave at the specified address. The receiving length must be specified by the host.
       -b.返回值ACK_REPORT表示发送从机地址结果，若发送成功返回ACK_repeat，若发送失败则则立刻退出并返回NACK_repeat 。
       -b.The return value ACK_REPORT indicates the result of sending the slave address. If the sending is successful, it returns ACK_repeat. If the sending fails, it will exit immediately and return NACK_repeat.

6-10: ACK_REPORT GPIO_I2C_ReadSlavReg(uint8_t SlaveAddr, uint8_t * sendQueue, uint8_t sendLength, uint8_t * recvQueue, uint8_t recvLength )
       -a.用于读取指定地址的从机中指定寄存器的连续报文。必须由主机指定接受长度。
       -a.Used to read the continuous message of the specified register in the slave with the specified address. The host must specify the acceptance length.
       -b.返回值ACK_REPORT表示发送结果，若全部发送成功返回ACK_repeat；若发送写地址、写报文任意字节失败则立刻退出并返回NACK_repeat，发送读地址失败则立刻退出并返回NACK_repeatType2 。
       -b.The return value ACK_REPORT indicates the result of the transmission. If all transmissions are successful, ACK_repeat is returned. If the transmission of the write address or any byte of the message fails, the function will exit immediately and return NACK_repeat. If the transmission of the read address fails, the function will exit immediately and return NACK_repeatType.

7-10: Oscilloscope_IO_Speed_Test(void)
       -a.用于供示波器测试SCL、SDA管脚高低电平的切换速度。建议使用上升沿触发模式。
       -a.Used for the oscilloscope to test the switching speed of the high and low levels of the SCL and SDA pins. It is recommended to use the rising edge trigger mode.
       -b.仅在使能宏定义  GPIO_IIC_DEBUG_MODE 时可以调用。
       -b.Can only be called when the macro definition GPIO_IIC_DEBUG_MODE is enabled.

8-10: GPIO_I2C_RESET(void)
       -a.用于重新复位IIC。
       -a.Used to reset IIC.

9-10: Oscilloscope_IO_Speed_Test(void)
       -a.用于供示波器测试SCL、SDA管脚高低电平的切换速度。建议使用上升沿触发模式。
       -a.Used for the oscilloscope to test the switching speed of the high and low levels of the SCL and SDA pins. It is recommended to use the rising edge trigger mode.
       -b.仅在使能宏定义  GPIO_IIC_DEBUG_MODE 时可以调用
       -b.Can only be called when the macro definition GPIO_IIC_DEBUG_MODE is enabled.

*以下为debug模式下ACK和NACK统计的说明。
*The following is an explanation of ACK and NACK statistics in debug mode.

10-10：countNACK_repeat、countACK_repeat、countWaitACK、countACKsend、countNACKsend.
       -a.仅在使能宏定义  GPIO_IIC_DEBUG_MODE 时上述变量有效。
       -a.The above variables are only valid when the macro definition GPIO_IIC_DEBUG_MODE is enabled.
       -b.变量均为初值为0的 uint16_t 全局变量。
       -b.All variables are uint16_t global variables with an initial value of 0
