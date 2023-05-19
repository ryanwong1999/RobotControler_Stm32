#define APP_TASK_GLOBALS	 //定义全局变量私有宏，即其他.c文件没有定义该宏
#include "includes.h" 

void Start_Task(void *pvParameters)
{
	taskENTER_CRITICAL();           												//进入临界区
	
	xTaskCreate((TaskFunction_t )Pmu_Task,            			//任务函数
							(const char*    )"Pmu_Task",          			//任务名称
							(uint16_t       )PMU_STK_SIZE,        			//任务堆栈大小
							(void*          )NULL,                			//传递给任务函数的参数
							(UBaseType_t    )PMU_TASK_PRIO,       			//任务优先级
							(TaskHandle_t*  )&Pmu_Task_Handler);				//任务句柄  

	xTaskCreate((TaskFunction_t )Cammand_Task,            	//任务函数
							(const char*    )"Cammand_Task",          	//任务名称
							(uint16_t       )CAMMAND_STK_SIZE,        	//任务堆栈大小
							(void*          )NULL,                			//传递给任务函数的参数
							(UBaseType_t    )CAMMAND_TASK_PRIO,       	//任务优先级
							(TaskHandle_t*  )&Cammand_Task_Handler);		//任务句柄  				
										 
	xTaskCreate((TaskFunction_t )Err_Handle_Task,           //任务函数
							(const char*    )"Err_Handle_Task",         //任务名称
							(uint16_t       )ERR_STK_SIZE,        			//任务堆栈大小
							(void*          )NULL,                			//传递给任务函数的参数
							(UBaseType_t    )ERR_TASK_PRIO,       			//任务优先级
							(TaskHandle_t*  )&Err_Task_Handler);				//任务句柄  		

	xTaskCreate((TaskFunction_t )Poweroff_Task,            	//任务函数
							(const char*    )"Poweroff_Task",          	//任务名称
							(uint16_t       )POWEROFF_STK_SIZE,        	//任务堆栈大小
							(void*          )NULL,                			//传递给任务函数的参数
							(UBaseType_t    )POWEROFF_TASK_PRIO,       	//任务优先级
							(TaskHandle_t*  )&Poweroff_Task_Handler);		//任务句柄  		

	xTaskCreate((TaskFunction_t )Chg_Task,            			//任务函数
							(const char*    )"Chg_Task",          			//任务名称
							(uint16_t       )CHG_STK_SIZE,        			//任务堆栈大小
							(void*          )NULL,                			//传递给任务函数的参数
							(UBaseType_t    )CHG_TASK_PRIO,       			//任务优先级
							(TaskHandle_t*  )&Chg_Task_Handler);				//任务句柄  	

	xTaskCreate((TaskFunction_t )Test_Task,            			//任务函数
							(const char*    )"Test_Task",          			//任务名称
							(uint16_t       )TEST_STK_SIZE,        			//任务堆栈大小
							(void*          )NULL,                			//传递给任务函数的参数
							(UBaseType_t    )TEST_TASK_PRIO,       			//任务优先级
							(TaskHandle_t*  )&Test_Task_Handler);				//任务句柄  

	xTaskCreate((TaskFunction_t )Head_Ctrl_Task,            //任务函数
							(const char*    )"Head_Ctrl_Task",          //任务名称
							(uint16_t       )HEAD_CTRL_STK_SIZE,        //任务堆栈大小
							(void*          )NULL,                			//传递给任务函数的参数
							(UBaseType_t    )HEAD_CTRL_TASK_PRIO,       //任务优先级
							(TaskHandle_t*  )&Head_Ctrl_Task_Handler);	//任务句柄  

	xTaskCreate((TaskFunction_t )LiftMoto_Task,            	//任务函数
							(const char*    )"LiftMoto_Task",          	//任务名称
							(uint16_t       )LIFTMOTO_STK_SIZE,        	//任务堆栈大小
							(void*          )NULL,                			//传递给任务函数的参数
							(UBaseType_t    )LIFTMOTO_TASK_PRIO,       	//任务优先级
							(TaskHandle_t*  )&LiftMoto_Task_Handler);		//任务句柄  
							
	xTaskCreate((TaskFunction_t )AutoCharge_Task,           //任务函数
							(const char*    )"AutoCharge_Task",         //任务名称
							(uint16_t       )AUTOCHARGE_STK_SIZE,       //任务堆栈大小
							(void*          )NULL,                			//传递给任务函数的参数
							(UBaseType_t    )AUTOCHARGE_TASK_PRIO,      //任务优先级
							(TaskHandle_t*  )&AutoCharge_Task_Handler);	//任务句柄  			
							
	xTaskCreate((TaskFunction_t )Send_Mdrv_Task,            //任务函数
							(const char*    )"Send_Mdrv_Task",          //任务名称
							(uint16_t       )SEND_MDRV_STK_SIZE,        //任务堆栈大小
							(void*          )NULL,                			//传递给任务函数的参数
							(UBaseType_t    )SEND_MDRV_TASK_PRIO,       //任务优先级
							(TaskHandle_t*  )&Send_Mdrv_Task_Handler);	//任务句柄 
							
	xTaskCreate((TaskFunction_t )Mdrv_Task,            			//任务函数
							(const char*    )"Mdrv_Task",          			//任务名称
							(uint16_t       )MDRV_STK_SIZE,        			//任务堆栈大小
							(void*          )NULL,                			//传递给任务函数的参数
							(UBaseType_t    )MDRV_TASK_PRIO,       			//任务优先级
							(TaskHandle_t*  )&Mdrv_Task_Handler);				//任务句柄
							
	xTaskCreate((TaskFunction_t )LED_Task,            			//任务函数
							(const char*    )"LED_Task",          			//任务名称
							(uint16_t       )LED_STK_SIZE,        			//任务堆栈大小
							(void*          )NULL,                			//传递给任务函数的参数
							(UBaseType_t    )LED_TASK_PRIO,       			//任务优先级
							(TaskHandle_t*  )&LED_Task_Handler);				//任务句柄
							
	vTaskDelete(Start_Task_Handler);												//删除开始任务
	taskEXIT_CRITICAL();            												//退出临界区
}


/************************************************/
//函数功能：异常任务处理任务
//输入参数：
//返回值：
//备注：
/************************************************/
void Err_Handle_Task(void *pvParameters)
{
	while(1)
	{
		IWDG_Feed();//喂狗
		
		delay_ms(100);
	}
}


/************************************************/
//函数功能：关机任务处理任务
//输入参数：
//返回值：
//备注：
/************************************************/
void Poweroff_Task(void *pvParameters)
{
	while(1)
	{
		delay_ms(200);
	}
}


/************************************************/
//函数功能：电源管理任务
//输入参数：
//返回值：
//备注：
/************************************************/
void Pmu_Task(void *pvParameters)
{
	while(1)
	{
		delay_ms(1000);
	}
}


/************************************************/
//函数功能：充电任务处理任务
//输入参数：
//返回值：
//备注：
/************************************************/
void Chg_Task(void *pvParameters)
{
	while(1)
	{
		delay_ms(200);
	}
}


/************************************************/
//函数功能：自动充电处理任务
//输入参数：
//返回值：
//备注：
/************************************************/
void AutoCharge_Task(void *pvParameters)
{
	while(1)
	{
		delay_ms(100);
	}
}


/************************************************/
//函数功能：命令处理任务
//输入参数：
//返回值：
//备注：
/************************************************/
void Cammand_Task(void *pvParameters)
{
	while(1)
	{
		delay_ms(3);
	}
}


/************************************************/
//函数功能：测试任务
//输入参数：
//返回值：
//备注：
/************************************************/
void Test_Task(void *pvParameters)
{
	while(1)
	{
		delay_ms(100);
	}
}


/************************************************/
//函数功能：手动头部控制任务
//输入参数：
//返回值：
//备注：
/************************************************/
void Head_Ctrl_Task(void *pvParameters)
{
	while(1)
	{
		delay_ms(20);
	}
}


/************************************************/
//函数功能：升降处理任务
//输入参数：
//返回值：
//备注：
/************************************************/
void LiftMoto_Task(void *pvParameters)
{
	while(1)
	{
		delay_ms(10);
	}
}


/************************************************/
//函数功能：发送伺服驱动器命令任务
//输入参数：
//返回值：
//备注：
/************************************************/
void Send_Mdrv_Task(void *pvParameters)
{
	while(1)
	{
		delay_ms(25);
	}
}


/************************************************/
//函数功能：伺服驱动器处理任务
//输入参数：
//返回值：
//备注：
/************************************************/
void Mdrv_Task(void *pvParameters)
{
	while(1)
	{
		delay_ms(5);
	}
}


/************************************************/
//函数功能：led控制任务
//输入参数：
//返回值：
//备注：
/************************************************/
void LED_Task(void *pvParameters)
{
	while(1)
	{
		LED_TEST_TOGGLE;
		
		delay_ms(500);
	}
}

