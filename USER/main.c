#define MAIN_GLOBALS
#include "includes.h"

Sys_Type   			Robot_Sys;
Odom_Data_type  Moto_Odom;    // 里程数据

int main(void)
{ 
	taskENTER_CRITICAL();		//进入临界区
	
	
	System_Board_Init();		//初始化系统硬件资源
	NVIC_Configuration();		//中断优先级配置
	IWDG_Init(IWDG_Prescaler_64, 625);			//与分频数为64,重载值为500,溢出时间为1s	
	delay_ms(200);
	System_StartTips();			//系统启动蜂鸣器提示
	MenuInit();

	

	
	//创建开始任务
	printf("ROBOT System starting!!\r\n"); 
	
	xTaskCreate((TaskFunction_t)Start_Task,            	//任务函数
							(const char*   )"Start_Task",          	//任务名称
							(uint16_t      )START_STK_SIZE,        	//任务堆栈大小
							(void*         )NULL,                  	//传递给任务函数的参数
							(UBaseType_t   )START_TASK_PRIO,       	//任务优先级
							(TaskHandle_t* )&Start_Task_Handler);		//任务句柄  

	taskEXIT_CRITICAL();		//退出临界区	
  vTaskStartScheduler();	//开启任务调度
							
	//不会运行到这里
	return 0;
}
 


