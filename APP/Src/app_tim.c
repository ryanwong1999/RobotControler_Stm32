#include "includes.h" 


//TIM2中断处理函数，1ms定时
void TIM2_IRQHandler(void)
{
	if((TIM_GetITStatus(TIM2, TIM_IT_Update) == SET))
	{
	
	}
}


//TIM1中断处理函数，10us定时
void TIM1_UP_TIM10_IRQHandler(void)
{
	if((TIM_GetITStatus(TIM1, TIM_IT_Update) == SET))
	{

  }
}

void TIM7_IRQHandler(void)
{ 	
	if(TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)//是更新中断
	{	 			   

	}	 
}