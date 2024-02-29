#ifndef __APP_USART_H
#define __APP_USART_H

#include "includes.h"	

#define RX_LEN_MAX  24
#define TX_LEN_MAX  24
	 
#define USART_PC  USART3

typedef struct 
{
	uint8_t Rx_Sta;    					//接收状态
  uint8_t Rx_Len;     				//接收数据长度
	uint16_t Comm_TimeOut;
	uint8_t Disconnect_flag;
	bool Usart_Rx_OK;    				//接收完成
	uint8_t Rx_Buf[RX_LEN_MAX];	//接收数组
}Usart_TypeDef;


extern Usart_TypeDef UsartToPC;
extern Usart_TypeDef UsartToTest;
extern Usart_TypeDef UsartToDrv;
extern Usart_TypeDef UsartToImu;
//extern Usart_TypeDef UsartToVoice;

#endif 