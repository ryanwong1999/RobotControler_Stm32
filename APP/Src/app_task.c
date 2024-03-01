#define APP_TASK_GLOBALS	 //����ȫ�ֱ���˽�к꣬������.c�ļ�û�ж���ú�
#include "includes.h" 

u8 isKeyUp = 0;
u8 isKeyDown = 0;
u8 isKeyBack = 0;
u8 isKeyEnter = 0;

void Start_Task(void *pvParameters)
{
	taskENTER_CRITICAL();           												//�����ٽ���
	
	xTaskCreate((TaskFunction_t )Pmu_Task,            			//������
							(const char*    )"Pmu_Task",          			//��������
							(uint16_t       )PMU_STK_SIZE,        			//�����ջ��С
							(void*          )NULL,                			//���ݸ��������Ĳ���
							(UBaseType_t    )PMU_TASK_PRIO,       			//�������ȼ�
							(TaskHandle_t*  )&Pmu_Task_Handler);				//������  

	xTaskCreate((TaskFunction_t )Cammand_Task,            	//������
							(const char*    )"Cammand_Task",          	//��������
							(uint16_t       )CAMMAND_STK_SIZE,        	//�����ջ��С
							(void*          )NULL,                			//���ݸ��������Ĳ���
							(UBaseType_t    )CAMMAND_TASK_PRIO,       	//�������ȼ�
							(TaskHandle_t*  )&Cammand_Task_Handler);		//������  				
										 
	xTaskCreate((TaskFunction_t )Err_Handle_Task,           //������
							(const char*    )"Err_Handle_Task",         //��������
							(uint16_t       )ERR_STK_SIZE,        			//�����ջ��С
							(void*          )NULL,                			//���ݸ��������Ĳ���
							(UBaseType_t    )ERR_TASK_PRIO,       			//�������ȼ�
							(TaskHandle_t*  )&Err_Task_Handler);				//������  		

	xTaskCreate((TaskFunction_t )Poweroff_Task,            	//������
							(const char*    )"Poweroff_Task",          	//��������
							(uint16_t       )POWEROFF_STK_SIZE,        	//�����ջ��С
							(void*          )NULL,                			//���ݸ��������Ĳ���
							(UBaseType_t    )POWEROFF_TASK_PRIO,       	//�������ȼ�
							(TaskHandle_t*  )&Poweroff_Task_Handler);		//������  		

	xTaskCreate((TaskFunction_t )Chg_Task,            			//������
							(const char*    )"Chg_Task",          			//��������
							(uint16_t       )CHG_STK_SIZE,        			//�����ջ��С
							(void*          )NULL,                			//���ݸ��������Ĳ���
							(UBaseType_t    )CHG_TASK_PRIO,       			//�������ȼ�
							(TaskHandle_t*  )&Chg_Task_Handler);				//������  	

	xTaskCreate((TaskFunction_t )Test_Task,            			//������
							(const char*    )"Test_Task",          			//��������
							(uint16_t       )TEST_STK_SIZE,        			//�����ջ��С
							(void*          )NULL,                			//���ݸ��������Ĳ���
							(UBaseType_t    )TEST_TASK_PRIO,       			//�������ȼ�
							(TaskHandle_t*  )&Test_Task_Handler);				//������  

	xTaskCreate((TaskFunction_t )Display_Task,            	//������
							(const char*    )"Display_Task",          	//��������
							(uint16_t       )DISPLAY_STK_SIZE,        	//�����ջ��С
							(void*          )NULL,                			//���ݸ��������Ĳ���
							(UBaseType_t    )DISPLAY_TASK_PRIO,       	//�������ȼ�
							(TaskHandle_t*  )&Display_Task_Handler);		//������  

//	xTaskCreate((TaskFunction_t )LiftMoto_Task,            	//������
//							(const char*    )"LiftMoto_Task",          	//��������
//							(uint16_t       )LIFTMOTO_STK_SIZE,        	//�����ջ��С
//							(void*          )NULL,                			//���ݸ��������Ĳ���
//							(UBaseType_t    )LIFTMOTO_TASK_PRIO,       	//�������ȼ�
//							(TaskHandle_t*  )&LiftMoto_Task_Handler);		//������  
							
	xTaskCreate((TaskFunction_t )AutoCharge_Task,           //������
							(const char*    )"AutoCharge_Task",         //��������
							(uint16_t       )AUTOCHARGE_STK_SIZE,       //�����ջ��С
							(void*          )NULL,                			//���ݸ��������Ĳ���
							(UBaseType_t    )AUTOCHARGE_TASK_PRIO,      //�������ȼ�
							(TaskHandle_t*  )&AutoCharge_Task_Handler);	//������  			
							
	xTaskCreate((TaskFunction_t )Send_Mdrv_Task,            //������
							(const char*    )"Send_Mdrv_Task",          //��������
							(uint16_t       )SEND_MDRV_STK_SIZE,        //�����ջ��С
							(void*          )NULL,                			//���ݸ��������Ĳ���
							(UBaseType_t    )SEND_MDRV_TASK_PRIO,       //�������ȼ�
							(TaskHandle_t*  )&Send_Mdrv_Task_Handler);	//������ 
							
	xTaskCreate((TaskFunction_t )Mdrv_Task,            			//������
							(const char*    )"Mdrv_Task",          			//��������
							(uint16_t       )MDRV_STK_SIZE,        			//�����ջ��С
							(void*          )NULL,                			//���ݸ��������Ĳ���
							(UBaseType_t    )MDRV_TASK_PRIO,       			//�������ȼ�
							(TaskHandle_t*  )&Mdrv_Task_Handler);				//������
							
	xTaskCreate((TaskFunction_t )LED_Task,            			//������
							(const char*    )"LED_Task",          			//��������
							(uint16_t       )LED_STK_SIZE,        			//�����ջ��С
							(void*          )NULL,                			//���ݸ��������Ĳ���
							(UBaseType_t    )LED_TASK_PRIO,       			//�������ȼ�
							(TaskHandle_t*  )&LED_Task_Handler);				//������

	xTaskCreate((TaskFunction_t )Key_Task,            			//������
							(const char*    )"Key_Task",          			//��������
							(uint16_t       )KEY_STK_SIZE,        			//�����ջ��С
							(void*          )NULL,                  		//���ݸ��������Ĳ���
							(UBaseType_t    )KEY_TASK_PRIO,       			//�������ȼ�
							(TaskHandle_t*  )&Key_Task_Handler);   			//������							
							
	vTaskDelete(Start_Task_Handler);												//ɾ����ʼ����
	taskEXIT_CRITICAL();            												//�˳��ٽ���
}


/************************************************/
//�������ܣ��쳣����������
//���������
//����ֵ��
//��ע��
/************************************************/
void Err_Handle_Task(void *pvParameters)
{
	while(1)
	{
		IWDG_Feed();//ι��
		vTaskDelay(100);
	}
}

/************************************************/
//�������ܣ���������������
//���������
//����ֵ��
//��ע��
/************************************************/
void Key_Task(void *p_arg)
{
	u8 key;
	while(1)
	{
		key = KEY_Scan(0);		//�õ���ֵ
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
//�������ܣ���ʾ����
//���������
//����ֵ��
//��ע��
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
//�������ܣ��ػ�����������
//���������
//����ֵ��
//��ע��
/************************************************/
void Poweroff_Task(void *pvParameters)
{
	while(1)
	{
		
		vTaskDelay(200);
	}
}


/************************************************/
//�������ܣ���Դ��������
//���������
//����ֵ��
//��ע��
/************************************************/
void Pmu_Task(void *pvParameters)
{
	while(1)
	{
		vTaskDelay(1000);
	}
}


/************************************************/
//�������ܣ��������������
//���������
//����ֵ��
//��ע��
/************************************************/
void Chg_Task(void *pvParameters)
{
	while(1)
	{
		vTaskDelay(200);
	}
}


/************************************************/
//�������ܣ��Զ���紦������
//���������
//����ֵ��
//��ע��
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
//�������ܣ����������
//���������
//����ֵ��
//��ע��
/************************************************/
void Cammand_Task(void *pvParameters)
{
	while(1)
	{
		vTaskDelay(10);
	}
}


/************************************************/
//�������ܣ���������
//���������
//����ֵ��
//��ע��
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
			delay_ms(100);	//�ȴ�ģ���ڲ��Զ�У׼�ã�ģ���ڲ����Զ�������Ҫһ����ʱ��
			savacalsw();
			delay_ms(100);	//���浱ǰ����
		}


//		//������ٶ�
//		//���ڽ��ܵ��������Ѿ���������Ӧ�Ľṹ��ı������ˣ�����˵�����Э�飬�Լ��ٶ�Ϊ�� stcAcc.a[0]/32768*16����X��ļ��ٶȣ�
//		printf("Acc:%.3f %.3f %.3f\r\n", (float)stcAcc.a[0]/32768*16, (float)stcAcc.a[1]/32768*16, (float)stcAcc.a[2]/32768*16);
//			delay_ms(10);
//		//������ٶ�
//		printf("Gyro:%.3f %.3f %.3f\r\n", (float)stcGyro.w[0]/32768*2000, (float)stcGyro.w[1]/32768*2000, (float)stcGyro.w[2]/32768*2000);
//			delay_ms(10);
//		//����Ƕ�
//		printf("Angle:%.3f %.3f %.3f\r\n", (float)stcAngle.Angle[0]/32768*180, (float)stcAngle.Angle[1]/32768*180, (float)stcAngle.Angle[2]/32768*180);
//			delay_ms(10);
//		//����ų�
//		printf("Mag:%d %d %d\r\n",stcMag.h[0], stcMag.h[1], stcMag.h[2]);	
//			delay_ms(10);


//		//���ʱ��
//		printf("Time:20%d-%d-%d %d:%d:%.3f\r\n", stcTime.ucYear, stcTime.ucMonth, stcTime.ucDay, stcTime.ucHour, stcTime.ucMinute, (float)stcTime.ucSecond+(float)stcTime.usMiliSecond/1000);
//			delay_ms(10);
//		//�����ѹ���߶�
//		printf("Pressure:%ld Height%.2f\r\n", stcPress.lPressure, (float)stcPress.lAltitude/100);
//			delay_ms(10);
//		//����˿�״̬
//		printf("DStatus:%d %d %d %d\r\n", stcDStatus.sDStatus[0], stcDStatus.sDStatus[1], stcDStatus.sDStatus[2], stcDStatus.sDStatus[3]);
//			delay_ms(10);
//		//�����γ��
//		printf("Longitude:%ldDeg%.5fm Lattitude:%ldDeg%.5fm\r\n", stcLonLat.lLon/10000000, (double)(stcLonLat.lLon % 10000000)/1e5, stcLonLat.lLat/10000000, (double)(stcLonLat.lLat % 10000000)/1e5);
//			delay_ms(10);
//		//�������
//		printf("GPSHeight:%.1fm GPSYaw:%.1fDeg GPSV:%.3fkm/h\r\n", (float)stcGPSV.sGPSHeight/10, (float)stcGPSV.sGPSYaw/10, (float)stcGPSV.lGPSVelocity/1000);
//			delay_ms(10);
//		//�����Ԫ��
//		printf("Four elements:%.5f %.5f %.5f %.5f\r\n\r\n", (float)stcQ.q[0]/32768, (float)stcQ.q[1]/32768, (float)stcQ.q[2]/32768, (float)stcQ.q[3]/32768);
//		  delay_ms(10);//�ȴ��������

		vTaskDelay(1000);
	}
}


/************************************************/
//�������ܣ�������������
//���������
//����ֵ��
//��ע��
/************************************************/
//void LiftMoto_Task(void *pvParameters)
//{
//	while(1)
//	{
//		vTaskDelay(10);
//	}
//}


/************************************************/
//�������ܣ������ŷ���������������
//���������
//����ֵ��
//��ע��
/************************************************/
void Send_Mdrv_Task(void *pvParameters)
{
	while(1)
	{
		vTaskDelay(25);
	}
}


/************************************************/
//�������ܣ��ŷ���������������
//���������
//����ֵ��
//��ע��
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
//�������ܣ�led��������
//���������
//����ֵ��
//��ע��
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

