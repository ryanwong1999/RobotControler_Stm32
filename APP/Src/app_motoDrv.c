#include "includes.h"

Moto_Drv Moto;


/************************************************/
//函数功能：驱动器参数初始化
//输入参数：
//返回值：
//备注：
/************************************************/
void Moto_mdrv_init(void)
{
	Moto.en_sta = 0;
	Moto.lear = 0;
	Moto.angle = 0;
	Moto.left_pos = 0;
	Moto.right_pos = 0;
	Moto.set_angle = 0;
	Moto.set_lear = 0;
	Moto.vcc_sta = 0;
}


/************************************************/
//函数功能：驱动器命令解析
//输入参数：
//返回值：
//备注：
/************************************************/
void Moto_mdrv_analysis(void)
{
	uint8_t i;
	uint16_t rx_crc;
	uint16_t cal_crc;
	uint8_t cmd;
	uint16_t addr1, addr2;
	int16_t l_pulse_tmp;
	int16_t r_pulse_tmp;
	
	if(UsartToDrv.Usart_Rx_OK == true)
	{
		delay_us(10);
		UsartToDrv.Usart_Rx_OK = false;
		UsartToDrv.Comm_TimeOut = 0;
		UsartToDrv.Disconnect_flag = 0;
		if(UsartToDrv.Rx_Buf[0] == 0x01)
		{		
			if(UsartToDrv.Rx_Len%2 != 0)
				UsartToDrv.Rx_Len--;
			
		  rx_crc = (uint16_t)UsartToDrv.Rx_Buf[UsartToDrv.Rx_Len - 2] << 8 | UsartToDrv.Rx_Buf[UsartToDrv.Rx_Len - 1];
			cal_crc = ModBusCRC16(UsartToDrv.Rx_Buf,UsartToDrv.Rx_Len - 2);
			cal_crc = rx_crc;	
//			printf("drv_cmd : %02x\r\n",UsartToDrv.Rx_Buf[1]);
			if(cal_crc == rx_crc)
			{
				cmd = UsartToDrv.Rx_Buf[1];
				switch(cmd)
				{
					case MDRV_SET_SPEED:
						Moto.lear = (int16_t)UsartToDrv.Rx_Buf[3]<<8 | UsartToDrv.Rx_Buf[2];
						Moto.angle = (int16_t)UsartToDrv.Rx_Buf[5]<<8 | UsartToDrv.Rx_Buf[4];
					
				    if(Moto.lear == 0 && Moto.angle == 0) Moto.stop_sta = 1;
						else Moto.stop_sta = 0;
					
						#ifndef ROBOT_YZ01
						if(UsartToPC.Disconnect_flag == 0 && Robot_Sys.Speed_Timeout_cnt < 2000)
							Send_Speed_reply(1, 0xff, Moto.lear, Moto.angle);
            #endif
					 break;
					
					case MDRV_READ:
						addr1 = (uint16_t)UsartToDrv.Rx_Buf[2]<<8 | UsartToDrv.Rx_Buf[3];
						addr2 = (uint16_t)UsartToDrv.Rx_Buf[4]<<8 | UsartToDrv.Rx_Buf[5];
					
						if(addr1 == 0x5000 && addr2 == 0x5100)
						{
							Moto.left_rpm = (int16_t)UsartToDrv.Rx_Buf[6]<<8 | UsartToDrv.Rx_Buf[7];
							Moto.right_rpm = (int16_t)UsartToDrv.Rx_Buf[8]<<8 | UsartToDrv.Rx_Buf[9];
						}
						else if(addr1 == 0x5002 && addr2 == 0x5102)
						{
						}
						else if(addr1 == 0x5004 && addr2 == 0x5104)
						{
							Moto.right_pos= (uint16_t)UsartToDrv.Rx_Buf[6]<<8 | UsartToDrv.Rx_Buf[7];
							Moto.left_pos = (uint16_t)UsartToDrv.Rx_Buf[8]<<8 | UsartToDrv.Rx_Buf[9];
							Get_odom_pulse(Moto.left_pos, Moto.right_pos, &Moto_Odom.Left_Value, &Moto_Odom.Right_Value);		
							
							if(UsartToPC.Disconnect_flag == 0 && Robot_Sys.Odom_Timeout_cnt < 5000)
								Send_OdomUpdata(1, 0xff, Moto_Odom );
							
							Moto_Odom.Left_Value = 0;
							Moto_Odom.Right_Value = 0;
						}
						break;
						
					case MDRV_WRITE:
						addr1 = (uint16_t)UsartToDrv.Rx_Buf[2]<<8 | UsartToDrv.Rx_Buf[3];
					  addr2 = (uint16_t)UsartToDrv.Rx_Buf[4]<<8 | UsartToDrv.Rx_Buf[5];
						if(addr1 == 0x2318 && addr2 == 0x3318)
						{
						  int16_t l_rpm, r_rpm;
							l_rpm = (int16_t)UsartToDrv.Rx_Buf[6]<<8 | UsartToDrv.Rx_Buf[7];
							r_rpm = (int16_t)UsartToDrv.Rx_Buf[8]<<8 | UsartToDrv.Rx_Buf[9];
						}
						else if(addr1 == 0x2100 && addr2 == 0x3100)
						{
							uint8_t rx_l_en, rx_r_en;
							rx_l_en = UsartToDrv.Rx_Buf[7];
							rx_r_en = UsartToDrv.Rx_Buf[9];
							if(rx_l_en == 1 || rx_r_en == 1) Moto.en_sta = 1;
							else Moto.en_sta = 0;
							
							Send_speed_set(Moto.set_lear, Moto.set_angle);
						}
						break;
						
					case MDRV_ALL:
						addr1 = (uint16_t)UsartToDrv.Rx_Buf[2]<<8 | UsartToDrv.Rx_Buf[3];
					  addr2 = (uint16_t)UsartToDrv.Rx_Buf[4]<<8 | UsartToDrv.Rx_Buf[5];
					  if(addr1 == 0x2610 ||  addr1 == 0x2620)
						{
							Moto.lear = (int16_t)UsartToDrv.Rx_Buf[6]<<8 | UsartToDrv.Rx_Buf[7];
							Moto.angle = (int16_t)UsartToDrv.Rx_Buf[8]<<8 | UsartToDrv.Rx_Buf[9];
							
							l_pulse_tmp = (uint16_t)UsartToDrv.Rx_Buf[10]<<8 | UsartToDrv.Rx_Buf[11];
							r_pulse_tmp = (uint16_t)UsartToDrv.Rx_Buf[12]<<8 | UsartToDrv.Rx_Buf[13];
							
							Moto_Odom.Left_Value += l_pulse_tmp;
							Moto_Odom.Right_Value += r_pulse_tmp;
							
							Moto.left_pwm = (int16_t)UsartToDrv.Rx_Buf[14]<<8 | UsartToDrv.Rx_Buf[15];
							Moto.right_pwm = (int16_t)UsartToDrv.Rx_Buf[16]<<8 | UsartToDrv.Rx_Buf[17];
							#ifndef ROBOT_YZ01	
							if(UsartToPC.Disconnect_flag == 0 && Robot_Sys.Speed_Timeout_cnt < 5000)
								Send_Speed_reply(1, 0xff, Moto.lear, Moto.angle);
							#endif
						}
						break;
				}
			}
		}
		UsartToDrv.Rx_Len = 0;
	}
}