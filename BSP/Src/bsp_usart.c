#include "includes.h" 


//USART1��ʼ��
static void USART1_Cfg_Init(uint32_t lBaudrate)
{
	//GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 			//ʹ��GPIOAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);			//ʹ��USART1ʱ��
	//����1��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);		//GPIOA9����ΪUSART1
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);	//GPIOA10����ΪUSART1
	//USART1�˿�����
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_9 | GPIO_Pin_10;		//GPIOA9��GPIOA10
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF;            		//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	      		//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;          		//���츴�����
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP;            		//����
	GPIO_Init(GPIOA, &GPIO_InitStructure);                   		//��ʼ��PA9��PA10
	//USART1 ��ʼ������
	USART_InitStructure.USART_BaudRate 						= lBaudrate;             					//����������
	USART_InitStructure.USART_WordLength 					= USART_WordLength_8b;						//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits 						= USART_StopBits_1;     					//һ��ֹͣλ
	USART_InitStructure.USART_Parity 							= USART_Parity_No;        				//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//��Ӳ������������
	USART_InitStructure.USART_Mode 								= USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
	USART_Init(USART1, &USART_InitStructure); 																			//��ʼ������1
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);	/* ʹ�ܽ����ж� */
	/*
		USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
		ע��: ��Ҫ�ڴ˴��򿪷����ж�
		�����ж�ʹ����SendUart()������
	*/
	USART_Cmd(USART1, ENABLE);		/* ʹ�ܴ��� */
	//CPU��Сȱ�ݣ��������úã����ֱ��Send�����1���ֽڷ��Ͳ���ȥ,�����������1���ֽ��޷���ȷ���ͳ�ȥ������ 
	USART_ClearFlag(USART1, USART_FLAG_TC);				/* �巢����ɱ�־��Transmission Complete flag */
	//USART1 NVIC ͳһ����
}


//USART2��ʼ��
static void USART2_Cfg_Init(uint32_t lBaudrate)
{
	//GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 			//ʹ��GPIOAʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);			//ʹ��USART1ʱ��
	//����1��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2); 	//GPIOA9����ΪUSART1
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);		//GPIOA10����ΪUSART1
	//USART1�˿�����
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_2 | GPIO_Pin_3;		//GPIOA9��GPIOA10
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF;            		//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	      		//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;          		//���츴�����
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP;            		//����
	GPIO_Init(GPIOA, &GPIO_InitStructure);                   		//��ʼ��PA9��PA10
	//USART1 ��ʼ������
	USART_InitStructure.USART_BaudRate 						= lBaudrate;                 			//����������
	USART_InitStructure.USART_WordLength 					= USART_WordLength_8b;     				//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits 						= USART_StopBits_1;          			//һ��ֹͣλ
	USART_InitStructure.USART_Parity 							= USART_Parity_No;             		//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl	= USART_HardwareFlowControl_None;	//��Ӳ������������
	USART_InitStructure.USART_Mode 								= USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
	USART_Init(USART2, &USART_InitStructure);                       								// ��ʼ������1
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);	/* ʹ�ܽ����ж� */
	/*
		USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
		ע��: ��Ҫ�ڴ˴��򿪷����ж�
		�����ж�ʹ����SendUart()������
	*/
	USART_Cmd(USART2, ENABLE);		/* ʹ�ܴ��� */
	//CPU��Сȱ�ݣ��������úã����ֱ��Send�����1���ֽڷ��Ͳ���ȥ,�����������1���ֽ��޷���ȷ���ͳ�ȥ������ 
	USART_ClearFlag(USART2, USART_FLAG_TC);     /* �巢����ɱ�־��Transmission Complete flag */
	//USART1 NVIC ͳһ����
}


//USART3��ʼ��
static void USART3_Cfg_Init(uint32_t lBaudrate)
{
	//GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 				//ʹ��GPIOAʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);				//ʹ��USART1ʱ��
	//����1��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3); 		//GPIOA9����ΪUSART1
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3);		//GPIOA10����ΪUSART1
	//USART1�˿�����
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_10 | GPIO_Pin_11;		//GPIOA9��GPIOA10
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF;            			//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	      			//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;          			//���츴�����
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP;            			//����
	GPIO_Init(GPIOB, &GPIO_InitStructure);                   			//��ʼ��PA9��PA10
	//USART1 ��ʼ������
	USART_InitStructure.USART_BaudRate 						= lBaudrate;                			 	//����������
	USART_InitStructure.USART_WordLength 					= USART_WordLength_8b;     					//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits						= USART_StopBits_1;          				//һ��ֹͣλ
	USART_InitStructure.USART_Parity 							= USART_Parity_No;             			//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		//��Ӳ������������
	USART_InitStructure.USART_Mode 								= USART_Mode_Rx | USART_Mode_Tx;		//�շ�ģʽ
	USART_Init(USART3, &USART_InitStructure);                       									//��ʼ������1
	
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);	/* ʹ�ܽ����ж� */
	/*
		USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
		ע��: ��Ҫ�ڴ˴��򿪷����ж�
		�����ж�ʹ����SendUart()������
	*/
	USART_Cmd(USART3, ENABLE);		/* ʹ�ܴ��� */
	//CPU��Сȱ�ݣ��������úã����ֱ��Send�����1���ֽڷ��Ͳ���ȥ,�����������1���ֽ��޷���ȷ���ͳ�ȥ������ 
	USART_ClearFlag(USART3, USART_FLAG_TC);     /* �巢����ɱ�־��Transmission Complete flag */
	//USART1 NVIC ͳһ����
}


//USART4��ʼ��
static void UART4_Cfg_Init(uint32_t lBaudrate)
{
	//GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); 				//ʹ��GPIOAʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);					//ʹ��USART1ʱ��
	//����1��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_UART4); 		//GPIOA9����ΪUSART1
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_UART4);			//GPIOA10����ΪUSART1
	//USART1�˿�����
	GPIO_InitStructure.GPIO_Pin	 	= GPIO_Pin_10 | GPIO_Pin_11;		//GPIOA9��GPIOA10
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF;            			//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	      			//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;          			//���츴�����
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP;            			//����
	GPIO_Init(GPIOC, &GPIO_InitStructure);                   			//��ʼ��PA9��PA10
	//USART1 ��ʼ������
	USART_InitStructure.USART_BaudRate 						= lBaudrate;                 				//����������
	USART_InitStructure.USART_WordLength 					= USART_WordLength_8b;     					//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits 						= USART_StopBits_1;          				//һ��ֹͣλ
	USART_InitStructure.USART_Parity 							= USART_Parity_No;             			//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		//��Ӳ������������
	USART_InitStructure.USART_Mode 								= USART_Mode_Rx | USART_Mode_Tx;		//�շ�ģʽ
	USART_Init(UART4, &USART_InitStructure);                       										//��ʼ������1
	
	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);	/* ʹ�ܽ����ж� */
	/*
		USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
		ע��: ��Ҫ�ڴ˴��򿪷����ж�
		�����ж�ʹ����SendUart()������
	*/
	USART_Cmd(UART4, ENABLE);		/* ʹ�ܴ��� */
	//CPU��Сȱ�ݣ��������úã����ֱ��Send�����1���ֽڷ��Ͳ���ȥ,�����������1���ֽ��޷���ȷ���ͳ�ȥ������ 
	USART_ClearFlag(UART4, USART_FLAG_TC);     /* �巢����ɱ�־��Transmission Complete flag */
	//USART1 NVIC ͳһ����
}


//USART5��ʼ��
static void UART5_Cfg_Init(uint32_t lBaudrate)
{
	//GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); 			//ʹ��GPIOAʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); 			//ʹ��GPIOAʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);				//ʹ��USART1ʱ��
	//����1��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource12, GPIO_AF_UART5); 	//GPIOA9����ΪUSART1
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource2, GPIO_AF_UART5);		//GPIOA10����ΪUSART1
	//USART1�˿�����
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_12; 								//GPIOA9��GPIOA10
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF;            		//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	      		//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;          		//���츴�����
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP;            		//����
	GPIO_Init(GPIOC, &GPIO_InitStructure);                   		//��ʼ��PA9��PA10
	//USART1�˿�����
	GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_2; 								//GPIOA9��GPIOA10
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF;            		//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	      		//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;          		//���츴�����
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP;            		//����
	GPIO_Init(GPIOD,&GPIO_InitStructure);                   		//��ʼ��PA9��PA10
	//USART1 ��ʼ������
	USART_InitStructure.USART_BaudRate 						= lBaudrate;                 				//����������
	USART_InitStructure.USART_WordLength 					= USART_WordLength_8b;     					//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits 						= USART_StopBits_1;          				//һ��ֹͣλ
	USART_InitStructure.USART_Parity 							= USART_Parity_No;             			//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		//��Ӳ������������
	USART_InitStructure.USART_Mode								= USART_Mode_Rx | USART_Mode_Tx;		//�շ�ģʽ
	USART_Init(UART5, &USART_InitStructure);                       										//��ʼ������1
	USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);	/* ʹ�ܽ����ж� */
	/*
		USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
		ע��: ��Ҫ�ڴ˴��򿪷����ж�
		�����ж�ʹ����SendUart()������
	*/
	USART_Cmd(UART5, ENABLE);		/* ʹ�ܴ��� */
	//CPU��Сȱ�ݣ��������úã����ֱ��Send�����1���ֽڷ��Ͳ���ȥ,�����������1���ֽ��޷���ȷ���ͳ�ȥ������ 
	USART_ClearFlag(UART5, USART_FLAG_TC);     /* �巢����ɱ�־��Transmission Complete flag */
	//USART1 NVIC ͳһ����
}


//USART8��ʼ��
void USART8_Cfg_Init(uint32_t lBaudrate)
{
	//GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); 			//ʹ��GPIOEʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART8, ENABLE);				//ʹ��USART8ʱ��
	//����1��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource0, GPIO_AF_UART8);		//GPIOE0����ΪUSART8
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource1, GPIO_AF_UART8);		//GPIOE1����ΪUSART8
	//USART1�˿�����
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_0 | GPIO_Pin_1;		//GPIOE0��GPIOE1
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF;            		//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	      		//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;          		//���츴�����
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP;            		//����
	GPIO_Init(GPIOE, &GPIO_InitStructure);                   		//��ʼ��PE0��PE1
	//USART1 ��ʼ������
	USART_InitStructure.USART_BaudRate 						= lBaudrate;                 				//����������
	USART_InitStructure.USART_WordLength 					= USART_WordLength_8b;     					//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits 						= USART_StopBits_1;          				//һ��ֹͣλ
	USART_InitStructure.USART_Parity 							= USART_Parity_No;             			//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		//��Ӳ������������
	USART_InitStructure.USART_Mode 								= USART_Mode_Rx | USART_Mode_Tx;		//�շ�ģʽ
	USART_Init(UART8, &USART_InitStructure);                       										// ��ʼ������1
	USART_ITConfig(UART8, USART_IT_RXNE, ENABLE);	/* ʹ�ܽ����ж� */
	/*
		USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
		ע��: ��Ҫ�ڴ˴��򿪷����ж�
		�����ж�ʹ����SendUart()������
	*/
	USART_Cmd(UART8, ENABLE);		/* ʹ�ܴ��� */
	//CPU��Сȱ�ݣ��������úã����ֱ��Send�����1���ֽڷ��Ͳ���ȥ,�����������1���ֽ��޷���ȷ���ͳ�ȥ������ 
	USART_ClearFlag(UART8, USART_FLAG_TC);     /* �巢����ɱ�־��Transmission Complete flag */
	//USART1 NVIC ͳһ����
}


//USART��ʼ��
void USARTx_Cfg_Init(USART_TypeDef* pUSARTx, uint32_t iBaudrate)
{
	if(pUSARTx == USART1) USART1_Cfg_Init(iBaudrate);
	else if(pUSARTx == USART2) USART2_Cfg_Init(iBaudrate);
	else if(pUSARTx == USART3) USART3_Cfg_Init(iBaudrate);
	else if(pUSARTx == UART4) UART4_Cfg_Init(iBaudrate);
	else if(pUSARTx == UART5) UART5_Cfg_Init(iBaudrate);
	else if(pUSARTx == UART8) USART8_Cfg_Init(iBaudrate);
}


//���ڷ���һ���ֽں���
void USARTx_SendOneByte(USART_TypeDef* pUSARTx, uint8_t cDat)
{
	USART_GetFlagStatus(pUSARTx,USART_FLAG_TC);
	USART_SendData(pUSARTx, (uint8_t) cDat);
	/* Loop until the end of transmission */
	while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}


//���ڷ��Ͷ���ֽں���
void USARTx_SendMultibyte(USART_TypeDef* pUSARTx, uint8_t *pBuf, uint32_t lLength)
{
	uint8_t i;
	for(i=0; i<lLength; i++)
	{
		USARTx_SendOneByte(pUSARTx,*pBuf);
		pBuf++;                           // ָ���ַ��1
	}
}


//���ڷ����ַ���
void USARTx_SendString(USART_TypeDef* pUSARTx, uint8_t *pStr)
{
	uint8_t i;
  do 
  {
		USARTx_SendOneByte(pUSARTx, *(pStr + i));
		i++;
  } 
	while(*(pStr + i)!='\0');
  /* �ȴ�������� */
  while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) == RESET){}	
}
