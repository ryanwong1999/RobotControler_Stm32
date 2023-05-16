#ifndef __BSP_RS485_H
#define __BSP_RS485_H

#define USART_RS485    							UART4
/* RS485_CS*/     
#define RS485_TX_EN_PORT_CLK				RCC_AHB1Periph_GPIOD
#define RS485_TX_EN_PORT            GPIOD
#define RS485_TX_EN_PIN             GPIO_Pin_3

#define RS485_TX_ENABLE             GPIO_ResetBits(RS485_TX_EN_PORT, RS485_TX_EN_PIN);
#define RS485_RX_ENABLE             GPIO_SetBits(RS485_TX_EN_PORT, RS485_TX_EN_PIN);	 
#define RS485_TX_DISABLE            RS485_RX_ENABLE
	 
void RS485_Cfg_Init(uint32_t lBaudrate);
void RS485_SendOneByte(USART_TypeDef* pUSARTx, uint8_t cDat);
void RS485_SendMultibyte(USART_TypeDef* pUSARTx, uint8_t *pBuf, uint16_t lLength);
void RS485_SendString(USART_TypeDef* pUSARTx, uint8_t *pStr);

#endif 