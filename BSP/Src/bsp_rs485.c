#include "includes.h" 

void RS485_Cfg_Init(uint32_t lBaudrate)
{
	//GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RS485_TX_EN_PORT_CLK, ENABLE); 

  GPIO_InitStructure.GPIO_Pin 	= RS485_TX_EN_PIN  ;
  GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_OUT;		      			//���
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;        				//�������
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_NOPULL;      				//������,Ҳ������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	 
  GPIO_Init(RS485_TX_EN_PORT, &GPIO_InitStructure);	

	RS485_RX_ENABLE;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); 				//ʹ��GPIOAʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);					//ʹ��USART1ʱ��
	//USART1�˿�����
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_10 | GPIO_Pin_11;		//GPIOA9��GPIOA10
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF;            			//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	      			//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;          			//���츴�����
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP;            			//����
	GPIO_Init(GPIOC, &GPIO_InitStructure);                   			//��ʼ��PA9��PA10
	//����1��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_UART4); 		//GPIOA9����ΪUSART1
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_UART4); 		//GPIOA10����ΪUSART1
	//USART1 ��ʼ������
	USART_InitStructure.USART_BaudRate 						= lBaudrate;                 				//����������
	USART_InitStructure.USART_WordLength 					= USART_WordLength_8b;     					//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits 						= USART_StopBits_1;          				//һ��ֹͣλ
	USART_InitStructure.USART_Parity 							= USART_Parity_No;             			//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		//��Ӳ������������
	USART_InitStructure.USART_Mode 								= USART_Mode_Rx | USART_Mode_Tx;		//�շ�ģʽ
	USART_Init(USART_RS485, &USART_InitStructure);                       							//��ʼ������1
	USART_ITConfig(USART_RS485, USART_IT_RXNE, ENABLE);	/* ʹ�ܽ����ж� */
	/*
		USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
		ע��: ��Ҫ�ڴ˴��򿪷����ж�
		�����ж�ʹ����SendUart()������
	*/
	USART_Cmd(USART_RS485, ENABLE);		/* ʹ�ܴ��� */
	//CPU��Сȱ�ݣ��������úã����ֱ��Send�����1���ֽڷ��Ͳ���ȥ�������������1���ֽ��޷���ȷ���ͳ�ȥ������
	USART_ClearFlag(USART_RS485, USART_FLAG_TC);     /* �巢����ɱ�־��Transmission Complete flag */
}


//���ڷ���һ���ֽ�
void RS485_SendOneByte(USART_TypeDef* pUSARTx, uint8_t cDat)
{
	//����ʹ��
	//RS485_TX_ENABLE ;
	USART_GetFlagStatus(pUSARTx, USART_FLAG_TC);
	USART_SendData(pUSARTx, (uint8_t) cDat);
	/* Loop until the end of transmission */
	while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
	//RS485_SendOneByte(pUSARTx, cDat);
	//  �رշ���ʹ�ܣ��ȴ�����
	//RS485_RX_ENABLE;
}


//���ڷ����ַ���
void RS485_SendString(USART_TypeDef* pUSARTx, uint8_t *pStr)
{
	uint8_t i;
	RS485_TX_ENABLE;  //485����ʹ��
	delay_us(100);
  do 
  {
		RS485_SendOneByte(pUSARTx, *(pStr + i));
		i++;
  } 
	while(*(pStr + i)!='\0');
  /* �ȴ�������� */
  while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET){}	
	delay_us(100);
	RS485_RX_ENABLE; //485���ͽ�ֹ���������ģʽ	
}

//���͹̶����ȵ��ַ�����
void RS485_SendMultibyte(USART_TypeDef* pUSARTx, uint8_t *pBuf, uint16_t lLength)
{
	uint16_t i;
	RS485_TX_ENABLE;  //485����ʹ��
	delay_ms(1);
	USART_ClearFlag(pUSARTx, USART_FLAG_TC);   //�巢����Ǳ�־��Transmission Complete flag 
	for(i=0; i<lLength; i++)
	{
		RS485_SendOneByte(pUSARTx, pBuf[i]);
	}
  while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) == RESET);	//ע��˾���RS232��ͬ
	RS485_RX_ENABLE; //485���ͽ�ֹ���������ģʽ	
}
