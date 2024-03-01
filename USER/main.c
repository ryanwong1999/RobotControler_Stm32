#define MAIN_GLOBALS
#include "includes.h"

Sys_Type   			Robot_Sys;
Odom_Data_type  Moto_Odom;    // �������

int main(void)
{ 
	taskENTER_CRITICAL();		//�����ٽ���
	
	
	System_Board_Init();		//��ʼ��ϵͳӲ����Դ
	NVIC_Configuration();		//�ж����ȼ�����
	IWDG_Init(IWDG_Prescaler_64, 625);			//���Ƶ��Ϊ64,����ֵΪ500,���ʱ��Ϊ1s	
	delay_ms(200);
	System_StartTips();			//ϵͳ������������ʾ
	MenuInit();

	

	
	//������ʼ����
	printf("ROBOT System starting!!\r\n"); 
	
	xTaskCreate((TaskFunction_t)Start_Task,            	//������
							(const char*   )"Start_Task",          	//��������
							(uint16_t      )START_STK_SIZE,        	//�����ջ��С
							(void*         )NULL,                  	//���ݸ��������Ĳ���
							(UBaseType_t   )START_TASK_PRIO,       	//�������ȼ�
							(TaskHandle_t* )&Start_Task_Handler);		//������  

	taskEXIT_CRITICAL();		//�˳��ٽ���	
  vTaskStartScheduler();	//�����������
							
	//�������е�����
	return 0;
}
 


