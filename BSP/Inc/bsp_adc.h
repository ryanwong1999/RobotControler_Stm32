#ifndef __BSP_ADC_H
#define __BSP_ADC_H

#define SAMPLE_NUM 				16						// 每通道采16次
#define CHAN_NUM 					6							// 为6个通道 

//引脚宏定义
#define ADC_CLK						RCC_APB2Periph_ADC1	 
#define ADC_PORT_CLK      RCC_AHB1Periph_GPIOC
#define ADC_PORT          GPIOC
	 
#define VBAT_PIN 	        GPIO_Pin_1   	//电池电压
#define STOPSW_PIN        GPIO_Pin_0	  //Emergency stop check
#define VIN_PIN 	        GPIO_Pin_2   	//charging input voltage check   
#define IDRV_PIN      		GPIO_Pin_3   	//驱动器电流
	 
//引脚宏定义
#define ADC1_CLK          RCC_APB2Periph_ADC1	 
#define ADC1_PORT_CLK     RCC_AHB1Periph_GPIOA
#define ADC1_PORT         GPIOA

#define IBAT_PIN      		GPIO_Pin_1   	//电池电流
#define ILIFT_PIN      		GPIO_Pin_0   	//升降机电流

#define ILIFT_CH 					ADC_Channel_0
#define IBAT_CH    				ADC_Channel_1   
#define STOPSW_CH  				ADC_Channel_10 
#define VBAT_CH       		ADC_Channel_11	       
#define VIN_CH     				ADC_Channel_12	      
#define IDRV_CH 					ADC_Channel_13

extern uint16_t ADC_Filter_Value[CHAN_NUM];     // 存放处理后的数
extern uint16_t AD_Value[SAMPLE_NUM][CHAN_NUM]; // 用来存放ADC转换结果，也是DMA的目标地址

void ADC_Cfg_Init(void);	 
void filter(void);

#endif