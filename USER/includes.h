#ifndef __INCLUDES_H
#define __INCLUDES_H

#ifdef   MAIN_GLOBALS  
#define  MAIN_EXT
#else
#define  MAIN_EXT  extern
#endif


/*********************************************************************************************************
                                         STANDARD LIBRARIES
*********************************************************************************************************/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <math.h>


/*********************************************************************************************************
                                          FreeRTOS include 
*********************************************************************************************************/
#include "FreeRTOS.h"
#include "task.h"


/*********************************************************************************************************
                                           STM32  SYSTEM
*********************************************************************************************************/
#include "stm32f4xx.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"	
#include "malloc.h"	 


/*********************************************************************************************************
                                           STM32 include
*********************************************************************************************************/
#include "stm32f4xx_adc.h"
#include "stm32f4xx_dac.h"
#include "stm32f4xx_dma.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_i2c.h"
#include "stm32f4xx_iwdg.h"
#include "stm32f4xx_spi.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_syscfg.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_rtc.h"
#include "stm32f4xx_pwr.h"


/*********************************************************************************************************
                                            STM32  BSP
*********************************************************************************************************/
#include "bsp_adc.h"
#include "bsp_cap.h"
#include "bsp_gpio.h"
#include "bsp_iic.h"
#include "bsp_iwdg.h"
#include "bsp_pwm.h"
#include "bsp_rs485.h"
#include "bsp_tim.h"
#include "bsp_usart.h"


/**********************************************************************************************************
                                             STM32  APP
**********************************************************************************************************/
#include "app_task.h" 
#include "app_24cxx.h"
#include "app_usart.h" 
//#include "app_analysisCMD.h" 
#include "app_autoCharge.h" 
#include "app_cap.h" 
#include "app_exit.h" 
//#include "app_headDone.h"
//#include "app_liftMoto.h" 
#include "app_motoDrv.h" 
#include "app_pms.h" 
#include "app_system.h" 
#include "app_tim.h" 
#include "app_imu.h" 
#include "app_key.h" 


/**********************************************************************************************************
                                             define
**********************************************************************************************************/
#define WHEEL_TRACK  					0.38			//YZ01C 单位米 轮距 ,金属外壳0.31,加拿大0.28，塑胶底壳0.41
#define WHEEL_RADIUS  				0.0845		//单位米,轮子半径
#define PI  									3.1415926       
#define PULSE_CYCLE   				5600			//脉冲周期

#endif
