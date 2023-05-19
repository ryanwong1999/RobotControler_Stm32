#include "includes.h" 


/************************************************/
//�������ܣ��ж����ȼ�����
//���������
//����ֵ��
//��ע��
/************************************************/
void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure; 
	//�����ж���Ϊ1
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);	   					// �жϷ���
	//USART1
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;           // ����USARTΪ�ж�Դ 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;   // ��ռ���ȼ�Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 7;          // �����ȼ�Ϊ1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             // ʹ���ж� 
	NVIC_Init(&NVIC_InitStructure);	                            // ��ʼ������NVIC 	
	//USART2
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;           // ����USARTΪ�ж�Դ 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;   // ��ռ���ȼ�Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 6;          // �����ȼ�Ϊ1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             // ʹ���ж� 
	NVIC_Init(&NVIC_InitStructure);	   
	//USART3
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;           // ����USARTΪ�ж�Դ 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;   // ��ռ���ȼ�Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;          // �����ȼ�Ϊ1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             // ʹ���ж� 
	NVIC_Init(&NVIC_InitStructure);	                            // ��ʼ������NVIC 	
	//UART4
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;           	// ����USARTΪ�ж�Դ 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;   // ��ռ���ȼ�Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;          // �����ȼ�Ϊ1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             // ʹ���ж� 
	NVIC_Init(&NVIC_InitStructure);	        
	//UART5
	NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;           	// ����USARTΪ�ж�Դ 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;   // ��ռ���ȼ�Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;          // �����ȼ�Ϊ1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             // ʹ���ж� 
	NVIC_Init(&NVIC_InitStructure);	                            // ��ʼ������NVIC 	
  //10us������ʱ��
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_TIM10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;   // ��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 6;	        // �����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			        // IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	  
	//���벶��
	NVIC_InitStructure.NVIC_IRQChannel = TIM8_CC_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;   // ��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 7;	        // �����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			        // IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	 
  //1ms������ʱ��
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;             // ����USARTΪ�ж�Դ 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;   // ��ռ���ȼ�Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 7;          // �����ȼ�Ϊ1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             // ʹ���ж� 
	NVIC_Init(&NVIC_InitStructure);	
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1 ;		//��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 6;					//�����ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;							//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��NVIC�Ĵ���
	                               
 	NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream0_IRQn;     // ����DMAΪ�ж�Դ 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;   // ��ռ���ȼ�Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;          // �����ȼ�Ϊ1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             // ʹ���ж� 
	NVIC_Init(&NVIC_InitStructure);	
  //�ⲿ�ж�
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;            // �ⲿ�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;   // ��ռ���ȼ�Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;          // �����ȼ�Ϊ1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             // ʹ���ж� 
	NVIC_Init(&NVIC_InitStructure);	  
	//�ⲿ�ж�
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;            // �ⲿ�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;   // ��ռ���ȼ�Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;          // �����ȼ�Ϊ1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             // ʹ���ж� 
	NVIC_Init(&NVIC_InitStructure);	  
	//�ⲿ�ж�
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;          // �ⲿ�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;   // ��ռ���ȼ�Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;          // �����ȼ�Ϊ1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             // ʹ���ж� 
	NVIC_Init(&NVIC_InitStructure);	                            // ��ʼ������NVIC 	
  //�ⲿ�ж�
  NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;        // �ⲿ�ж�
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;   // ��ռ���ȼ�3
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;          // �����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             // ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);                             // ��ʼ������NVIC 	
}


/************************************************/
//�������ܣ���ʼ��ϵͳӲ����Դ
//���������
//����ֵ��
//��ע��
/************************************************/
void System_Board_Init(void)
{
	taskENTER_CRITICAL();           		//�����ٽ���
	
//	SystemInit();		        						//����ϵͳʱ��Ϊ72M
	delay_init(168);  									//ʱ�ӳ�ʼ��
	LED_GPIO_Cfg_Init();								//LED��ʼ��
	BEEP_GPIO_Cfg_Init();								//��������ʼ��
	Lamp_GPIO_Cfg_Init();								//��ʾ�Ƴ�ʼ��
	PowerSys_Gpio_Cfg_Init();						//��Դ���Ƴ�ʼ��
	PC_Power_Cfg_Init(PC_STARTUP_OFF);	//���ػ������źų�ʼ��
	IR_Decoding_GPIO_Cfg_Init();				//��������ʼ��
	Crash_Gpio_Cfg_Init();							//��ײ���źų�ʼ��
	LiftMoto_Gpio_Cfg_Init();						//��������źų�ʼ��
	LimitSwitch_Gpio_Cfg_Init();				//��λ���س�ʼ��
	ADC_Cfg_Init();    									//ADC��ʼ��
	AT24CXX_Init();											//AT24C02��ʼ��
	NVIC_Configuration();  							//�ж����ȼ�����
//	IWDG_Init(4,500); 									//���Ƶ��Ϊ64,����ֵΪ500,���ʱ��Ϊ1s	
	
	//��ʱ����ʼ��
	TIMx_Cfg_Init(RCC_APB2Periph_TIM1, TIM1, 10, 168);   	//1ms timer
	TIMx_Cfg_Init(RCC_APB1Periph_TIM2, TIM2, 1000, 84);  	//10us timer
	TIMx_Cfg_Init(RCC_APB1Periph_TIM7, TIM7, 100, 840);		//10ms timer
	PWM_Head_Cfg_Init(20000, 84);   		//TIM4 PWM��ʼ��
//	TIM8_Configuration();								//TIM8 ���벶���ʼ��
	
	//���ڳ�ʼ��
  USARTx_Cfg_Init(USART1, 115200);  	//USART to printf 
	USARTx_Cfg_Init(USART2, 9600);    	//USART to 
	USARTx_Cfg_Init(USART3, 9600);    	//USART to PC
	USARTx_Cfg_Init(UART5, 9600);       //USART to Environmental
	RS485_Cfg_Init(115200);  						//UART4 to moto drv
	
	//�ڴ��ʼ��
	my_mem_init(SRAMIN);								//��ʼ���ڲ��ڴ�� 
//	my_mem_init(SRAMEX);								//��ʼ���ⲿ�ڴ��
	my_mem_init(SRAMCCM);								//��ʼ��CCM�ڴ�� 

	taskEXIT_CRITICAL();            //�˳��ٽ���	 
	printf("Bsp init OK!\r\n");
}


/************************************************/
//�������ܣ�ϵͳ������������ʾ
//���������
//����ֵ��
//��ע��
/************************************************/
void System_StartTips(void)
{
	LED_GREEN_ON;
	LED_TEST_ON;
	BEEP_ON;
	delay_ms(100);
	LED_GREEN_OFF;
	LED_TEST_OFF;
	BEEP_OFF;
	delay_ms(200);
	
	LED_GREEN_ON;
	LED_TEST_ON;
	BEEP_ON ;
	delay_ms(100);
	LED_GREEN_OFF;
	LED_TEST_OFF;
	BEEP_OFF;
	delay_ms(200);	
	
	LED_GREEN_ON;
	LED_TEST_ON;
	BEEP_ON ;
	delay_ms(100);
	BEEP_OFF;
	LED_GREEN_OFF;
	LED_TEST_OFF;
	delay_ms(200);
}
