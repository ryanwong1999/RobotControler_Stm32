#ifndef __BSP_USART_H
#define __BSP_USART_H

void USART8_Cfg_Init(uint32_t lBaudrate);	 
void USARTx_Cfg_Init(USART_TypeDef* pUSARTx, uint32_t iBaudrate);
void USARTx_SendOneByte(USART_TypeDef* pUSARTx, uint8_t cDat);
void USARTx_SendMultibyte(USART_TypeDef* pUSARTx, uint8_t *pBuf, uint32_t lLength);	 
void USARTx_SendString(USART_TypeDef* pUSARTx, uint8_t *pStr);	 

#endif