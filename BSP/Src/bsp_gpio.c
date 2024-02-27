#include "includes.h" 


/************************************************/
//�������ܣ�LEDָʾ��GPIO��ʼ��
//���������
//����ֵ��
//��ע��
/************************************************/
void LED_GPIO_Init(void)
{
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
	GPIO_InitTypeDef GPIO_InitStructure;
	/*����LED��ص�GPIO����ʱ��*/
	RCC_AHB1PeriphClockCmd (LEDG_PORT_CLK | LEDR_PORT_CLK | LED1_PORT_CLK | LED2_PORT_CLK , ENABLE); 	
														   
	GPIO_InitStructure.GPIO_Pin 	= LED_GREEN_PIN;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_OUT;   		/*��������ģʽΪ���ģʽ */
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      /*�������ŵ��������Ϊ������� */
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP;				/*��������Ϊ����ģʽ */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;		/*������������Ϊ2MHz */  
	GPIO_Init(LEDG_PORT, &GPIO_InitStructure);			    /*���ÿ⺯����ʹ���������õ�GPIO_InitStructure��ʼ��GPIO */
														   
	GPIO_InitStructure.GPIO_Pin 	= LED_RED_PIN;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_OUT;   		/*��������ģʽΪ���ģʽ */
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      /*�������ŵ��������Ϊ������� */
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP;				/*��������Ϊ����ģʽ */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;		/*������������Ϊ2MHz */  
	GPIO_Init(LEDR_PORT, &GPIO_InitStructure);					/*���ÿ⺯����ʹ���������õ�GPIO_InitStructure��ʼ��GPIO */
	
	GPIO_InitStructure.GPIO_Pin		= LED1_PIN;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_OUT;			/*��������ģʽΪ���ģʽ*/
	GPIO_InitStructure.GPIO_OType	= GPIO_OType_PP;			/*�������ŵ��������Ϊ�������*/
	GPIO_InitStructure.GPIO_PuPd	= GPIO_PuPd_UP;				/*��������Ϊ����ģʽ*/
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_2MHz;		/*������������Ϊ2MHz*/  
	GPIO_Init(LED1_PORT, &GPIO_InitStructure);					/*���ÿ⺯����ʹ���������õ�GPIO_InitStructure��ʼ��GPIO*/
	
	GPIO_InitStructure.GPIO_Pin		= LED2_PIN;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_OUT;			/*��������ģʽΪ���ģʽ*/
	GPIO_InitStructure.GPIO_OType	= GPIO_OType_PP;			/*�������ŵ��������Ϊ�������*/
	GPIO_InitStructure.GPIO_PuPd	= GPIO_PuPd_UP;				/*��������Ϊ����ģʽ*/
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_2MHz;		/*������������Ϊ2MHz*/  
	GPIO_Init(LED2_PORT, &GPIO_InitStructure);					/*���ÿ⺯����ʹ���������õ�GPIO_InitStructure��ʼ��GPIO*/
	
	LED_RED_OFF;
	LED_GREEN_OFF;
	LED1_OFF;
	LED2_OFF;
}


/************************************************/
//�������ܣ�������GPIO��ʼ��
//���������
//����ֵ��
//��ע��
/************************************************/
void BEEP_GPIO_Init(void)
{
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(BEEP_PORT_CLK, ENABLE); 

  GPIO_InitStructure.GPIO_Pin		=	BEEP_PIN;
  GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_OUT;		//���
	GPIO_InitStructure.GPIO_OType	= GPIO_OType_PP;		//�������
	GPIO_InitStructure.GPIO_PuPd	= GPIO_PuPd_NOPULL;	//������ ,Ҳ������
  GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_100MHz;	 
  GPIO_Init(BEEP_PORT, &GPIO_InitStructure);	
	
  BEEP_OFF;	 
}


void Key_GPIO_Init(void)
{ 
	GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOE, ENABLE);//ʹ��GPIOA,GPIOEʱ��
 
  GPIO_InitStructure.GPIO_Pin 	= KEY_UP_PIN | KEY_DOWN_PIN;	//KEY0 KEY1 KEY2��Ӧ����
  GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_IN;								//��ͨ����ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;					//100M
  GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP;								//����
  GPIO_Init(GPIOE, &GPIO_InitStructure);											//��ʼ��GPIOE3,4
	
	 
  GPIO_InitStructure.GPIO_Pin 	= KEY_ENTER_PIN;							//WK_UP��Ӧ����PA0
  GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_DOWN ;						//����
  GPIO_Init(GPIOA, &GPIO_InitStructure);											//��ʼ��GPIOA0
}


/************************************************/
//�������ܣ�����ģ��GPIO��ʼ����ECHO�ڶ���Ϊ�ⲿ�ж������ʼ��
//���������
//����ֵ��
//��ע��
/************************************************/
void Ultrasonic_Exti_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;	
	
  RCC_AHB1PeriphClockCmd(ULTRA1_PORT_CLK, ENABLE); 

  GPIO_InitStructure.GPIO_Pin		=	TRIG1_PIN;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_OUT;			//���
	GPIO_InitStructure.GPIO_OType	= GPIO_OType_PP;			//�������
	GPIO_InitStructure.GPIO_PuPd	= GPIO_PuPd_NOPULL;		//������ ,Ҳ������
  GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_100MHz;	 
  GPIO_Init(ULTRA1_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin		= ECHO1_PIN;
  GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_IN;				//����
	GPIO_InitStructure.GPIO_PuPd	= GPIO_PuPd_DOWN;     //������,Ҳ������
  GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_100MHz;	 
  GPIO_Init(ULTRA1_PORT, &GPIO_InitStructure);
	
	RCC_AHB1PeriphClockCmd(ULTRA2_PORT_CLK, ENABLE); 

  GPIO_InitStructure.GPIO_Pin		= TRIG2_PIN;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_OUT;		  //���
	GPIO_InitStructure.GPIO_OType	= GPIO_OType_PP;      //�������
	GPIO_InitStructure.GPIO_PuPd	= GPIO_PuPd_NOPULL;   //������,Ҳ������
  GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_100MHz;	 
  GPIO_Init(ULTRA2_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin		= ECHO2_PIN ;
  GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_IN;		    //����
	GPIO_InitStructure.GPIO_PuPd	= GPIO_PuPd_DOWN;     //������,Ҳ������
  GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_100MHz;	 
  GPIO_Init(ULTRA2_PORT, &GPIO_InitStructure);

	RCC_AHB1PeriphClockCmd(ULTRA3_PORT_CLK, ENABLE); 

  GPIO_InitStructure.GPIO_Pin		= TRIG3_PIN;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_OUT;		  //���
	GPIO_InitStructure.GPIO_OType	= GPIO_OType_PP;      //�������
	GPIO_InitStructure.GPIO_PuPd	= GPIO_PuPd_NOPULL;   //������,Ҳ������
  GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_100MHz;	 
  GPIO_Init(ULTRA3_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin		= ECHO3_PIN;
  GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_IN;		    //����
	GPIO_InitStructure.GPIO_PuPd	= GPIO_PuPd_DOWN;     //������,Ҳ������
  GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_100MHz;	 
  GPIO_Init(ULTRA3_PORT, &GPIO_InitStructure);
	
	RCC_AHB1PeriphClockCmd(ULTRA4_PORT_CLK, ENABLE); 

  GPIO_InitStructure.GPIO_Pin		= TRIG4_PIN;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_OUT;		  //���
	GPIO_InitStructure.GPIO_OType	= GPIO_OType_PP;      //�������
	GPIO_InitStructure.GPIO_PuPd	= GPIO_PuPd_NOPULL;   //������,Ҳ������
  GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_100MHz;	 
  GPIO_Init(ULTRA4_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin		= ECHO4_PIN;
  GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_IN;		    //����
	GPIO_InitStructure.GPIO_PuPd	= GPIO_PuPd_DOWN;     //������,Ҳ������
  GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_100MHz;	
  GPIO_Init(ULTRA4_PORT, &GPIO_InitStructure);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);					//ʹ��SYSCFGʱ��
	
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource7);		//GPIOC.11
	
  EXTI_InitStructure.EXTI_Line 		= EXTI_LINE_ECHO1;
  EXTI_InitStructure.EXTI_Mode 		= EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;	//���崥��
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure); 
	
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource5);		//GPIOC.11
	
  EXTI_InitStructure.EXTI_Line 		= EXTI_LINE_ECHO2;
  EXTI_InitStructure.EXTI_Mode 		= EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;	//���崥��
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure); 
		
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource9);		//GPIOC.11
	
  EXTI_InitStructure.EXTI_Line 		= EXTI_LINE_ECHO3;
  EXTI_InitStructure.EXTI_Mode 		= EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;	//���崥��
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure); 

  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource11);	//GPIOC.11
	
  EXTI_InitStructure.EXTI_Line 		= EXTI_LINE_ECHO4;
  EXTI_InitStructure.EXTI_Mode 		= EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;	//���崥��
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure); 
}


/************************************************/
//�������ܣ��Զ����������GPIO��ʼ��������Ϊ�ⲿ�ж�
//���������
//����ֵ��
//��ע��
/************************************************/
void IR_Decoding_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;    
	EXTI_InitTypeDef EXTI_InitStructure;
	
	RCC_AHB1PeriphClockCmd(IRCODE_PORT_CLK, ENABLE);		
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);					//ע��Ҫ��SYSCFGʱ��	
	
	GPIO_InitStructure.GPIO_Pin 	= IRCODE_BL_PIN | IRCODE_BR_PIN;	//�������
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_IN;         					//����ģʽ
  GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP;         					//��������
 	GPIO_Init(IRCODE_PORT, &GPIO_InitStructure);        		 				//��ʼ�� �������˿�

	//�����ұ߽���GPIO
  SYSCFG_EXTILineConfig(EXIT_SOURCE_IRPORT, EXTI_SOURCE_IRBR);		//GPIOC.11
  EXTI_InitStructure.EXTI_Line 		= EXTI_LINE_IRBR;
  EXTI_InitStructure.EXTI_Mode 		= EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;	//���崥��
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure); 

  SYSCFG_EXTILineConfig(EXIT_SOURCE_IRPORT, EXTI_SOURCE_IRBL);		//GPIOA.15
  EXTI_InitStructure.EXTI_Line 		= EXTI_LINE_IRBL;
  EXTI_InitStructure.EXTI_Mode 		= EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;	//���崥��
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure); 
}


/************************************************/
//�������ܣ���ײGPIO��ʼ��
//���������
//����ֵ��
//��ע��
/************************************************/
void Crash_Gpio_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;    
	
	RCC_AHB1PeriphClockCmd(CRASH_FRONT_PORT_CLK, ENABLE);		

	GPIO_InitStructure.GPIO_Pin 	= CRASH_FRONT_PIN;		//ǰ��ײIO
  GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_IN;				//����
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP;				//���� 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 
  GPIO_Init(CRASH_FRONT_PORT, &GPIO_InitStructure);
	
	RCC_AHB1PeriphClockCmd(CRASH_BACK_PORT_CLK, ENABLE);		

	GPIO_InitStructure.GPIO_Pin 	= CRASH_BACK_PIN;			//ǰ��ײIO
  GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_IN;		    //����
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP;				//���� 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 
  GPIO_Init(CRASH_BACK_PORT, &GPIO_InitStructure);	
}
