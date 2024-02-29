#include "includes.h" 


//初始化IIC
void IIC2_Init(void)
{			
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);	//使能GPIOB时钟
  //GPIOB6,B7初始化设置
  GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_10 | GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_OUT;				//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;				//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;		//100MHz
  GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP;					//上拉
  GPIO_Init(GPIOB, &GPIO_InitStructure);								//初始化
	IIC_SCL2 = 1;
	IIC_SDA2 = 1;
}


//产生IIC起始信号
void IIC2_Start(void)
{
	SDA_OUT2();			//sda线输出
	IIC_SDA2 = 1;	  	  
	IIC_SCL2 = 1;
	delay_us(4);
 	IIC_SDA2 = 0;		//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL2 = 0;		//钳住I2C总线，准备发送或接收数据 
}	  


//产生IIC停止信号
void IIC2_Stop(void)
{
  SDA_OUT2();			//sda线输出
	IIC_SCL2 = 1;
	IIC_SDA2 = 0;		//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SDA2 = 1;		//发送I2C总线结束信号
	delay_us(4);	
}


//等待应答信号到来
//返回值： 1，接收应答失败
//        0，接收应答成功
u8 IIC2_Wait_Ack(void)
{
	u8 ucErrTime = 0;
	SDA_IN2();				//SDA设置为输入  
	IIC_SDA2 = 1; 
	delay_us(1);	   
	IIC_SCL2 = 1; 
	delay_us(1);	 
	while(READ_SDA2)
	{
		ucErrTime++;
		if(ucErrTime > 250)
		{
			printf("iic2 timeout\r\n");
			IIC2_Stop();
			return 1;
		}
	}
	IIC_SCL2 = 0;		//时钟输出0 	   
	return 0;  
} 


//产生ACK应答
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


//不产生ACK应答		    
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


//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void IIC2_Send_Byte(u8 txd)
{                        
  u8 t;   
	SDA_OUT2(); 	    
  //IIC_SCL2 = 0;		//拉低时钟开始数据传输
	for(t = 0; t < 8; t++)
	{              
		IIC_SDA2 = (txd & 0x80) >> 7;
		txd <<= 1; 	  
		delay_us(2);		//对TEA5767这三个延时都是必须的
		IIC_SCL2 = 1;
		delay_us(2); 
		IIC_SCL2 = 0;	
		delay_us(2);
		if(t == 7) 
			IIC_SDA2 = 1;
	}	 
} 	    


//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 IIC2_Read_Byte(unsigned char ack)
{
	unsigned char i, receive = 0;
	SDA_IN();					//SDA设置为输入
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
		IIC2_NAck();		//发送nACK
  else
    IIC2_Ack();		//发送ACK   
  return receive;
}
