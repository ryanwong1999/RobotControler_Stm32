#include "includes.h" 


/************************************************/
//函数功能：LED指示灯GPIO初始化
//输入参数：
//返回值：
//备注：
/************************************************/
void LED_GPIO_Init(void)
{
	/*定义一个GPIO_InitTypeDef类型的结构体*/
	GPIO_InitTypeDef GPIO_InitStructure;
	/*开启LED相关的GPIO外设时钟*/
	RCC_AHB1PeriphClockCmd (LEDG_PORT_CLK | LEDR_PORT_CLK | LED1_PORT_CLK | LED2_PORT_CLK , ENABLE); 	
														   
	GPIO_InitStructure.GPIO_Pin 	= LED_GREEN_PIN;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_OUT;   		/*设置引脚模式为输出模式 */
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      /*设置引脚的输出类型为推挽输出 */
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP;				/*设置引脚为上拉模式 */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;		/*设置引脚速率为2MHz */  
	GPIO_Init(LEDG_PORT, &GPIO_InitStructure);			    /*调用库函数，使用上面配置的GPIO_InitStructure初始化GPIO */
														   
	GPIO_InitStructure.GPIO_Pin 	= LED_RED_PIN;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_OUT;   		/*设置引脚模式为输出模式 */
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      /*设置引脚的输出类型为推挽输出 */
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP;				/*设置引脚为上拉模式 */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;		/*设置引脚速率为2MHz */  
	GPIO_Init(LEDR_PORT, &GPIO_InitStructure);					/*调用库函数，使用上面配置的GPIO_InitStructure初始化GPIO */
	
	GPIO_InitStructure.GPIO_Pin		= LED1_PIN;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_OUT;			/*设置引脚模式为输出模式*/
	GPIO_InitStructure.GPIO_OType	= GPIO_OType_PP;			/*设置引脚的输出类型为推挽输出*/
	GPIO_InitStructure.GPIO_PuPd	= GPIO_PuPd_UP;				/*设置引脚为上拉模式*/
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_2MHz;		/*设置引脚速率为2MHz*/  
	GPIO_Init(LED1_PORT, &GPIO_InitStructure);					/*调用库函数，使用上面配置的GPIO_InitStructure初始化GPIO*/
	
	GPIO_InitStructure.GPIO_Pin		= LED2_PIN;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_OUT;			/*设置引脚模式为输出模式*/
	GPIO_InitStructure.GPIO_OType	= GPIO_OType_PP;			/*设置引脚的输出类型为推挽输出*/
	GPIO_InitStructure.GPIO_PuPd	= GPIO_PuPd_UP;				/*设置引脚为上拉模式*/
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_2MHz;		/*设置引脚速率为2MHz*/  
	GPIO_Init(LED2_PORT, &GPIO_InitStructure);					/*调用库函数，使用上面配置的GPIO_InitStructure初始化GPIO*/
	
	LED_RED_OFF;
	LED_GREEN_OFF;
	LED1_OFF;
	LED2_OFF;
}


/************************************************/
//函数功能：蜂鸣器GPIO初始化
//输入参数：
//返回值：
//备注：
/************************************************/
void BEEP_GPIO_Init(void)
{
	/*定义一个GPIO_InitTypeDef类型的结构体*/
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(BEEP_PORT_CLK, ENABLE); 

  GPIO_InitStructure.GPIO_Pin		=	BEEP_PIN;
  GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_OUT;		//输出
	GPIO_InitStructure.GPIO_OType	= GPIO_OType_PP;		//推挽输出
	GPIO_InitStructure.GPIO_PuPd	= GPIO_PuPd_NOPULL;	//不上拉 ,也不下拉
  GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_100MHz;	 
  GPIO_Init(BEEP_PORT, &GPIO_InitStructure);	
	
  BEEP_OFF;	 
}


void Key_GPIO_Init(void)
{ 
	GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOE, ENABLE);//使能GPIOA,GPIOE时钟
 
  GPIO_InitStructure.GPIO_Pin 	= KEY_UP_PIN | KEY_DOWN_PIN;	//KEY0 KEY1 KEY2对应引脚
  GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_IN;								//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;					//100M
  GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP;								//上拉
  GPIO_Init(GPIOE, &GPIO_InitStructure);											//初始化GPIOE3,4
	
	 
  GPIO_InitStructure.GPIO_Pin 	= KEY_ENTER_PIN;							//WK_UP对应引脚PA0
  GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_DOWN ;						//下拉
  GPIO_Init(GPIOA, &GPIO_InitStructure);											//初始化GPIOA0
}


/************************************************/
//函数功能：超声模块GPIO初始化，ECHO口定义为外部中断输入初始化
//输入参数：
//返回值：
//备注：
/************************************************/
void Ultrasonic_Exti_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;	
	
  RCC_AHB1PeriphClockCmd(ULTRA1_PORT_CLK, ENABLE); 

  GPIO_InitStructure.GPIO_Pin		=	TRIG1_PIN;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_OUT;			//输出
	GPIO_InitStructure.GPIO_OType	= GPIO_OType_PP;			//推挽输出
	GPIO_InitStructure.GPIO_PuPd	= GPIO_PuPd_NOPULL;		//不上拉 ,也不下拉
  GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_100MHz;	 
  GPIO_Init(ULTRA1_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin		= ECHO1_PIN;
  GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_IN;				//输入
	GPIO_InitStructure.GPIO_PuPd	= GPIO_PuPd_DOWN;     //不上拉,也不下拉
  GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_100MHz;	 
  GPIO_Init(ULTRA1_PORT, &GPIO_InitStructure);
	
	RCC_AHB1PeriphClockCmd(ULTRA2_PORT_CLK, ENABLE); 

  GPIO_InitStructure.GPIO_Pin		= TRIG2_PIN;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_OUT;		  //输出
	GPIO_InitStructure.GPIO_OType	= GPIO_OType_PP;      //推挽输出
	GPIO_InitStructure.GPIO_PuPd	= GPIO_PuPd_NOPULL;   //不上拉,也不下拉
  GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_100MHz;	 
  GPIO_Init(ULTRA2_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin		= ECHO2_PIN ;
  GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_IN;		    //输入
	GPIO_InitStructure.GPIO_PuPd	= GPIO_PuPd_DOWN;     //不上拉,也不下拉
  GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_100MHz;	 
  GPIO_Init(ULTRA2_PORT, &GPIO_InitStructure);

	RCC_AHB1PeriphClockCmd(ULTRA3_PORT_CLK, ENABLE); 

  GPIO_InitStructure.GPIO_Pin		= TRIG3_PIN;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_OUT;		  //输出
	GPIO_InitStructure.GPIO_OType	= GPIO_OType_PP;      //推挽输出
	GPIO_InitStructure.GPIO_PuPd	= GPIO_PuPd_NOPULL;   //不上拉,也不下拉
  GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_100MHz;	 
  GPIO_Init(ULTRA3_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin		= ECHO3_PIN;
  GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_IN;		    //输入
	GPIO_InitStructure.GPIO_PuPd	= GPIO_PuPd_DOWN;     //不上拉,也不下拉
  GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_100MHz;	 
  GPIO_Init(ULTRA3_PORT, &GPIO_InitStructure);
	
	RCC_AHB1PeriphClockCmd(ULTRA4_PORT_CLK, ENABLE); 

  GPIO_InitStructure.GPIO_Pin		= TRIG4_PIN;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_OUT;		  //输出
	GPIO_InitStructure.GPIO_OType	= GPIO_OType_PP;      //推挽输出
	GPIO_InitStructure.GPIO_PuPd	= GPIO_PuPd_NOPULL;   //不上拉,也不下拉
  GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_100MHz;	 
  GPIO_Init(ULTRA4_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin		= ECHO4_PIN;
  GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_IN;		    //输入
	GPIO_InitStructure.GPIO_PuPd	= GPIO_PuPd_DOWN;     //不上拉,也不下拉
  GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_100MHz;	
  GPIO_Init(ULTRA4_PORT, &GPIO_InitStructure);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);					//使能SYSCFG时钟
	
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource7);		//GPIOC.11
	
  EXTI_InitStructure.EXTI_Line 		= EXTI_LINE_ECHO1;
  EXTI_InitStructure.EXTI_Mode 		= EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;	//脉冲触发
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure); 
	
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource5);		//GPIOC.11
	
  EXTI_InitStructure.EXTI_Line 		= EXTI_LINE_ECHO2;
  EXTI_InitStructure.EXTI_Mode 		= EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;	//脉冲触发
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure); 
		
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource9);		//GPIOC.11
	
  EXTI_InitStructure.EXTI_Line 		= EXTI_LINE_ECHO3;
  EXTI_InitStructure.EXTI_Mode 		= EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;	//脉冲触发
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure); 

  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource11);	//GPIOC.11
	
  EXTI_InitStructure.EXTI_Line 		= EXTI_LINE_ECHO4;
  EXTI_InitStructure.EXTI_Mode 		= EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;	//脉冲触发
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure); 
}


/************************************************/
//函数功能：自动充电红外解码GPIO初始化，定义为外部中断
//输入参数：
//返回值：
//备注：
/************************************************/
void IR_Decoding_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;    
	EXTI_InitTypeDef EXTI_InitStructure;
	
	RCC_AHB1PeriphClockCmd(IRCODE_PORT_CLK, ENABLE);		
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);					//注意要打开SYSCFG时钟	
	
	GPIO_InitStructure.GPIO_Pin 	= IRCODE_BL_PIN | IRCODE_BR_PIN;	//红外解码
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_IN;         					//输入模式
  GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP;         					//上拉输入
 	GPIO_Init(IRCODE_PORT, &GPIO_InitStructure);        		 				//初始化 红外解码端口

	//后面右边解码GPIO
  SYSCFG_EXTILineConfig(EXIT_SOURCE_IRPORT, EXTI_SOURCE_IRBR);		//GPIOC.11
  EXTI_InitStructure.EXTI_Line 		= EXTI_LINE_IRBR;
  EXTI_InitStructure.EXTI_Mode 		= EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;	//脉冲触发
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure); 

  SYSCFG_EXTILineConfig(EXIT_SOURCE_IRPORT, EXTI_SOURCE_IRBL);		//GPIOA.15
  EXTI_InitStructure.EXTI_Line 		= EXTI_LINE_IRBL;
  EXTI_InitStructure.EXTI_Mode 		= EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;	//脉冲触发
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure); 
}


/************************************************/
//函数功能：碰撞GPIO初始化
//输入参数：
//返回值：
//备注：
/************************************************/
void Crash_Gpio_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;    
	
	RCC_AHB1PeriphClockCmd(CRASH_FRONT_PORT_CLK, ENABLE);		

	GPIO_InitStructure.GPIO_Pin 	= CRASH_FRONT_PIN;		//前碰撞IO
  GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_IN;				//输入
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP;				//上拉 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 
  GPIO_Init(CRASH_FRONT_PORT, &GPIO_InitStructure);
	
	RCC_AHB1PeriphClockCmd(CRASH_BACK_PORT_CLK, ENABLE);		

	GPIO_InitStructure.GPIO_Pin 	= CRASH_BACK_PIN;			//前碰撞IO
  GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_IN;		    //输入
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP;				//上拉 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 
  GPIO_Init(CRASH_BACK_PORT, &GPIO_InitStructure);	
}
