#include "includes.h" 


//��ʼ��IIC
void IIC2_Init(void)
{			
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);	//ʹ��GPIOBʱ��
  //GPIOB6,B7��ʼ������
  GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_10 | GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_OUT;				//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;				//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;		//100MHz
  GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP;					//����
  GPIO_Init(GPIOB, &GPIO_InitStructure);								//��ʼ��
	IIC_SCL2 = 1;
	IIC_SDA2 = 1;
}


//����IIC��ʼ�ź�
void IIC2_Start(void)
{
	SDA_OUT2();			//sda�����
	IIC_SDA2 = 1;	  	  
	IIC_SCL2 = 1;
	delay_us(4);
 	IIC_SDA2 = 0;		//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL2 = 0;		//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  


//����IICֹͣ�ź�
void IIC2_Stop(void)
{
  SDA_OUT2();			//sda�����
	IIC_SCL2 = 1;
	IIC_SDA2 = 0;		//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SDA2 = 1;		//����I2C���߽����ź�
	delay_us(4);	
}


//�ȴ�Ӧ���źŵ���
//����ֵ�� 1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 IIC2_Wait_Ack(void)
{
	u8 ucErrTime = 0;
	SDA_IN2();				//SDA����Ϊ����  
	IIC_SDA2 = 1; 
	delay_us(1);	   
	IIC_SCL2 = 1; 
	delay_us(1);	 
	while(READ_SDA2)
	{
		ucErrTime++;
		if(ucErrTime > 250)
		{
			printf("iic timeout\r\n");
			IIC2_Stop();
			return 1;
		}
	}
	IIC_SCL2 = 0;		//ʱ�����0 	   
	return 0;  
} 


//����ACKӦ��
void IIC2_Ack(void)
{
	SDA_OUT2();
	IIC_SDA2 = 0;
	delay_us(2);
	IIC_SCL2 = 1;
	delay_us(2);
	IIC_SCL2 = 0;
	delay_us(2);
	IIC_SDA2 = 1;
}


//������ACKӦ��		    
void IIC2_NAck(void)
{
	SDA_OUT2();
	IIC_SDA2 = 1;
	delay_us(2);
	IIC_SCL2 = 1;
	delay_us(2);
	IIC_SCL2 = 0;
	delay_us(2);
}					 				


//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC2_Send_Byte(u8 txd)
{                        
  u8 t;   
	SDA_OUT2(); 	    
  //IIC_SCL2 = 0;		//����ʱ�ӿ�ʼ���ݴ���
	for(t = 0; t < 8; t++)
	{              
		IIC_SDA2 = (txd & 0x80) >> 7;
		txd <<= 1; 	  
		delay_us(2);		//��TEA5767��������ʱ���Ǳ����
		IIC_SCL2 = 1;
		delay_us(2); 
		IIC_SCL2 = 0;	
		delay_us(2);
		if(t == 7) 
			IIC_SDA2 = 1;
	}	 
} 	    


//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 IIC2_Read_Byte(unsigned char ack)
{
	unsigned char i, receive = 0;
	SDA_IN();					//SDA����Ϊ����
  for(i = 0; i < 8; i++)
	{
		receive <<= 1;
    IIC_SCL2 = 1; 
    delay_us(2);   
    if(READ_SDA2)
			receive++;  
		IIC_SCL2 = 0;		
		delay_us(1); 
  }					 
  if(!ack)
		IIC2_NAck();		//����nACK
  else
    IIC2_Ack();		//����ACK   
  return receive;
}
