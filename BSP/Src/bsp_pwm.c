#include "includes.h" 


//电机驱动控制PWM GPIO初始化
void PWM_Wheel_Cfg_Init(uint16_t iArr, uint16_t iPsc)
{
	/* PWM信号电平跳变的值 */   
 	uint16_t CCR1_Val = 0;   // PWM_CH1  Value              
 	uint16_t CCR2_Val = 0;   // PWM_CH2  Value  	
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;	
	
	/* 1: 配置GPIO */
	RCC_AHB1PeriphClockCmd(PWM_WHEEL_GPIO_CLK, ENABLE); 	
	
	GPIO_InitStructure.GPIO_Pin 						= PWM_LEFT_PIN | PWM_RIGHT_PIN;
  GPIO_InitStructure.GPIO_Mode 						= GPIO_Mode_AF;								//功能复用
	GPIO_InitStructure.GPIO_OType 					= GPIO_OType_PP;           		//推挽复用输出
	GPIO_InitStructure.GPIO_PuPd 						= GPIO_PuPd_UP;             	//上拉
  GPIO_InitStructure.GPIO_Speed 					= GPIO_Speed_100MHz;
  GPIO_Init(PWM_WHEEL_PORT, &GPIO_InitStructure);		
	
	GPIO_PinAFConfig(PWM_WHEEL_PORT, GPIO_PinSource12, GPIO_AF_TIM4);   	//TIM4_CH1
	GPIO_PinAFConfig(PWM_WHEEL_PORT, GPIO_PinSource13, GPIO_AF_TIM4);   	//TIM4_CH1

	RCC_APB1PeriphClockCmd(PWM_WHEEL_TIM_CLK, ENABLE);  	             		//TIM5时钟使能      

	TIM_TimeBaseStructure.TIM_Period 				= iArr - 1;                 	//自动重装载值
	TIM_TimeBaseStructure.TIM_Prescaler 		= iPsc - 1;                 	//定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode		= TIM_CounterMode_Up;       	//向上计数模式
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM_TimeBaseInit(PWM_WHEEL_TIM, &TIM_TimeBaseStructure);            	//初始化定时器
	
	//初始化TIM CH1 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode 					= TIM_OCMode_PWM1;						//选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState 		= TIM_OutputState_Enable;			//比较输出使能
	TIM_OCInitStructure.TIM_OutputNState 		= TIM_OutputNState_Disable;		//关闭互补通道
	TIM_OCInitStructure.TIM_OCPolarity 			= TIM_OCPolarity_High;        //输出极性:TIM输出比较极性高
		
	TIM_OCInitStructure.TIM_Pulse 					= CCR1_Val;                   //初值 0
	TIM_OC1Init(PWM_WHEEL_TIM, &TIM_OCInitStructure);                   	//根据T指定的参数初始化外设
	TIM_OC1PreloadConfig(PWM_WHEEL_TIM, TIM_OCPreload_Enable);          	//使能TIM8在CCR1上的预装载寄存器
	
	TIM_OCInitStructure.TIM_Pulse 					= CCR2_Val;                   //初值 0
	TIM_OC2Init(PWM_WHEEL_TIM, &TIM_OCInitStructure);                   	//根据T指定的参数初始化外设
	TIM_OC2PreloadConfig(PWM_WHEEL_TIM, TIM_OCPreload_Enable);          	//使能TIM8在CCR2上的预装载寄存器	
  TIM_ARRPreloadConfig(PWM_WHEEL_TIM, ENABLE);   												//使能TIM 重载寄存器ARR
	
	//TIM_ClearFlag(PWM_TIMx, TIM_FLAG_Update);
	TIM_ITConfig(PWM_WHEEL_TIM, TIM_IT_Update, ENABLE);
  TIM_Cmd(PWM_WHEEL_TIM, ENABLE);                 					  					//使能定时器	
	//对于TIM1 TIM8 必须添加
	TIM_CtrlPWMOutputs(PWM_WHEEL_TIM, ENABLE);	                					//PWM 输出使能

	//默认输出0占空比
	PWM_Output_Set( PWM_LEFT_CH, 0);
	PWM_Output_Set( PWM_RIGHT_CH, 0);
}


//设置通道N的PWM输出
void PWM_Output_Set(uint8_t ucChx, uint16_t  uiPWM_Val)
{	
	switch( ucChx )
	{
		case PWM_LEFT_CH:		// 左侧
			TIM_SetCompare2(PWM_WHEEL_TIM, uiPWM_Val);
			//TIM_OC2PreloadConfig(PWM_TIMx, TIM_OCPreload_Enable);
			break;
		case PWM_RIGHT_CH:  // 右侧
			TIM_SetCompare1(PWM_WHEEL_TIM, uiPWM_Val);
			//TIM_OC1PreloadConfig(PWM_TIMx, TIM_OCPreload_Enable);
			break;		
		/*
		case PWM_CH3:   		// 左侧
			TIM_SetCompare3(PWM_WHEEL_TIM, uiPWM_Val);
		  //TIM_OC3PreloadConfig(PWM_TIMx, TIM_OCPreload_Enable);
			break;		
		case PWM_CH4:   		// 左侧
			TIM_SetCompare4(PWM_WHEEL_TIM, uiPWM_Val);
		  //TIM_OC4PreloadConfig(PWM_TIMx, TIM_OCPreload_Enable);
			break;	
		*/
		default:  
			break;
	}	
}


//云台舵机控制PWM 初始化
void PWM_Head_Cfg_Init(uint16_t iArr, uint16_t iPsc)
{
	/* PWM信号电平跳变的值 */   
 	uint16_t CCR1_Val = 0;   // PWM_CH1  Value              
 	uint16_t CCR2_Val = 0;   // PWM_CH2  Value  	
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;	
	
	/* 1: 配置GPIO  */
	RCC_AHB1PeriphClockCmd(PWM_HEAD_PORT_CLK, ENABLE); 	
	
	GPIO_InitStructure.GPIO_Pin 	=  PWM_PITCH_PIN | PWM_LEVEL_PIN ;
  GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF;		         							//功能复用
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;           							//推挽复用输出
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP;             						//上拉
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_Init(PWM_HEAD_PORT, &GPIO_InitStructure);		
	
	GPIO_PinAFConfig(PWM_HEAD_PORT, GPIO_PinSource8, GPIO_AF_TIM4);				//TIM4_CH3
	GPIO_PinAFConfig(PWM_HEAD_PORT, GPIO_PinSource9, GPIO_AF_TIM4);				//TIM4_CH4
	
	/* 2: 配置TIM  (TIM1/TIM8 <==> APB2, TIM2/TIM3/TIM4 ... <==> APB1)*/
	RCC_APB1PeriphClockCmd(PWM_HEAD_TIM_CLK, ENABLE);  	              		//TIM5时钟使能      

	TIM_TimeBaseStructure.TIM_Period 				= iArr - 1;               		//自动重装载值
	TIM_TimeBaseStructure.TIM_Prescaler 		= iPsc - 1;               		//定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode		=TIM_CounterMode_Up;      		//向上计数模式
	TIM_TimeBaseStructure.TIM_ClockDivision	=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(PWM_HEAD_TIM, &TIM_TimeBaseStructure);           		//初始化定时器
	
	// 初始化TIM CH1 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode 					= TIM_OCMode_PWM1;						//选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState 		= TIM_OutputState_Enable;     //比较输出使能
	TIM_OCInitStructure.TIM_OutputNState 		= TIM_OutputNState_Disable;		//关闭互补通道
	TIM_OCInitStructure.TIM_OCPolarity 			= TIM_OCPolarity_High;				//输出极性:TIM输出比较极性低
	//TIM_OCInitStructure.TIM_OCNPolarity 	= TIM_OCPolarity_Low;
		
	TIM_OCInitStructure.TIM_Pulse = CCR1_Val ;                        		//初值 0
	TIM_OC3Init(PWM_HEAD_TIM, &TIM_OCInitStructure);                  		//根据T指定的参数初始化外设
	TIM_OC3PreloadConfig(PWM_HEAD_TIM, TIM_OCPreload_Enable);							//使能TIM8在CCR1上的预装载寄存器
	
	TIM_OCInitStructure.TIM_Pulse = CCR2_Val ;                        		//初值 0
	TIM_OC4Init(PWM_HEAD_TIM, &TIM_OCInitStructure);                  		//根据T指定的参数初始化外设
	TIM_OC4PreloadConfig(PWM_HEAD_TIM, TIM_OCPreload_Enable);         		//使能TIM8在CCR2上的预装载寄存器	
 
  TIM_ARRPreloadConfig(PWM_HEAD_TIM, ENABLE);   												//使能TIM 重载寄存器ARR
	
//TIM_ClearFlag(PWM_TIMx, TIM_FLAG_Update);
	TIM_ITConfig(PWM_HEAD_TIM, TIM_IT_Update, ENABLE);

  TIM_Cmd(PWM_HEAD_TIM, ENABLE);																				//使能定时器	
	// 对于TIM1 TIM8 必须添加
	TIM_CtrlPWMOutputs(PWM_HEAD_TIM, ENABLE);															//PWM 输出使能                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
}


//设置云台的PWM输出
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


//设置云台俯仰角
void SetHeadPitchPosition(float pos, float offset)
{
	uint16_t tmp ;
	Head_PWM_Set(PWM_PITCH_CH, (uint16_t)(500+((pos+offset)*2000/270)));				//对应270度舵机                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
}


//设置云台水平转动角度
void SetHeadLevelPosition(float pos, float offset)
{
	uint16_t tmp ;
	Head_PWM_Set(PWM_LEVEL_CH, (uint16_t)(500+((180-pos+offset)*2000/270)));		//对应270度舵机
}

