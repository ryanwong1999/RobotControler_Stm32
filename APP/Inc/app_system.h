#ifndef __APP_SYSTEM_H
#define __APP_SYSTEM_H

#include "includes.h"

//头部云台姿势结构体
typedef struct
{
	int16_t		Level;
	int16_t   Pitch;
}HeadPose_Type;

//充电状态结构体
typedef struct
{
	uint32_t  charger ;      // 充电
	uint32_t  power ;        // 电量
}Power_Type ;

//蜂鸣器模式结构体
typedef struct
{
	uint8_t  BeepMode;
	uint16_t BeepTime;
}Beep_Type;

typedef struct
{
	uint8_t		Sys_Dev_ID;         //设备ID 号
	uint16_t	Sys_Version;				//系统版本
	
	uint8_t PC_Run_Flag;        //PC机 运行标志
	uint8_t Ultra_sta;          //障碍标志
	uint8_t Obs_IR_Front;
	uint8_t Obs_IR_Bottom;
  uint8_t Ultra_Disable_Flag;
	uint8_t IR_Front_Disable_Flag;
	uint8_t IR_Bottom_Disable_Flag;
	uint8_t Crash_Flag;  				//碰撞标志
	uint8_t Voice_flag;
	uint8_t PowerOff_flag;
	uint8_t StopDisable_flag;		//解除停止
	uint8_t Stop_flag;					//停止
	
	bool Set_PWM_Task_Flag;
  bool Move_Speed_Task_flag;	
	bool Psc_Task_flag;						//云台任务标志位
	bool Lift_Task_flag;					//升降任务标志位
	bool AutoCharge_task_flag;		//自动充电任务标志位
	bool GetGuideSta_task_flag;
	bool AGV_Guide_task_flag;
	bool Remote_flag;
	bool Mergency_Stop_flag;			//急停标志位
	bool Comm_break_flag;					//通讯异常标志位

	uint16_t  Speed_Timeout_cnt;
	uint16_t  Odom_Timeout_cnt;
	uint8_t   Last_Task;
  uint8_t   Out_en_flag;
	uint8_t   Beep_en_flag;
	
	Power_Type    mSysPower;
	HeadPose_Type mHeadPose;					// 头部姿态
	Beep_Type     mBeepStatus;

}Sys_Type;

extern	Sys_Type	Robot_Sys ;

void RCC_Configuration(void);
void NVIC_Configuration(void);
void System_Board_Init(void);
void System_StartTips(void);

#endif