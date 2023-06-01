#include "includes.h" 

/*��һ·����*/
uint8_t  CH1_IrDa_STA = 0;    
uint16_t CH1_IrDa_VAL1 = 0;			// ͨ��1 �����ؼ���ֵ
uint16_t CH1_IrDa_VAL2 = 0;			// ͨ��1 �½��ؼ���ֵ
uint8_t  CH1_IrDa_Data = 0;			// ͨ��1 ���յ�������
/*����·����*/
uint8_t  CH3_IrDa_STA = 0;    
uint16_t CH3_IrDa_VAL1 = 0;			// ͨ��3 �����ؼ���ֵ
uint16_t CH3_IrDa_VAL2 = 0;			// ͨ��3 �½��ؼ���ֵ
uint8_t  CH3_IrDa_Data = 0;			// ͨ��3 ���յ�������

uint16_t BaseTimeCount = 0;			// 10us ʱ���׼���� 

/************************************************/
//�������ܣ��ⲿ�ж�����Ҫ�ļ�����
//���������
//����ֵ��
//��ע��
/************************************************/
void IR_Code_Delay10us(void)
{
	BaseTimeCount ++;
	if(BaseTimeCount >= 0xffff)
		BaseTimeCount = 0 ;
}


/************************************************/
//�������ܣ��ⲿ�ж�, �����Զ�������ı���
//���������
//����ֵ��
//��ע��
/************************************************/
void EXTI0_IRQHandler(void)
{
	uint16_t tmp ;
	
	if(EXTI_GetITStatus(EXTI_LINE_IRBL) != RESET){   	// Line6�����ж�
		if((CH1_IrDa_STA & 0x40) != 0x40){            	// û�в���������	0100 0000
			if((CH1_IrDa_STA & 0x20) != 0x20){          	// û�в���������	0010 0000
				if(GPIO_ReadInputDataBit(IRCODE_PORT,IRCODE_BL_PIN) == SET){  // �ߵ�ƽ
					CH1_IrDa_VAL1 = BaseTimeCount;
				  CH1_IrDa_STA |= 0x20;               			// ��ǲ���������	0010 0000				
				}
			}else{
				if(GPIO_ReadInputDataBit(IRCODE_PORT,IRCODE_BL_PIN) == RESET){  // �͵�ƽ �½�����
					CH1_IrDa_VAL2 = BaseTimeCount;
				  CH1_IrDa_STA &= 0xDF;               			// ������������ر�ǣ�������һ��	1101 1111
					if(CH1_IrDa_VAL2 < CH1_IrDa_VAL1){   			// �����
						tmp = 65535 + CH1_IrDa_VAL2 - CH1_IrDa_VAL1;
					}else{
						tmp = CH1_IrDa_VAL2 - CH1_IrDa_VAL1;
					}if(tmp >= 370 && tmp < 550){           	// 450*10us=4.5ms  4ms  4.5ms    ������
						CH1_IrDa_STA |= 0x40 ;            			// ��ǲ���������	0100 0000
						CH1_IrDa_Data = 0;
					}
				}
			}
		}else{         // ���յ�������
			if((CH1_IrDa_STA & 0x20) != 0x20){         		// û�в���������	0010 0000
				if(GPIO_ReadInputDataBit(IRCODE_PORT,IRCODE_BL_PIN) == SET){  // �ߵ�ƽ
					CH1_IrDa_VAL1 = BaseTimeCount;
					CH1_IrDa_STA |= 0x20;               			// ��ǲ���������
				}
			}else{
				if(GPIO_ReadInputDataBit(IRCODE_PORT,IRCODE_BL_PIN) == RESET){  // �͵�ƽ �½�����
					CH1_IrDa_VAL2 = BaseTimeCount;
					CH1_IrDa_STA &= 0xDF;               			// ������������ر�ǣ�������һ��	1101 1111
					if(CH1_IrDa_VAL2 < CH1_IrDa_VAL1){   			// �����
						tmp = 65535 + CH1_IrDa_VAL2 - CH1_IrDa_VAL1;
					}else{
						tmp = CH1_IrDa_VAL2 - CH1_IrDa_VAL1;
					}if(tmp >= 20 && tmp < 90){               // 56*10us=560us 
						CH1_IrDa_Data |= 0;	
					}else if(tmp >= 100 && tmp < 210){       	// 169*10us=1690us
						CH1_IrDa_Data |= 1;
					}else if(tmp >= 220 && tmp < 270){       	// 225*10us=2250us ����  δ����
						
					}else if(tmp >= 300 ){
						CH1_IrDa_STA = 0;            						// ���״̬�Ĵ��������½���						
					}
					if((CH1_IrDa_STA & 0x1F) >= 6){						//	0001 1111
						CH1_IrDa_STA = 0;
						if(CH1_IrDa_Data == TXDAT_LEFT){
							AutoCharge.CH1_IrDa_Dat[0] = TXDAT_LEFT;	
						}	else if(CH1_IrDa_Data == TXDAT_MIDL){
							AutoCharge.CH1_IrDa_Dat[1] = TXDAT_MIDL;	
						}	else if(CH1_IrDa_Data == TXDAT_RIGHT){
							AutoCharge.CH1_IrDa_Dat[2] = TXDAT_RIGHT;
						}else if(CH1_IrDa_Data == TXDAT_MIDR){
							AutoCharge.CH1_IrDa_Dat[3] = TXDAT_MIDR;	
						}
					}else{
						CH1_IrDa_STA ++ ;
						CH1_IrDa_Data <<= 1;
					}
				}
			}
		}
		EXTI_ClearITPendingBit(EXTI_LINE_IRBL);       // ���Lin6�жϱ�־λ
	}	
}


/************************************************/
//�������ܣ��ⲿ�ж�, �����Զ�������ı���
//���������
//����ֵ��
//��ע��
/************************************************/
void EXTI1_IRQHandler(void)
{
  uint16_t tmp;

	if(EXTI_GetITStatus(EXTI_LINE_IRBR) != RESET)	// Line6�����ж� EXTI_LINE_IRBR :EXTI_Line10
	{
		if((CH3_IrDa_STA & 0x40) != 0x40)						// û�в���������
		{
			if((CH3_IrDa_STA & 0x20) != 0x20)					// û�в���������
			{
				if(GPIO_ReadInputDataBit(IRCODE_PORT, IRCODE_BR_PIN) == SET)  // �ߵ�ƽ
				{
					CH3_IrDa_VAL1 = BaseTimeCount;
				  CH3_IrDa_STA |= 0x20;									// ��ǲ���������				
				}
			}
			else
			{
				if(GPIO_ReadInputDataBit(IRCODE_PORT, IRCODE_BR_PIN) == RESET)  // �͵�ƽ �½�����
				{
					CH3_IrDa_VAL2 = BaseTimeCount;
				  CH3_IrDa_STA &= 0xDF;									// ������������ر�ǣ�������һ��
					if(CH3_IrDa_VAL2 < CH3_IrDa_VAL1)			// �����
						tmp = 65535 + CH3_IrDa_VAL2 - CH3_IrDa_VAL1;
					else
						tmp = CH3_IrDa_VAL2 - CH3_IrDa_VAL1;
					if(tmp >= 370 && tmp < 550)
					{
						CH3_IrDa_STA |= 0x40 ;							// ��ǲ���������
						CH3_IrDa_Data = 0;
					}
				}
			}
		}
		else         																// ���յ�������
		{
			if((CH3_IrDa_STA & 0x20) != 0x20)					// û�в���������
			{
				if(GPIO_ReadInputDataBit(IRCODE_PORT, IRCODE_BR_PIN) == SET)  // �ߵ�ƽ
				{
					CH3_IrDa_VAL1 = BaseTimeCount;
					CH3_IrDa_STA |= 0x20;									// ��ǲ���������
				}
			}
			else
			{
				if(GPIO_ReadInputDataBit(IRCODE_PORT,IRCODE_BR_PIN) == RESET)  // �͵�ƽ �½�����
				{
					CH3_IrDa_VAL2 = BaseTimeCount;
					CH3_IrDa_STA &= 0xDF;									// ������������ر�ǣ�������һ��
					if(CH3_IrDa_VAL2 < CH3_IrDa_VAL1)			// �����
						tmp = 65535 + CH3_IrDa_VAL2 - CH3_IrDa_VAL1;
					else
						tmp = CH3_IrDa_VAL2 - CH3_IrDa_VAL1;
					if(tmp >= 20 && tmp < 100)						// 56*10us=560us 
						CH3_IrDa_Data |= 0;
					else if(tmp >= 100 && tmp < 220)			// 169*10us=1690us
						CH3_IrDa_Data |= 1;
//					else if(tmp >= 230 && tmp < 270)			// 225*10us=2250us ����  δ����
					else if(tmp >= 300)
						CH3_IrDa_STA = 0;										// ���״̬�Ĵ��������½���						
					if((CH3_IrDa_STA & 0x1F) >= 6){
						CH3_IrDa_STA = 0;										// ����ͷ�������һ�ν���
						if(CH3_IrDa_Data == TXDAT_LEFT)
							AutoCharge.CH3_IrDa_Dat[0] = TXDAT_LEFT;	
						else if(CH3_IrDa_Data == TXDAT_MIDL)
							AutoCharge.CH3_IrDa_Dat[1] = TXDAT_MIDL;	
						else if(CH3_IrDa_Data == TXDAT_RIGHT)
							AutoCharge.CH3_IrDa_Dat[2] = TXDAT_RIGHT;	
						else if(CH3_IrDa_Data == TXDAT_MIDR)
							AutoCharge.CH3_IrDa_Dat[3] = TXDAT_MIDR;	
					}
					else
					{
						CH3_IrDa_STA ++ ;
						CH3_IrDa_Data <<= 1;
					}
				}
			}
		}
		EXTI_ClearITPendingBit(EXTI_LINE_IRBR);			// ���Lin6�жϱ�־λ EXTI_LINE_IRBR :EXTI_Line10
	}
}


/************************************************/
//�������ܣ��ⲿ�ж�
//���������
//����ֵ��
//��ע��
/************************************************/
void EXTI2_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line2) != RESET)   // Line12�����ж�
		EXTI_ClearITPendingBit(EXTI_Line2);       // ���Lin6�жϱ�־λ
}


/************************************************/
//�������ܣ��ⲿ�ж�
//���������
//����ֵ��
//��ע��
/************************************************/
void EXTI4_IRQHandler(void)
{
	uint16_t tmp;
  static uint16_t ultra3_val1 = 0;
	static uint16_t ultra3_val2 = 0;
	if(EXTI_GetITStatus(EXTI_Line4) != RESET)   // Line12�����ж�
		EXTI_ClearITPendingBit(EXTI_Line4);       // ���Lin6�жϱ�־λ
}


/************************************************/
//�������ܣ��ⲿ�ж�,��ȡ����Ultra1��Ultra2��Ultra3�ľ���
//���������
//����ֵ��
//��ע��
/************************************************/
void EXTI9_5_IRQHandler(void)
{
	uint16_t tmp;
	static uint16_t ultra1_val1 = 0;
	static uint16_t ultra1_val2 = 0;
	static uint16_t ultra2_val1 = 0;
	static uint16_t ultra2_val2 = 0;
	static uint16_t ultra3_val1 = 0;
	static uint16_t ultra3_val2 = 0;
	
	if(EXTI_GetITStatus(EXTI_Line5) != RESET)   // Line12�����ж�
	{
//		if((Ultra2.Uswave_Sta &0x20) ==0x20)			// �Ѿ�ʹ�ܳ��������ݲ���
//		{
//			if((Ultra2.Uswave_Sta &0x80)!=0x80)			// ����û�н������
//			{
//				if((Ultra2.Uswave_Sta &0x40)!=0x40)		// û�в���������
//				{
//					if( ECHO_READ_2 == SET)							// �ߵ�ƽ
//					{
//						ultra2_val1 =BaseTimeCount;
//						Ultra2.Uswave_Sta |= 0x40;				// ��ǲ���������	
//					}
//				}
//				else                                 	// �����������ˣ��жϲ����½���
//				{
//					if(ECHO_READ_2 == RESET)						// �͵�ƽ �½�����
//					{
//						ultra2_val2 = BaseTimeCount;
//						if(ultra2_val2 < ultra2_val1)     // ���������
//							tmp= 65535 + ultra2_val2 - ultra2_val1;
//						else
//							tmp= ultra2_val2 - ultra2_val1;
//						Ultra2.Distance = tmp*50/29;    	// �ϰ������  mm
//						if(Ultra2.Distance>2000) Ultra2.Distance = 2000;
//						Ultra2.Uswave_Sta &= 0x0F;				// ���ʹ�ܽ�������
//						Ultra2.Uswave_Sta |=0x80;					// ���ݽ������
//					  Ultra2.Out_time = 0;
//					}
//				}
//			}
//		}
//		EXTI_ClearITPendingBit(EXTI_Line5);       // ���Lin6�жϱ�־λ
//	}

//	if(EXTI_GetITStatus(EXTI_Line7) != RESET)   // Line12�����ж�
//	{
//		if((Ultra1.Uswave_Sta &0x20) ==0x20)			// �Ѿ�ʹ�ܳ��������ݲ���
//		{
//			if((Ultra1.Uswave_Sta &0x80)!=0x80)			// ����û�н������
//			{
//				if((Ultra1.Uswave_Sta &0x40)!=0x40)		// û�в���������
//				{
//					if( ECHO_READ_1 == SET)       			// �ߵ�ƽ
//					{
//						ultra1_val1 =BaseTimeCount;
//						Ultra1.Uswave_Sta |= 0x40;				// ��ǲ���������	
//					}
//				}
//				else                                 	// �����������ˣ��жϲ����½���
//				{
//					if( ECHO_READ_1 == RESET)     			// �͵�ƽ �½�����
//					{
//						ultra1_val2 = BaseTimeCount;
//						if(ultra1_val2 < ultra1_val1)     // ���������
//							tmp= 65535 + ultra1_val2 - ultra1_val1;
//						else
//							tmp= ultra1_val2 - ultra1_val1;
//						Ultra1.Distance = tmp*50/29;  		// �ϰ������  mm
//						if(Ultra1.Distance>2000) Ultra1.Distance = 2000;
//						Ultra1.Uswave_Sta &= 0x0F;				// ���ʹ�ܽ�������
//						Ultra1.Uswave_Sta |=0x80;					// ���ݽ������
//					  Ultra1.Out_time = 0;
//					}
//				}
//			}
//		}
		EXTI_ClearITPendingBit(EXTI_Line7);       // ���Lin6�жϱ�־λ
	}
	
	if(EXTI_GetITStatus(EXTI_Line9) != RESET)   // Line12�����ж�
	{
//   if((Ultra3.Uswave_Sta &0x20) ==0x20)				// �Ѿ�ʹ�ܳ��������ݲ���
//		{
//			if((Ultra3.Uswave_Sta &0x80)!=0x80)			// ����û�н������
//			{
//				if((Ultra3.Uswave_Sta &0x40)!=0x40)		// û�в���������
//				{
//					if(ECHO_READ_3 == SET)       				// �ߵ�ƽ
//					{
//						ultra3_val1 =BaseTimeCount;
//						Ultra3.Uswave_Sta |= 0x40;				// ��ǲ���������	
//					}
//				}
//				else                                 	// �����������ˣ��жϲ����½���
//				{
//					if(ECHO_READ_3 == RESET)     				// �͵�ƽ �½�����
//					{
//						ultra3_val2 = BaseTimeCount;
//						if(ultra3_val2 < ultra3_val1)     // ���������
//							tmp= 65535 + ultra3_val2 - ultra3_val1;
//						else
//							tmp= ultra3_val2 - ultra3_val1;
//						Ultra3.Distance = tmp*50/29;    	// �ϰ������  mm
////						printf("Ultra3.Distance = %d\r\n",Ultra3.Distance);
//						if(Ultra3.Distance>2000) Ultra3.Distance = 2000;
//						Ultra3.Uswave_Sta &= 0x0F;				// ���ʹ�ܽ�������
//						Ultra3.Uswave_Sta |=0x80;					// ���ݽ������
//					  Ultra3.Out_time = 0;
//					}
//				}
//			}
//		}
		EXTI_ClearITPendingBit(EXTI_Line9);       // ���Lin6�жϱ�־λ
	}
}


/************************************************/
//�������ܣ��ⲿ�ж�,��ȡ����Ultra4�ľ���
//���������
//����ֵ��
//��ע��
/************************************************/
void  EXTI15_10_IRQHandler(void)
{
	uint16_t tmp ;
	static uint16_t ultra4_val1 = 0;
	static uint16_t ultra4_val2 = 0;
	static uint16_t ultra5_val1 = 0;
	static uint16_t ultra5_val2 = 0;
	static uint16_t ultra6_val1 = 0;
	static uint16_t ultra6_val2 = 0;
	
	if(EXTI_GetITStatus(EXTI_Line11) != RESET)		// Line12�����ж�
	{
//		if((Ultra4.Uswave_Sta &0x20) ==0x20)				// �Ѿ�ʹ�ܳ��������ݲ���
//		{
//			if((Ultra4.Uswave_Sta &0x80)!=0x80)				// ����û�н������
//			{
//				if((Ultra4.Uswave_Sta &0x40)!=0x40)			// û�в���������
//				{
//					if(ECHO_READ_4 == SET)       					// �ߵ�ƽ
//					{
//						ultra4_val1 =BaseTimeCount;
//						Ultra4.Uswave_Sta |= 0x40;					// ��ǲ���������	
//					}
//				}
//				else                                 		// �����������ˣ��жϲ����½���
//				{
//					if(ECHO_READ_4 == RESET)     					// �͵�ƽ �½�����
//					{
//						ultra4_val2 = BaseTimeCount;
//						if(ultra4_val2 < ultra4_val1)     	// ���������
//							tmp= 65535 + ultra4_val2 - ultra4_val1;
//						else
//							tmp= ultra4_val2 - ultra4_val1;
//						Ultra4.Distance = tmp*50/29;    		// �ϰ������  mm  
//						if(Ultra4.Distance>2000) Ultra4.Distance = 2000;
//						Ultra4.Uswave_Sta &= 0x0F;					// ���ʹ�ܽ�������
//						Ultra4.Uswave_Sta |=0x80;						// ���ݽ������
//					  Ultra4.Out_time = 0;
//					}
//				}
//			}
//		}
		EXTI_ClearITPendingBit(EXTI_Line11);       // ���Lin6�жϱ�־λ
	}
}
