#include "includes.h" 

#include "includes.h"

#define  UD_MAX_      180
#define  UD_MIN_      0

Head_Pos_Type Head_Status;   

uint8_t autoscan_flag ;


/************************************************/
//�������ܣ��趨�����ǶȺ�ˮƽ��ת�Ƕ�
//���������
//����ֵ��
//��ע��
/************************************************/
void Head_Angle_Control(int level, int pitch)
{
	 Head_UD_To_SomeWhere(pitch);    
	 Head_Level_To_SomeWhere(level);
}


/************************************************/
//�������ܣ���������
//���������
//����ֵ��
//��ע��
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
//�������ܣ�ˮƽ��ת����
//���������
//����ֵ��
//��ע��
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
//�������ܣ�������ָ����λ��
//���������
//����ֵ��
//��ע��
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
//�������ܣ�ˮƽ��ת��ָ����λ��
//���������
//����ֵ��
//��ע��
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


/************************************************/
//�������ܣ�ͷ����λ������
//���������
//����ֵ��
//��ע��
/************************************************/
void Head_Back()
{
	/* ���� */
	Head_UD_To_SomeWhere(Head_Status.PSC_UD_Default_Pos);
	/* ˮƽ */
	Head_Level_To_SomeWhere(Head_Status.PSC_Level_Default_Pos);
}


/************************************************/
//�������ܣ��Ƿ�ת��λ��ת��λ��ֹͣ
//���������
//����ֵ��
//��ע��
/************************************************/
void Check_Assign_Ok()
{
	/* ˮƽĿ��ֵ */
	if(Head_Status.PSC_Level_Goal_Pos > 0)
	{
		if(fabs(Head_Status.PSC_Level_Pos - Head_Status.PSC_Level_Goal_Pos) < 0.5)
		{
			/* ����ֹͣ */
			Head_Status.PSC_Dir &= ~((1 << (5-1)) | (1<<(7-1)));
			Head_Status.PSC_Level_Goal_Pos = 0;
			
		}
	}
	/* ��ֱĿ��ֵ */
	if(Head_Status.PSC_UD_Goal_Pos > 0)
	{
		if(fabs(Head_Status.PSC_UD_Pos - Head_Status.PSC_UD_Goal_Pos) < 0.5)
		{
			/* ����ֹͣ */
			Head_Status.PSC_Dir &= ~((1 << (6-1)) | (1<<(8-1)));
			Head_Status.PSC_UD_Goal_Pos = 0;			
		}
	}
}


/************************************************/
//�������ܣ�ͷ��ת������
//���������
//����ֵ��
//��ע��
/************************************************/
void Head_Control_Done()
{
	if(Head_Status.PSC_Dir == 0)
	{
	}
	else if((Head_Status.PSC_Dir & (1<<(5-1))) != 0)
	{
		/* 5  �� */
		Moto_Level(PSC_MOVE_LEFT);  
	}
	else if((Head_Status.PSC_Dir & (1<<(7-1))) != 0)
	{
		/* 7  ��   Ϊ 0 */
		Moto_Level(PSC_MOVE_RIGHT);
	}

	if((Head_Status.PSC_Dir & (1<<(6-1))) != 0)
	{
		/* ����� �� */
		Moto_Pit(PSC_MOVE_UP);
	}
	else if((Head_Status.PSC_Dir & (1<<(8-1))) != 0)
	{
		/* ����� �� */
		Moto_Pit(PSC_MOVE_DOWN);
	}
	else if(Head_Status.PSC_Dir == 9)
	{
		/* ���� */
		Head_Back();
	}

	if((Head_Status.PSC_Dir & 0xF0) == 0)
	{
		Head_Status.PSC_Dir = 0;
	}

	if(Head_Status.PSC_Dir != 0)
	{
		Check_Assign_Ok();
	}
}





