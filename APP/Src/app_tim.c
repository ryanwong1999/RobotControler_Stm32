#include "includes.h" 


//TIM2�жϴ�������1ms��ʱ
void TIM2_IRQHandler(void)
{
	if((TIM_GetITStatus(TIM2, TIM_IT_Update) == SET))
	{
	
	}
}


//TIM1�жϴ�������10us��ʱ
void TIM1_UP_TIM10_IRQHandler(void)
{
	if((TIM_GetITStatus(TIM1, TIM_IT_Update) == SET))
	{

  }
}

void TIM7_IRQHandler(void)
{ 	
	if(TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)//�Ǹ����ж�
	{	 			   

	}	 
}