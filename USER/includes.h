#ifndef __INCLUDES_H
#define __INCLUDES_H

/*
*********************************************************************************************************
*                                         STANDARD LIBRARIES
*********************************************************************************************************
*/
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


/*
*********************************************************************************************************
*                                            STM32  SYSTEM
*********************************************************************************************************
*/
#include "stm32f4xx.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"	
//#include "malloc.h"	 

/*
*********************************************************************************************************
*                                            STM32  BSP
*********************************************************************************************************
*/
#include "bsp_adc.h"
#include "bsp_cap.h"
#include "bsp_gpio.h"
#include "bsp_iic.h"
#include "bsp_iwdg.h"
#include "bsp_pwm.h"
#include "bsp_rs485.h"
#include "bsp_tim.h"
#include "bsp_usart.h"

/*
*********************************************************************************************************
*                                            STM32  APP
*********************************************************************************************************
*/
#include "led.h"
#include "app_task.h" 
#include "app_24cxx.h"
#include "app_usart.h" 
#include "app_analysisCMD.h" 
#include "app_autoCharge.h" 
#include "app_cap.h" 
#include "app_exit.h" 
#include "app_headDone.h"
#include "app_liftMoto.h" 
#include "app_pms.h" 
#include "app_system.h" 
#include "app_tim.h" 


#endif
