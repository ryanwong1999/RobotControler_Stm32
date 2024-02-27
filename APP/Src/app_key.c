#include "includes.h" 

u8 KEY_Scan(u8 mode)
{	 
	static u8 key_null=1;	//�������ɿ���־
	if(mode) key_null=1;  //֧������		  
	if(key_null && (KEY_UP_READ==0 || KEY_DOWN_READ==0 || KEY_ENTER_READ==1))
	{
		delay_ms(10);//ȥ���� 
		key_null = 0;
		if(KEY_UP_READ==0) return KEY_UP_PRES;
		else if(KEY_DOWN_READ==0) return KEY_DOWN_PRES;
		else if(KEY_ENTER_READ==1) return KEY_ENTER_PRES; 
	}
	else if(KEY_UP_READ==1 && KEY_DOWN_READ==1 && KEY_ENTER_READ==0) key_null=1; 	     
	return 0;//�ް�������
}
