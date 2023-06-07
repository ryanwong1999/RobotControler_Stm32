#include "includes.h" 

#include "includes.h"

#define  UD_MAX_      180
#define  UD_MIN_      0

Head_Pos_Type Head_Status;   

uint8_t autoscan_flag ;


/************************************************/
//函数功能：设定俯仰角度和水平旋转角度
//输入参数：
//返回值：
//备注：
/************************************************/
void Head_Angle_Control(int level, int pitch)
{
	 Head_UD_To_SomeWhere(pitch);    
	 Head_Level_To_SomeWhere(level);
}


/************************************************/
//函数功能：俯仰控制
//输入参数：
//返回值：
//备注：
/************************************************/
void Moto_Pit(uint8_t Pit_dir)
{
	switch(Pit_dir)
	{
		case PSC_MOVE_UP:
			if(Head_Status.PSC_UD_Pos < Head_Status.PSC_UD_MAX_Pos)
				Head_Status.PSC_UD_Pos += 0.5;
			SetHeadPitchPosition(Head_Status.PSC_UD_Pos, Head_Status.Pitch_Offset);
			break;
			
		case PSC_MOVE_DOWN:
			if(Head_Status.PSC_UD_Pos > Head_Status.PSC_UD_MIN_Pos)
				Head_Status.PSC_UD_Pos -= 0.5;
			SetHeadPitchPosition(Head_Status.PSC_UD_Pos, Head_Status.Pitch_Offset);
			break;
			
		default:
			break;
	}
}


/************************************************/
//函数功能：水平旋转控制
//输入参数：
//返回值：
//备注：
/************************************************/
void Moto_Level(uint8_t Level_dir)
{
	switch(Level_dir)
	{
		case PSC_MOVE_LEFT:
			if(Head_Status.PSC_Level_Pos >= Head_Status.PSC_Level_MIN_Pos + 0.5)
				Head_Status.PSC_Level_Pos -= 0.5;
			else
				Head_Status.PSC_Level_Pos = Head_Status.PSC_Level_MIN_Pos;
			SetHeadLevelPosition(Head_Status.PSC_Level_Pos,	Head_Status.Level_Offset);
			break;
			
		case PSC_MOVE_RIGHT:
			if(Head_Status.PSC_Level_Pos <= Head_Status.PSC_Level_MAX_Pos - 0.5) 
				Head_Status.PSC_Level_Pos += 0.5;
			else
				Head_Status.PSC_Level_Pos =  Head_Status.PSC_Level_MAX_Pos ;
			SetHeadLevelPosition(Head_Status.PSC_Level_Pos,	Head_Status.Level_Offset);
			break;
			
		default:
			break;
	}
}


/************************************************/
//函数功能：俯仰到指定的位置
//输入参数：
//返回值：
//备注：
/************************************************/
void  Head_UD_To_SomeWhere(float pos)
{
	Head_Status.PSC_UD_Goal_Pos = pos;
	if(Head_Status.PSC_UD_Pos < Head_Status.PSC_UD_Goal_Pos - 0.5)
	{
		// Up
		Head_Status.PSC_Dir  |= 1<<(6-1);
		Head_Status.PSC_Dir  &= ~(1<<(8-1));
	}
	else if(Head_Status.PSC_UD_Pos > Head_Status.PSC_UD_Goal_Pos + 0.5)
	{
		// Down
		Head_Status.PSC_Dir  |= 1<<(8-1);
		Head_Status.PSC_Dir  &= ~(1<<(6-1));
	}
	else
	{
		Head_Status.PSC_Dir  &= ~(1<<(6-1));
		Head_Status.PSC_Dir  &= ~(1<<(8-1));
	}
}


/************************************************/
//函数功能：水平旋转到指定的位置
//输入参数：
//返回值：
//备注：
/************************************************/
void Head_Level_To_SomeWhere(float pos)
{
	Head_Status.PSC_Level_Goal_Pos = pos;
	if(Head_Status.PSC_Level_Pos > Head_Status.PSC_Level_Goal_Pos + 0.5)
	{
		//left
		Head_Status.PSC_Dir |= 1<<(5-1);
		Head_Status.PSC_Dir &= ~(1<< (7-1));
	}
	else if(Head_Status.PSC_Level_Pos < Head_Status.PSC_Level_Goal_Pos - 0.5)
	{
		// right
		Head_Status.PSC_Dir |= 1<<(7-1);
		Head_Status.PSC_Dir &= ~(1<< (5-1));
	}
	else
	{
		Head_Status.PSC_Dir &= ~(1<<(5-1));
		Head_Status.PSC_Dir &= ~(1<<(7-1));
	}
}




