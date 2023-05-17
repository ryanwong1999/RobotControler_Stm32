#include "includes.h" 

void Start_Task(void *pvParameters)
{
	taskENTER_CRITICAL();           //�����ٽ���
	
	xTaskCreate((TaskFunction_t )Pmu_Task,            //������
							(const char*    )"Pmu_Task",          //��������
							(uint16_t       )PMU_STK_SIZE,        //�����ջ��С
							(void*          )NULL,                  //���ݸ��������Ĳ���
							(UBaseType_t    )PMU_TASK_PRIO,       //�������ȼ�
							(TaskHandle_t*  )&Pmu_Task_Handler);   //������
							

							
										 
	vTaskDelete(Start_Task_Handler); //ɾ����ʼ����
										 
	taskEXIT_CRITICAL();            //�˳��ٽ���
}