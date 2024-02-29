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

char ACCCALSW[5] = {0XFF,0XAA,0X01,0X01,0X00};//进入加速度校准模式
char SAVACALSW[5]= {0XFF,0XAA,0X00,0X00,0X00};//保存当前配置


/************************************************/
//函数功能：imu通信
//输入参数：
//返回值：
//备注：
/************************************************/
void UART5_IRQHandler(void)    
{
	static uint8_t dat;
	static unsigned char ucRxBuffer[250];
	static unsigned char ucRxCnt = 0;	
	
	if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)
  {
		USART_ClearITPendingBit(UART5, USART_IT_RXNE);       
		
		ucRxBuffer[ucRxCnt++] = USART_ReceiveData(UART5);	//将收到的数据存入缓冲区中
		if(ucRxBuffer[0] != 0x55) //数据头不对，则重新开始寻找0x55数据头
		{
			ucRxCnt=0;
			return;
		}
		if(ucRxCnt < 11){return;}	//数据不满11个，则返回
		else
		{
			switch(ucRxBuffer[1])		//判断数据是哪种数据，然后将其拷贝到对应的结构体中，有些数据包需要通过上位机打开对应的输出后，才能接收到这个数据包的数据
			{
				//0x50	0x51		0x52	  0x53	0x54	0x55	  	0x56	  	0x57	  0x58	0x59	  0x5A				0x5F	
				//时间	加速度		角速度		角度	磁场	端口状态		气压高度		经纬度		地速	四元数		GPS定位精度	读取
				case 0x50:	//输出时间
					memcpy(&stcTime, &ucRxBuffer[2], 8);	
//					printf("Time:20%d-%d-%d %d:%d:%.3f\r\n",stcTime.ucYear,stcTime.ucMonth,stcTime.ucDay,stcTime.ucHour,stcTime.ucMinute,(float)stcTime.ucSecond+(float)stcTime.usMiliSecond/1000);
					break;
				case 0x51:	//输出加速度
					memcpy(&stcAcc, &ucRxBuffer[2], 8);	
//					printf("Acc:%.3f %.3f %.3f\r\n",(float)stcAcc.a[0]/32768*16,(float)stcAcc.a[1]/32768*16,(float)stcAcc.a[2]/32768*16);
					break;
				case 0x52:	//输出角速度
					memcpy(&stcGyro, &ucRxBuffer[2], 8);	
//					printf("Gyro:%.3f %.3f %.3f\r\n",(float)stcGyro.w[0]/32768*2000,(float)stcGyro.w[1]/32768*2000,(float)stcGyro.w[2]/32768*2000);
					break;
				case 0x53:	//输出角度
					memcpy(&stcAngle, &ucRxBuffer[2], 8);	
//					printf("Angle:%.3f %.3f %.3f\r\n",(float)stcAngle.Angle[0]/32768*180,(float)stcAngle.Angle[1]/32768*180,(float)stcAngle.Angle[2]/32768*180);
					break;
				case 0x54:	//输出磁场
					memcpy(&stcMag, &ucRxBuffer[2],	8);	
//					printf("Mag:%d %d %d\r\n",stcMag.h[0],stcMag.h[1],stcMag.h[2]);	
					break;
				case 0x55:	//输出端口状态
					memcpy(&stcDStatus,	&ucRxBuffer[2],	8);	
//					printf("DStatus:%d %d %d %d\r\n",stcDStatus.sDStatus[0],stcDStatus.sDStatus[1],stcDStatus.sDStatus[2],stcDStatus.sDStatus[3]);
					break;
				case 0x56:	//输出气压、高度
					memcpy(&stcPress, &ucRxBuffer[2],	8);	
//					printf("Pressure:%ld Height%.2f\r\n",stcPress.lPressure,(float)stcPress.lAltitude/100);
					break;
				case 0x57:	//输出经纬度
					memcpy(&stcLonLat, &ucRxBuffer[2], 8);	
//					printf("Longitude:%ldDeg%.5fm Lattitude:%ldDeg%.5fm\r\n",stcLonLat.lLon/10000000,(double)(stcLonLat.lLon % 10000000)/1e5,stcLonLat.lLat/10000000,(double)(stcLonLat.lLat % 10000000)/1e5);
					break;
				case 0x58:	//输出地速
					memcpy(&stcGPSV, &ucRxBuffer[2], 8);	
//					printf("GPSHeight:%.1fm GPSYaw:%.1fDeg GPSV:%.3fkm/h\r\n",(float)stcGPSV.sGPSHeight/10,(float)stcGPSV.sGPSYaw/10,(float)stcGPSV.lGPSVelocity/1000);
					break;
				case 0x59:	//输出四元素
					memcpy(&stcQ, &ucRxBuffer[2],	8);	
//					printf("Four elements:%.5f %.5f %.5f %.5f\r\n\r\n",(float)stcQ.q[0]/32768,(float)stcQ.q[1]/32768,(float)stcQ.q[2]/32768,(float)stcQ.q[3]/32768);
					break;
			}
			ucRxCnt=0;//清空缓存区
		}
	}
}

void accalsw(void)
{
	uint8_t *buf;
	uint8_t sramx = 0;				//默认为内部sram
  buf = mymalloc(sramx, 5);	//申请5字节

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
	uint8_t sramx = 0;				//默认为内部sram
  buf = mymalloc(sramx, 5);	//申请5字节

	buf[0] = 0XFF;
	buf[1] = 0XAA;
	buf[2] = 0X00;
	buf[3] = 0X00;
	buf[4] = 0x00;
	USARTx_SendMultibyte(UART5, buf, 5);
}