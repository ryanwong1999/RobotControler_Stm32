#ifndef __BSP_PWM_H
#define __BSP_PWM_H

//GPIO -> PWM 
//PWM GPIO define ,wheel speed set
#define PWM_WHEEL_GPIO_CLK		RCC_AHB1Periph_GPIOD
#define PWM_WHEEL_PORT				GPIOD
	 
#define PWM_LEFT_PIN					GPIO_Pin_12
#define PWM_RIGHT_PIN     		GPIO_Pin_13	 

#define PWM_WHEEL_TIM_CLK   	RCC_APB1Periph_TIM4
#define PWM_WHEEL_TIM        	TIM4
	
#define PWM_LEFT_CH          	2			//�Ҳ� PWM	 
#define PWM_RIGHT_CH         	1			//��� PWM	 
	 
#define PWM_HEAD_PORT_CLK 		RCC_AHB1Periph_GPIOB
#define PWM_HEAD_PORT 				GPIOB

#define PWM_PITCH_PIN					GPIO_Pin_8			//tim4_ch3
#define PWM_LEVEL_PIN					GPIO_Pin_9			//tim4_ch4

#define PWM_HEAD_TIM_CLK  		RCC_APB1Periph_TIM4
#define PWM_HEAD_TIM					TIM4

#define PWM_PITCH_CH    			1
#define PWM_LEVEL_CH    			2

void Head_PWM_Set(uint8_t _usChannel, uint16_t _usPWM_Val);
void PWM_Wheel_Cfg_Init(uint16_t iArr, uint16_t iPsc);				//���ӵ������PWM��ʼ��
void PWM_Output_Set(uint8_t ucChx, uint16_t  uiPWM_Val); 			//��������PWMֵ
void PWM_Head_Cfg_Init(uint16_t iArr, uint16_t iPsc);   			//ͷ�����(���)PWM��ʼ��
void PWM_Head_Set(uint8_t _usChannel, uint16_t _usPWM_Val);		//����PWMֵ
void SetHeadPitchPosition(float pos, float offset); 					//���ø����Ƕ�
void SetHeadLevelPosition(float pos, float offset);						//����ˮƽ�Ƕ�

#endif 