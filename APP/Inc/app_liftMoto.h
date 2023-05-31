#ifndef __APP_LIFTMOTO_H
#define __APP_LIFTMOTO_H

#include "includes.h"	

#define MAX_HEIGHT    144	 		//最高高度
#define MAX_LIFT_TIM  10200   //升到最高高度所需时间

typedef enum
{
	LIFT_STOP = 0x00,
	LIFT_UP = 0x01,
	LIFT_DOWN = 0x02,
}Lift_Cmd;

typedef struct
{
	uint8_t Status;
	uint8_t Limit_Switch_Flag;	//限位标志
	uint8_t OverCurrent_Flag;
	bool  Lift_OK_flag;
	uint16_t Height;						//高度
	uint16_t Set_Height;
	uint16_t Lift_Tim;  				//升降时间
	uint8_t Init_OK_Flag;
	Lift_Cmd Cmd;
}LiftMoto_Type;

extern LiftMoto_Type Lift_Moto;

void Get_Lift_time(uint8_t _cmd);
void LiftMoto_Set(uint8_t _cmd);
uint8_t Get_LimitSwitch(void);
uint16_t Get_LiftMoto_Height(void);
uint8_t Get_OverCurFlag(uint8_t _cmd, uint16_t _cur);
void LiftMoto_GoTO_SetHeiht(uint16_t *_set_height);
void LiftMoto_Process(void);
void LiftMoto_Init(void);

#endif 