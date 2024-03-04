#ifndef __APP_IMU_H
#define __APP_IMU_H

#include "wt901.h"

extern struct STime			stcTime;  
extern struct SAcc 			stcAcc;
extern struct SGyro 		stcGyro;
extern struct SAngle 		stcAngle;
extern struct SMag 			stcMag;
extern struct SDStatus	stcDStatus;
extern struct SPress 		stcPress;
extern struct SLonLat 	stcLonLat;
extern struct SGPSV 		stcGPSV;
extern struct SQ       	stcQ;

void imu_accalsw(void);
void imu_savacalsw(void);

	
#endif 