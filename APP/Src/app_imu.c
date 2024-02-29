#include "includes.h" 

//jy901  https://wit-motion.yuque.com/docs/share/68d5aebd-703a-473a-836a-9bef2e5c0b4a?#%20%E3%80%8AWIT%E7%A7%81%E6%9C%89%E5%8D%8F%E8%AE%AE%E3%80%8B
struct STime		stcTime;  
struct SAcc 		stcAcc;
struct SGyro 		stcGyro;
struct SAngle 	stcAngle;
struct SMag 		stcMag;
struct SDStatus stcDStatus;
struct SPress 	stcPress;
struct SLonLat 	stcLonLat;
struct SGPSV 		stcGPSV;
struct SQ       stcQ;

char ACCCALSW[5] = {0XFF,0XAA,0X01,0X01,0X00};//������ٶ�У׼ģʽ
char SAVACALSW[5]= {0XFF,0XAA,0X00,0X00,0X00};//���浱ǰ����

float angle1, angle2, angle3;
/************************************************/
//�������ܣ�imuͨ��
//���������
//����ֵ��
//��ע��
/************************************************/
void UART5_IRQHandler(void)    
{
	static uint8_t dat;
	static unsigned char ucRxBuffer[250];
	static unsigned char ucRxCnt = 0;	
	
	if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)
  {
		USART_ClearITPendingBit(UART5, USART_IT_RXNE);       
		
		ucRxBuffer[ucRxCnt++] = USART_ReceiveData(UART5);	//���յ������ݴ��뻺������
		if(ucRxBuffer[0] != 0x55) //����ͷ���ԣ������¿�ʼѰ��0x55����ͷ
		{
			ucRxCnt=0;
			return;
		}
		if(ucRxCnt < 11){return;}	//���ݲ���11�����򷵻�
		else
		{
			switch(ucRxBuffer[1])		//�ж��������������ݣ�Ȼ���俽������Ӧ�Ľṹ���У���Щ���ݰ���Ҫͨ����λ���򿪶�Ӧ������󣬲��ܽ��յ�������ݰ�������
			{
				//0x50	0x51		0x52	  0x53	0x54	0x55	  	0x56	  	0x57	  0x58	0x59	  0x5A				0x5F	
				//ʱ��	���ٶ�		���ٶ�		�Ƕ�	�ų�	�˿�״̬		��ѹ�߶�		��γ��		����	��Ԫ��		GPS��λ����	��ȡ
				case 0x50:	memcpy(&stcTime,		&ucRxBuffer[2],	8);	break;
				case 0x51:	memcpy(&stcAcc,			&ucRxBuffer[2],	8);	break;
				case 0x52:	memcpy(&stcGyro,		&ucRxBuffer[2],	8);	break;
				case 0x53:	
					memcpy(&stcAngle,		&ucRxBuffer[2],	8);	
					angle1 = (float)stcAngle.Angle[0]/32768*180;
					angle2 = (float)stcAngle.Angle[1]/32768*180;
					angle3 = (float)stcAngle.Angle[2]/32768*180;
					printf("Angle:%.3f %.3f %.3f\r\n", angle1, angle2, angle3);
					break;
				case 0x54:	memcpy(&stcMag,			&ucRxBuffer[2],	8);	break;
				case 0x55:	memcpy(&stcDStatus,	&ucRxBuffer[2],	8);	break;
				case 0x56:	memcpy(&stcPress,		&ucRxBuffer[2],	8);	break;
				case 0x57:	memcpy(&stcLonLat,	&ucRxBuffer[2],	8);	break;
				case 0x58:	memcpy(&stcGPSV,		&ucRxBuffer[2],	8);	break;
				case 0x59:	memcpy(&stcQ,				&ucRxBuffer[2],	8);	break;
			}
			ucRxCnt=0;//��ջ�����
		}
	}
}

void accalsw(void)
{
	uint8_t *buf;
	uint8_t sramx = 0;				//Ĭ��Ϊ�ڲ�sram
  buf = mymalloc(sramx, 5);	//����5�ֽ�

	buf[0] = 0XFF;
	buf[1] = 0XAA;
	buf[2] = 0X01;
	buf[3] = 0X01;
	buf[4] = 0x00;
	USARTx_SendMultibyte(UART5, buf, 5);
}

void savacalsw(void)
{
	uint8_t *buf;
	uint8_t sramx = 0;				//Ĭ��Ϊ�ڲ�sram
  buf = mymalloc(sramx, 5);	//����5�ֽ�

	buf[0] = 0XFF;
	buf[1] = 0XAA;
	buf[2] = 0X00;
	buf[3] = 0X00;
	buf[4] = 0x00;
	USARTx_SendMultibyte(UART5, buf, 5);
}