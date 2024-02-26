#ifndef __APP_SYSTEM_H
#define __APP_SYSTEM_H

#include "includes.h"

//ͷ����̨���ƽṹ��
typedef struct
{
	int16_t		Level;
	int16_t   Pitch;
}HeadPose_Type;

//���״̬�ṹ��
typedef struct
{
	uint32_t  charger ;      // ���
	uint32_t  power ;        // ����
}Power_Type ;

//������ģʽ�ṹ��
typedef struct
{
	uint8_t  BeepMode;
	uint16_t BeepTime;
}Beep_Type;

typedef struct
{
	uint8_t		Sys_Dev_ID;         //�豸ID ��
	uint16_t	Sys_Version;				//ϵͳ�汾
	
	uint8_t PC_Run_Flag;        //PC�� ���б�־
	uint8_t Ultra_sta;          //�ϰ���־
	uint8_t Obs_IR_Front;
	uint8_t Obs_IR_Bottom;
  uint8_t Ultra_Disable_Flag;
	uint8_t IR_Front_Disable_Flag;
	uint8_t IR_Bottom_Disable_Flag;
	uint8_t Crash_Flag;  				//��ײ��־
	uint8_t Voice_flag;
	uint8_t PowerOff_flag;
	uint8_t StopDisable_flag;		//���ֹͣ
	uint8_t Stop_flag;					//ֹͣ
	
	bool Set_PWM_Task_Flag;
  bool Move_Speed_Task_flag;	
	bool Psc_Task_flag;						//��̨�����־λ
	bool Lift_Task_flag;					//���������־λ
	bool AutoCharge_task_flag;		//�Զ���������־λ
	bool GetGuideSta_task_flag;
	bool AGV_Guide_task_flag;
	bool Remote_flag;
	bool Mergency_Stop_flag;			//��ͣ��־λ
	bool Comm_break_flag;					//ͨѶ�쳣��־λ

	uint16_t  Speed_Timeout_cnt;
	uint16_t  Odom_Timeout_cnt;
	uint8_t   Last_Task;
  uint8_t   Out_en_flag;
	uint8_t   Beep_en_flag;
	
	Power_Type    mSysPower;
	HeadPose_Type mHeadPose;					// ͷ����̬
	Beep_Type     mBeepStatus;

}Sys_Type;

extern	Sys_Type	Robot_Sys ;

void RCC_Configuration(void);
void NVIC_Configuration(void);
void System_Board_Init(void);
void System_StartTips(void);

#endif