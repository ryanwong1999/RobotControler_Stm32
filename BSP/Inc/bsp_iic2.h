#ifndef __BSP_IIC2_H
#define __BSP_IIC2_H


//IO��������
#define SDA_IN2()		{GPIOB->MODER&=~(3<<(11*2)); GPIOB->MODER|=0<<11*2;}	
#define SDA_OUT2()	{GPIOB->MODER&=~(3<<(11*2)); GPIOB->MODER|=1<<11*2;} 
//IO��������	 
#define IIC_SCL2		PBout(10)	//SCL
#define IIC_SDA2		PBout(11)	//SDA	 
#define READ_SDA2   PBin(11)	//���SDA 


//IIC���в�������
void IIC2_Init(void);									//��ʼ��IIC��IO��				 
void IIC2_Start(void);									//����IIC��ʼ�ź�
void IIC2_Stop(void);	  							//����IICֹͣ�ź�
void IIC2_Send_Byte(u8 txd);						//IIC����һ���ֽ�
u8 IIC2_Read_Byte(unsigned char ack);	//IIC��ȡһ���ֽ�
u8 IIC2_Wait_Ack(void); 								//IIC�ȴ�ACK�ź�
void IIC2_Ack(void);										//IIC����ACK�ź�
void IIC2_NAck(void);									//IIC������ACK�ź�
void IIC2_Write_One_Byte(u8 daddr, u8 addr, u8 data);
u8 IIC2_Read_One_Byte(u8 daddr, u8 addr);	  

#endif