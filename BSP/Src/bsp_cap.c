#include "includes.h" 

//定时器捕获初始化配置
void TIM_ICP_Cfg_Init(uint16_t iArr, uint16_t iPsc)
{	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef ICP_ICInitStructure;
	
	RCC_AHB1PeriphClockCmd(CAP_PORT_CLK, ENABLE);		// 使能PORT时钟	
	RCC_APB2PeriphClockCmd(CAP_TIM_CLK, ENABLE);		// TIM时钟使能    
	
	GPIO_InitStructure.GPIO_Pin 		= CAP_LEFT_PIN | CAP_RIGHT_PIN | CAP2_LEFT_PIN | CAP2_RIGHT_PIN;		// GPIO
	GPIO_InitStructure.GPIO_Mode 		= GPIO_Mode_AF;										//复用功能
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_100MHz;							//速度100MHz
	GPIO_InitStructure.GPIO_OType 	= GPIO_OType_PP;									//推挽复用输出
	GPIO_InitStructure.GPIO_PuPd 		= GPIO_PuPd_DOWN;									//下拉
	GPIO_Init(CAP_PORT, &GPIO_InitStructure);              						//初始化PORT
	
	GPIO_PinAFConfig(CAP_PORT, GPIO_PinSource6, GPIO_AF_TIM8);  			//PB0复用位定时器3
	GPIO_PinAFConfig(CAP_PORT, GPIO_PinSource7, GPIO_AF_TIM8);  			//PB0复用位定时器3
	GPIO_PinAFConfig(CAP_PORT, GPIO_PinSource8, GPIO_AF_TIM8);  			//PB0复用位定时器3
	GPIO_PinAFConfig(CAP_PORT, GPIO_PinSource9, GPIO_AF_TIM8);  			//PB0复用位定时器3
	
	TIM_TimeBaseStructure.TIM_Period 		= iArr - 1; 	
	TIM_TimeBaseStructure.TIM_Prescaler = iPsc - 1;		                //高级控制定时器时钟源TIMxCLK = HCLK=180MHz 
																																		//设定定时器频率为=TIMxCLK/(TIM_Prescaler+1)=100KHz
	TIM_TimeBaseStructure.TIM_ClockDivision	= TIM_CKD_DIV1;		        //对外部时钟进行采样的时钟分频,这里没有用到 */
	TIM_TimeBaseStructure.TIM_CounterMode		= TIM_CounterMode_Up;	    //计数方式
	TIM_TimeBaseInit(CAP_TIM, &TIM_TimeBaseStructure);	            	//初始化定时器TIMx, x[1,8]	
	
	//初始化TIM5输入捕获参数
	ICP_ICInitStructure.TIM_Channel 		= TIM_Channel_1;              //CC1S=01 	选择输入端 IC1映射到TI1上
	ICP_ICInitStructure.TIM_ICPolarity 	= TIM_ICPolarity_Rising;	  	//上升沿捕获
	ICP_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;		//映射到TI1上
	ICP_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	          	//配置输入分频,不分频 
	ICP_ICInitStructure.TIM_ICFilter 		= 0x00;                       //IC1F=0000 配置输入滤波器 不滤波
	TIM_ICInit(CAP_TIM, &ICP_ICInitStructure);
	
	ICP_ICInitStructure.TIM_Channel 		= TIM_Channel_2;              //CC1S=01 	选择输入端 IC1映射到TI1上
	ICP_ICInitStructure.TIM_ICPolarity 	= TIM_ICPolarity_Rising;	  	//上升沿捕获
	ICP_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 	//映射到TI1上
	ICP_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	          	//配置输入分频,不分频 
	ICP_ICInitStructure.TIM_ICFilter 		= 0x00;                       //IC1F=0000 配置输入滤波器 不滤波
	TIM_ICInit(CAP_TIM, &ICP_ICInitStructure);	 

	//初始化TIM5输入捕获参数
	ICP_ICInitStructure.TIM_Channel 		= TIM_Channel_3;              //CC1S=01 	选择输入端 IC1映射到TI1上
	ICP_ICInitStructure.TIM_ICPolarity 	= TIM_ICPolarity_Rising;	  	//上升沿捕获
	ICP_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 	//映射到TI1上
	ICP_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	          	//配置输入分频,不分频 
	ICP_ICInitStructure.TIM_ICFilter 		= 0x00;                       //IC1F=0000 配置输入滤波器 不滤波
	TIM_ICInit(CAP_TIM, &ICP_ICInitStructure);
	
	ICP_ICInitStructure.TIM_Channel 		= TIM_Channel_4;              //CC1S=01 	选择输入端 IC1映射到TI1上
	ICP_ICInitStructure.TIM_ICPolarity 	= TIM_ICPolarity_Rising;	  	//上升沿捕获
	ICP_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 	//映射到TI1上
	ICP_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	          	//配置输入分频,不分频 
	ICP_ICInitStructure.TIM_ICFilter 		= 0x00;                       //IC1F=0000 配置输入滤波器 不滤波
	TIM_ICInit(CAP_TIM, &ICP_ICInitStructure);	 
	
	TIM_ITConfig(CAP_TIM, TIM_IT_CC1, ENABLE);	//允许更新中断, 允许CC1IE捕获中断	
	TIM_ITConfig(CAP_TIM, TIM_IT_CC2, ENABLE);	//允许更新中断, 允许CC1IE捕获中断	
	TIM_ITConfig(CAP_TIM, TIM_IT_CC3, ENABLE);	//允许更新中断, 允许CC1IE捕获中断	
	TIM_ITConfig(CAP_TIM, TIM_IT_CC4, ENABLE);	//允许更新中断, 允许CC1IE捕获中断	
	
	//TIM_Cmd(CAP_TIM,ENABLE );									//使能定时器5
	TIM_Cmd(CAP_TIM, DISABLE );									//禁止定时器5
	//NVIC 配置, 统一放置于main.c 统一处理
}

