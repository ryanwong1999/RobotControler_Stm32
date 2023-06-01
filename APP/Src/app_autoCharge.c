#include "includes.h" 

Charge_typedef AutoCharge;


/************************************************/
//�������ܣ������ʱ��־
//���������
//����ֵ��
//��ע��
/************************************************/
void Charge_Tim1ms(void)
{
  AutoCharge.OverTime++;
	AutoCharge.Loop_Tim++;
	if(Robot_Sys.Last_Task == CHG_TASK && (Pms.Bat_Sta & 0x01) == 0)
		AutoCharge.Time_out++;
	else
		AutoCharge.Time_out = 0;
}


/************************************************/
//�������ܣ��Զ���������ʼ��
//���������
//����ֵ��
//��ע��
/************************************************/
void Charge_Init(void)
{
	AutoCharge.Position = POSITION_NULL;
	AutoCharge.Last_Position = POSITION_NULL;
	AutoCharge.Loop_Tim = 0;	
	AutoCharge.OverTime = 0;
	AutoCharge.Time_out = 0;
	AutoCharge.NotFind_Flag = false;
	AutoCharge.Move_Sta = CHG_MOVE_STOP;
	
	memset(AutoCharge.CH1_IrDa_Dat, 0x00, 4);
	memset(AutoCharge.CH2_IrDa_Dat, 0x00, 4);
	memset(AutoCharge.CH3_IrDa_Dat, 0x00, 4);
	AutoCharge.Move_Sta = CHG_MOVE_STOP;
}


/************************************************/
//�������ܣ���ȡ�Զ�������
//���������
//����ֵ��
//��ע��
/************************************************/
void Get_Charger_Code(void)
{
	AutoCharge.CH_IrDate[0] = AutoCharge.CH1_IrDa_Dat[0]|AutoCharge.CH1_IrDa_Dat[1]|AutoCharge.CH1_IrDa_Dat[2]|AutoCharge.CH1_IrDa_Dat[3];   	//��߽���ͷ�յ����������Ϊ0
	AutoCharge.CH_IrDate[2] = AutoCharge.CH3_IrDa_Dat[0]|AutoCharge.CH3_IrDa_Dat[1]|AutoCharge.CH3_IrDa_Dat[2]|AutoCharge.CH3_IrDa_Dat[3];  	//�ұ߽���ͷ�յ�����
	
	AutoCharge.CH_IrDate[3] = AutoCharge.CH1_IrDa_Dat[0]|AutoCharge.CH3_IrDa_Dat[0];    //�յ��������ߵ�����Ϊ0
	AutoCharge.CH_IrDate[4] = AutoCharge.CH1_IrDa_Dat[1]|AutoCharge.CH3_IrDa_Dat[1];   	//��������ϵ���
	AutoCharge.CH_IrDate[5] = AutoCharge.CH1_IrDa_Dat[2]|AutoCharge.CH3_IrDa_Dat[2];   	//������ұߵ���
	AutoCharge.CH_IrDate[6] = AutoCharge.CH1_IrDa_Dat[3]|AutoCharge.CH3_IrDa_Dat[3];   	//��������ϵ���
}


/************************************************/
//�������ܣ��Զ���紦����
//���������
//����ֵ��
//��ע��
/************************************************/
void AutoCharge_Processing(void)
{
  static u8 Position_Cnt=0;
	
	Get_Charger_Code();
	//�״ν�������� 0010 0000
	if((AutoCharge.Chg_Sta & 0x20) == 0)
	{
		AutoCharge.Chg_Sta |= 0x20;        					
		AutoCharge.Chg_Sta &= 0x20;
		Charge_Init();
	}
	else
	{
		if(AutoCharge.Position == POSITION_NULL)
		{
			AutoCharge.Chg_Sta &= 0xfe;	//1111 1110
			//��ȫû�յ��ź�
			if((AutoCharge.CH_IrDate[0] == 0) && (AutoCharge.CH_IrDate[2] == 0))
			{
				Position_Cnt = 0;
				AutoCharge.Position = POSITION_NULL;              
				AutoCharge.Last_Position = POSITION_NULL;          
				AutoCharge.Move_Sta = CHG_MOVE_ZEROLEFT;
				if(AutoCharge.OverTime > 60000)
				{ 				
					AutoCharge.Chg_Sta |= 0x40;	//0100 0000 				
					AutoCharge.NotFind_Flag = true;	//�Ҳ������׮
				}
			}
			//���յ��ź�
			else
			{
				AutoCharge.Chg_Sta |= 0x01;    
				Position_Cnt = 0;
				AutoCharge.Position = POSITION_IR;		        
				Chg_Position_Judge();		//��������Գ��׮λ���ж�
				if((AutoCharge.CH_IrDate[4] != 0) && (AutoCharge.CH_IrDate[6] == 0))
				{			
					AutoCharge.Last_Position = POSITION_LEFT;
					AutoCharge.Move_Sta = CHG_MOVE_ZERORIGHT;
				}
				else if((AutoCharge.CH_IrDate[4] == 0) && (AutoCharge.CH_IrDate[6] != 0))
				{ 			
					AutoCharge.Last_Position = POSITION_RIGHT;
					AutoCharge.Move_Sta = CHG_MOVE_ZEROLEFT;
				}
				else if((AutoCharge.CH_IrDate[4] != 0) && (AutoCharge.CH_IrDate[6] != 0))
				{
					AutoCharge.Last_Position = POSITION_MID;		
					AutoCharge.Move_Sta = CHG_MOVE_FORWARD;
				}
				//���߶�Ϊ0
				else
				{		
					AutoCharge.Last_Position = AutoCharge.Last_Position;
					AutoCharge.Move_Sta = CHG_MOVE_ZEROLEFT;
				}		
			}
		}
		else
		{
			Chg_Position_Judge();                   			// λ���ж�   
			Charge_OverTime_Process();              			// ��ʱ����
			Charge_Crash_Pross();                   			// ���ʱ��ײ����
			Charge_IRCode_Process(AutoCharge.Move_Sta);		// �յ�������������˶�����         
			AutoCharge_move(AutoCharge.Move_Sta);         // ���ߴ���
			if(AutoCharge.Position == POSITION_IR)				// ���������־λ�����ϴγ��׮λ���ж�   
				Chg_Last_Position_Judge();
			//��ȫû�յ��ź�
			if((AutoCharge.CH_IrDate[0] == 0) && (AutoCharge.CH_IrDate[2] == 0))
			{	
				Position_Cnt++;
				if(Position_Cnt > 200)
				{
					Position_Cnt = 0; 
					AutoCharge.Position = POSITION_NULL;
					AutoCharge.Last_Position = POSITION_NULL;
				}
			}else Position_Cnt = 0;
		}
		memset(AutoCharge.CH1_IrDa_Dat, 0x00, 4);  
		memset(AutoCharge.CH3_IrDa_Dat, 0x00, 4);
	}
	AutoCharge_move(AutoCharge.Move_Sta);		// ���ߴ���    
}


/************************************************/
//�������ܣ��Զ�����ٶ�����
//���������
//����ֵ��
//��ע��
/************************************************/
void AutoCharge_move( uint8_t Move_sta1)
{	
	static uint16_t left_period_set;
	static uint16_t right_period_set;
	static int16_t max_pwm;
	static int16_t min_pwm;
	static uint8_t sta_last = 0;
	if(Robot_Sys.Mergency_Stop_flag == true)
	{
		Move_sta1 = CHG_MOVE_STOP;
		sta_last = 0;
	}
	switch (Move_sta1)
	{
		case CHG_MOVE_FORWARD:  
			if(sta_last != Move_sta1)
			{
				sta_last = Move_sta1;
				AutoCharge.set_lear = -60;
				AutoCharge.set_angle = 0;
			}	
			break;
				
		case CHG_MOVE_RIGHT:
			if(sta_last != Move_sta1)
			{
				sta_last = Move_sta1;
				#ifdef ROBOT_M100
				AutoCharge.set_lear = -30;     //60,230
				AutoCharge.set_angle = -110;
				#else						
				AutoCharge.set_lear = -40;     //60,230
				AutoCharge.set_angle = -246;
				#endif
			}
			break;
		 
		case CHG_MOVE_LEFT: 
			if(sta_last != Move_sta1)
			{
				sta_last = Move_sta1;
				#ifdef ROBOT_M100
				AutoCharge.set_lear = -30;
				AutoCharge.set_angle = 110;
				#else
				AutoCharge.set_lear = -40;
				AutoCharge.set_angle = 246;
				#endif
			}
		 break;
		
		case CHG_MOVE_ZERORIGHT:
			if(sta_last != Move_sta1)
			{
				sta_last = Move_sta1;
				#ifdef ROBOT_M100
				AutoCharge.set_lear = 0;
				AutoCharge.set_angle = -200;
				#else
				AutoCharge.set_lear = 0;
				AutoCharge.set_angle = -250;
				#endif
			}
			break;
	 
		case CHG_MOVE_ZEROLEFT:
			if(sta_last != Move_sta1)
			{
				sta_last = Move_sta1;
				#ifdef ROBOT_M100
				AutoCharge.set_lear = 0;
				AutoCharge.set_angle = 200;
				#else
				AutoCharge.set_lear = 0;
				AutoCharge.set_angle = 250;
				#endif
			}
				break;
	
		case CHG_MOVE_BACKWARD:
			break;
		
	 default:
		 sta_last = 0;
			break;
	}
}


/************************************************/
//�������ܣ��˶�������
//���������
//����ֵ��
//��ע��
/************************************************/
void Charge_IRCode_Process(uint8_t _move_sta)
{
	switch(_move_sta)
	{
		case CHG_MOVE_FORWARD :
			chg_move_forward_Process();
			break;		
		case CHG_MOVE_RIGHT :
			chg_move_right_process();
			break;		
		case CHG_MOVE_LEFT :
			chg_move_left_process();
			break;
		case CHG_MOVE_ZERORIGHT:
			chg_move_zeroright_process();		//ԭ����ת
			break;	
		case CHG_MOVE_ZEROLEFT :
			chg_move_zeroleft_process();		//ԭ����ת
			break;
		default :
			break;
	}
}


/************************************************/
//�������ܣ���������Գ��׮λ���ж�
//���������
//����ֵ��
//��ע��
/************************************************/
void Chg_Position_Judge(void)
{
	static u8 Left_Cnt = 0;
	static u8 Right_Cnt = 0;
	static u8 mid_cnt = 0;
	
	if((AutoCharge.CH1_IrDa_Dat[0] == TXDAT_LEFT) && (AutoCharge.CH3_IrDa_Dat[2] == TXDAT_RIGHT))		//����
	{
		if(AutoCharge.Position == POSITION_IR)
			AutoCharge.Position = POSITION_MID;
		else
		{
			mid_cnt++;
			if(mid_cnt >= 1)
			{
				mid_cnt = 0;
				Left_Cnt = 0;
				Right_Cnt = 0;
				AutoCharge.Position = POSITION_MID;
			}
		}
	}
	else if((AutoCharge.CH1_IrDa_Dat[0] == TXDAT_LEFT) && (AutoCharge.CH3_IrDa_Dat[0] == TXDAT_LEFT))		//����
	{
		if(AutoCharge.Position == POSITION_IR)
			AutoCharge.Position = POSITION_LEFT;
		else
		{
			Left_Cnt++;
			Right_Cnt = 0;
			mid_cnt = 0;
			if(Left_Cnt >= 1)
			{
				Left_Cnt = 0;
				Right_Cnt = 0;
				AutoCharge.Position = POSITION_LEFT;
			}
		}		
	}
	else if((AutoCharge.CH1_IrDa_Dat[2] == TXDAT_RIGHT) && (AutoCharge.CH3_IrDa_Dat[2] == TXDAT_RIGHT))		//�ҡ���
	{
		if(AutoCharge.Position == POSITION_IR)
			AutoCharge.Position = POSITION_RIGHT;
		else
		{
			Left_Cnt = 0;
			mid_cnt = 0;
			Right_Cnt++;
			if(Right_Cnt >= 1)
			{
				Right_Cnt = 0;
				AutoCharge.Position = POSITION_RIGHT; 		
			}		 
		}
	}
	else
	{
		if(AutoCharge.Position == POSITION_IR)
		{
			if((AutoCharge.CH_IrDate[3] != 0) && (AutoCharge.CH_IrDate[5] == 0))		//����
				AutoCharge.Position = POSITION_LEFT;
			else if((AutoCharge.CH_IrDate[3] == 0) && (AutoCharge.CH_IrDate[5] != 0))
				AutoCharge.Position = POSITION_RIGHT;
		}
		Left_Cnt = 0;
		Right_Cnt = 0;
		mid_cnt = 0;
	}
}


/************************************************/
//�������ܣ��ж��ϴλ�����λ��
//���������
//����ֵ��
//��ע��
/************************************************/
void Chg_Last_Position_Judge(void)
{
	if((AutoCharge.CH_IrDate[4] != 0) && (AutoCharge.CH_IrDate[6] == 0))	
		AutoCharge.Last_Position = POSITION_LEFT;
	else if((AutoCharge.CH_IrDate[4] == 0) && (AutoCharge.CH_IrDate[6] != 0))			
		AutoCharge.Last_Position = POSITION_RIGHT;
	else if((AutoCharge.CH_IrDate[4] != 0 ) && (AutoCharge.CH_IrDate[6] != 0))
		AutoCharge.Last_Position = POSITION_MID;		
	else
		AutoCharge.Last_Position = AutoCharge.Last_Position;
}


/************************************************/
//�������ܣ��Զ����ǰ��ʱ����
//���������
//����ֵ��
//��ע��
/************************************************/
void chg_move_forward_Process(void)
{
	static uint8_t cnt1 = 0;
	static uint8_t cnt2 = 0;
	
	if(AutoCharge.Position == POSITION_LEFT)
		AutoCharge.Move_Sta = CHG_MOVE_RIGHT;
	else if(AutoCharge.Position == POSITION_RIGHT)
    AutoCharge.Move_Sta = CHG_MOVE_LEFT;
	else if(AutoCharge.Position == POSITION_MID)
	{
		if(AutoCharge.CH1_IrDa_Dat[0] == TXDAT_LEFT && AutoCharge.CH3_IrDa_Dat[2] == TXDAT_RIGHT)
		{
			if(AutoCharge.CH3_IrDa_Dat[0] == TXDAT_LEFT && AutoCharge.CH1_IrDa_Dat[2] == 0)
			{
				cnt1++;
				cnt2 = 0;
				if(cnt1 >= 2)
				{
				 cnt1 = 0;
				 AutoCharge.Move_Sta = CHG_MOVE_RIGHT;	
				}
			}
			else if(AutoCharge.CH3_IrDa_Dat[0] == 0 && AutoCharge.CH1_IrDa_Dat[2] == TXDAT_RIGHT)
			{
				cnt1 = 0;
				cnt2++;
				if(cnt2 >= 2)
				{
					cnt2 = 0;
					AutoCharge.Move_Sta = CHG_MOVE_LEFT;
				}			
			}else AutoCharge.Move_Sta = CHG_MOVE_FORWARD;	
	  }
//--------------------------------------------------------------------
		else if(AutoCharge.CH1_IrDa_Dat[0] == 0 )
		{
			if(AutoCharge.CH3_IrDa_Dat[0] == TXDAT_LEFT)
				AutoCharge.Move_Sta = CHG_MOVE_RIGHT;	
	  }
		else if(AutoCharge.CH3_IrDa_Dat[2] == 0 )
		{
			if(AutoCharge.CH1_IrDa_Dat[2] == TXDAT_RIGHT)
				AutoCharge.Move_Sta = CHG_MOVE_LEFT;	
		}
		else
		{
			if(AutoCharge.CH1_IrDa_Dat[0] == TXDAT_LEFT && AutoCharge.CH3_IrDa_Dat[2] == TXDAT_RIGHT)
				AutoCharge.Move_Sta = CHG_MOVE_FORWARD;	
	    else
				AutoCharge.Move_Sta = CHG_MOVE_RIGHT;
		}
//--------------------------------------------------------------------
	}
	else
	{       
		if(AutoCharge.CH_IrDate[4] != 0 && AutoCharge.CH_IrDate[6] != 0)
		{
			delay_ms(500);
			AutoCharge.Move_Sta = CHG_MOVE_FORWARD;
		}
		else
		{
			delay_ms(2000);
			if(AutoCharge.CH_IrDate[4] != 0)
				AutoCharge.Move_Sta = CHG_MOVE_ZERORIGHT;
			else if(AutoCharge.CH_IrDate[6] != 0)
				AutoCharge.Move_Sta = CHG_MOVE_ZEROLEFT;
			else if(AutoCharge.Last_Position == POSITION_RIGHT)
				AutoCharge.Move_Sta = CHG_MOVE_ZERORIGHT;	
			else if(AutoCharge.Last_Position == POSITION_LEFT)
				AutoCharge.Move_Sta = CHG_MOVE_ZEROLEFT;
			else
				AutoCharge.Move_Sta = CHG_MOVE_ZERORIGHT;	
		}
	}
}


/************************************************/
//�������ܣ��Զ������תʱ������
//���������
//����ֵ��
//��ע��
/************************************************/
void chg_move_right_process(void)
{
	static uint8_t right_cnt = 0;
	static uint8_t cnt = 0;

	if(AutoCharge.Position == POSITION_LEFT)
	{
    right_cnt = 0;		
		if(AutoCharge.CH_IrDate[3] == 0 && AutoCharge.CH_IrDate[5] == 0)
		{
			if(AutoCharge.No_Sigh_Flag != 1)
			{
				cnt++;
				if(cnt >= 2)
				{
					cnt = 0;
					AutoCharge.Move_Sta = CHG_MOVE_LEFT;
				}
			}
		}
		else if(AutoCharge.CH1_IrDa_Dat[2] == TXDAT_RIGHT)
		{
			cnt = 0;
			AutoCharge.Move_Sta = CHG_MOVE_LEFT;
		}
	}
	else if(AutoCharge.Position == POSITION_RIGHT)
	{		
		cnt = 0;
		if(AutoCharge.CH1_IrDa_Dat[2] == TXDAT_RIGHT && AutoCharge.CH3_IrDa_Dat[2] == TXDAT_RIGHT)
		{
			 right_cnt = 0;
			AutoCharge.Move_Sta = CHG_MOVE_LEFT;
		}	
		else if(AutoCharge.CH1_IrDa_Dat[2] == TXDAT_RIGHT && AutoCharge.CH3_IrDa_Dat[2] == 0x0)
		{
			AutoCharge.Move_Sta = CHG_MOVE_LEFT;
		}
		else if(AutoCharge.CH_IrDate[0] != 0 && AutoCharge.CH_IrDate[2] == 0)
		{
			AutoCharge.Move_Sta = CHG_MOVE_LEFT;
		}
	}
	else if(AutoCharge.Position == POSITION_MID)
	{
		right_cnt = 0;		
		cnt = 0;
		if(AutoCharge.CH1_IrDa_Dat[2] == TXDAT_RIGHT && AutoCharge.CH3_IrDa_Dat[2] == 0x0)
			AutoCharge.Move_Sta = CHG_MOVE_LEFT;
		else if(AutoCharge.CH3_IrDa_Dat[0] == TXDAT_LEFT && AutoCharge.CH1_IrDa_Dat[0] == 0x0)
			AutoCharge.Move_Sta = CHG_MOVE_RIGHT;	
	  else if(AutoCharge.CH1_IrDa_Dat[0] == TXDAT_LEFT && AutoCharge.CH3_IrDa_Dat[2] == TXDAT_RIGHT)
			AutoCharge.Move_Sta = CHG_MOVE_FORWARD;	
	}
	else
	{
		cnt = 0;
		right_cnt = 0;
		if(AutoCharge.CH_IrDate[4] != 0 && AutoCharge.CH_IrDate[6] == 0)
		{
		  AutoCharge.Last_Position = POSITION_LEFT;
		  AutoCharge.Move_Sta = CHG_MOVE_ZERORIGHT;	
	  }
		else if((AutoCharge.CH_IrDate[4] == 0) && (AutoCharge.CH_IrDate[6] != 0))
		{
		  AutoCharge.Last_Position = POSITION_RIGHT;
			AutoCharge.Move_Sta = CHG_MOVE_ZEROLEFT;
	  }
		else if((AutoCharge.CH_IrDate[4]!=0) && (AutoCharge.CH_IrDate[6] != 0))
		{
			AutoCharge.Last_Position = POSITION_LEFT;	
			AutoCharge.Move_Sta = CHG_MOVE_FORWARD;
		}
	}
}


/************************************************/
//�������ܣ��Զ������תʱ������
//���������
//����ֵ��
//��ע��
/************************************************/
void chg_move_left_process(void)
{
	static uint8_t left_cnt = 0;
	static uint8_t cnt = 0;
	if(AutoCharge.Position == POSITION_LEFT)
	{
		cnt = 0;
		if(AutoCharge.CH1_IrDa_Dat[0] == TXDAT_LEFT && AutoCharge.CH3_IrDa_Dat[0] == TXDAT_LEFT)
		{
			left_cnt = 0;
			AutoCharge.Move_Sta = CHG_MOVE_RIGHT;	
		}
		else if(AutoCharge.CH1_IrDa_Dat[0] == 0x0 && AutoCharge.CH3_IrDa_Dat[0] == TXDAT_LEFT)
			AutoCharge.Move_Sta = CHG_MOVE_RIGHT;	
		else if(AutoCharge.CH_IrDate[0] == 0 && AutoCharge.CH_IrDate[2] != 0)
			AutoCharge.Move_Sta = CHG_MOVE_RIGHT;
	}
	else if(AutoCharge.Position == POSITION_RIGHT)
	{
		left_cnt = 0;
		if(AutoCharge.CH_IrDate[3] == 0 && AutoCharge.CH_IrDate[5] == 0)
		{
			if(AutoCharge.No_Sigh_Flag != 1)
			{
				cnt ++;
				if(cnt >= 2)
				{
					cnt = 0;
					AutoCharge.Move_Sta=CHG_MOVE_RIGHT;
				}
			}
		}
		else if(AutoCharge.CH3_IrDa_Dat[0] == TXDAT_LEFT)
			AutoCharge.Move_Sta = CHG_MOVE_RIGHT;	
	}
	else if(AutoCharge.Position == POSITION_MID)
	{
		left_cnt = 0;
		cnt = 0;
		if(AutoCharge.CH1_IrDa_Dat[0] == TXDAT_LEFT && AutoCharge.CH3_IrDa_Dat[2] == TXDAT_RIGHT)
			AutoCharge.Move_Sta = CHG_MOVE_FORWARD;	
	  else if(AutoCharge.CH1_IrDa_Dat[0] == 0x0 && AutoCharge.CH3_IrDa_Dat[0] == TXDAT_LEFT)
			AutoCharge.Move_Sta = CHG_MOVE_RIGHT;	
		else if(AutoCharge.CH3_IrDa_Dat[2]==0x0 && AutoCharge.CH1_IrDa_Dat[2]==TXDAT_RIGHT)
			AutoCharge.Move_Sta = CHG_MOVE_LEFT;	
	}
	else
	{
		left_cnt = 0;
		if(AutoCharge.CH_IrDate[4] != 0 && AutoCharge.CH_IrDate[6] == 0)
		{
		  AutoCharge.Last_Position = POSITION_LEFT;
			AutoCharge.Move_Sta = CHG_MOVE_ZERORIGHT;
	  }
		else if(AutoCharge.CH_IrDate[4] == 0 && AutoCharge.CH_IrDate[6] != 0)
		{
		  AutoCharge.Last_Position = POSITION_RIGHT;
			AutoCharge.Move_Sta = CHG_MOVE_ZEROLEFT;
	  }
		else if(AutoCharge.CH_IrDate[4] != 0 && AutoCharge.CH_IrDate[6] != 0)
		{
			AutoCharge.Last_Position = POSITION_LEFT;	
			AutoCharge.Move_Sta = CHG_MOVE_FORWARD;
		}
	}	
}


/************************************************/
//�������ܣ��Զ����ԭ����תʱ������
//���������
//����ֵ��
//��ע��
/************************************************/
void chg_move_zeroright_process(void)
{
  if(AutoCharge.Position == POSITION_LEFT)
		AutoCharge.Move_Sta = CHG_MOVE_RIGHT;
	else if(AutoCharge.Position == POSITION_MID)
		AutoCharge.Move_Sta = CHG_MOVE_FORWARD;	
	else if(AutoCharge.Position == POSITION_RIGHT)
		AutoCharge.Move_Sta = CHG_MOVE_LEFT;
	else
	{
		if(AutoCharge.Last_Position == POSITION_RIGHT)
		{
			if(AutoCharge.CH_IrDate[4] != 0 && AutoCharge.CH_IrDate[6] == 0)
				AutoCharge.Move_Sta = CHG_MOVE_ZERORIGHT;
	    else if(AutoCharge.CH_IrDate[4] == 0 && AutoCharge.CH_IrDate[6] != 0)
			{
		    AutoCharge.Last_Position = POSITION_RIGHT;
				AutoCharge.Move_Sta = CHG_MOVE_ZEROLEFT;
	    }
			else if(AutoCharge.CH_IrDate[5] != 0)
			{
				AutoCharge.Last_Position = POSITION_RIGHT;
				AutoCharge.Move_Sta = CHG_MOVE_ZEROLEFT;
			}
			else if(AutoCharge.CH_IrDate[4] !=0 && AutoCharge.CH_IrDate[6] != 0)
			{
				delay_ms(500);
				AutoCharge.Move_Sta = CHG_MOVE_FORWARD;
			}
		}
		else if(AutoCharge.Last_Position == POSITION_LEFT)
		{
			if(AutoCharge.CH_IrDate[4] != 0 && AutoCharge.CH_IrDate[6] == 0)
			{
		    AutoCharge.Last_Position = POSITION_LEFT;
				AutoCharge.Move_Sta = CHG_MOVE_ZERORIGHT;
	    }
			else if(AutoCharge.CH_IrDate[4] == 0 && AutoCharge.CH_IrDate[6] != 0)
				AutoCharge.Move_Sta = CHG_MOVE_ZEROLEFT;
	    else 
			{
				delay_ms(600);
				AutoCharge.Move_Sta = CHG_MOVE_FORWARD;
			}
		}
		else
		{
			if(AutoCharge.CH_IrDate[4] != 0 && AutoCharge.CH_IrDate[6] == 0)
		    AutoCharge.Last_Position = POSITION_LEFT;
	    else if(AutoCharge.CH_IrDate[4] == 0 && AutoCharge.CH_IrDate[6] != 0)
		    AutoCharge.Last_Position = POSITION_RIGHT;
		}
	}
} 


/************************************************/
//�������ܣ��Զ����ԭ����תʱ������
//���������
//����ֵ��
//��ע��
/************************************************/
void chg_move_zeroleft_process(void)
{
	if(AutoCharge.angle < -200)
	{
		AutoCharge.Position = POSITION_NULL;             
		AutoCharge.Last_Position = POSITION_NULL;        
		AutoCharge.Move_Sta = CHG_MOVE_ZERORIGHT;
	}
	else if(AutoCharge.Position == POSITION_LEFT)
		AutoCharge.Move_Sta = CHG_MOVE_RIGHT;
	else if(AutoCharge.Position == POSITION_MID)
		AutoCharge.Move_Sta = CHG_MOVE_FORWARD;	
	else if(AutoCharge.Position == POSITION_RIGHT)
		AutoCharge.Move_Sta = CHG_MOVE_LEFT;
	else
	{
		if(AutoCharge.Last_Position == POSITION_RIGHT)
		{
			if(AutoCharge.CH_IrDate[4] != 0 && AutoCharge.CH_IrDate[6] == 0)
				AutoCharge.Move_Sta = CHG_MOVE_ZERORIGHT;
	    else if(AutoCharge.CH_IrDate[4] == 0 && AutoCharge.CH_IrDate[6] != 0)
			{
				AutoCharge.Last_Position = POSITION_RIGHT;
				AutoCharge.Move_Sta = CHG_MOVE_ZEROLEFT;
			}
			else
			{
				delay_ms(500);
				AutoCharge.Move_Sta = CHG_MOVE_FORWARD;
			}
		}
		else if(AutoCharge.Last_Position == POSITION_LEFT)
		{
			if(AutoCharge.CH_IrDate[4] != 0 && AutoCharge.CH_IrDate[6] == 0)
			{
		    AutoCharge.Last_Position = POSITION_LEFT;
				AutoCharge.Move_Sta = CHG_MOVE_ZERORIGHT;
	    }
			else if(AutoCharge.CH_IrDate[4] == 0 && AutoCharge.CH_IrDate[6] != 0)
				AutoCharge.Move_Sta = CHG_MOVE_ZEROLEFT;
	    else if(AutoCharge.CH_IrDate[3] != 0)
			{	  
				AutoCharge.Last_Position = POSITION_LEFT;
				AutoCharge.Move_Sta = CHG_MOVE_ZERORIGHT;
			}
			else if(AutoCharge.CH_IrDate[4] != 0 && AutoCharge.CH_IrDate[6] != 0)
			{
				delay_ms(500);
				AutoCharge.Move_Sta = CHG_MOVE_FORWARD;
			}
		}
		else
		{
			if(AutoCharge.CH_IrDate[4] != 0 && AutoCharge.CH_IrDate[6] == 0)
		    AutoCharge.Last_Position = POSITION_LEFT;
			else if(AutoCharge.CH_IrDate[4] == 0 && AutoCharge.CH_IrDate[6] != 0)
		    AutoCharge.Last_Position = POSITION_RIGHT;	
	    else if(AutoCharge.CH_IrDate[4] != 0 && AutoCharge.CH_IrDate[6] != 0)
			{
				delay_ms(500);
				AutoCharge.Move_Sta = CHG_MOVE_FORWARD;
			}
		}
	}
	if(AutoCharge.Move_Sta != CHG_MOVE_ZEROLEFT )
		AutoCharge.OverTime = 0;
}


/************************************************/
//�������ܣ��Զ���糬ʱ����
//���������
//����ֵ��
//��ע��
/************************************************/
void Charge_OverTime_Process(void)
{
	if(AutoCharge.OverTime > 20000)
		AutoCharge.Last_Position = POSITION_NULL;
}


/************************************************/
//�������ܣ��Զ������ײ����
//���������
//����ֵ��
//��ע��
/************************************************/
void Charge_Crash_Pross(void)
{
	if((Robot_Sys.Crash_Flag & 0x02) != 0)
		AutoCharge.Chg_Sta = 0;
}
