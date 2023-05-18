#include "includes.h" 


//�����������PWM GPIO��ʼ��
void PWM_Wheel_Cfg_Init(uint16_t iArr, uint16_t iPsc)
{
	/* PWM�źŵ�ƽ�����ֵ */   
 	uint16_t CCR1_Val = 0;   // PWM_CH1  Value              
 	uint16_t CCR2_Val = 0;   // PWM_CH2  Value  	
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;	
	
	/* 1: ����GPIO */
	RCC_AHB1PeriphClockCmd(PWM_WHEEL_GPIO_CLK, ENABLE); 	
	
	GPIO_InitStructure.GPIO_Pin 						= PWM_LEFT_PIN | PWM_RIGHT_PIN;
  GPIO_InitStructure.GPIO_Mode 						= GPIO_Mode_AF;								//���ܸ���
	GPIO_InitStructure.GPIO_OType 					= GPIO_OType_PP;           		//���츴�����
	GPIO_InitStructure.GPIO_PuPd 						= GPIO_PuPd_UP;             	//����
  GPIO_InitStructure.GPIO_Speed 					= GPIO_Speed_100MHz;
  GPIO_Init(PWM_WHEEL_PORT, &GPIO_InitStructure);		
	
	GPIO_PinAFConfig(PWM_WHEEL_PORT, GPIO_PinSource12, GPIO_AF_TIM4);   	//TIM4_CH1
	GPIO_PinAFConfig(PWM_WHEEL_PORT, GPIO_PinSource13, GPIO_AF_TIM4);   	//TIM4_CH1

	RCC_APB1PeriphClockCmd(PWM_WHEEL_TIM_CLK, ENABLE);  	             		//TIM5ʱ��ʹ��      

	TIM_TimeBaseStructure.TIM_Period 				= iArr - 1;                 	//�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_Prescaler 		= iPsc - 1;                 	//��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode		= TIM_CounterMode_Up;       	//���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM_TimeBaseInit(PWM_WHEEL_TIM, &TIM_TimeBaseStructure);            	//��ʼ����ʱ��
	
	//��ʼ��TIM CH1 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode 					= TIM_OCMode_PWM1;						//ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState 		= TIM_OutputState_Enable;			//�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OutputNState 		= TIM_OutputNState_Disable;		//�رջ���ͨ��
	TIM_OCInitStructure.TIM_OCPolarity 			= TIM_OCPolarity_High;        //�������:TIM����Ƚϼ��Ը�
		
	TIM_OCInitStructure.TIM_Pulse 					= CCR1_Val;                   //��ֵ 0
	TIM_OC1Init(PWM_WHEEL_TIM, &TIM_OCInitStructure);                   	//����Tָ���Ĳ�����ʼ������
	TIM_OC1PreloadConfig(PWM_WHEEL_TIM, TIM_OCPreload_Enable);          	//ʹ��TIM8��CCR1�ϵ�Ԥװ�ؼĴ���
	
	TIM_OCInitStructure.TIM_Pulse 					= CCR2_Val;                   //��ֵ 0
	TIM_OC2Init(PWM_WHEEL_TIM, &TIM_OCInitStructure);                   	//����Tָ���Ĳ�����ʼ������
	TIM_OC2PreloadConfig(PWM_WHEEL_TIM, TIM_OCPreload_Enable);          	//ʹ��TIM8��CCR2�ϵ�Ԥװ�ؼĴ���	
  TIM_ARRPreloadConfig(PWM_WHEEL_TIM, ENABLE);   												//ʹ��TIM ���ؼĴ���ARR
	
	//TIM_ClearFlag(PWM_TIMx, TIM_FLAG_Update);
	TIM_ITConfig(PWM_WHEEL_TIM, TIM_IT_Update, ENABLE);
  TIM_Cmd(PWM_WHEEL_TIM, ENABLE);                 					  					//ʹ�ܶ�ʱ��	
	//����TIM1 TIM8 �������
	TIM_CtrlPWMOutputs(PWM_WHEEL_TIM, ENABLE);	                					//PWM ���ʹ��

	//Ĭ�����0ռ�ձ�
	PWM_Output_Set( PWM_LEFT_CH, 0);
	PWM_Output_Set( PWM_RIGHT_CH, 0);
}


//����ͨ��N��PWM���
void PWM_Output_Set(uint8_t ucChx, uint16_t  uiPWM_Val)
{	
	switch( ucChx )
	{
		case PWM_LEFT_CH:		// ���
			TIM_SetCompare2(PWM_WHEEL_TIM, uiPWM_Val);
			//TIM_OC2PreloadConfig(PWM_TIMx, TIM_OCPreload_Enable);
			break;
		case PWM_RIGHT_CH:  // �Ҳ�
			TIM_SetCompare1(PWM_WHEEL_TIM, uiPWM_Val);
			//TIM_OC1PreloadConfig(PWM_TIMx, TIM_OCPreload_Enable);
			break;		
		/*
		case PWM_CH3:   		// ���
			TIM_SetCompare3(PWM_WHEEL_TIM, uiPWM_Val);
		  //TIM_OC3PreloadConfig(PWM_TIMx, TIM_OCPreload_Enable);
			break;		
		case PWM_CH4:   		// ���
			TIM_SetCompare4(PWM_WHEEL_TIM, uiPWM_Val);
		  //TIM_OC4PreloadConfig(PWM_TIMx, TIM_OCPreload_Enable);
			break;	
		*/
		default:  
			break;
	}	
}


//��̨�������PWM ��ʼ��
void PWM_Head_Cfg_Init(uint16_t iArr, uint16_t iPsc)
{
	/* PWM�źŵ�ƽ�����ֵ */   
 	uint16_t CCR1_Val = 0;   // PWM_CH1  Value              
 	uint16_t CCR2_Val = 0;   // PWM_CH2  Value  	
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;	
	
	/* 1: ����GPIO  */
	RCC_AHB1PeriphClockCmd(PWM_HEAD_PORT_CLK, ENABLE); 	
	
	GPIO_InitStructure.GPIO_Pin 	=  PWM_PITCH_PIN | PWM_LEVEL_PIN ;
  GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF;		         							//���ܸ���
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;           							//���츴�����
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP;             						//����
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_Init(PWM_HEAD_PORT, &GPIO_InitStructure);		
	
	GPIO_PinAFConfig(PWM_HEAD_PORT, GPIO_PinSource8, GPIO_AF_TIM4);				//TIM4_CH3
	GPIO_PinAFConfig(PWM_HEAD_PORT, GPIO_PinSource9, GPIO_AF_TIM4);				//TIM4_CH4
	
	/* 2: ����TIM  (TIM1/TIM8 <==> APB2, TIM2/TIM3/TIM4 ... <==> APB1)*/
	RCC_APB1PeriphClockCmd(PWM_HEAD_TIM_CLK, ENABLE);  	              		//TIM5ʱ��ʹ��      

	TIM_TimeBaseStructure.TIM_Period 				= iArr - 1;               		//�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_Prescaler 		= iPsc - 1;               		//��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode		=TIM_CounterMode_Up;      		//���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_ClockDivision	=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(PWM_HEAD_TIM, &TIM_TimeBaseStructure);           		//��ʼ����ʱ��
	
	// ��ʼ��TIM CH1 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode 					= TIM_OCMode_PWM1;						//ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState 		= TIM_OutputState_Enable;     //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OutputNState 		= TIM_OutputNState_Disable;		//�رջ���ͨ��
	TIM_OCInitStructure.TIM_OCPolarity 			= TIM_OCPolarity_High;				//�������:TIM����Ƚϼ��Ե�
	//TIM_OCInitStructure.TIM_OCNPolarity 	= TIM_OCPolarity_Low;
		
	TIM_OCInitStructure.TIM_Pulse = CCR1_Val ;                        		//��ֵ 0
	TIM_OC3Init(PWM_HEAD_TIM, &TIM_OCInitStructure);                  		//����Tָ���Ĳ�����ʼ������
	TIM_OC3PreloadConfig(PWM_HEAD_TIM, TIM_OCPreload_Enable);							//ʹ��TIM8��CCR1�ϵ�Ԥװ�ؼĴ���
	
	TIM_OCInitStructure.TIM_Pulse = CCR2_Val ;                        		//��ֵ 0
	TIM_OC4Init(PWM_HEAD_TIM, &TIM_OCInitStructure);                  		//����Tָ���Ĳ�����ʼ������
	TIM_OC4PreloadConfig(PWM_HEAD_TIM, TIM_OCPreload_Enable);         		//ʹ��TIM8��CCR2�ϵ�Ԥװ�ؼĴ���	
 
  TIM_ARRPreloadConfig(PWM_HEAD_TIM, ENABLE);   												//ʹ��TIM ���ؼĴ���ARR
	
//TIM_ClearFlag(PWM_TIMx, TIM_FLAG_Update);
	TIM_ITConfig(PWM_HEAD_TIM, TIM_IT_Update, ENABLE);

  TIM_Cmd(PWM_HEAD_TIM, ENABLE);																				//ʹ�ܶ�ʱ��	
	// ����TIM1 TIM8 �������
	TIM_CtrlPWMOutputs(PWM_HEAD_TIM, ENABLE);															//PWM ���ʹ��                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
}


//������̨��PWM���
void Head_PWM_Set(uint8_t _usChannel, uint16_t _usPWM_Val)
{
	switch(_usChannel)
	{
		case PWM_PITCH_CH:
			TIM_SetCompare3(PWM_HEAD_TIM, _usPWM_Val);
			break;
		case PWM_LEVEL_CH:
			TIM_SetCompare4(PWM_HEAD_TIM, _usPWM_Val);
			break;
		default:
			break;
	}
}


//������̨������
void SetHeadPitchPosition(float pos, float offset)
{
	uint16_t tmp ;
	Head_PWM_Set(PWM_PITCH_CH, (uint16_t)(500+((pos+offset)*2000/270)));				//��Ӧ270�ȶ��                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
}


//������̨ˮƽת���Ƕ�
void SetHeadLevelPosition(float pos, float offset)
{
	uint16_t tmp ;
	Head_PWM_Set(PWM_LEVEL_CH, (uint16_t)(500+((180-pos+offset)*2000/270)));		//��Ӧ270�ȶ��
}

