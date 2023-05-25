#ifndef __APP_AUTOCHARGE_H
#define __APP_AUTOCHARGE_H

#include "includes.h"	

#define TXDAT_LEFT    			0x50      //左边解码数据	0101 0000
#define TXDAT_MIDL    			0x0C      //中间解码数据	0000 1100
#define TXDAT_RIGHT   			0x02      //右边解码数据	0000 0010
#define TXDAT_MIDR   				0x0A      //右边解码数据	0000 1010

#define POSITION_NULL   		0 	
#define POSITION_MID    		1
#define POSITION_LEFT   		2
#define POSITION_RIGHT  		3	 
#define POSITION_IR     		4

#define CHG_MOVE_FORWARD    5
#define CHG_MOVE_LEFT       7	 
#define CHG_MOVE_ZEROLEFT 	2	 
#define CHG_MOVE_RIGHT      3	 
#define CHG_MOVE_ZERORIGHT	6	 
#define CHG_MOVE_BACKWARD   1
#define CHG_MOVE_STOP       0

typedef struct {
  uint8_t CH1_IrDa_Dat[4];
  uint8_t CH2_IrDa_Dat[4];
	uint8_t CH3_IrDa_Dat[4];
	uint8_t CH_IrDate[7];
	bool StopChg_flag;
	bool AutoChg_Cmd;
	bool NotFind_Flag;
	bool StartUp_Flag;
	bool ReChg_flag;
	uint8_t Chg_Sta;
	uint8_t Position;
	uint8_t Last_Position;
	uint16_t Loop_Tim;
	uint32_t OverTime;
	uint16_t Time_out;
	uint8_t Move_Sta;
	uint8_t No_Sigh_Flag;
  int16_t set_lear;
  int16_t set_angle;
	uint8_t chg_flag;
	int16_t left_pulse;
	int16_t right_pulse;
	uint8_t ultra_flag;
	int16_t distance;
	int16_t angle;
	uint8_t chg_fail;
	uint8_t rechg_cnt;
}Charge_typedef;

extern Charge_typedef AutoCharge;

void Charge_Init(void);
void Charge_Tim1ms(void);
void AutoCharge_Processing(void);
void Charge_IRCode_Process(uint8_t _move_sta);
void AutoCharge_move( uint8_t Move_sta); 
void Chg_Position_Judge(void);
void Chg_Last_Position_Judge(void);
void chg_move_forward_Process(void);
void chg_move_right_process(void);
void chg_move_left_process(void);
void chg_move_zeroright_process(void);
void chg_move_zeroleft_process(void);
void Charge_OverTime_Process(void);
void Charge_Crash_Pross(void);
void Get_Charger_Code(void);

#endif 