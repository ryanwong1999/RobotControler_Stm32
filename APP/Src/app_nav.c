#include "includes.h" 

//定义全局变量
float g_x = 0;       	//机器人的全局x坐标
float g_y = 0;       	//机器人的全局y坐标
float totle_radian;		//机器人的累积角度

//编码器数据
int16_t left_pulse = 0;
int16_t right_pulse = 0;

//陀螺仪数据
float gyro_angle = 0;

//EKF状态向量和协方差矩阵
float X[3] = {0};    	//[x, y, theta]
float P[3][3] = {0}; 	//状态协方差矩阵

