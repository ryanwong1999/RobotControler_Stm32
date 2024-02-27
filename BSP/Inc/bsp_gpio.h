#ifndef __BSP_GPIO_H
#define __BSP_GPIO_H

/* 直接操作寄存器的方法控制IO */
#define	digitalHi(p,i)			 {p->BSRRL=i;}		//设置为高电平
#define digitalLo(p,i)			 {p->BSRRH=i;}		//输出低电平
#define digitalToggle(p,i)	 {p->ODR ^=i;}		//输出反转状态	 

/********************************************************
* LED IO初始化
********************************************************/	
//LED1
#define LED1_PORT_CLK      			RCC_AHB1Periph_GPIOF
#define LED1_PORT          			GPIOF
#define LED1_PIN	          		GPIO_Pin_9
#define LED1_TOGGLE      				digitalToggle(LED1_PORT, LED1_PIN)
#define LED1_ON			    				digitalLo(LED1_PORT, LED1_PIN)
#define LED1_OFF			  				digitalHi(LED1_PORT, LED1_PIN)

//LED2
#define LED2_PORT_CLK      			RCC_AHB1Periph_GPIOF
#define LED2_PORT          			GPIOF
#define LED2_PIN	          		GPIO_Pin_10
#define LED2_TOGGLE      				digitalToggle(LED2_PORT, LED2_PIN)
#define LED2_ON			    				digitalLo(LED2_PORT, LED2_PIN)
#define LED2_OFF			  				digitalHi(LED2_PORT, LED2_PIN)

//绿灯
#define LEDG_PORT_CLK          	RCC_AHB1Periph_GPIOC
#define LEDG_PORT              	GPIOC
#define LED_GREEN_PIN	        	GPIO_Pin_5
#define LED_RED_TOGGLE					digitalToggle(LEDR_PORT, LED_RED_PIN)
#define LED_RED_ON			    		digitalHi(LEDR_PORT, LED_RED_PIN)
#define LED_RED_OFF			    		digitalLo(LEDR_PORT, LED_RED_PIN)

//红灯
#define LEDR_PORT_CLK          	RCC_AHB1Periph_GPIOC
#define LEDR_PORT              	GPIOC
#define LED_RED_PIN	          	GPIO_Pin_4
#define LED_GREEN_TOGGLE				digitalToggle(LEDG_PORT, LED_GREEN_PIN)
#define LED_GREEN_ON			  		digitalHi(LEDG_PORT, LED_GREEN_PIN)
#define LED_GREEN_OFF			  		digitalLo(LEDG_PORT, LED_GREEN_PIN)

//蜂鸣器
#define BEEP_PORT_CLK          	RCC_AHB1Periph_GPIOD
#define BEEP_PORT              	GPIOD
#define BEEP_PIN               	GPIO_Pin_9
#define BEEP_TOGGLE		   				digitalToggle(BEEP_PORT, BEEP_PIN)
#define BEEP_ON		       				digitalHi(BEEP_PORT, BEEP_PIN)
#define BEEP_OFF				 				digitalLo(BEEP_PORT, BEEP_PIN)

#define ON  	0
#define OFF 	1

/********************************************************
* 按键IO初始化
********************************************************/	
#define KEY_UP_PORT_CLK					RCC_AHB1Periph_GPIOE
#define KEY_UP_PORT							GPIOE
#define KEY_UP_PIN							GPIO_Pin_3
#define KEY_UP_READ							GPIO_ReadInputDataBit(KEY_UP_PORT, KEY_UP_PIN)				//读取按键

#define KEY_DOWN_PORT_CLK				RCC_AHB1Periph_GPIOE
#define KEY_DOWN_PORT						GPIOE
#define KEY_DOWN_PIN						GPIO_Pin_4
#define KEY_DOWN_READ 					GPIO_ReadInputDataBit(KEY_DOWN_PORT, KEY_DOWN_PIN)		//读取按键

#define KEY_ENTER_PORT_CLK			RCC_APB1Periph_GPIOA
#define KEY_ENTER_PORT					GPIOA
#define KEY_ENTER_PIN						GPIO_Pin_0
#define KEY_ENTER_READ					GPIO_ReadInputDataBit(KEY_ENTER_PORT, KEY_ENTER_PIN)	//读取按键


/********************************************************
* 红外解码GPIO,定义为外部中断
* PC10 -> IRCODE_BM_PIN 中间红外管解码IO
* PC11 -> IRCODE_BR_PIN 右边红外管解码IO
* PA15 -> IRCODE_BL_PIN 左边红外管解码IO
********************************************************/	
#define IRCODE_PORT_CLK     		RCC_AHB1Periph_GPIOB
#define IRCODE_PORT         		GPIOB

#define IRCODE_BL_PIN       		GPIO_Pin_0
#define IRCODE_BR_PIN       		GPIO_Pin_1

#define EXIT_SOURCE_IRPORT  		EXTI_PortSourceGPIOB

#define EXTI_SOURCE_IRBL    		EXTI_PinSource0
#define EXTI_SOURCE_IRBR    		EXTI_PinSource1

#define EXTI_LINE_IRBL    			EXTI_Line0
#define EXTI_LINE_IRBR    			EXTI_Line1	


/********************************************************
* 超声IO初始化
********************************************************/	
#define ULTRA1_PORT_CLK			  	RCC_AHB1Periph_GPIOD
#define ULTRA1_PORT							GPIOD
#define ECHO1_PIN			    			GPIO_Pin_7
#define TRIG1_PIN			    			GPIO_Pin_6

#define ULTRA2_PORT_CLK			  	RCC_AHB1Periph_GPIOD
#define ULTRA2_PORT							GPIOD
#define ECHO2_PIN				      	GPIO_Pin_5		
#define TRIG2_PIN				      	GPIO_Pin_4

#define ULTRA3_PORT_CLK			  	RCC_AHB1Periph_GPIOE
#define ULTRA3_PORT							GPIOE
#define ECHO3_PIN				      	GPIO_Pin_9
#define TRIG3_PIN				      	GPIO_Pin_8

#define ULTRA4_PORT_CLK			  	RCC_AHB1Periph_GPIOE
#define ULTRA4_PORT							GPIOE
#define ECHO4_PIN				      	GPIO_Pin_11
#define TRIG4_PIN			        	GPIO_Pin_10

#define EXTI_LINE_ECHO1					EXTI_Line7  
#define EXTI_LINE_ECHO2					EXTI_Line5	 
#define EXTI_LINE_ECHO3					EXTI_Line9
#define EXTI_LINE_ECHO4					EXTI_Line11

#define TRIG1_ON			  				digitalHi(ULTRA1_PORT, TRIG1_PIN)
#define TRIG1_OFF			  				digitalLo(ULTRA1_PORT, TRIG1_PIN)

#define TRIG2_ON			  				digitalHi(ULTRA2_PORT, TRIG2_PIN)
#define TRIG2_OFF								digitalLo(ULTRA2_PORT, TRIG2_PIN)

#define TRIG3_ON			  				digitalHi(ULTRA3_PORT, TRIG3_PIN)
#define TRIG3_OFF								digitalLo(ULTRA3_PORT, TRIG3_PIN)

#define TRIG4_ON			  				digitalHi(ULTRA4_PORT, TRIG4_PIN)
#define TRIG4_OFF								digitalLo(ULTRA4_PORT, TRIG4_PIN)

#define ECHO_READ_1       			GPIO_ReadInputDataBit(ULTRA1_PORT, ECHO1_PIN)
#define ECHO_READ_2       			GPIO_ReadInputDataBit(ULTRA2_PORT, ECHO2_PIN)
#define ECHO_READ_3       			GPIO_ReadInputDataBit(ULTRA3_PORT, ECHO3_PIN)
#define ECHO_READ_4       			GPIO_ReadInputDataBit(ULTRA4_PORT, ECHO4_PIN)


/********************************************************
* 碰撞IO初始化
********************************************************/	
#define CRASH_FRONT_PORT_CLK	  RCC_AHB1Periph_GPIOA
#define CRASH_FRONT_PORT       	GPIOA
#define CRASH_FRONT_PIN        	GPIO_Pin_12

#define CRASH_BACK_PORT_CLK	   	RCC_AHB1Periph_GPIOE
#define CRASH_BACK_PORT       	GPIOE
#define CRASH_BACK_PIN        	GPIO_Pin_12

#define CRASH_FRONT_READ       	GPIO_ReadInputDataBit(CRASH_FRONT_PORT, CRASH_FRONT_PIN)
#define CRASH_BACK_READ        	GPIO_ReadInputDataBit(CRASH_BACK_PORT, CRASH_BACK_PIN)


//电机控制GPIO宏定义
#define MOTO_LEFT_DIR_CLK       RCC_AHB1Periph_GPIOD
#define MOTO_LEFT_DIR_PORT      GPIOD
#define MOTO_LEFT_DIR_PIN       GPIO_Pin_10

//电机控制GPIO宏定义
#define MOTO_LEFT_PORT_CLK      RCC_AHB1Periph_GPIOD
#define MOTO_LEFT_PORT          GPIOD
#define MOTO_LEFT_EN_PIN       	GPIO_Pin_11
//#define MOTO_LEFT_DIR_PIN      GPIO_Pin_5     // Dir

#define MOTO_RIGHT_PORT_CLK     RCC_AHB1Periph_GPIOD
#define MOTO_RIGHT_PORT         GPIOD
#define MOTO_RIGHT_DIR_PIN      GPIO_Pin_8      // Dir
#define MOTO_RIGHT_EN_PIN       GPIO_Pin_11

#define MOTO_LEFT_EN_ENABLE    	GPIO_ResetBits(MOTO_LEFT_PORT, MOTO_LEFT_EN_PIN);
#define MOTO_LEFT_EN_DISABLE    GPIO_SetBits(MOTO_LEFT_PORT, MOTO_LEFT_EN_PIN);

#define MOTO_RIGHT_EN_ENABLE    GPIO_ResetBits(MOTO_RIGHT_PORT, MOTO_RIGHT_EN_PIN);
#define MOTO_RIGHT_EN_DISABLE   GPIO_SetBits(MOTO_RIGHT_PORT, MOTO_RIGHT_EN_PIN);

#define MOTO_LEFT_DIR_FRONT    	GPIO_SetBits(MOTO_LEFT_DIR_PORT, MOTO_LEFT_DIR_PIN);
#define MOTO_LEFT_DIR_BACK      GPIO_ResetBits(MOTO_LEFT_DIR_PORT, MOTO_LEFT_DIR_PIN);

#define MOTO_RIGHT_DIR_FRONT    GPIO_ResetBits(MOTO_RIGHT_PORT, MOTO_RIGHT_DIR_PIN);
#define MOTO_RIGHT_DIR_BACK     GPIO_SetBits(MOTO_RIGHT_PORT, MOTO_RIGHT_DIR_PIN);

void LED_GPIO_Init(void);
void Lamp_GPIO_Init(void);
void BEEP_GPIO_Init(void);
void Key_GPIO_Init(void);
void Obstacle_GPIO_Init(void);
void Ultrasonic_Exti_Init(void);
void IR_Decoding_GPIO_Init(void);
void Crash_Gpio_Init(void);

#endif