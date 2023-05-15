#ifndef __BSP_CAP_H
#define __BSP_CAP_H

//输入捕获GPIO	 
#define CAP_PORT_CLK  		RCC_AHB1Periph_GPIOC
#define CAP_PORT      		GPIOC
	 
#define CAP_LEFT_PIN			GPIO_Pin_7
#define CAP_RIGHT_PIN			GPIO_Pin_6
	 
#define CAP2_LEFT_PIN			GPIO_Pin_9
#define CAP2_RIGHT_PIN		GPIO_Pin_8
//输入捕获定时器	 
#define CAP_TIM_CLK				RCC_APB2Periph_TIM8
#define CAP_TIM       		TIM8
#define CAP_TIM_AF    		GPIO_AF_TIM8
	 
#define TIM_IT_CC_LEFT	  TIM_IT_CC2
#define TIM_IT_CC_RIGHT   TIM_IT_CC1
	
#define LEFT_READ_C1      GPIO_ReadInputDataBit(CAP_PORT,CAP_LEFT_PIN)
#define LEFT_READ_C2      GPIO_ReadInputDataBit(CAP_PORT,CAP2_LEFT_PIN)
#define RIGHT_READ_C1     GPIO_ReadInputDataBit(CAP_PORT,CAP_RIGHT_PIN)
#define RIGHT_READ_C2     GPIO_ReadInputDataBit(CAP_PORT,CAP2_RIGHT_PIN)

void  TIM_ICP_Cfg_Init(uint16_t iArr, uint16_t iPsc);

#endif