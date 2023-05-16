#include "includes.h" 

uint16_t ADC_Filter_Value[CHAN_NUM];      //��Ŵ�������
uint16_t AD_Value[SAMPLE_NUM][CHAN_NUM]; //�������ADCת�������Ҳ��DMA��Ŀ���ַ


//ADC GPIO��ʼ������
static void ADC_GOIO_Cfg_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(ADC_PORT_CLK, ENABLE);
	
  GPIO_InitStructure.GPIO_Pin = VIN_PIN | VBAT_PIN  | STOPSW_PIN | IDRV_PIN;	 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;	                      //ADCģʽ������ģ������
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;                   //����������
	GPIO_Init(ADC_PORT, &GPIO_InitStructure);  
	
	RCC_AHB1PeriphClockCmd(ADC1_PORT_CLK, ENABLE);
	
  GPIO_InitStructure.GPIO_Pin = IBAT_PIN | ILIFT_PIN;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;	                     
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;                  
	GPIO_Init(ADC1_PORT, &GPIO_InitStructure);  
}


//ADC DMA��ʼ������
void ADC_DMA_Cfg_Init(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);    //DMA2ʱ��ʹ��
	
	while(DMA_GetCmdStatus(DMA2_Stream0) != DISABLE){;}       //�ȴ�DMA��������

  DMA_InitStructure.DMA_Channel							= DMA_Channel_0;										//DMAͨ��0 
	DMA_InitStructure.DMA_PeripheralBaseAddr	= (uint32_t)&ADC1->DR;        			//�����ַ
	DMA_InitStructure.DMA_Memory0BaseAddr			= (uint32_t)&AD_Value;							//��ȡ����ַ  
  DMA_InitStructure.DMA_DIR									= DMA_DIR_PeripheralToMemory;				//��������赽�ڴ�     
  DMA_InitStructure.DMA_BufferSize					= SAMPLE_NUM*CHAN_NUM;							//���ݴ��������
  DMA_InitStructure.DMA_PeripheralInc				= DMA_PeripheralInc_Disable;				//��ַ������
  DMA_InitStructure.DMA_MemoryInc						= DMA_MemoryInc_Enable;							//��ַ����
  DMA_InitStructure.DMA_PeripheralDataSize 	= DMA_PeripheralDataSize_HalfWord;	//�������ݳ��Ȱ���,16λ
  DMA_InitStructure.DMA_MemoryDataSize 			= DMA_PeripheralDataSize_HalfWord;	//�洢���Ȱ��� 16λ
  DMA_InitStructure.DMA_Mode 								= DMA_Mode_Circular;								//�����ж�,����һ��ģʽ,�������ж�,��ѭ��ģʽ
  DMA_InitStructure.DMA_Priority 						= DMA_Priority_High;								//���ȼ�
  DMA_InitStructure.DMA_FIFOMode 						= DMA_FIFOMode_Disable;							//��ֹFIFO    
  DMA_InitStructure.DMA_FIFOThreshold 			= DMA_FIFOThreshold_HalfFull;				//FIFO��ֵ
  DMA_InitStructure.DMA_MemoryBurst 				= DMA_MemoryBurst_Single;						//���δ���
  DMA_InitStructure.DMA_PeripheralBurst 		= DMA_PeripheralBurst_Single;				//���δ���
  DMA_Init(DMA2_Stream0, &DMA_InitStructure); 
	
  DMA_Cmd(DMA2_Stream0, ENABLE); 									//DMA2_Stream0 enable 
  DMA_ClearFlag(DMA2_Stream0, DMA_IT_TC);    			//���жϱ�־λ
  DMA_ITConfig(DMA2_Stream0, DMA_IT_TC,ENABLE); 	//ʹ���ж�
}


//ADC��ʼ������
void ADC_Cfg_Init(void)
{
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_InitTypeDef       ADC_InitStructure;

	RCC_APB2PeriphClockCmd(ADC_CLK, ENABLE);  
	
	ADC_GOIO_Cfg_Init();		//����ADC_GPIO
  ADC_DMA_Cfg_Init();			//����ADC DMA
	 
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1, ENABLE);	   
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1, DISABLE);		 
	
	ADC_CommonInitStructure.ADC_DMAAccessMode 		= ADC_DMAAccessMode_Disabled;			//DMAʧ��
	ADC_CommonInitStructure.ADC_Mode 							= ADC_Mode_Independent;						//����ģʽ
	ADC_CommonInitStructure.ADC_Prescaler 				= ADC_Prescaler_Div4;							//APB2��4��Ƶ ��84/4=21M
	ADC_CommonInitStructure.ADC_TwoSamplingDelay 	= ADC_TwoSamplingDelay_5Cycles;		//���������׶ε���ʱ5��ʱ��
	ADC_CommonInit(&ADC_CommonInitStructure);																				//��ʼ��

	ADC_InitStructure.ADC_Resolution  					  = ADC_Resolution_12b;							//12λģʽ
	ADC_InitStructure.ADC_ScanConvMode 					  = ENABLE;													//ɨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode		  = ENABLE;													//����ת��
	ADC_InitStructure.ADC_ExternalTrigConvEdge 	  = ADC_ExternalTrigConvEdge_None;	//��ֹ������� ʹ���������
	ADC_InitStructure.ADC_DataAlign 						  = ADC_DataAlign_Right;						//�Ҷ���
	ADC_InitStructure.ADC_NbrOfConversion 			  = CHAN_NUM;												//2ͨ�� 1
	ADC_Init(ADC1,&ADC_InitStructure);                                            	//��ʼ��
 
  ADC_Cmd(ADC1, ENABLE);   //ʹ��ADC����
	 
	ADC_RegularChannelConfig(ADC1, VBAT_CH, 	1, ADC_SampleTime_144Cycles);
	ADC_RegularChannelConfig(ADC1, STOPSW_CH, 2, ADC_SampleTime_144Cycles);
	ADC_RegularChannelConfig(ADC1, VIN_CH, 		3, ADC_SampleTime_144Cycles);
	ADC_RegularChannelConfig(ADC1, IBAT_CH, 	4, ADC_SampleTime_144Cycles);
	ADC_RegularChannelConfig(ADC1, ILIFT_CH, 	5, ADC_SampleTime_144Cycles);
	ADC_RegularChannelConfig(ADC1, IDRV_CH, 	6, ADC_SampleTime_144Cycles);
	
	ADC_SoftwareStartConv(ADC1);    //�������ת��
	ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE); //Դ���ݱ仯ʱ����DMA����
  ADC_DMACmd(ADC1, ENABLE);   		//ʹ��ADC DMA����
}


//ADC����ֵ����
void filter(void)
{
	static u32 sum = 0;
  u8 ch_num = 0;    		// ͨ����
  u8 ave_num;        		// ����ƽ����
	
	for(ch_num=0;ch_num<CHAN_NUM;ch_num++)
	{
		for (ave_num=0;ave_num<SAMPLE_NUM;ave_num++)
    {
      sum += AD_Value[ave_num][ch_num];
		}
		ADC_Filter_Value[ch_num]=sum/SAMPLE_NUM;   
    sum=0;
	}
}


//ADC DMA�ж�ֵ����
void DMA2_Stream0_IRQHandler(void) 
{
	if(DMA_GetITStatus(DMA2_Stream0, DMA_IT_TCIF0))
  {
     DMA_ClearITPendingBit(DMA2_Stream0, DMA_IT_TCIF0);
     filter();
  } 
}
