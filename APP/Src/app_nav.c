#include "includes.h" 

//����ȫ�ֱ���
float g_x = 0;       	//�����˵�ȫ��x����
float g_y = 0;       	//�����˵�ȫ��y����
float totle_radian;		//�����˵��ۻ��Ƕ�

//����������
int16_t left_pulse = 0;
int16_t right_pulse = 0;

//����������
float gyro_angle = 0;

//EKF״̬������Э�������
float X[3] = {0};    	//[x, y, theta]
float P[3][3] = {0}; 	//״̬Э�������

