#include "includes.h" 

Sys_Type   			Robot_Sys;
Odom_Data_type  Moto_Odom;    // 里程数据
Moto_Typedef  	Robot_Moto;

void  Send_Head_Pose(uint8_t index, uint8_t addr, HeadPose_Type mHead_Pose, bool stop_key);
void  Send_PowerDataUpdata(uint8_t index, uint8_t addr, Power_Type mPower);

void Send_LiftMoto_Mess(uint8_t index, uint8_t addr,LiftMoto_Type *_liftmoto);

uint8_t gUpdateCnt = 0;
uint8_t gPscCnt = 0;