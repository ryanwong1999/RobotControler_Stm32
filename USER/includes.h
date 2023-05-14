#ifndef  INCLUDES_MODULES_PRESENT
#define  INCLUDES_MODULES_PRESENT


/*
*********************************************************************************************************
*                                         STANDARD LIBRARIES
*********************************************************************************************************
*/
#include  <stdio.h>
#include  <string.h>
#include  <ctype.h>
#include  <stdlib.h>
#include  <stdarg.h>
#include  <math.h>

/*
*********************************************************************************************************
*                                            STM32  SYSTEM
*********************************************************************************************************
*/
#include "delay.h"
#include "sys.h"
#include "usart.h"	
//#include "malloc.h"	 
#include "FreeRTOS.h"
#include "task.h"
/*
*********************************************************************************************************
*                                            STM32  BSP
*********************************************************************************************************
*/


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
