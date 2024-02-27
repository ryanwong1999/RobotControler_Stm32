#include "includes.h" 

u8 KEY_Scan(u8 mode)
{	 
	static u8 key_null=1;	//按键按松开标志
	if(mode) key_null=1;  //支持连按		  
	if(key_null && (KEY_UP_READ==0 || KEY_DOWN_READ==0 || KEY_ENTER_READ==1))
	{
		delay_ms(10);//去抖动 
		key_null = 0;
		if(KEY_UP_READ==0) return KEY_UP_PRES;
		else if(KEY_DOWN_READ==0) return KEY_DOWN_PRES;
		else if(KEY_ENTER_READ==1) return KEY_ENTER_PRES; 
	}
	else if(KEY_UP_READ==1 && KEY_DOWN_READ==1 && KEY_ENTER_READ==0) key_null=1; 	     
	return 0;//无按键按下
}
