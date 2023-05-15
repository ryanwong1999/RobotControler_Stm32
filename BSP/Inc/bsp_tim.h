#ifndef __BSP_TIM_H
#define __BSP_TIM_H

#define BASIC_TIM_CLK				RCC_APB1Periph_TIM2
#define BASIC_TIM						TIM2
	 
void TIM2_Cfg_Init(uint16_t iArr, uint16_t iPsc);
void TIMx_Cfg_Init(uint32_t rcc_periph, TIM_TypeDef* TIMx, uint16_t iArr, uint16_t iPsc);
void TIM7_Cfg_Init(u16 arr, u16 psc);

#endif 
