#include "includes.h" 


//TIM初始化，该函数适用所有的定时器初始化
void TIMx_Cfg_Init(uint32_t rcc_periph, TIM_TypeDef* TIMx,uint16_t iArr, uint16_t iPsc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	if(TIMx == TIM1 || TIMx == TIM8)
		RCC_APB2PeriphClockCmd(rcc_periph, ENABLE);
	else
		RCC_APB1PeriphClockCmd(rcc_periph, ENABLE); 
	//定时器时钟源TIMxCLK = 2 * PCLK1  
	//				PCLK1 = HCLK / 4 
	//				=> TIMxCLK=HCLK/2=SystemCoreClock/2=90MHz
	// 设定定时器频率为=TIMxCLK/(TIM_Prescaler+1)=10000Hz
	TIM_TimeBaseStructure.TIM_Period 				= iArr-1;               //自动重载
	TIM_TimeBaseStructure.TIM_Prescaler 		= iPsc-1;	             	//定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode 	= TIM_CounterMode_Up;		//向上计数
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;		 			//对外部时钟进行采样的时钟分频,这里没有用到 */
	TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure);
	
	TIM_ClearFlag(TIMx, TIM_FLAG_Update);	    											//清除定时器更新中断标志位
	TIM_ITConfig(TIMx, TIM_IT_Update,ENABLE);												//开启定时器更新中断
	TIM_Cmd(TIMx, ENABLE);			                										//使能定时器
}
