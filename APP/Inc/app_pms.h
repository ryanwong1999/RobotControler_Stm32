#ifndef __APP_PMS_H
#define __APP_PMS_H

#include "includes.h"	

#define FELI8S		1
//#define FELI5S		1
//#define PB24V			1 

#ifdef  FELI8S	
#define FULL_CAP		14000   //LiFe 8S4P 24V 14.4Ah
#define EMPTY_VOL		21600   //LiFe 8S4P 24V 14.4Ah
#define FULL_VOL		28000   //LiFe 8S4P 24V 14.4Ah 
#elif  FELI5S
#define FULL_CAP		21000   //LiFe 5S8P 18V 21Ah
#define EMPTY_VOL 	14500   //LiFe 5S8P 18V 21Ah
#define FULL_VOL 		17500   //LiFe 5S8P  18V 21Ah  
#elif PB24V
#define FULL_CAP		20000   //acid_lead 24V 20Ah
#define EMPTY_VOL 	21000   //acid_lead 24V 20Ah
#define FULL_VOL 		26800   //acid_lead 24V 20Ah 
#endif

#define EMPTY_CAP		150

typedef struct 
{
	uint16_t Bat_Voltage;		//battery voltage
	int16_t Bat_Current;		//battery current
	uint16_t Input_Voltage;	//charge input voltage
	uint16_t Moto_Voltage;
	uint16_t LiftMoto_Cur;
	uint16_t Moto_Cur;
	uint8_t Capacity;				//battery capacity
	uint16_t Capacity_mah;
	uint16_t Capacity_Set;
  uint8_t PMS_Sta;
	uint8_t PowerOff_Sta;
	uint8_t Bat_Sta;
  uint8_t Low_Flag;
	uint8_t Reset_Flag;			//�Զ�У׼��־λ
}PMS_Typedef;

extern PMS_Typedef Pms;

void Read_PMUData(void);
void Capacity_Init(void);
uint8_t Get_Batt_Capacity(int16_t _bat_cur,uint16_t _bat_vol);

#endif 