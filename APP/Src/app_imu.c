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

//char ACCCALSW[5] = {0XFF,0XAA,0X01,0X01,0X00};//������ٶ�У׼ģʽ
//char SAVACALSW[5]= {0XFF,0XAA,0X00,0X00,0X00};//���浱ǰ����


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
				case 0x50:	//���ʱ��
//					memcpy(&stcTime, &ucRxBuffer[2], 8);	
					stcTime.ucYear = ucRxBuffer[2];
					stcTime.ucMonth = ucRxBuffer[3];
					stcTime.ucDay = ucRxBuffer[4];
					stcTime.ucHour = ucRxBuffer[5];
					stcTime.ucMinute = ucRxBuffer[6];
					stcTime.ucSecond = ucRxBuffer[7];
					stcTime.usMiliSecond = (ucRxBuffer[8] << 8) | ucRxBuffer[9];
//					printf("Time:20%d-%d-%d %d:%d:%.3f\r\n",stcTime.ucYear,stcTime.ucMonth,stcTime.ucDay,stcTime.ucHour,stcTime.ucMinute,(float)stcTime.ucSecond+(float)stcTime.usMiliSecond/1000);
					break;
				case 0x51:	//������ٶ�
//					memcpy(&stcAcc, &ucRxBuffer[2], 8);	
					stcAcc.a[0] = (int16_t)((ucRxBuffer[2] << 8) | ucRxBuffer[3]);
					stcAcc.a[1] = (int16_t)((ucRxBuffer[4] << 8) | ucRxBuffer[5]);
					stcAcc.a[2] = (int16_t)((ucRxBuffer[6] << 8) | ucRxBuffer[7]);
//					printf("Acc:%.3f %.3f %.3f\r\n",(float)stcAcc.a[0]/32768*16,(float)stcAcc.a[1]/32768*16,(float)stcAcc.a[2]/32768*16);
					break;
				case 0x52:	//������ٶ�
//					memcpy(&stcGyro, &ucRxBuffer[2], 8);	
					stcGyro.w[0] = (int16_t)((ucRxBuffer[2] << 8) | ucRxBuffer[3]);
					stcGyro.w[1] = (int16_t)((ucRxBuffer[4] << 8) | ucRxBuffer[5]);
					stcGyro.w[2] = (int16_t)((ucRxBuffer[6] << 8) | ucRxBuffer[7]);
//					printf("Gyro:%.3f %.3f %.3f\r\n",(float)stcGyro.w[0]/32768*2000,(float)stcGyro.w[1]/32768*2000,(float)stcGyro.w[2]/32768*2000);
					break;
				case 0x53:	//����Ƕ�
//					memcpy(&stcAngle, &ucRxBuffer[2], 8);
					stcAngle.Angle[0] = (int16_t)((ucRxBuffer[2] << 8) | ucRxBuffer[3]);
					stcAngle.Angle[1] = (int16_t)((ucRxBuffer[4] << 8) | ucRxBuffer[5]);
					stcAngle.Angle[2] = (int16_t)((ucRxBuffer[6] << 8) | ucRxBuffer[7]);
//					printf("Angle:%.3f %.3f %.3f\r\n",(float)stcAngle.Angle[0]/32768*180,(float)stcAngle.Angle[1]/32768*180,(float)stcAngle.Angle[2]/32768*180);
					break;
				case 0x54:	//����ų�
//					memcpy(&stcMag, &ucRxBuffer[2],	8);	
					stcMag.h[0] = (int16_t)((ucRxBuffer[2] << 8) | ucRxBuffer[3]);
					stcMag.h[1] = (int16_t)((ucRxBuffer[4] << 8) | ucRxBuffer[5]);
					stcMag.h[2] = (int16_t)((ucRxBuffer[6] << 8) | ucRxBuffer[7]);
//					printf("Mag:%d %d %d\r\n",stcMag.h[0],stcMag.h[1],stcMag.h[2]);	
					break;
				case 0x55:	//����˿�״̬
//					memcpy(&stcDStatus,	&ucRxBuffer[2],	8);	
					stcDStatus.sDStatus[0] = ucRxBuffer[2];
					stcDStatus.sDStatus[1] = ucRxBuffer[3];
					stcDStatus.sDStatus[2] = ucRxBuffer[4];
					stcDStatus.sDStatus[3] = ucRxBuffer[5];
//					printf("DStatus:%d %d %d %d\r\n",stcDStatus.sDStatus[0],stcDStatus.sDStatus[1],stcDStatus.sDStatus[2],stcDStatus.sDStatus[3]);
					break;
				case 0x56:	//�����ѹ���߶�
//					memcpy(&stcPress, &ucRxBuffer[2],	8);	
					stcPress.lPressure = (int32_t)((ucRxBuffer[2] << 24) | (ucRxBuffer[3] << 16) | (ucRxBuffer[4] << 8) | ucRxBuffer[5]);
					stcPress.lAltitude = (int32_t)((ucRxBuffer[6] << 24) | (ucRxBuffer[7] << 16) | (ucRxBuffer[8] << 8) | ucRxBuffer[9]);
//					printf("Pressure:%ld Height%.2f\r\n",stcPress.lPressure,(float)stcPress.lAltitude/100);
					break;
				case 0x57:	//�����γ��
//					memcpy(&stcLonLat, &ucRxBuffer[2], 8);	
					stcLonLat.lLon = (int32_t)((ucRxBuffer[2] << 24) | (ucRxBuffer[3] << 16) | (ucRxBuffer[4] << 8) | ucRxBuffer[5]);
					stcLonLat.lLat = (int32_t)((ucRxBuffer[6] << 24) | (ucRxBuffer[7] << 16) | (ucRxBuffer[8] << 8) | ucRxBuffer[9]);
//					printf("Longitude:%ldDeg%.5fm Lattitude:%ldDeg%.5fm\r\n",stcLonLat.lLon/10000000,(double)(stcLonLat.lLon % 10000000)/1e5,stcLonLat.lLat/10000000,(double)(stcLonLat.lLat % 10000000)/1e5);
					break;
				case 0x58:	//�������
//					memcpy(&stcGPSV, &ucRxBuffer[2], 8);	
					stcGPSV.sGPSHeight = (int16_t)((ucRxBuffer[2] << 8) | ucRxBuffer[3]);
					stcGPSV.sGPSYaw = (int16_t)((ucRxBuffer[4] << 8) | ucRxBuffer[5]);
					stcGPSV.lGPSVelocity = (int32_t)((ucRxBuffer[6] << 24) | (ucRxBuffer[7] << 16) | (ucRxBuffer[8] << 8) | ucRxBuffer[9]);
//					printf("GPSHeight:%.1fm GPSYaw:%.1fDeg GPSV:%.3fkm/h\r\n",(float)stcGPSV.sGPSHeight/10,(float)stcGPSV.sGPSYaw/10,(float)stcGPSV.lGPSVelocity/1000);
					break;
				case 0x59:	//�����Ԫ��
//					memcpy(&stcQ, &ucRxBuffer[2],	8);	
					stcQ.q[0] = (int16_t)((ucRxBuffer[2] << 8) | ucRxBuffer[3]);
					stcQ.q[1] = (int16_t)((ucRxBuffer[4] << 8) | ucRxBuffer[5]);
					stcQ.q[2] = (int16_t)((ucRxBuffer[6] << 8) | ucRxBuffer[7]);
					stcQ.q[3] = (int16_t)((ucRxBuffer[8] << 8) | ucRxBuffer[9]);
//					printf("Four elements:%.5f %.5f %.5f %.5f\r\n\r\n",(float)stcQ.q[0]/32768,(float)stcQ.q[1]/32768,(float)stcQ.q[2]/32768,(float)stcQ.q[3]/32768);
					break;
			}
			ucRxCnt=0;//��ջ�����
		}
	}
}

void imu_accalsw(void)
{
	uint8_t *buf;
	uint8_t sramx = 0;				//Ĭ��Ϊ�ڲ�sram
  buf = mymalloc(sramx, 10);	//����5�ֽ�

	buf[0] = 0XFF;
	buf[1] = 0XAA;
	buf[2] = 0X01;
	buf[3] = 0X01;
	buf[4] = 0x00;
	USARTx_SendMultibyte(UART5, buf, 5);
}

void imu_savacalsw(void)
{
	uint8_t *buf;
	uint8_t sramx = 0;				//Ĭ��Ϊ�ڲ�sram
  buf = mymalloc(sramx, 10);	//����5�ֽ�

	buf[0] = 0XFF;
	buf[1] = 0XAA;
	buf[2] = 0X00;
	buf[3] = 0X00;
	buf[4] = 0x00;
	USARTx_SendMultibyte(UART5, buf, 5);
}