#include "includes.h" 

uint16_t Lift_Cnt = 0;

LiftMoto_Type Lift_Moto;


/************************************************/
//�������ܣ���ȡ����ʱ��
//���������
//����ֵ��
//��ע��
/************************************************/
void Get_Lift_time(uint8_t _cmd)
{
	switch(_cmd)
	{
		case LIFT_UP:       	//moto up
		  if((Lift_Moto.Limit_Switch_Flag & 0x01) != 0 || (Lift_Moto.OverCurrent_Flag & 0x01) != 0)
				Lift_Moto.Lift_Tim = MAX_LIFT_TIM;
			else{
				if(Lift_Moto.Lift_Tim < MAX_LIFT_TIM)
					Lift_Moto.Lift_Tim ++;
			}
			break;
			
		case LIFT_DOWN:				//moto down
			if((Lift_Moto.Limit_Switch_Flag & 0x02) != 0 || (Lift_Moto.OverCurrent_Flag & 0x02) != 0){
					Lift_Moto.Lift_Tim = 0;
			}else{
				if( Lift_Moto.Lift_Tim > 0)
					Lift_Moto.Lift_Tim --;
			}
			break;
			
		case LIFT_STOP:
			if((Lift_Moto.Limit_Switch_Flag & 0x01) != 0)
				Lift_Moto.Lift_Tim = MAX_LIFT_TIM;
			else if((Lift_Moto.Limit_Switch_Flag & 0x02) != 0)
				Lift_Moto.Lift_Tim = 0;
			else
				Lift_Moto.Lift_Tim = Lift_Moto.Lift_Tim;
			break;
			
		default:
			break;
	}
}


/************************************************/
//�������ܣ���������
//���������
//����ֵ��
//��ע��
/************************************************/
void LiftMoto_Set(uint8_t _cmd)
{
	static uint8_t down_limit_sta = 0;
	switch(_cmd)
	{
		case LIFT_UP:       	//moto up
			Lift_Moto.Init_OK_Flag = 0;
			if((Lift_Moto.Limit_Switch_Flag & 0x01) != 0 || (Lift_Moto.OverCurrent_Flag & 0x01) != 0)
			{
				LIFTMOTO_DISABLE;
			}
			else if(Lift_Moto.Lift_Tim >= MAX_LIFT_TIM)
			{
				LIFTMOTO_DISABLE;
			}
			else
			{
				LIFTMOTO_UP;	
				LIFTMOTO_ENABLE;
			}
			break;
			
		case LIFT_DOWN:				//moto down
			if(Lift_Moto.Init_OK_Flag == 1)
			{
				LIFTMOTO_DISABLE;
			}
			else if((Lift_Moto.Limit_Switch_Flag & 0x02) != 0 || (Lift_Moto.OverCurrent_Flag & 0x02) != 0 )
			{
				LIFTMOTO_DISABLE;
				delay_ms(50);
				LIFTMOTO_UP;
				LIFTMOTO_ENABLE;
				delay_ms(300);
				LIFTMOTO_DISABLE;
				Lift_Moto.Init_OK_Flag = 1;
			}
			else
			{
				LIFTMOTO_DOWN;
				LIFTMOTO_ENABLE;
			}
			break;
			
		case LIFT_STOP:  
			LIFTMOTO_DISABLE;
		  Lift_Moto.Set_Height = 0xffff;
			break;
		
		default:
			break;
	}
}


/************************************************/
//�������ܣ���ȡ��λ����
//���������
//����ֵ��
//��ע��
/************************************************/
uint8_t Get_LimitSwitch(void)
{
	uint8_t limit_flag = 0;

	if(LIMIT_UP_READ == 0  &&  Lift_Moto.Height > 60)
		limit_flag |= 0x01;
	else
		limit_flag &= 0xfe;
	
	if(LIMIT_DOWN_READ == 0 &&  Lift_Moto.Height < 30)
		limit_flag |= 0x02;
	else
		limit_flag &=0xfd;
	
	return limit_flag;
}


/************************************************/
//�������ܣ���ȡ����״̬
//���������
//����ֵ��
//��ע��
/************************************************/
uint8_t Get_OverCurFlag(uint8_t _cmd, uint16_t _cur)
{
	static uint8_t overcur_cnt = 0;
	static uint8_t overcur_flag = 0;
	switch(_cmd)
	{
		case LIFT_UP:       	//moto up
			overcur_flag &= 0xfd;
			if(_cur > 1000)
			{
				overcur_cnt++;
				if(overcur_cnt >= 20)
				{
					overcur_cnt = 0;
					overcur_flag |= 0x01;
				}
			}
			else
				overcur_cnt = 0;
			break;
			
		case LIFT_DOWN:				//moto down
			overcur_flag &= 0xfe;
			if(_cur > 1000)
			{
				overcur_cnt++;
				if(overcur_cnt >= 10)
				{
					overcur_cnt = 0;
					overcur_flag |= 0x02;
				}
			}
			else
				overcur_cnt = 0;
			break;
			
		case LIFT_STOP:
			break;
		
		default:
			break;
	}	
	return overcur_flag;
}


/************************************************/
//�������ܣ����������߶�
//���������
//����ֵ��
//��ע��
/************************************************/
uint16_t Get_LiftMoto_Height(void)
{
	return (Lift_Moto.Lift_Tim * MAX_HEIGHT)/MAX_LIFT_TIM;
}


/************************************************/
//�������ܣ�������ָ���ĸ߶�
//���������
//����ֵ��
//��ע��
/************************************************/
void LiftMoto_GoTO_SetHeiht(uint16_t *_set_height)
{
	if(*_set_height == MAX_HEIGHT)
	{
		if(Lift_Moto.Limit_Switch_Flag == 0x01)		//����λ
			Lift_Moto.Lift_OK_flag = true;
		else
			Lift_Moto.Cmd = LIFT_UP;
	}
	else if(*_set_height == 0)
	{
		if(Lift_Moto.Limit_Switch_Flag == 0x02)		//����λ
			Lift_Moto.Lift_OK_flag = true;
		else
			Lift_Moto.Cmd = LIFT_DOWN;
	}
	else if(Lift_Moto.Height < *_set_height )
	{	
		if(Lift_Moto.Height >= *_set_height)
		{
			Lift_Moto.Cmd = LIFT_STOP;
			Lift_Moto.Lift_OK_flag = true;
		}
		else
		{
			Lift_Moto.Cmd = LIFT_UP;
			Lift_Moto.Lift_OK_flag = false;
		}
	}
	else
	{
		if(Lift_Moto.Height <= *_set_height)
		{
			Lift_Moto.Cmd = LIFT_STOP;
			Lift_Moto.Lift_OK_flag = true;
		}
		else
		{
			Lift_Moto.Cmd = LIFT_DOWN;
			Lift_Moto.Lift_OK_flag = false;
		}
	}	
}


/************************************************/
//�������ܣ�����������
//���������
//����ֵ��
//��ע��
/************************************************/
void LiftMoto_Process(void)
{
	Lift_Moto.Limit_Switch_Flag = Get_LimitSwitch();
	Lift_Moto.OverCurrent_Flag = Get_OverCurFlag(Lift_Moto.Cmd, ADC_Filter_Value[4]);
	Lift_Moto.Height = Get_LiftMoto_Height();
	if(Lift_Moto.Set_Height != 0xffff)
		LiftMoto_GoTO_SetHeiht(&Lift_Moto.Set_Height);
	else
		Lift_Moto.Lift_OK_flag = false;
	LiftMoto_Set(Lift_Moto.Cmd);
}


/************************************************/
//�������ܣ�������ʼ��������
//���������
//����ֵ��
//��ע��
/************************************************/
void LiftMoto_Init(void)
{
	static uint8_t cnt = 0;

	if( LIMIT_DOWN_READ == 0)
	{
		LIFTMOTO_DISABLE;
		delay_ms(50);
		LIFTMOTO_UP;
		LIFTMOTO_ENABLE;
		delay_ms(300);
		LIFTMOTO_DISABLE;	
		Lift_Moto.Cmd = LIFT_STOP;
		LiftMoto_Set(Lift_Moto.Cmd);
		Lift_Moto.Set_Height = 0xffff;
		Lift_Moto.Lift_Tim = 0;
		Lift_Moto.Height = 0;
		Lift_Moto.Init_OK_Flag = 1;
		printf("limit bit lift OK\r\n");
	}
	else if(ADC_Filter_Value[4] > 500)		//2.8A
	{
		cnt++;
		if(cnt > 10)
		{
			cnt = 0;
			LIFTMOTO_DISABLE;
			delay_ms(50);
			LIFTMOTO_UP;
			LIFTMOTO_ENABLE;            
			delay_ms(1000);
			LIFTMOTO_DISABLE;	
			Lift_Moto.Cmd = LIFT_STOP;
			LiftMoto_Set(Lift_Moto.Cmd);
			Lift_Moto.Set_Height = 0xffff;
			Lift_Moto.Lift_Tim = 0;
			Lift_Moto.Height = 0;	
			Lift_Moto.Init_OK_Flag = 1;
			printf("over cur lift OK\r\n");
		}
	}
	else
	{
		Lift_Moto.Lift_Tim = MAX_LIFT_TIM/2;
		Lift_Moto.Height = MAX_HEIGHT/2;
		Lift_Moto.Cmd = LIFT_DOWN;
		cnt = 0;
	}
	LiftMoto_Set(Lift_Moto.Cmd);
	delay_ms(10);
}