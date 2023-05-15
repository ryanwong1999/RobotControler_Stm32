#include "includes.h" 

//LEDָʾ��GPIO��ʼ��
void LED_GPIO_Cfg_Init(void)
{
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
	GPIO_InitTypeDef GPIO_InitStructure;
	/*����LED��ص�GPIO����ʱ��*/
	RCC_AHB1PeriphClockCmd (LEDG_PORT_CLK , ENABLE); 	

	/*ѡ��Ҫ���Ƶ�GPIO����*/															   
	GPIO_InitStructure.GPIO_Pin 		= LED_GREEN_PIN;
	GPIO_InitStructure.GPIO_Mode 		= GPIO_Mode_OUT;		/* ��������ģʽΪ���ģʽ       */
	GPIO_InitStructure.GPIO_OType 	= GPIO_OType_PP;		/* �������ŵ��������Ϊ������� */
	GPIO_InitStructure.GPIO_PuPd 		= GPIO_PuPd_UP;			/* ��������Ϊ����ģʽ          */
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_2MHz;	/*������������Ϊ2MHz */  
	GPIO_Init(LEDG_PORT, &GPIO_InitStructure);					/*���ÿ⺯����ʹ���������õ�GPIO_InitStructure��ʼ��GPIO*/

	RCC_AHB1PeriphClockCmd (LEDR_PORT_CLK, ENABLE); 	

	/*ѡ��Ҫ���Ƶ�GPIO����*/															   
	GPIO_InitStructure.GPIO_Pin 		= LED_RED_PIN;
	GPIO_InitStructure.GPIO_Mode 		= GPIO_Mode_OUT;		/* ��������ģʽΪ���ģʽ       */
	GPIO_InitStructure.GPIO_OType 	= GPIO_OType_PP;		/* �������ŵ��������Ϊ������� */
	GPIO_InitStructure.GPIO_PuPd 		= GPIO_PuPd_UP;			/* ��������Ϊ����ģʽ          */
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_2MHz;	/*������������Ϊ2MHz */  
	GPIO_Init(LEDR_PORT, &GPIO_InitStructure);					/*���ÿ⺯����ʹ���������õ�GPIO_InitStructure��ʼ��GPIO*/

	RCC_AHB1PeriphClockCmd (LED_TEST_PORT_CLK , ENABLE); 	

	GPIO_InitStructure.GPIO_Pin 		= LED_TEST_PIN;
	GPIO_InitStructure.GPIO_Mode 		= GPIO_Mode_OUT;		/* ��������ģʽΪ���ģʽ       */
	GPIO_InitStructure.GPIO_OType 	= GPIO_OType_PP;		/* �������ŵ��������Ϊ������� */
	GPIO_InitStructure.GPIO_PuPd 		= GPIO_PuPd_UP;			/* ��������Ϊ����ģʽ          */
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_2MHz;	/*������������Ϊ2MHz */  
	GPIO_Init(LED_TEST_PORT, &GPIO_InitStructure);			/*���ÿ⺯����ʹ���������õ�GPIO_InitStructure��ʼ��GPIO*/
     
	LED_RED_OFF;                                                                                                                                                                                                                
	LED_GREEN_OFF;
	LED_TEST_OFF;
}

//ָʾ��GPIO��ʼ��
void Lamp_GPIO_Cfg_Init(void)
{
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
	GPIO_InitTypeDef GPIO_InitStructure;
	/*����LED��ص�GPIO����ʱ��*/
	RCC_AHB1PeriphClockCmd (LAMP_PORT_CLK, ENABLE); 	

	/*ѡ��Ҫ���Ƶ�GPIO����*/															   
	GPIO_InitStructure.GPIO_Pin 		= LAMP_RED_PIN | LAMP_GREEN_PIN |LAMP_YELLOW_PIN | LAMP_BEEP_PIN;
	GPIO_InitStructure.GPIO_Mode 		= GPIO_Mode_OUT;		/* ��������ģʽΪ���ģʽ       */
	GPIO_InitStructure.GPIO_OType 	= GPIO_OType_PP;		/* �������ŵ��������Ϊ������� */
	GPIO_InitStructure.GPIO_PuPd 		= GPIO_PuPd_UP;			/* ��������Ϊ����ģʽ          */
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_2MHz;	/*������������Ϊ2MHz */  
	GPIO_Init(LAMP_PORT, &GPIO_InitStructure);					/*���ÿ⺯����ʹ���������õ�GPIO_InitStructure��ʼ��GPIO*/

	RCC_AHB1PeriphClockCmd (LEDR_PORT_CLK , ENABLE); 	

	LAMP_RED_OFF;
	LAMP_GREEN_OFF;
	LAMP_YELLOW_OFF;
	LAMP_BEEP_OFF;
}

//������GPIO��ʼ��
void BEEP_GPIO_Cfg_Init(void)
{
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
  GPIO_InitTypeDef GPIO_InitStructure;
	
  RCC_AHB1PeriphClockCmd(BEEP_PORT_CLK, ENABLE); 

  GPIO_InitStructure.GPIO_Pin 		=	BEEP_PIN;
  GPIO_InitStructure.GPIO_Mode 		= GPIO_Mode_OUT;		// ���
	GPIO_InitStructure.GPIO_OType 	= GPIO_OType_PP;		// �������
	GPIO_InitStructure.GPIO_PuPd 		= GPIO_PuPd_NOPULL;	// ������ ,Ҳ������
  GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_100MHz;	 
  GPIO_Init(BEEP_PORT, &GPIO_InitStructure);	
	
	BEEP_DISABLE ;
}

//ϵͳ�����������GPIO�ڳ�ʼ��
void PowerSys_Gpio_Cfg_Init(void)
{
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd (EN_CHG_PORT_CLK, ENABLE);  	 	//������ص�GPIO����ʱ��	
															 
	GPIO_InitStructure.GPIO_Pin 		= EN_CHG_PIN;					//���ʹ�ܿ�
	GPIO_InitStructure.GPIO_Mode 		= GPIO_Mode_OUT;   		/*��������ģʽΪ���ģʽ*/
	GPIO_InitStructure.GPIO_OType 	= GPIO_OType_PP;      /*�������ŵ��������Ϊ������� */
	GPIO_InitStructure.GPIO_PuPd 		= GPIO_PuPd_UP;				/*��������Ϊ����ģʽ*/
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_2MHz;		/*������������Ϊ2MHz */  
	GPIO_Init(EN_CHG_PORT, &GPIO_InitStructure);					/*���ÿ⺯����ʹ���������õ�GPIO_InitStructure��ʼ��GPIO*/
 
	RCC_AHB1PeriphClockCmd (EN_OUT_PORT_CLK, ENABLE);   	//������ص�GPIO����ʱ��	
													 
	GPIO_InitStructure.GPIO_Pin 		= EN_OUT_PIN;	        //ϵͳ����ʹ��
	GPIO_InitStructure.GPIO_Mode 		= GPIO_Mode_OUT;   		/*��������ģʽΪ���ģʽ*/
	GPIO_InitStructure.GPIO_OType 	= GPIO_OType_PP;      /*�������ŵ��������Ϊ������� */
	GPIO_InitStructure.GPIO_PuPd 		= GPIO_PuPd_DOWN;     /*��������Ϊ����ģʽ*/
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_2MHz; 		/*������������Ϊ2MHz */  
	GPIO_Init(EN_OUT_PORT, &GPIO_InitStructure);			  	/*���ÿ⺯����ʹ���������õ�GPIO_InitStructure��ʼ��GPIO*/

	RCC_AHB1PeriphClockCmd (EN24_PORT_CLK, ENABLE);   		//������ص�GPIO����ʱ��	
													 
	GPIO_InitStructure.GPIO_Pin 		= EN24_PIN   ;        //24V���ʹ��
	GPIO_InitStructure.GPIO_Mode 		= GPIO_Mode_OUT;   		/*��������ģʽΪ���ģʽ*/
	GPIO_InitStructure.GPIO_OType 	= GPIO_OType_PP;      /*�������ŵ��������Ϊ������� */
	GPIO_InitStructure.GPIO_PuPd 		= GPIO_PuPd_DOWN;     /*��������Ϊ����ģʽ*/
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_2MHz; 		/*������������Ϊ2MHz */  
	GPIO_Init(EN24_PORT, &GPIO_InitStructure);			  		/*���ÿ⺯����ʹ���������õ�GPIO_InitStructure��ʼ��GPIO*/
	
	RCC_AHB1PeriphClockCmd (EN_MDRV_PORT_CLK, ENABLE);   	//������ص�GPIO����ʱ��	
						 
	GPIO_InitStructure.GPIO_Pin 		= EN_MDRV_PIN;        //��������������ʹ��
	GPIO_InitStructure.GPIO_Mode 		= GPIO_Mode_OUT;   		/*��������ģʽΪ���ģʽ*/
	GPIO_InitStructure.GPIO_OType 	= GPIO_OType_PP;      /*�������ŵ��������Ϊ������� */
	GPIO_InitStructure.GPIO_PuPd 		= GPIO_PuPd_DOWN;     /*��������Ϊ����ģʽ*/
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_2MHz; 		/*������������Ϊ2MHz */  
	GPIO_Init(EN_MDRV_PORT, &GPIO_InitStructure);			  	/*���ÿ⺯����ʹ���������õ�GPIO_InitStructure��ʼ��GPIO*/

	RCC_AHB1PeriphClockCmd (POWERKEY_PORT_CLK, ENABLE);   //������ص�GPIO����ʱ��	
														 
	GPIO_InitStructure.GPIO_Pin 		= POWERKEY_PIN;    		//���ػ����������
	GPIO_InitStructure.GPIO_Mode 		= GPIO_Mode_IN;   		/* ��������ģʽΪ���ģʽ*/
	GPIO_InitStructure.GPIO_PuPd 		= GPIO_PuPd_DOWN;     /* ��������Ϊ����ģʽ*/
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_100MHz; 	/*������������Ϊ2MHz */  
	GPIO_Init(POWERKEY_PORT, &GPIO_InitStructure);			  /*���ÿ⺯����ʹ���������õ�GPIO_InitStructure��ʼ��GPIO*/
			
	RCC_AHB1PeriphClockCmd (EN_DC12V_PORT_CLK, ENABLE);   //������ص�GPIO����ʱ��	
															 
	GPIO_InitStructure.GPIO_Pin 		= EN_DC12V_PIN;       //12V���ʹ��
	GPIO_InitStructure.GPIO_Mode 		= GPIO_Mode_OUT;   		//��������ģʽΪ���ģʽ       
	GPIO_InitStructure.GPIO_OType 	= GPIO_OType_PP;      //�������ŵ��������Ϊ������� 
	GPIO_InitStructure.GPIO_PuPd 		= GPIO_PuPd_DOWN;     //��������Ϊ����ģʽ          
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_2MHz; 		//������������Ϊ2MHz  
	GPIO_Init(EN_DC12V_PORT, &GPIO_InitStructure);			  //���ÿ⺯����ʹ���������õ�GPIO_InitStructure��ʼ��GPIO

	RCC_AHB1PeriphClockCmd (PC_EN_PORT_CLK, ENABLE);   		//������ص�GPIO����ʱ��	
															 
	GPIO_InitStructure.GPIO_Pin 		= PC_EN_PIN;          //PC������ʹ��
	GPIO_InitStructure.GPIO_Mode 		= GPIO_Mode_OUT;   		//��������ģʽΪ���ģʽ       
	GPIO_InitStructure.GPIO_OType 	= GPIO_OType_PP;      // �������ŵ��������Ϊ������� 
	GPIO_InitStructure.GPIO_PuPd 		= GPIO_PuPd_DOWN;     //��������Ϊ����ģʽ          
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_2MHz; 		//������������Ϊ2MHz  
	GPIO_Init(PC_EN_PORT, &GPIO_InitStructure);			  		//���ÿ⺯����ʹ���������õ�GPIO_InitStructure��ʼ��GPIO
	
	RCC_AHB1PeriphClockCmd(VOICE_EN_CLK, ENABLE);		

	GPIO_InitStructure.GPIO_Pin 		= VOICE_EN_PIN;       //���а���������
	GPIO_InitStructure.GPIO_Mode 		= GPIO_Mode_IN;		    
	GPIO_InitStructure.GPIO_PuPd 		= GPIO_PuPd_UP;       //������,Ҳ������
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_100MHz;	 
	GPIO_Init(VOICE_EN_PORT, &GPIO_InitStructure);	

	RCC_AHB1PeriphClockCmd(STOP_KEY_CLK, ENABLE);		

	GPIO_InitStructure.GPIO_Pin 		= STOP_KEY_PIN;       //��ͣ����������
	GPIO_InitStructure.GPIO_Mode 		= GPIO_Mode_IN;		    
	GPIO_InitStructure.GPIO_PuPd 		= GPIO_PuPd_UP;       //������,Ҳ������
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_100MHz;	 
	GPIO_Init(STOP_KEY_PORT, &GPIO_InitStructure);	

	EN_CHG_DISABLE;
	EN_OUT_DISABLE;
	EN_MDRV_DISABLE;
	EN24_DISABLE;
	EN_DC12V_ENABLE;
	PC_EN_ENABLE;
}

//ϵͳ���ػ�GPIO��ʼ��
void PC_Power_Cfg_Init(uint8_t on_off)
{
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
	GPIO_InitTypeDef GPIO_InitStructure;
	/*����LED��ص�GPIO����ʱ��*/
	RCC_AHB1PeriphClockCmd (PC_STARTUP_CLK, ENABLE); 	
	/*ѡ��Ҫ���Ƶ�GPIO����*/															   
	switch(on_off)
	{
		case PC_STARTUP_ON:
				GPIO_InitStructure.GPIO_Pin 		= PC_STARTUP_PIN;   //PC�����ź�
				GPIO_InitStructure.GPIO_Mode 		= GPIO_Mode_OUT;   	/*��������ģʽΪ���ģʽ*/
				GPIO_InitStructure.GPIO_OType 	= GPIO_OType_PP;    /*�������ŵ��������Ϊ�������*/
				GPIO_InitStructure.GPIO_PuPd 		= GPIO_PuPd_UP;			/*��������Ϊ����ģʽ*/
				GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_2MHz;	/*������������Ϊ2MHz */  
				GPIO_Init(PC_STARTUP_PORT, &GPIO_InitStructure);		/*���ÿ⺯����ʹ���������õ�GPIO_InitStructure��ʼ��GPIO*/
				PC_STARTUP_LOW;
			break;
		case PC_STARTUP_OFF:
				GPIO_InitStructure.GPIO_Pin 		= PC_STARTUP_PIN;
				GPIO_InitStructure.GPIO_Mode 		= GPIO_Mode_IN;			/*��������ģʽΪ����ģʽ*/
				GPIO_InitStructure.GPIO_PuPd 		= GPIO_PuPd_UP;			/*��������Ϊ����ģʽ*/
				GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_100MHz;
				GPIO_Init(PC_STARTUP_PORT, &GPIO_InitStructure);
			break;
		default:
			break;
	}
}

//����ģ��GPIO��ʼ����ECHO�ڶ���Ϊ�ⲿ�ж������ʼ��
void Ultrasonic_Exti_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;	
	
  RCC_AHB1PeriphClockCmd(ULTRA1_PORT_CLK, ENABLE); 

  GPIO_InitStructure.GPIO_Pin 		=	TRIG1_PIN;
	GPIO_InitStructure.GPIO_Mode 		= GPIO_Mode_OUT;			//���
	GPIO_InitStructure.GPIO_OType 	= GPIO_OType_PP;			//�������
	GPIO_InitStructure.GPIO_PuPd 		= GPIO_PuPd_NOPULL;		//������ ,Ҳ������
  GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_100MHz;	 
  GPIO_Init(ULTRA1_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin 		= ECHO1_PIN;
  GPIO_InitStructure.GPIO_Mode 		= GPIO_Mode_IN;				//����
	GPIO_InitStructure.GPIO_PuPd 		= GPIO_PuPd_DOWN;     //������,Ҳ������
  GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_100MHz;	 
  GPIO_Init(ULTRA1_PORT, &GPIO_InitStructure);
	
	RCC_AHB1PeriphClockCmd(ULTRA2_PORT_CLK, ENABLE); 

  GPIO_InitStructure.GPIO_Pin 		= TRIG2_PIN;
	GPIO_InitStructure.GPIO_Mode 		= GPIO_Mode_OUT;		  //���
	GPIO_InitStructure.GPIO_OType 	= GPIO_OType_PP;      //�������
	GPIO_InitStructure.GPIO_PuPd 		= GPIO_PuPd_NOPULL;   //������,Ҳ������
  GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_100MHz;	 
  GPIO_Init(ULTRA2_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin 		= ECHO2_PIN ;
  GPIO_InitStructure.GPIO_Mode 		= GPIO_Mode_IN;		    //����
	GPIO_InitStructure.GPIO_PuPd 		= GPIO_PuPd_DOWN;     //������,Ҳ������
  GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_100MHz;	 
  GPIO_Init(ULTRA2_PORT, &GPIO_InitStructure);

	RCC_AHB1PeriphClockCmd(ULTRA3_PORT_CLK, ENABLE); 

  GPIO_InitStructure.GPIO_Pin 		= TRIG3_PIN;
	GPIO_InitStructure.GPIO_Mode 		= GPIO_Mode_OUT;		  //���
	GPIO_InitStructure.GPIO_OType 	= GPIO_OType_PP;      //�������
	GPIO_InitStructure.GPIO_PuPd 		= GPIO_PuPd_NOPULL;   //������,Ҳ������
  GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_100MHz;	 
  GPIO_Init(ULTRA3_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin 		= ECHO3_PIN;
  GPIO_InitStructure.GPIO_Mode 		= GPIO_Mode_IN;		    //����
	GPIO_InitStructure.GPIO_PuPd 		= GPIO_PuPd_DOWN;     //������,Ҳ������
  GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_100MHz;	 
  GPIO_Init(ULTRA3_PORT, &GPIO_InitStructure);
	
	RCC_AHB1PeriphClockCmd(ULTRA4_PORT_CLK, ENABLE); 

  GPIO_InitStructure.GPIO_Pin 		= TRIG4_PIN;
	GPIO_InitStructure.GPIO_Mode 		= GPIO_Mode_OUT;		  //���
	GPIO_InitStructure.GPIO_OType 	= GPIO_OType_PP;      //�������
	GPIO_InitStructure.GPIO_PuPd 		= GPIO_PuPd_NOPULL;   //������,Ҳ������
  GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_100MHz;	 
  GPIO_Init(ULTRA4_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin 		= ECHO4_PIN;
  GPIO_InitStructure.GPIO_Mode 		= GPIO_Mode_IN;		    //����
	GPIO_InitStructure.GPIO_PuPd 		= GPIO_PuPd_DOWN;     //������,Ҳ������
  GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_100MHz;	
  GPIO_Init(ULTRA4_PORT, &GPIO_InitStructure);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);					//ʹ��SYSCFGʱ��
	
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource7);		//GPIOC.11
	
  EXTI_InitStructure.EXTI_Line 		= EXTI_LINE_ECHO1;
  EXTI_InitStructure.EXTI_Mode 		= EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;	//���崥��
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure); 
	
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource5);		//GPIOC.11
	
  EXTI_InitStructure.EXTI_Line 		= EXTI_LINE_ECHO2;
  EXTI_InitStructure.EXTI_Mode 		= EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;	//���崥��
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure); 
		
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource9);		//GPIOC.11
	
  EXTI_InitStructure.EXTI_Line 		= EXTI_LINE_ECHO3;
  EXTI_InitStructure.EXTI_Mode 		= EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;	//���崥��
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure); 

  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource11);	//GPIOC.11
	
  EXTI_InitStructure.EXTI_Line 		= EXTI_LINE_ECHO4;
  EXTI_InitStructure.EXTI_Mode 		= EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;	//���崥��
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure); 
}

//�Զ����������GPIO��ʼ��������Ϊ�ⲿ�ж�
void IR_Decoding_GPIO_Cfg_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;    
	EXTI_InitTypeDef EXTI_InitStructure;
	
	RCC_AHB1PeriphClockCmd(IRCODE_PORT_CLK, ENABLE);		
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);					//ע��Ҫ��SYSCFGʱ��	
	
	GPIO_InitStructure.GPIO_Pin 	= IRCODE_BL_PIN | IRCODE_BR_PIN;	//�������
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_IN;         					//����ģʽ
  GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP;         					//��������
 	GPIO_Init(IRCODE_PORT, &GPIO_InitStructure);        		 				//��ʼ�� �������˿�

	//�����ұ߽���GPIO
  SYSCFG_EXTILineConfig(EXIT_SOURCE_IRPORT, EXTI_SOURCE_IRBR);		//GPIOC.11
  EXTI_InitStructure.EXTI_Line 		= EXTI_LINE_IRBR;
  EXTI_InitStructure.EXTI_Mode 		= EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;	//���崥��
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure); 

  SYSCFG_EXTILineConfig(EXIT_SOURCE_IRPORT, EXTI_SOURCE_IRBL);		//GPIOA.15
  EXTI_InitStructure.EXTI_Line 		= EXTI_LINE_IRBL;
  EXTI_InitStructure.EXTI_Mode 		= EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;	//���崥��
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure); 
}

//��ײGPIO��ʼ��
void Crash_Gpio_Cfg_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;    
	
	RCC_AHB1PeriphClockCmd(CRASH_FRONT_PORT_CLK, ENABLE);		

	GPIO_InitStructure.GPIO_Pin 	= CRASH_FRONT_PIN;		//ǰ��ײIO
  GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_IN;				//����
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP;				//���� 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 
  GPIO_Init(CRASH_FRONT_PORT, &GPIO_InitStructure);
	
	RCC_AHB1PeriphClockCmd(CRASH_BACK_PORT_CLK, ENABLE);		

	GPIO_InitStructure.GPIO_Pin 	= CRASH_BACK_PIN;			//ǰ��ײIO
  GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_IN;		    //����
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP;				//���� 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 
  GPIO_Init(CRASH_BACK_PORT, &GPIO_InitStructure);	
}

//�������GPIO��ʼ��
void LiftMoto_Gpio_Cfg_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;								//����һ��GPIO_InitTypeDef���͵Ľṹ��
	
	RCC_AHB1PeriphClockCmd(LIFTMOTO_PORT_CLK,ENABLE);		//���� GPIO ��ʱ��
	
	GPIO_InitStructure.GPIO_Pin 	= LIFTMOTO_EN_PIN | LIFTMOTO_DIR_PIN;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_OUT;			//���
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;			//�������
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_NOPULL;		//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;				
	GPIO_Init(LIFTMOTO_PORT, &GPIO_InitStructure);
	
	RCC_AHB1PeriphClockCmd(LIFTMOTO_PWM_CLK,ENABLE);		//���� GPIO ��ʱ��
	
	GPIO_InitStructure.GPIO_Pin 	= LIFTMOTO_PWM_PIN;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_OUT;			//���
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;			//�������
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_NOPULL;		//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;				
	GPIO_Init(LIFTMOTO_PWM_PORT, &GPIO_InitStructure);
	
 #ifdef LIFTMOTO_TASK_OS
	LIFTMOTO_DISABLE;
	LIFTMOTO_DOWN;
	LIFTMOTO_PWM_EN;   
 #else	
 	LIFTMOTO_ENABLE;
	LIFTMOTO_UP;
	LIFTMOTO_PWM_EN;   
	#endif
}

//���������λ����GPIO��ʼ��
void LimitSwitch_Gpio_Cfg_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;    

	RCC_AHB1PeriphClockCmd(LIMIT_UP_PORT_CLK, ENABLE);		

	GPIO_InitStructure.GPIO_Pin 	= LIMIT_UP_PIN;				//����λ
  GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_IN;				//���
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP;				//���� 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	 
  GPIO_Init(LIMIT_UP_PORT, &GPIO_InitStructure);
	
	RCC_AHB1PeriphClockCmd(LIMIT_DOWN_PORT_CLK, ENABLE);		

	GPIO_InitStructure.GPIO_Pin 	= LIMIT_DOWN_PIN;			//����λ
  GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_IN;				//���
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP;				//���� 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	 
  GPIO_Init(LIMIT_DOWN_PORT, &GPIO_InitStructure);	
}