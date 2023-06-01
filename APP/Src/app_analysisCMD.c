#include "includes.h" 

Sys_Type   			Robot_Sys;
Odom_Data_type  Moto_Odom;    // 里程数据

void Send_Head_Pose(uint8_t index, uint8_t addr, HeadPose_Type mHead_Pose, bool stop_key);
void Send_PowerDataUpdata(uint8_t index, uint8_t addr, Power_Type mPower);
void Send_LiftMoto_Mess(uint8_t index, uint8_t addr, LiftMoto_Type *_liftmoto);

uint8_t gUpdateCnt = 0;
uint8_t gPscCnt = 0;

/************************************************/
//函数功能：工控机命令解析
//输入参数：
//返回值：
//备注：
/************************************************/
void AnalysisCMD(void)
{
	int level;
	int pitch;
	uint8_t i=0;
	int16_t lear_tmp;
	int16_t angular_tmp;
	int16_t real_lear;
	int16_t real_angle;
	float pulse_width_r;
	float pulse_width_l;
	static float left_speed_tmp = 0;
	static float right_speed_tmp = 0;
	static uint16_t left_inc_pwm = 0;
	static uint16_t right_inc_pwm = 0;
	static uint16_t peroid_tmp = 0;
	static uint8_t period_set_sta = 0;
	float period_inc_tmp;
	uint16_t addr1;
	uint16_t addr2;
	uint8_t charge_tmp = 0;
	uint8_t cmd_tmp ;
	uint8_t Sdev_tmp ;  // 源地址
	uint8_t Pdev_tmp ;  // 目地址	
	float l_speed;
	float r_speed;
	float angle_div;
	int16_t rx_angle;
	int16_t rx_lear;
	int16_t chg_dis;
  int16_t chg_angle;
		
	if(UsartToPC.Usart_Rx_OK == true)
	{
		UsartToPC.Usart_Rx_OK = false;					// 清空等待下一次接收完成
		UsartToPC.Comm_TimeOut = 0;
		UsartToPC.Disconnect_flag = 0;	
		Sdev_tmp = UsartToPC.Rx_Buf[S_ID_REG];	// 取源地址
		Pdev_tmp = UsartToPC.Rx_Buf[P_ID_REG];  // 取目的地址,与本地地址匹配
			
		if(Pdev_tmp == DEV_ID)
		{
			cmd_tmp =  UsartToPC.Rx_Buf[CMD_REG];
			switch(cmd_tmp)
			{
				case CMD_QUERY_ODOM:   // 查询ODOM
					Robot_Sys.Odom_Timeout_cnt = 0;
					if(Robot_Sys.Mergency_Stop_flag == true)
					{
						Moto_Odom.Left_Value = 0;
						Moto_Odom.Right_Value = 0;
						Send_OdomUpdata(1, 0xff, Moto_Odom);
					}
					else Send_code_disk_query();
					break;

        case CMD_SET_SPEED:   // 设置速度	
					Robot_Sys.Speed_Timeout_cnt = 0;
				  memcpy(&lear_tmp, &UsartToPC.Rx_Buf[SPEED1_REG1], sizeof(int16_t));
					memcpy(&angular_tmp, &UsartToPC.Rx_Buf[SPEED2_REG1], sizeof(int16_t));
					rx_lear = (short int)t_ntohs(lear_tmp);
					rx_angle = (short int)t_ntohs(angular_tmp);
				 
					if(rx_lear > 1500) rx_lear = 1500;
				  else if(rx_lear < -1500) rx_lear = -1500;
					
					if(rx_lear != 0 || rx_angle != 0)
					{
						Robot_Sys.AutoCharge_task_flag = false;
						AutoCharge.AutoChg_Cmd = false;
						Robot_Sys.Remote_flag = true;
						Robot_Sys.Set_PWM_Task_Flag = false;
						Robot_Sys.Last_Task = REMOTE_TASK;
						AutoCharge.chg_flag = 0 ;
						AutoCharge.chg_fail = 0;
					}
					
					if(Robot_Sys.Mergency_Stop_flag == true || Moto.over_cur_flag == true)
					{
						if(Moto.en_sta == 1)
						{
							Moto.set_lear = 0;
							Moto.set_angle = 0;
							Send_speed_set(Moto.set_lear, Moto.set_angle);
						}
						else Send_mdrv_en_set(1, 1);
					}
					else if(Robot_Sys.Mergency_Stop_flag != true)
					{
						if(Robot_Sys.AutoCharge_task_flag == false)
						{
							if(((Robot_Sys.Ultra_sta & 0x03) != 0 || ((Robot_Sys.Crash_Flag & 0x01) != 0)) && rx_lear > 0)
							{
								Moto.set_lear = 0;
								Moto.set_angle = 0;
							}
							else if(((Robot_Sys.Ultra_sta & 0x30) != 0 || ((Robot_Sys.Crash_Flag & 0x02) != 0)) && rx_lear < 0)
							{
								Moto.set_lear = 0;
								Moto.set_angle = 0;
							}
							else
							{
								Moto.set_lear = rx_lear;
								Moto.set_angle = rx_angle;
							}
						}
						else
						{
							Moto.set_lear = AutoCharge.set_lear;
							Moto.set_angle = AutoCharge.set_angle;
						}
						
						#ifdef MOTO_LOCK	 	
						//电机不动时可以用手推动，适用于室外
						if(Moto.en_sta == 0) Send_mdrv_en_set(1, 1);
						else Send_speed_set(Moto.set_lear, Moto.set_angle);
						#else
						//电机不动时可以用手推动，适用于室内
						if(Moto.set_lear == 0 && Moto.set_angle == 0 && (Pms.Bat_Sta & 0x01) == 0)
						{
							if(Moto.stop_sta == 1 && Moto.en_sta == 1) 
								Send_mdrv_en_set(0, 0);
							else 
								Send_speed_set(Moto.set_lear, Moto.set_angle);
						}else{
							if(Moto.en_sta == 0) Send_mdrv_en_set(1, 1);
							else Send_speed_set(Moto.set_lear, Moto.set_angle);
						}
						#endif
					}
					break;

				case CMD_QUERY_POWER:        // 查询电量及充电状态
					Robot_Sys.mSysPower.charger = Pms.Bat_Sta | AutoCharge.chg_fail ;
				  Robot_Sys.mSysPower.power = Pms.Capacity;
					Send_PowerDataUpdata(gPscCnt++, Sdev_tmp, Robot_Sys.mSysPower);
					break;
				
				case CMD_Ultrasonic:    //障碍状态
					Send_Obstacle_Sta(gUpdateCnt, Sdev_tmp, Robot_Sys.Ultra_sta, Robot_Sys.Crash_Flag);
					Robot_Sys.StopDisable_flag = UsartToPC.Rx_Buf[9];		//解除过流停止
					break;
				
				case CMD_AUTOCHARGE:  // 自动充电
					if((Pms.Bat_Sta & 0x01) == 0)
					{				
						charge_tmp = UsartToPC.Rx_Buf[8];
						if(	Robot_Sys.Last_Task != CHG_TASK)
						{
							Robot_Sys.Last_Task = CHG_TASK;
							Robot_Sys.mBeepStatus.BeepMode = 0x01;
							AutoCharge.AutoChg_Cmd = true;
							Robot_Sys.AutoCharge_task_flag = false;
							Robot_Sys.Remote_flag = true;
						}
					}
					#ifndef ROBOT_YZ01	
					Send_Autocharge_reply(gUpdateCnt, Sdev_tmp, charge_tmp);
					#endif
					break;
								
				case CMD_HEAD_POSE:     // 查询头部角度
					Robot_Sys.mHeadPose.Level = Head_Status.PSC_Level_Pos * 10;
					Robot_Sys.mHeadPose.Pitch = Head_Status.PSC_UD_Pos * 10;
				  Send_Head_Pose(gPscCnt ++, Sdev_tmp, Robot_Sys.mHeadPose, 0);
					break;
				
				case CMD_HEAD_ANGLE:    // 设置头部角度
					level = ((UsartToPC.Rx_Buf[8] & 0xFF) << 8) + (UsartToPC.Rx_Buf[9] & 0xFF);
					pitch = ((UsartToPC.Rx_Buf[10] & 0xFF) << 8) + (UsartToPC.Rx_Buf[11] & 0xFF);
				  Head_Angle_Control(level, pitch);
				
				  #ifndef ROBOT_YZ01	
					Send_HeadAngle_reply(gPscCnt ++, Sdev_tmp, level, pitch);
					#endif
					break;
				
				case CMD_HEAD:  // 控制头部电机
					//55 AA 11 13 FF 01 06 00 05 00 00 00 00 00 00 00 3A 0D 0A   //左
					//55 AA 11 13 FF 01 06 00 07 00 00 00 00 00 00 00 3A 0D 0A   //右
					//55 AA 11 13 FF 01 06 00 06 00 00 00 00 00 00 00 3A 0D 0A   //仰
					//55 AA 11 13 FF 01 06 00 08 00 00 00 00 00 00 00 3A 0D 0A   //右
					//55 AA 11 13 FF 01 06 00 00 00 00 00 00 00 00 00 3A 0D 0A   //俯
					switch(UsartToPC.Rx_Buf[8])
					{
						case 0x05:    // 05 左
							Head_Status.PSC_Dir |= 1<<(5-1);
						  Head_Status.PSC_Dir &= ~(1<<(7-1));
							break; 
						case 0x06:    // 06 仰
							Head_Status.PSC_Dir |= 1<<(6-1);
					    Head_Status.PSC_Dir &= ~(1<<(8-1));
							break;
						case 0x07:    // 07 右
							Head_Status.PSC_Dir |= 1<<(7-1);
						  Head_Status.PSC_Dir &= ~(1<<(5-1));
						  break;
						case 0x08:    // 08 俯
							Head_Status.PSC_Dir |= 1<<(8-1);
						  Head_Status.PSC_Dir &= ~(1<<(6-1));
						  break;
						case 0x09:
							Head_Back();
							break;
						default :
							Head_Status.PSC_Dir = 0;
						  break;
					}	
					#ifndef ROBOT_YZ01	
				  Send_HeadCtrl_reply(gUpdateCnt++, Sdev_tmp, UsartToPC.Rx_Buf[8]);		
          #endif					
					break;
					
				case CMD_QUERY_LIFT:			//查询升降高度
					Robot_Sys.Out_en_flag = UsartToPC.Rx_Buf[8];
					Robot_Sys.Beep_en_flag = UsartToPC.Rx_Buf[9];
					Send_LiftMoto_Mess(gUpdateCnt++, Sdev_tmp, &Lift_Moto);
					break;
				
				case CMD_QUERY_TEMP:			//查询温湿度,CO2
//					Send_TempHumMess(gUpdateCnt++, Sdev_tmp, &Environ);
					break;
				
				case CMD_QUERY_ENVIRON:		//查询PM值
//					Send_EnvironMess(gUpdateCnt++, Sdev_tmp, &Environ);
					break;	
				
        case CMD_QUERY_OBS_EN:		//障碍传感器使能
					Send_Obs_EN_Mess(gUpdateCnt++, Sdev_tmp);
					break;
				
				case CMD_SET_LIFT:				//设置升降高度	
					Lift_Moto.Set_Height = (uint16_t)UsartToPC.Rx_Buf[8]<<8 | UsartToPC.Rx_Buf[9];
					Lift_Moto.Lift_OK_flag = false;
					#ifndef ROBOT_YZ01	
					Send_SetLift_reply(gUpdateCnt++, Sdev_tmp, Lift_Moto.Set_Height);
					#endif
					break;
	
				case CMD_SET_HEAD_OFFSET:	//设置头部偏差角度
					Head_Status.Pitch_Offset = Head_Status.Pitch_Offset +  Head_Status.PSC_UD_Pos - 90 ;
					Head_Status.Level_Offset = Head_Status.Level_Offset + 90 - Head_Status.PSC_Level_Pos ;
				  Head_Status.PSC_UD_Pos = PSC_UD_DEFAULT;
				  Head_Status.PSC_Level_Pos = PSC_LEVEL_DEFAULT;
					SetHeadLevelPosition(PSC_LEVEL_DEFAULT, Head_Status.Level_Offset);
					SetHeadPitchPosition(PSC_UD_DEFAULT, Head_Status.Pitch_Offset);
					Send_angle_offset_reply(gUpdateCnt++, Sdev_tmp, Head_Status.Level_Offset, Head_Status.Pitch_Offset);
					break;
				
				case CMD_SET_SENSOR_EN:		//设置传感器使能
					Robot_Sys.Ultra_Disable_Flag = UsartToPC.Rx_Buf[8];
					Robot_Sys.IR_Front_Disable_Flag = UsartToPC.Rx_Buf[9];
					Robot_Sys.IR_Bottom_Disable_Flag = UsartToPC.Rx_Buf[10];
				  Send_ultra_en_reply(gUpdateCnt++, Sdev_tmp, Robot_Sys.Ultra_Disable_Flag);
					break;
				
				case CMD_LIFT_CON:				//升降控制命令
					Lift_Moto.Cmd = UsartToPC.Rx_Buf[8];
					Lift_Moto.Set_Height = 0xffff;
					#ifndef ROBOT_YZ01	
          Send_LiftCtrl_reply(gUpdateCnt++, Sdev_tmp, Lift_Moto.Cmd);
					#endif
					break;
					
				case CMD_CON_MOVE:				//控制运动状态		
					break;  
				
				default:break;
			}
		}	
	}
}