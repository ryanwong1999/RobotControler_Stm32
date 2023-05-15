#include "includes.h" 

//��ʱ�������ʼ������
void TIM_ICP_Cfg_Init(uint16_t iArr, uint16_t iPsc)
{	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef ICP_ICInitStructure;
	
	RCC_AHB1PeriphClockCmd(CAP_PORT_CLK, ENABLE);		// ʹ��PORTʱ��	
	RCC_APB2PeriphClockCmd(CAP_TIM_CLK, ENABLE);		// TIMʱ��ʹ��    
	
	GPIO_InitStructure.GPIO_Pin 		= CAP_LEFT_PIN | CAP_RIGHT_PIN | CAP2_LEFT_PIN | CAP2_RIGHT_PIN;		// GPIO
	GPIO_InitStructure.GPIO_Mode 		= GPIO_Mode_AF;										//���ù���
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_100MHz;							//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType 	= GPIO_OType_PP;									//���츴�����
	GPIO_InitStructure.GPIO_PuPd 		= GPIO_PuPd_DOWN;									//����
	GPIO_Init(CAP_PORT, &GPIO_InitStructure);              						//��ʼ��PORT
	
	GPIO_PinAFConfig(CAP_PORT, GPIO_PinSource6, GPIO_AF_TIM8);  			//PB0����λ��ʱ��3
	GPIO_PinAFConfig(CAP_PORT, GPIO_PinSource7, GPIO_AF_TIM8);  			//PB0����λ��ʱ��3
	GPIO_PinAFConfig(CAP_PORT, GPIO_PinSource8, GPIO_AF_TIM8);  			//PB0����λ��ʱ��3
	GPIO_PinAFConfig(CAP_PORT, GPIO_PinSource9, GPIO_AF_TIM8);  			//PB0����λ��ʱ��3
	
	TIM_TimeBaseStructure.TIM_Period 		= iArr - 1; 	
	TIM_TimeBaseStructure.TIM_Prescaler = iPsc - 1;		                //�߼����ƶ�ʱ��ʱ��ԴTIMxCLK = HCLK=180MHz 
																																		//�趨��ʱ��Ƶ��Ϊ=TIMxCLK/(TIM_Prescaler+1)=100KHz
	TIM_TimeBaseStructure.TIM_ClockDivision	= TIM_CKD_DIV1;		        //���ⲿʱ�ӽ��в�����ʱ�ӷ�Ƶ,����û���õ� */
	TIM_TimeBaseStructure.TIM_CounterMode		= TIM_CounterMode_Up;	    //������ʽ
	TIM_TimeBaseInit(CAP_TIM, &TIM_TimeBaseStructure);	            	//��ʼ����ʱ��TIMx, x[1,8]	
	
	//��ʼ��TIM5���벶�����
	ICP_ICInitStructure.TIM_Channel 		= TIM_Channel_1;              //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
	ICP_ICInitStructure.TIM_ICPolarity 	= TIM_ICPolarity_Rising;	  	//�����ز���
	ICP_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;		//ӳ�䵽TI1��
	ICP_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	          	//���������Ƶ,����Ƶ 
	ICP_ICInitStructure.TIM_ICFilter 		= 0x00;                       //IC1F=0000 ���������˲��� ���˲�
	TIM_ICInit(CAP_TIM, &ICP_ICInitStructure);
	
	ICP_ICInitStructure.TIM_Channel 		= TIM_Channel_2;              //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
	ICP_ICInitStructure.TIM_ICPolarity 	= TIM_ICPolarity_Rising;	  	//�����ز���
	ICP_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 	//ӳ�䵽TI1��
	ICP_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	          	//���������Ƶ,����Ƶ 
	ICP_ICInitStructure.TIM_ICFilter 		= 0x00;                       //IC1F=0000 ���������˲��� ���˲�
	TIM_ICInit(CAP_TIM, &ICP_ICInitStructure);	 

	//��ʼ��TIM5���벶�����
	ICP_ICInitStructure.TIM_Channel 		= TIM_Channel_3;              //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
	ICP_ICInitStructure.TIM_ICPolarity 	= TIM_ICPolarity_Rising;	  	//�����ز���
	ICP_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 	//ӳ�䵽TI1��
	ICP_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	          	//���������Ƶ,����Ƶ 
	ICP_ICInitStructure.TIM_ICFilter 		= 0x00;                       //IC1F=0000 ���������˲��� ���˲�
	TIM_ICInit(CAP_TIM, &ICP_ICInitStructure);
	
	ICP_ICInitStructure.TIM_Channel 		= TIM_Channel_4;              //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
	ICP_ICInitStructure.TIM_ICPolarity 	= TIM_ICPolarity_Rising;	  	//�����ز���
	ICP_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 	//ӳ�䵽TI1��
	ICP_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	          	//���������Ƶ,����Ƶ 
	ICP_ICInitStructure.TIM_ICFilter 		= 0x00;                       //IC1F=0000 ���������˲��� ���˲�
	TIM_ICInit(CAP_TIM, &ICP_ICInitStructure);	 
	
	TIM_ITConfig(CAP_TIM, TIM_IT_CC1, ENABLE);	//��������ж�, ����CC1IE�����ж�	
	TIM_ITConfig(CAP_TIM, TIM_IT_CC2, ENABLE);	//��������ж�, ����CC1IE�����ж�	
	TIM_ITConfig(CAP_TIM, TIM_IT_CC3, ENABLE);	//��������ж�, ����CC1IE�����ж�	
	TIM_ITConfig(CAP_TIM, TIM_IT_CC4, ENABLE);	//��������ж�, ����CC1IE�����ж�	
	
	//TIM_Cmd(CAP_TIM,ENABLE );									//ʹ�ܶ�ʱ��5
	TIM_Cmd(CAP_TIM, DISABLE );									//��ֹ��ʱ��5
	//NVIC ����, ͳһ������main.c ͳһ����
}

