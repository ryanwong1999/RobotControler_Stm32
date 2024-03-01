#define APP_TASK_GLOBALS	 //定义全局变量私有宏，即其他.c文件没有定义该宏
#include "includes.h" 

u8 isKeyUp = 0;
u8 isKeyDown = 0;
u8 isKeyBack = 0;
u8 isKeyEnter = 0;

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

	xTaskCreate((TaskFunction_t )Display_Task,            	//任务函数
							(const char*    )"Display_Task",          	//任务名称
							(uint16_t       )DISPLAY_STK_SIZE,        	//任务堆栈大小
							(void*          )NULL,                			//传递给任务函数的参数
							(UBaseType_t    )DISPLAY_TASK_PRIO,       	//任务优先级
							(TaskHandle_t*  )&Display_Task_Handler);		//任务句柄  

//	xTaskCreate((TaskFunction_t )LiftMoto_Task,            	//任务函数
//							(const char*    )"LiftMoto_Task",          	//任务名称
//							(uint16_t       )LIFTMOTO_STK_SIZE,        	//任务堆栈大小
//							(void*          )NULL,                			//传递给任务函数的参数
//							(UBaseType_t    )LIFTMOTO_TASK_PRIO,       	//任务优先级
//							(TaskHandle_t*  )&LiftMoto_Task_Handler);		//任务句柄  
							
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

	xTaskCreate((TaskFunction_t )Key_Task,            			//任务函数
							(const char*    )"Key_Task",          			//任务名称
							(uint16_t       )KEY_STK_SIZE,        			//任务堆栈大小
							(void*          )NULL,                  		//传递给任务函数的参数
							(UBaseType_t    )KEY_TASK_PRIO,       			//任务优先级
							(TaskHandle_t*  )&Key_Task_Handler);   			//任务句柄							
							
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
		vTaskDelay(100);
	}
}

/************************************************/
//函数功能：按键任务处理任务
//输入参数：
//返回值：
//备注：
/************************************************/
void Key_Task(void *p_arg)
{
	u8 key;
	while(1)
	{
		key = KEY_Scan(0);		//得到键值
		LED2_OFF;
		switch(key)
		{				 
			case KEY_UP_PRES:
				printf("KEY_UP_PRES!!\r\n");
				LED2_ON;
				isKeyUp = 1;
				break;
			case KEY_DOWN_PRES:
				printf("KEY_DOWN_PRES!!\r\n");
				LED2_ON;
				isKeyDown = 1;
				break;
			case KEY_ENTER_PRES:
				printf("KEY_ENTER_PRES!!\r\n");
				LED2_ON;
			  isKeyEnter = 1;
				break;
//			default:
//				break;
		}
		vTaskDelay(100);
	}
}


/************************************************/
//函数功能：显示任务
//输入参数：
//返回值：
//备注：
/************************************************/
void Display_Task(void *pvParameters)
{
	while(1)
	{
		count1++;
		count2++;
		count3++;
		count4++;
		MenuControl();
		GuiDataDisplayRefresh();
//		MainUiSet();
		vTaskDelay(100);
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
		
		vTaskDelay(200);
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
		vTaskDelay(1000);
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
		vTaskDelay(200);
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
		if(Robot_Sys.AutoCharge_task_flag == true)
		{
		}
		else
		{
		}
		vTaskDelay(100);
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
		vTaskDelay(10);
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
	u8 i=0;
	while(1)
	{
		i++;
		if(i>20)
		{
			i = 0;
			printf("start ACC Cali\r\n");
			accalsw();
			delay_ms(100);	//等待模块内部自动校准好，模块内部会自动计算需要一定的时间
			savacalsw();
			delay_ms(100);	//保存当前配置
		}


//		//输出加速度
//		//串口接受到的数据已经拷贝到对应的结构体的变量中了，根据说明书的协议，以加速度为例 stcAcc.a[0]/32768*16就是X轴的加速度，
//		printf("Acc:%.3f %.3f %.3f\r\n", (float)stcAcc.a[0]/32768*16, (float)stcAcc.a[1]/32768*16, (float)stcAcc.a[2]/32768*16);
//			delay_ms(10);
//		//输出角速度
//		printf("Gyro:%.3f %.3f %.3f\r\n", (float)stcGyro.w[0]/32768*2000, (float)stcGyro.w[1]/32768*2000, (float)stcGyro.w[2]/32768*2000);
//			delay_ms(10);
//		//输出角度
//		printf("Angle:%.3f %.3f %.3f\r\n", (float)stcAngle.Angle[0]/32768*180, (float)stcAngle.Angle[1]/32768*180, (float)stcAngle.Angle[2]/32768*180);
//			delay_ms(10);
//		//输出磁场
//		printf("Mag:%d %d %d\r\n",stcMag.h[0], stcMag.h[1], stcMag.h[2]);	
//			delay_ms(10);


//		//输出时间
//		printf("Time:20%d-%d-%d %d:%d:%.3f\r\n", stcTime.ucYear, stcTime.ucMonth, stcTime.ucDay, stcTime.ucHour, stcTime.ucMinute, (float)stcTime.ucSecond+(float)stcTime.usMiliSecond/1000);
//			delay_ms(10);
//		//输出气压、高度
//		printf("Pressure:%ld Height%.2f\r\n", stcPress.lPressure, (float)stcPress.lAltitude/100);
//			delay_ms(10);
//		//输出端口状态
//		printf("DStatus:%d %d %d %d\r\n", stcDStatus.sDStatus[0], stcDStatus.sDStatus[1], stcDStatus.sDStatus[2], stcDStatus.sDStatus[3]);
//			delay_ms(10);
//		//输出经纬度
//		printf("Longitude:%ldDeg%.5fm Lattitude:%ldDeg%.5fm\r\n", stcLonLat.lLon/10000000, (double)(stcLonLat.lLon % 10000000)/1e5, stcLonLat.lLat/10000000, (double)(stcLonLat.lLat % 10000000)/1e5);
//			delay_ms(10);
//		//输出地速
//		printf("GPSHeight:%.1fm GPSYaw:%.1fDeg GPSV:%.3fkm/h\r\n", (float)stcGPSV.sGPSHeight/10, (float)stcGPSV.sGPSYaw/10, (float)stcGPSV.lGPSVelocity/1000);
//			delay_ms(10);
//		//输出四元数
//		printf("Four elements:%.5f %.5f %.5f %.5f\r\n\r\n", (float)stcQ.q[0]/32768, (float)stcQ.q[1]/32768, (float)stcQ.q[2]/32768, (float)stcQ.q[3]/32768);
//		  delay_ms(10);//等待传输完成

		vTaskDelay(1000);
	}
}


/************************************************/
//函数功能：升降处理任务
//输入参数：
//返回值：
//备注：
/************************************************/
//void LiftMoto_Task(void *pvParameters)
//{
//	while(1)
//	{
//		vTaskDelay(10);
//	}
//}


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
		vTaskDelay(25);
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
		Moto_mdrv_analysis();
		vTaskDelay(5);
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
		LED1_TOGGLE;
//		LED2_TOGGLE;
		
		vTaskDelay(500);
	}
}

