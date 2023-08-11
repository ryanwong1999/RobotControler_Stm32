#include "includes.h"

Moto_Drv Moto;


/************************************************/
//�������ܣ�������������ʼ��
//���������
//����ֵ��
//��ע��
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
//�������ܣ��������������
//���������
//����ֵ��
//��ע��
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


/************************************************/
//�������ܣ���������������
//���������
//����ֵ��
//��ע��
/************************************************/
bool Get_Drv_OverCur_Flag(uint16_t drv_cur, int16_t bat_cur)
{
	static bool sta = 0;
	static uint8_t over_cnt = 0, over_rst_cnt = 0;
	if(drv_cur >= 40000){
		over_cnt ++;
		over_rst_cnt = 0;
		if(over_cnt >= 3){
			over_cnt = 0;
			sta = true;
		}
	}else{
		over_rst_cnt ++;
		over_cnt = 0;
		if(over_rst_cnt > 20){
			over_rst_cnt = 0;
			sta = false;
		}
	}
	return sta;
}


/************************************************/
//�������ܣ�����������
//���������
//����ֵ��
//��ע��
/************************************************/
void Get_odom_pulse(int16_t l_pos, int16_t r_pos, int16_t *l_pulse, int16_t *r_pulse)
{
	static int16_t last_l_pos = 0, last_r_pos = 0;
	static int16_t last_l_pulse = 0, last_r_pulse = 0;
	static int16_t l_pulse_temp = 0, r_pulse_temp = 0;
	int16_t pulse_tmp;

	/* ������������ */
	if(l_pos > PULSE_CYCLE * 0.75 && last_l_pos < PULSE_CYCLE * 0.25)
	{
		pulse_tmp = PULSE_CYCLE;
	}
	else if(l_pos < PULSE_CYCLE * 0.25 && last_l_pos > PULSE_CYCLE * 0.75)
	{
		pulse_tmp = 0 - PULSE_CYCLE;
	}
	else
	{
		pulse_tmp = 0;
	} 
	l_pulse_temp = pulse_tmp + last_l_pos - l_pos;
	l_pulse_temp = l_pulse_temp/4; 
	/* ������������ */
	if(r_pos > PULSE_CYCLE * 0.75 && last_r_pos < PULSE_CYCLE * 0.25)
	{
		pulse_tmp = 0 - PULSE_CYCLE;
	}
	else if(r_pos < PULSE_CYCLE * 0.25 && last_r_pos > PULSE_CYCLE * 0.75)
	{
		pulse_tmp = PULSE_CYCLE;
	}
	else
	{
		pulse_tmp = 0;
	}
	r_pulse_temp = pulse_tmp + r_pos - last_r_pos;
	r_pulse_temp = r_pulse_temp/4;
	/* �жϼ�ͣ�ɿ���ĵ�һ�������������䣬�˵� */
	if(Moto_Odom.Clean_Flag == 1)
	{
		*l_pulse = 0;
		*r_pulse = 0;
		Moto_Odom.Clean_Flag = 0;
	}
	else
	{
		*l_pulse = l_pulse_temp;
		*r_pulse = r_pulse_temp;
	}
//	printf("last_l_pos : %d, last_r_pos : %d, last_l_pulse : %d, last_r_pulse : %d\r\n",last_l_pos, last_r_pos, last_l_pulse, last_r_pulse);
	last_l_pulse = l_pulse_temp;
	last_r_pulse = r_pulse_temp;
	last_l_pos = l_pos;
	last_r_pos = r_pos;
//	printf("l_pos : %d, r_pos : %d, *l_pulse : %d, *r_pulse : %d ----------------------------------\r\n", l_pos, r_pos, *l_pulse, *r_pulse);
}


/************************************************/
//�������ܣ���ѯ����λ��
//���������
//����ֵ��
//��ע��
/************************************************/
void Send_code_disk_query(void)
{
	Send_read_mdrv_cmd(0x5004, 0x5104);
}


/************************************************/
//�������ܣ����õ��ʹ��
//���������
//����ֵ��
//��ע��
/************************************************/
void Send_mdrv_en_set(int16_t l_en, int16_t r_en)
{
	Send_write_mdrv_cmd(0x2100, 0x3100, l_en, r_en);
}


/************************************************/
//�������ܣ����õ���ٶ�
//���������
//����ֵ��
//��ע��
/************************************************/
void Send_wheel_speed_set(int16_t l_speed, int16_t r_speed)
{
  Send_write_mdrv_cmd(0x2318, 0x3318, r_speed, l_speed);
}


/************************************************/
//�������ܣ����õ�����ٶȺͽ��ٶ�
//���������
//����ֵ��
//��ע��
/************************************************/
void Send_speed_set(int16_t set_lear, int16_t set_angle)
{
	uint8_t i;
  uint16_t crc16_data;
	uint8_t *buf;
	uint8_t sramx = 0;					//Ĭ��Ϊ�ڲ�sram
  buf = mymalloc(sramx, 10);	//����2K�ֽ�
	
	buf[0] = 0x01;
	buf[1] = 0xEA;
	buf[2] = set_lear;
	buf[3] = set_lear>>8;
	buf[4] = set_angle;
	buf[5] = set_angle>>8;
	crc16_data = ModBusCRC16(buf, 6);
	buf[6] = crc16_data >> 8;
	buf[7] = crc16_data;
	
	RS485_SendMultibyte(USART_RS485, buf, 8);
	myfree(sramx, buf);				//�ͷ��ڴ�
}


/************************************************/
//�������ܣ�������
//���������
//����ֵ��
//��ע��
/************************************************/
void Send_read_mdrv_cmd(uint16_t addr1, uint16_t addr2)
{
  uint16_t crc16_data;
  uint8_t *buf;
	uint8_t sramx = 0;					//Ĭ��Ϊ�ڲ�sram
  buf = mymalloc(sramx, 10);	//����20�ֽ�
	
	buf[0] = 0x01;
	buf[1] = 0x43;
	buf[2] = addr1>>8;
	buf[3] = addr1;
	buf[4] = addr2>>8;
	buf[5] = addr2;
	crc16_data = ModBusCRC16(buf, 6);
	buf[6] = crc16_data >> 8;
	buf[7] = crc16_data;
	
	RS485_SendMultibyte(USART_RS485, buf, 8);
	myfree(sramx, buf);
}


/************************************************/
//�������ܣ�д��������
//���������
//����ֵ��
//��ע��
/************************************************/
void Send_write_mdrv_cmd(uint16_t addr1, uint16_t addr2, int16_t dat1, int16_t dat2)
{
  uint16_t crc16_data;
	uint8_t *buf;
	uint8_t sramx = 0;					//Ĭ��Ϊ�ڲ�sram
  buf = mymalloc(sramx, 20); 	//����2K�ֽ�
	
	buf[0] = 0x01;
	buf[1] = 0x44;
	buf[2] = addr1>>8;
	buf[3] = addr1;
	buf[4] = addr2>>8;
	buf[5] = addr2;
	buf[6] = dat1>>8;
	buf[7] = dat1;
	buf[8] = dat2>>8;
	buf[9] = dat2;
	crc16_data = ModBusCRC16(buf, 10);
	buf[10] = crc16_data >> 8;
	buf[11] = crc16_data;
	
	RS485_SendMultibyte(USART_RS485, buf, 12);
	myfree(sramx, buf);
}


/************************************************/
//�������ܣ�У��
//���������
//����ֵ��
//��ע��
/************************************************/
unsigned short ModBusCRC16(const void *s, int n) 
{
	unsigned short c = 0xffff, b;
	char i;
	int k;
	for(k = 0; k < n; k++) 
	{  
		b=(((u8 *)s)[k]); 
		for(i = 0; i < 8; i++) 
		{  
			c = ((b^c)&1) ? (c>>1)^0xA001 : (c>>1); 
			b>>=1; 
		}  
	}  
	return (c<<8)|(c>>8);
}