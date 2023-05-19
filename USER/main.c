#include "includes.h"

int main(void)
{ 
	System_Board_Init();		//��ʼ��ϵͳӲ����Դ
	delay_ms(200);
	EN_OUT_ENABLE;					//Ӳ�����ʹ��VCC-OUT
	System_StartTips();			//ϵͳ������������ʾ
	
	
	taskENTER_CRITICAL();		//�����ٽ���
	
	//������ʼ����
	xTaskCreate((TaskFunction_t )Start_Task,            	//������
							(const char*    )"Start_Task",          	//��������
							(uint16_t       )START_STK_SIZE,        	//�����ջ��С
							(void*          )NULL,                  	//���ݸ��������Ĳ���
							(UBaseType_t    )START_TASK_PRIO,       	//�������ȼ�
							(TaskHandle_t*  )&Start_Task_Handler);		//������  

	taskEXIT_CRITICAL();		//�˳��ٽ���	
  vTaskStartScheduler();	//�����������			
	while(1);
}
 


