#ifndef __APP_EXIT_H
#define __APP_EXIT_H

#include "includes.h"	

/********************************************************
 红外输入状态
********************************************************/

extern uint8_t CH1_IrDa_STA;
extern uint8_t CH1_IrDa_Data;
extern uint8_t CH2_IrDa_STA;
extern uint8_t CH2_IrDa_Data;
extern uint8_t CH3_IrDa_STA;
extern uint8_t CH3_IrDa_Data;

extern uint16_t BaseTimeCount;	// 10us 时间基准计数 

void IR_Code_Delay10us(void);
void IRObstacle_GPIO_EN_Init(void);
void IRObstacle_GPIO_Cfg_Init(void);
void IRBackward_Decoding_GPIO_Cfg_Init(void);
void IRForward_Decoding_GPIO_Cfg_Init(void);
void Send_Charge_Code(void);

#endif 