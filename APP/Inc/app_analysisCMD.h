#ifndef __APP_ANALYSISCMD_H
#define __APP_ANALYSISCMD_H

#include "includes.h"

//#define ROBOT_YZ01		1		//YZ01
//#define ROBOT_M100		1		//M100
#define ROBOT_MR9			1		//MR9

//#define MOTO_LOCK			1		//����Ƿ���

#define SEND_PC_LEN		19

#define END_H     		0x0D
#define END_L     		0x0A	 
//buffer ��������С	 
#define	MAX_TX_LEN		64
#define	MAX_RX_LEN		64
//����֡�Ĵ���
#define FRH_REG   		0x00   // ֡1
#define FRL_REG   		0x01   // ֡2
#define FINX_REG  		0x02   // index
#define FLEN_REG  		0x03   // Frame length
#define S_ID_REG  		0x04   // ԴID
#define P_ID_REG  		0x05	 // Ŀ��ID
#define CMD_REG   		0x06   // ����
#define DUM_REG   		0x07   // ���ݰ���С

#define SPEED1_REG1		0x08
#define SPEED2_REG1		0x0A
//���ص�ַ
#define DEV_ID    		0x01
#define PSC_ID    		0x02
//����
#define CMD_QUERY_ODOM       	0x01		//��ѯODOM
#define CMD_QUERY_PWR        	0x02    //��ѯ����
#define CMD_QUERY_TEMPHUM    	0x03    //��ѯ�¶ȣ�ʪ��
#define CMD_SET_SPEED        	0x15		//����ת��
#define CMD_STOP             	0x05		//ɲ��
#define CMD_HEAD             	0x06    //ͷ���˶�����
#define CMD_Ultrasonic       	0x07    //��ѯ  ������
#define CMD_AUTOCHARGE       	0x08    //�Զ����
#define CMD_CHECK            	0x19    //���淢����������У��ֱ��
#define CMD_QUERY_POWER      	0x09    //��ѯ����
#define CMD_HEAD_POSE        	0x10    //��ѯ  ͷ������̬
#define CMD_HEAD_ANGLE			 	0x11    //�ýǶȿ���ͷ��
#define CMD_Recall					 	0x12		//����Ǹ���ros�Ƿ��� ������ڸ���
#define CMD_AGV_Near			   	0x20			
#define CMD_QUERY_AGV				 	0x60		//��ѯAGV��Ϣ(RFID����,�����־)
#define CMD_QUERY_LIFT       	0x61		//��ѯ���������Ϣ
#define CMD_QUERY_TEMP			 	0x62		//��ѯ��������
#define CMD_QUERY_ENVIRON    	0x63		//��ѯ��������
#define CMD_QUERY_OBS_EN     	0x64		//��ѯ�ϰ�ʹ��
#define CMD_SET_LIFT					0x71		//������������߶�
#define CMD_SET_BAT_CAP       0x72		//���õ�ص�����  
#define CMD_SET_RESET_EEPOM   0x73		//��λEEPOM 
#define CMD_SET_RFID          0x74		//
#define CMD_SET_HEAD_OFFSET   0x75		//����ͷ������
#define CMD_SET_SENSOR_EN     0x77		//���ô�����ʹ��
#define CMD_LIFT_CON					0x81		//�����������
#define CMD_CON_MOVE					0x82


#define WHEEL_TRACK  					0.38		//YZ01C ��λ�� �־� ,�������0.31,���ô�0.28���ܽ��׿�0.41
#define WHEEL_RADIUS  				0.0845	//��λ��,���Ӱ뾶
#define PI  									3.1415926
#define PULSE_CYCLE   				5600		//��������

typedef struct
{
	uint8_t Send_BUF[MAX_TX_LEN];
	uint8_t Recv_BUF[MAX_RX_LEN];
	uint8_t RX_STA;
	uint8_t Recv_Length;
	bool Recv_OK;
}PC_COM_type;	
	 
typedef struct
{
	int16_t Left_Value;
	int16_t Right_Value;
	int16_t Left_Value_Sum;
	int16_t Right_Value_Sum;
	int8_t Clean_Flag;
}Odom_Data_type;

extern Odom_Data_type  Moto_Odom; 

void Send_OdomUpdata(uint8_t index, uint8_t paddr, Odom_Data_type odom_dat);
void Send_HeadCtrlCmd(uint8_t index, uint8_t addr, uint8_t cmd_dat);
void Send_HeadCtrlAngle(uint8_t index, uint8_t addr, uint8_t level,uint8_t);
void Send_Obs_EN_Mess(uint8_t index,uint8_t addr);
unsigned char CRC8_Table(unsigned char *p, char counter);
uint8_t CRC8(uint8_t *pDate, uint8_t length);
void AnalysisCMD(void);	 
unsigned char CRC8_Table(unsigned char *p, char counter);	 
void SetMotoSpeed(void);
void Send_Obstacle_Sta(uint8_t index, uint8_t paddr, uint8_t obs_sta, uint8_t crach_sta);
void Send_Speed_reply(uint8_t index, uint8_t paddr, uint16_t linear, uint16_t angular);
void Send_Autocharge_reply(uint8_t index, uint8_t paddr, uint8_t dat);
void Send_HeadCtrl_reply(uint8_t index, uint8_t paddr, uint8_t cmd);
void Send_HeadAngle_reply(uint8_t index, uint8_t paddr, uint16_t set_level, uint16_t set_pitch);
void Send_SetLift_reply(uint8_t index, uint8_t paddr, uint16_t heitht);
void Send_LiftCtrl_reply(uint8_t index, uint8_t paddr, uint8_t cmd);
void Send_ultra_en_reply(uint8_t index, uint8_t paddr, uint8_t cmd);
void Send_angle_offset_reply(uint8_t index, uint8_t paddr, int8_t level_offset, int8_t pitch_offset);

#endif 