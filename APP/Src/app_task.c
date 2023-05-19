#define APP_TASK_GLOBALS	 //����ȫ�ֱ���˽�к꣬������.c�ļ�û�ж���ú�
#include "includes.h" 

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

	xTaskCreate((TaskFunction_t )Head_Ctrl_Task,            //������
							(const char*    )"Head_Ctrl_Task",          //��������
							(uint16_t       )HEAD_CTRL_STK_SIZE,        //�����ջ��С
							(void*          )NULL,                			//���ݸ��������Ĳ���
							(UBaseType_t    )HEAD_CTRL_TASK_PRIO,       //�������ȼ�
							(TaskHandle_t*  )&Head_Ctrl_Task_Handler);	//������  

	xTaskCreate((TaskFunction_t )LiftMoto_Task,            	//������
							(const char*    )"LiftMoto_Task",          	//��������
							(uint16_t       )LIFTMOTO_STK_SIZE,        	//�����ջ��С
							(void*          )NULL,                			//���ݸ��������Ĳ���
							(UBaseType_t    )LIFTMOTO_TASK_PRIO,       	//�������ȼ�
							(TaskHandle_t*  )&LiftMoto_Task_Handler);		//������  
							
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
		
		delay_ms(100);
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
		delay_ms(200);
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
		delay_ms(1000);
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
		delay_ms(200);
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
		delay_ms(100);
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
		delay_ms(3);
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
	while(1)
	{
		delay_ms(100);
	}
}


/************************************************/
//�������ܣ��ֶ�ͷ����������
//���������
//����ֵ��
//��ע��
/************************************************/
void Head_Ctrl_Task(void *pvParameters)
{
	while(1)
	{
		delay_ms(20);
	}
}


/************************************************/
//�������ܣ�������������
//���������
//����ֵ��
//��ע��
/************************************************/
void LiftMoto_Task(void *pvParameters)
{
	while(1)
	{
		delay_ms(10);
	}
}


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
		delay_ms(25);
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
		delay_ms(5);
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
		LED_TEST_TOGGLE;
		
		delay_ms(500);
	}
}

