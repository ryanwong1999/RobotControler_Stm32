#include "includes.h" 

PMS_Typedef Pms;

/************************************************/
//�������ܣ���ȡPMS����
//���������
//����ֵ��
//��ע��
/************************************************/
void Read_PMUData(void)	
{
	static uint8_t low_cnt = 0;
	
	Pms.Bat_Voltage = ADC_Filter_Value[0] * 10;   				//iBat_Vol = After_filter[0] *3.3 * 6 * 1000/4096 ,??1mV
	Pms.Input_Voltage = ADC_Filter_Value[2] * 10 + 500;  	//iChg_Vol = After_filter[0] *3.3 * 6 * 1000/4096 mV
	Pms.Moto_Voltage = ADC_Filter_Value[1] * 10;
	Pms.LiftMoto_Cur = ADC_Filter_Value[4] * 3.125;   		//ma
	Pms.Moto_Cur = ADC_Filter_Value[5] * 31.25;      			//ma
	
  if(abs(ADC_Filter_Value[3] - 2000) < 5)
	  Pms.Bat_Current = 0;
	else
		Pms.Bat_Current = (ADC_Filter_Value[3] - 2000) * 18.75;		//��ص���
	
	Pms.Capacity = Get_Batt_Capacity(Pms.Bat_Current, Pms.Bat_Voltage);		//����������
	
	if(Pms.Capacity <= 20) Pms.Bat_Sta |= 0x10;		//������
	else Pms.Bat_Sta &= 0xef;		//1110 1111
	 
  if(Pms.Bat_Voltage < EMPTY_VOL){
		low_cnt ++;
		if(low_cnt > 30){
			Pms.Low_Flag = 1;
		}
	}else{
		low_cnt = 0;
		Pms.Low_Flag = 0;
	}
}


/************************************************/
//�������ܣ�����������
//�����������ص�������ص�ѹ
//����ֵ���������
//��ע��
/************************************************/
uint8_t Get_Batt_Capacity(int16_t _bat_cur,uint16_t _bat_vol)
{
	static uint32_t voltage_sum = 0;
	static int32_t current_sum = 0;
	static int8_t voltage_cnt = 0;
	static uint32_t vol_tmp;
	static int32_t cur_tmp;
	static uint8_t first = 0;
	static uint8_t  min_cnt = 0;
	static uint32_t batt_cap;
	
	if(first == 0){		//���ν���
		first = 1;
		batt_cap = Pms.Capacity_mah /(Pms.Capacity_Set/100);
	}
	voltage_cnt ++;     //1��1��
	voltage_sum += _bat_vol;
	current_sum += _bat_cur;
	if(voltage_cnt >= 60)
	{
		vol_tmp = voltage_sum/60;		//1���ӵ�ƽ��ֵ
	  cur_tmp = current_sum/60;		//1���ӵ�ƽ��ֵ
		
		if(cur_tmp < 0 && Pms.Capacity_mah < abs(cur_tmp/60))
			Pms.Capacity_mah = 0;
		else
			Pms.Capacity_mah += cur_tmp/60;
		//�жϿ�ʼ����ʱ���ѹ����20%��ֱ������
		if(vol_tmp <= 25040 && (Pms.Bat_Sta & 0x11) != 0) Pms.Reset_Flag = 1;		//�Զ�У׼������־λ��1
		
		//�ǳ����û����
		if(vol_tmp < EMPTY_VOL && (Pms.Bat_Sta & 0x01) == 0) Pms.Capacity_mah = EMPTY_CAP;
		//�����������
		else if(vol_tmp > FULL_VOL && (Pms.Bat_Sta & 0x01) != 0 && cur_tmp < 800)		
		{
			if(Pms.Reset_Flag == 1 && Pms.Capacity_mah <= Pms.Capacity_Set && Pms.Capacity_mah >= 10000)
			{
				Pms.Capacity_Set = Pms.Capacity_mah;
				//��У׼��ֵдat24c02
				AT24CXX_WriteOneByte(2,(Pms.Capacity_Set>>8) & 0x00ff);
				AT24CXX_WriteOneByte(3,Pms.Capacity_Set& 0x00ff);
			}
			else Pms.Capacity_mah = Pms.Capacity_Set;
			Pms.Reset_Flag = 0;
		}
		else if(Pms.Capacity_mah >= Pms.Capacity_Set) 
			Pms.Capacity_mah = Pms.Capacity_Set;
		else if(Pms.Capacity_mah <= EMPTY_CAP) //û����
			Pms.Capacity_mah = EMPTY_CAP;
		else 
			Pms.Capacity_mah = Pms.Capacity_mah;
		//û���������ˣ�����У׼ʧ��
		if(vol_tmp < FULL_VOL && (Pms.Bat_Sta & 0x01) == 0) Pms.Reset_Flag = 0;		
				
		batt_cap = Pms.Capacity_mah/(Pms.Capacity_Set/100);
		
		#ifdef FELI8S
		//���ݵ�ѹУ׼��أ��ŵ����С��2A
		if(batt_cap > 20 && vol_tmp <= 25040 && cur_tmp >= -2000)		
		{
			Pms.Capacity_mah = 2400;
			batt_cap = 20;
		}
		if(batt_cap > 5 && vol_tmp <= 22400 && cur_tmp >= -2000)
		{
			Pms.Capacity_mah = 600;
			batt_cap = 5;
		}
		#endif
		voltage_sum = 0;
		voltage_cnt = 0;
		current_sum = 0;
	}
	return (uint8_t)batt_cap;
}


/************************************************/
//�������ܣ����������ʼ��
//���������
//����ֵ��
//��ע��
/************************************************/
void Capacity_Init(void)
{
	Pms.Bat_Voltage =  ADC_Filter_Value[0] * 10;
	#ifdef FELI8S
	if(Pms.Bat_Voltage < 24400) Pms.Capacity = 5;
	else if(Pms.Bat_Voltage < 25040) Pms.Capacity = 20;
	else if(Pms.Bat_Voltage < 26000) Pms.Capacity = 50;
	else if(Pms.Bat_Voltage < 27000) Pms.Capacity = 75; 
	else Pms.Capacity = 90;
	#elif FELI5S
	if(Pms.Bat_Voltage <  15500) Pms.Capacity = 20;
	else if(Pms.Bat_Voltage < 16500) Pms.Capacity = 50;
	else if(Pms.Bat_Voltage < 16800) Pms.Capacity = 75; 
  else Pms.Capacity = 90;
  #endif
}

