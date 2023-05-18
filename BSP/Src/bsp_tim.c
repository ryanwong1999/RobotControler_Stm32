#include "includes.h" 


//TIM��ʼ�����ú����������еĶ�ʱ����ʼ��
void TIMx_Cfg_Init(uint32_t rcc_periph, TIM_TypeDef* TIMx,uint16_t iArr, uint16_t iPsc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	if(TIMx == TIM1 || TIMx == TIM8)
		RCC_APB2PeriphClockCmd(rcc_periph, ENABLE);
	else
		RCC_APB1PeriphClockCmd(rcc_periph, ENABLE); 
	//��ʱ��ʱ��ԴTIMxCLK = 2 * PCLK1  
	//				PCLK1 = HCLK / 4 
	//				=> TIMxCLK=HCLK/2=SystemCoreClock/2=90MHz
	// �趨��ʱ��Ƶ��Ϊ=TIMxCLK/(TIM_Prescaler+1)=10000Hz
	TIM_TimeBaseStructure.TIM_Period 				= iArr-1;               //�Զ�����
	TIM_TimeBaseStructure.TIM_Prescaler 		= iPsc-1;	             	//��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode 	= TIM_CounterMode_Up;		//���ϼ���
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;		 			//���ⲿʱ�ӽ��в�����ʱ�ӷ�Ƶ,����û���õ� */
	TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure);
	
	TIM_ClearFlag(TIMx, TIM_FLAG_Update);	    											//�����ʱ�������жϱ�־λ
	TIM_ITConfig(TIMx, TIM_IT_Update,ENABLE);												//������ʱ�������ж�
	TIM_Cmd(TIMx, ENABLE);			                										//ʹ�ܶ�ʱ��
}
