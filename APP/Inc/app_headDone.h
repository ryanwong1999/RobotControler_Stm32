#ifndef __APP_HEAD_DONE_H
#define __APP_HEAD_DONE_H

#include "includes.h"	

//��ֱĬ��λ��
#define H_Pos_Default     	75.0
	 
#define PSC_UD_OFFSET	    	45
#define PSC_LEVEL_OFFSET  	45	 
	 
#define PSC_UD_DEFAULT     	90
#define PSC_UD_MAX         	135
#define PSC_UD_MIN         	45

#define PSC_LEVEL_DEFAULT   90
#define PSC_LEVEL_MAX       180
#define PSC_LEVEL_MIN       0
	                                                                                                                                                                                              
#define PSC_MOVE_LEFT				2
#define PSC_MOVE_RIGHT			3

#define PSC_MOVE_UP					2
#define PSC_MOVE_DOWN				3

typedef struct{
	uint8_t PSC_Dir;							//����ķ���
	uint8_t PSC_Limit_Flag;				//��λ���ص�״̬
	uint16_t PSC_MAX_Step;				//���������� ����
	uint16_t PSC_Now_Step;				//���ҵĵ�ǰ ����
	uint16_t PSC_Level_Goal_Step;	//����� ˮƽ����� Ŀ�� ��
	uint8_t PSC_Pitch_OK_Flag;
	int8_t Level_Offset;
	int8_t Pitch_Offset;
	float PSC_UD_Pos;							//��������ĽǶ�
	float PSC_UD_Goal_Pos;				//����� ���������  Ŀ�� λ��  ��Ӧ����
	float PSC_UD_Default_Pos;			//����� ����������м�� pos ��
	float PSC_UD_MAX_Pos;					//����� ����  pwmֵ  ���µ�
	float PSC_UD_MIN_Pos;
	float PSC_Level_Pos;					//��������ĽǶ�
	float PSC_Level_Goal_Pos;			//����� ���������  Ŀ�� λ��  ��Ӧ����
	float PSC_Level_Default_Pos;	//����� ����������м�� pos ��
	float PSC_Level_MAX_Pos;			//����� ����  pwmֵ  ���µ�
	float PSC_Level_MIN_Pos;
}Head_Pos_Type;

extern Head_Pos_Type Head_Status;

void Head_Control_Done(void);
void Head_UD_To_SomeWhere(float pos);
void Head_Level_To_SomeWhere(float pos);
void Head_Angle_Control(int level, int pitch);
void Head_Back(void);

#endif 