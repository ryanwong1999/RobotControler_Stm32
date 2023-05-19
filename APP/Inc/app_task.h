#ifndef __APP_TASK_H__
#define __APP_TASK_H__
#include "includes.h"

#ifdef   APP_TASK_GLOBALS  //当编译app_task.c文件时，因为在app_task.c文件的最开始定义了APP_TASK_GLOBALS，因此将 APP_TASK_EXT定义为空，而当编译其他.C文件时，因为没有定义该宏，所以将APP_TASK_EXT 定义为 extern 
												   //这样就实现了直接在.h文件中定义全局变量
#define  APP_TASK_EXT
#else
#define  APP_TASK_EXT  extern
#endif


/**************************************任务句柄*************************************/
APP_TASK_EXT TaskHandle_t Start_Task_Handler;
APP_TASK_EXT TaskHandle_t Pmu_Task_Handler;
APP_TASK_EXT TaskHandle_t Cammand_Task_Handler;
APP_TASK_EXT TaskHandle_t Err_Task_Handler;
APP_TASK_EXT TaskHandle_t Poweroff_Task_Handler;
APP_TASK_EXT TaskHandle_t Chg_Task_Handler;
APP_TASK_EXT TaskHandle_t Test_Task_Handler;
APP_TASK_EXT TaskHandle_t Head_Ctrl_Task_Handler;
APP_TASK_EXT TaskHandle_t AutoCharge_Task_Handler;
APP_TASK_EXT TaskHandle_t Ultra_Task_Handler;
APP_TASK_EXT TaskHandle_t Send_Mdrv_Task_Handler;
APP_TASK_EXT TaskHandle_t Mdrv_Task_Handler;
APP_TASK_EXT TaskHandle_t LiftMoto_Task_Handler;
APP_TASK_EXT TaskHandle_t LED_Task_Handler;


/**********************************设置任务优先级***********************************/
#define START_TASK_PRIO		   		3 
#define PMU_TASK_PRIO	     	 		3   
#define CAMMAND_TASK_PRIO    		4
#define ERR_TASK_PRIO        		5
#define POWEROFF_TASK_PRIO   		6    
#define CHG_TASK_PRIO        		7
#define TEST_TASK_PRIO    			8
#define HEAD_CTRL_TASK_PRIO  		10
#define AUTOCHARGE_TASK_PRIO		11
#define SEND_MDRV_TASK_PRIO   	13
#define MDRV_TASK_PRIO    			14
#define LIFTMOTO_TASK_PRIO			17
#define LED_TASK_PRIO		     		30  
//#define ULTRA_TASK_PRIO      		12
//#define MOVE_SPEED_TASK_PRIO 		4
//#define ENVIRON_TASK_PRIO				8
//#define ENVIRON_QUERY_TASK_PRIO	19


/**********************************设置任务堆栈大小*********************************/
#define START_STK_SIZE 		   		128  
#define PMU_STK_SIZE 		     		128 
#define ERR_STK_SIZE 		     		128 
#define POWEROFF_STK_SIZE    		128  
#define CHG_STK_SIZE         		128
#define TEST_STK_SIZE        		128
#define CAMMAND_STK_SIZE     		128
#define SEND_MDRV_STK_SIZE    	128
#define MDRV_STK_SIZE         	128
#define HEAD_CTRL_STK_SIZE 	 		128 
#define AUTOCHARGE_STK_SIZE			128
#define LIFTMOTO_STK_SIZE    		128
#define LED_STK_SIZE 		     		128 
//#define ULTRA_STK_SIZE 	     		128 
//#define MOVE_SPEED_STK_SIZE	 		128
//#define ENVIRON_STK_SIZE				128
//#define ENVIRON_QUERY_STK_SIZE	128


/*************************************任务堆栈**************************************/
APP_TASK_EXT StackType_t START_TASK_STK[START_STK_SIZE];
APP_TASK_EXT StackType_t PMU_TASK_STK[PMU_STK_SIZE];
APP_TASK_EXT StackType_t ERR_TASK_STK[ERR_STK_SIZE];
APP_TASK_EXT StackType_t POWEROFF_TASK_STK[POWEROFF_STK_SIZE];
APP_TASK_EXT StackType_t CHG_TASK_STK[CHG_STK_SIZE];
APP_TASK_EXT StackType_t TEST_TASK_STK[TEST_STK_SIZE];
APP_TASK_EXT StackType_t CAMMAND_TASK_STK[CAMMAND_STK_SIZE];
APP_TASK_EXT StackType_t SEND_MDRV_TASK_STK[SEND_MDRV_STK_SIZE];
APP_TASK_EXT StackType_t MDRV_TASK_STK[MDRV_STK_SIZE];
APP_TASK_EXT StackType_t HEAD_CTRL_TASK_STK[HEAD_CTRL_STK_SIZE];
APP_TASK_EXT StackType_t AUTOCHARGE_TASK_STK[AUTOCHARGE_STK_SIZE];
APP_TASK_EXT StackType_t LIFTMOTO_TASK_STK[LIFTMOTO_STK_SIZE];
APP_TASK_EXT StackType_t LED_TASK_STK[LED_STK_SIZE];
//APP_TASK_EXT StackType_t ULTRA_TASK_STK[ULTRA_STK_SIZE];


/***********************************任务函数声明*************************************/
void Start_Task(void *pvParameters);	
void Err_Handle_Task(void *pvParameters);		//异常任务处理函数
void Poweroff_Task(void *pvParameters);    	//关机任务处理函数
void Pmu_Task(void *pvParameters);     			//电源管理函数
void Chg_Task(void *pvParameters);    			//充电任务处理函数
void AutoCharge_Task(void *pvParameters);   //自动充电处理
void Cammand_Task(void *pvParameters);    	//命令处理函数
void Test_Task(void *pvParameters);					//测试任务
void Head_Ctrl_Task(void *pvParameters);    //手动头部控制
void LiftMoto_Task(void *pvParameters);			//升降处理
void Send_Mdrv_Task(void *pvParameters);		//发送伺服驱动器命令
void Mdrv_Task(void *pvParameters);					//伺服驱动器处理
void LED_Task(void *pvParameters);     			//led测试函数
//void Ultrasonic_Task(void *pvParameters);			//超声处理
//void Move_Speed_task(void *pvParameters);			//速度处理
//void Environ_task(void *pvParameters);				//环境处理
//void Environ_Query_task(void *pvParameters);	//环境数据请求

#endif