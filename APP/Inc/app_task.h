#ifndef __APP_TASK_H__
#define __APP_TASK_H__


/**********************************设置任务优先级***********************************/
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


/**********************************设置任务堆栈大小*********************************/
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

/**************************************任务句柄*************************************/
TaskHandle_t Start_Task_Handler;
//TaskHandle_t Pmu_Task_Handler;
//TaskHandle_t Cammand_Task_Handler;
//TaskHandle_t Err_Task_Handler;
//TaskHandle_t Poweroff_Task_Handler;
//TaskHandle_t Chg_Task_Handler;
//TaskHandle_t Test_Task_Handler;
//TaskHandle_t Head_Ctrl_Task_Handler;
//TaskHandle_t AutoCharge_Task_Handler;
//TaskHandle_t Ultra_Task_Handler;
//TaskHandle_t Send_Mdrv_Task_Handler;
//TaskHandle_t Mdrv_Task_Handler;
//TaskHandle_t LiftMoto_Task_Handler;
//TaskHandle_t Led_Task_Handler;

/*************************************任务堆栈**************************************/



/***********************************任务函数声明*************************************/
void Start_Task(void *p_arg);	
void Err_Handle_Task(void *p_arg);    //异常任务处理函数
void Poweroff_Task(void *p_arg);    	//关机任务处理函数
void Chg_Task(void *p_arg);    				//充电任务处理函数
void Cammand_Task(void *p_arg);    		//命令处理函数
void Test_Task(void *p_arg);
void Head_Ctrl_Task(void *p_arg);     //手动头部控制
void Pmu_Task(void *p_arg);     			//电源管理函数
void Ultrasonic_Task(void *p_arg);    //超声处理
void LiftMoto_Task(void *p_arg);			//升降处理
void AutoCharge_Task(void *p_arg);    //超声处理
void Send_Mdrv_Task(void *p_arg);			//发送伺服驱动器命令
void Mdrv_Task(void *p_arg);					//伺服驱动器处理
void LED_Task(void *p_arg);     			//led测试函数
//void Move_Speed_task(void *p_arg);   	//速度处理
//void Environ_task(void *p_arg);
//void Environ_Query_task(void *p_arg);

#endif