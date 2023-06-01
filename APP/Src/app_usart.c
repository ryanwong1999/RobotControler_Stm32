#include "includes.h" 

Usart_TypeDef	UsartToPC;
Usart_TypeDef UsartToTest;
Usart_TypeDef UsartToDrv;
//Usart_TypeDef UsartToEnviro;
//Usart_TypeDef UsartToVoice;


/************************************************/
//函数功能：串口1 中断函数，用于测试
//输入参数：
//返回值：
//备注：
/************************************************/
void USART1_IRQHandler(void)  
{
	uint8_t dat;
	// 串口数据接收处理
  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)	//若接收数据寄存器满
  {  	
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);       
		dat = USART_ReceiveData(USART1);           					//先把UART1串口数据取出来暂存
		if(UsartToTest.Usart_Rx_OK == false)
		{
			if((UsartToTest.Rx_Sta & 0x02) != 0x02 )    			//收到帧头
			{
				if((UsartToTest.Rx_Sta & 0x01) != 0x01)
				{
					if(dat == 0x55)
					{
						UsartToTest.Rx_Len = 0;
						UsartToTest.Rx_Buf[UsartToTest.Rx_Len++] = dat;
						UsartToTest.Rx_Sta |= 0x01;
					}
				}
				else 
				{
					if(dat == 0xAA)
					{
						UsartToTest.Rx_Buf[UsartToTest.Rx_Len++] = dat;
						UsartToTest.Rx_Sta |= 0x02;
					}
					else if(dat == 0x55)
					{
						UsartToTest.Rx_Len = 0;;
						UsartToTest.Rx_Buf[UsartToTest.Rx_Len++] = dat;
						UsartToTest.Rx_Sta |= 0x01;
					}
					else 
					{
						UsartToTest.Rx_Len = 0;
						UsartToTest.Rx_Sta = 0;
						UsartToTest.Usart_Rx_OK = false;
					}
				}
			}
			else 
			{
				UsartToTest.Rx_Buf[UsartToTest.Rx_Len++] = dat;
				if((UsartToTest.Rx_Sta & 0x04) !=  0x04)
				{
					if(UsartToTest.Rx_Len == UsartToTest.Rx_Buf[3] - 1)
					{
						if(dat == 0x0D)
						{
							UsartToTest.Rx_Sta |= 0x04;
						}
						else 
						{
							UsartToTest.Rx_Len = 0;
							UsartToTest.Rx_Sta = 0;
							UsartToTest.Usart_Rx_OK = false;
						}
					}
				}
				else
				{
					if(dat == 0x0A)
					{
						UsartToTest.Rx_Buf[UsartToTest.Rx_Len] = dat;

						UsartToTest.Rx_Len = 0;
						UsartToTest.Rx_Sta = 0;
						UsartToTest.Usart_Rx_OK = true ;         //接收完成
					}
					else 
					{
						UsartToTest.Rx_Len = 0;
						UsartToTest.Rx_Sta = 0;
						UsartToTest.Usart_Rx_OK = false;
					}
				}
			}
		}   
	}
}


/************************************************/
//函数功能：中断函数，工控机通信
//输入参数：
//返回值：
//备注：
/************************************************/
void USART3_IRQHandler(void)  
{
	static unsigned char bTemp;
	static unsigned char dat;
	static unsigned char res;
	static unsigned char rfid_flag = 0;
	uint8_t checksum = 0;
	static uint16_t distance = 0;

	// 串口数据接收处理
  if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)	//若接收数据寄存器满
  {  	
		USART_ClearITPendingBit(USART3, USART_IT_RXNE);
		dat = USART_ReceiveData(USART3);//(USART1->DR);			//读取接收到的数据
//	  USARTx_SendOneByte(USART1, dat);
		if(UsartToPC.Usart_Rx_OK == false)
		{
			if((UsartToPC.Rx_Sta & 0x02) != 0x02)							//收到帧头
			{
				if((UsartToPC.Rx_Sta & 0x01) != 0x01)
				{
					if(dat == 0x55)
					{
						UsartToPC.Rx_Len = 0;
						UsartToPC.Rx_Buf[UsartToPC.Rx_Len++] = dat;
						UsartToPC.Rx_Sta |= 0x01;
					}
				}
				else 
				{
					if(dat == 0xAA)
					{
						UsartToPC.Rx_Buf[UsartToPC.Rx_Len++] = dat;
						UsartToPC.Rx_Sta |= 0x02;
					}
					else if(dat == 0x55)
					{
						UsartToPC.Rx_Len = 0;;
						UsartToPC.Rx_Buf[UsartToPC.Rx_Len++] = dat;
						UsartToPC.Rx_Sta |= 0x01;
					}
					else 
					{
						UsartToPC.Rx_Len = 0;
						UsartToPC.Rx_Sta = 0;
						UsartToPC.Usart_Rx_OK = false;
					}
				}
			}
			else 
			{
				UsartToPC.Rx_Buf[UsartToPC.Rx_Len++] = dat;
				if((UsartToPC.Rx_Sta & 0x04) !=  0x04)
				{
					if(UsartToPC.Rx_Len == UsartToPC.Rx_Buf[3] - 1)
					{
						if(dat == 0x0D)
						{
//							Usart3_Rx_Struct.Rx_Buf[Usart3_Rx_Struct.Rx_Len] = dat;
							UsartToPC.Rx_Sta |= 0x04;
						}
						else 
						{
							UsartToPC.Rx_Len = 0;
							UsartToPC.Rx_Sta = 0;
							UsartToPC.Usart_Rx_OK = false;
						}
					}
				}
				else
				{
					if(dat == 0x0A)
					{
						UsartToPC.Rx_Buf[UsartToPC.Rx_Len] = dat;

						UsartToPC.Rx_Len = 0;
						UsartToPC.Rx_Sta = 0;
						UsartToPC.Usart_Rx_OK = true ;         //接收完成
					}
					else 
					{
						UsartToPC.Rx_Len = 0;
						UsartToPC.Rx_Sta = 0;
						UsartToPC.Usart_Rx_OK = false;
					}
				}
			}
		} 
	}
}


/************************************************/
//函数功能：中断函数，电机驱动器通信
//输入参数：
//返回值：
//备注：
/************************************************/
void UART4_IRQHandler(void)   
{	
	static uint8_t dat;
	if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)	//若接收数据寄存器满
  {  	
		USART_ClearITPendingBit(UART4, USART_IT_RXNE);       
		dat = USART_ReceiveData(UART4);           					//先把UART4串口数据取出来暂存
//	  USARTx_SendOneByte(USART1, dat);
		if(UsartToDrv.Usart_Rx_OK == false)
		{
			UsartToDrv.Rx_Buf[UsartToDrv.Rx_Len++] = dat;
			TIM_SetCounter(TIM7,0);
			TIM_Cmd(TIM7,ENABLE);
		}
	}
}