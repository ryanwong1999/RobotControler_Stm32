#include "includes.h" 

void Start_Task(void *pvParameters)
{
	taskENTER_CRITICAL();           //进入临界区
	
	xTaskCreate((TaskFunction_t )Pmu_Task,            //任务函数
							(const char*    )"Pmu_Task",          //任务名称
							(uint16_t       )PMU_STK_SIZE,        //任务堆栈大小
							(void*          )NULL,                  //传递给任务函数的参数
							(UBaseType_t    )PMU_TASK_PRIO,       //任务优先级
							(TaskHandle_t*  )&Pmu_Task_Handler);   //任务句柄
							

							
										 
	vTaskDelete(Start_Task_Handler); //删除开始任务
										 
	taskEXIT_CRITICAL();            //退出临界区
}