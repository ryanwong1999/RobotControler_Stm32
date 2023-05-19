#ifndef __APP_TASK_H__
#define __APP_TASK_H__
#include "includes.h"

#ifdef   APP_TASK_GLOBALS  //������app_task.c�ļ�ʱ����Ϊ��app_task.c�ļ����ʼ������APP_TASK_GLOBALS����˽� APP_TASK_EXT����Ϊ�գ�������������.C�ļ�ʱ����Ϊû�ж���ú꣬���Խ�APP_TASK_EXT ����Ϊ extern 
												   //������ʵ����ֱ����.h�ļ��ж���ȫ�ֱ���
#define  APP_TASK_EXT
#else
#define  APP_TASK_EXT  extern
#endif


/**************************************������*************************************/
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


/**********************************�����������ȼ�***********************************/
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


/**********************************���������ջ��С*********************************/
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


/*************************************�����ջ**************************************/
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


/***********************************����������*************************************/
void Start_Task(void *pvParameters);	
void Err_Handle_Task(void *pvParameters);		//�쳣��������
void Poweroff_Task(void *pvParameters);    	//�ػ���������
void Pmu_Task(void *pvParameters);     			//��Դ������
void Chg_Task(void *pvParameters);    			//�����������
void AutoCharge_Task(void *pvParameters);   //�Զ���紦��
void Cammand_Task(void *pvParameters);    	//�������
void Test_Task(void *pvParameters);					//��������
void Head_Ctrl_Task(void *pvParameters);    //�ֶ�ͷ������
void LiftMoto_Task(void *pvParameters);			//��������
void Send_Mdrv_Task(void *pvParameters);		//�����ŷ�����������
void Mdrv_Task(void *pvParameters);					//�ŷ�����������
void LED_Task(void *pvParameters);     			//led���Ժ���
//void Ultrasonic_Task(void *pvParameters);			//��������
//void Move_Speed_task(void *pvParameters);			//�ٶȴ���
//void Environ_task(void *pvParameters);				//��������
//void Environ_Query_task(void *pvParameters);	//������������

#endif