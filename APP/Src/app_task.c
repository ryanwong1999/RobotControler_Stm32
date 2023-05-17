#include "includes.h" 

//�������ȼ�
#define START_TASK_PRIO		   		3 
#define PMU_TASK_PRIO	     	 		3   
#define CAMMAND_TASK_PRIO    		4
#define ERR_TASK_PRIO        		5
#define POWEROFF_TASK_PRIO   		6    
#define CHG_TASK_PRIO        		7
#define TEST_TASK_PRIO    			8
#define HEAD_CTRL_TASK_PRIO  		10
#define AUTOCHARGE_TASK_PRIO		11
#define ULTRA_TASK_PRIO      		12
#define SEND_MDRV_TASK_PRIO   	13
#define MDRV_TASK_PRIO    			14
#define LIFTMOTO_TASK_PRIO			17
#define LED_TASK_PRIO		     		30  
//#define MOVE_SPEED_TASK_PRIO 		4
//#define ENVIRON_TASK_PRIO				8
//#define ENVIRON_QUERY_TASK_PRIO	19


//�����ջ��С	
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
#define ULTRA_STK_SIZE 	     		128 
#define AUTOCHARGE_STK_SIZE			128
#define LIFTMOTO_STK_SIZE    		128
#define LED_STK_SIZE 		     		128 
//#define MOVE_SPEED_STK_SIZE	 		128
//#define ENVIRON_STK_SIZE				128
//#define ENVIRON_QUERY_STK_SIZE	128




//��������
void Err_Handle_task(void *p_arg);    //�쳣��������
void Poweroff_task(void *p_arg);    	//�ػ���������
void Chg_task(void *p_arg);    				//�����������
void Cammand_task(void *p_arg);    		//�������
void Test_task(void *p_arg);
void Head_Ctrl_task(void *p_arg);     //�ֶ�ͷ������
void Pmu_task(void *p_arg);     			//��Դ������
void Ultrasonic_task(void *p_arg);    //��������
void LiftMoto_task(void *p_arg);			//��������
void AutoCharge_task(void *p_arg);    //��������
void Send_Mdrv_task(void *p_arg);			//�����ŷ�����������
void Mdrv_task(void *p_arg);					//�ŷ�����������
void LED_task(void *p_arg);     			//led���Ժ���
//void Move_Speed_task(void *p_arg);   	//�ٶȴ���
//void Environ_task(void *p_arg);
//void Environ_Query_task(void *p_arg);