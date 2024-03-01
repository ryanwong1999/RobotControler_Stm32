#include "includes.h" 

int8_t selectItem = 0;		//当前菜单在当前菜单页的索引，最大为3，一页最多显示四个菜单
int8_t scrollBar  = 0;		//滚动条
struct Menu_t *menuPoint;	//当前菜单
struct Menu_t *menuLast;

//拿来做测试的数据
int8_t kp = 0;
int8_t ki = 0;
int8_t kd = 0;
int16_t count_test = 0;
uint16_t count1 = 0, count2 = 2, count3 = 4, count4 = 6, count5 = 8;

//int fontColor = WHITE;
//int backColor = BLACK;

//一些菜单的功能函数
void KpSub(void);
void KiAdd(void);
void KdAdd(void);
void KpAdd(void);
void HourAdd(void);
void MinuteAdd(void);
void SecondAdd(void);
void YearAdd(void);
void MonthAdd(void);
void DayAdd(void);
void TimeOK(void);
void TimeSetInit(void);

//主UI
struct MenuProperty_t MainUIProperty = {1, 0};
struct Menu_t MainUI =
{&MainUIProperty, "MainUI", NULL, NULL, NULL};

//主菜单
struct MenuProperty_t menuMainProperty = {4, 0};
struct Menu_t menuMain[4] =
{
	{&menuMainProperty,"last menu     ", NULL, NULL, &MainUI, NULL},
	{&menuMainProperty,"Imu        		", NULL, NULL, &MainUI, NULL},
	{&menuMainProperty,"Pid           ", NULL, NULL, &MainUI, NULL},
	{&menuMainProperty,"Time set      ", NULL, TimeSetInit, &MainUI, NULL}
};
//imu的子菜单
struct MenuProperty_t setMenu1Property = {14, 10};
struct Menu_t setMenu1[14] =
{
	{&setMenu1Property, "last menu     ", NULL, NULL, menuMain, NULL},
	{&setMenu1Property, "Acc	 0			 ", NULL, NULL, menuMain, NULL},
	{&setMenu1Property, "       			 ", NULL, NULL, menuMain, NULL},
	{&setMenu1Property, "       			 ", NULL, NULL, menuMain, NULL},
	{&setMenu1Property, "Gyro  0       ", NULL, NULL, menuMain, NULL},
	{&setMenu1Property, "       			 ", NULL, NULL, menuMain, NULL},
	{&setMenu1Property, "       			 ", NULL, NULL, menuMain, NULL},
	{&setMenu1Property, "Angle 0			 ", NULL, NULL, menuMain, NULL},
	{&setMenu1Property, "       			 ", NULL, NULL, menuMain, NULL},
	{&setMenu1Property, "       			 ", NULL, NULL, menuMain, NULL},
	{&setMenu1Property, "Quat	 0			 ", NULL, NULL, menuMain, NULL},
	{&setMenu1Property, "       			 ", NULL, NULL, menuMain, NULL},
	{&setMenu1Property, "       			 ", NULL, NULL, menuMain, NULL},
	{&setMenu1Property, "       			 ", NULL, NULL, menuMain, NULL}
};
//Pid的子菜单
struct MenuProperty_t setMenu2Property = {5, 1};
struct Menu_t setMenu2[5] =
{
	{&setMenu2Property, "last menu      ", NULL, 	NULL, 	menuMain, NULL},
	{&setMenu2Property, "KP   0         ", KpSub,	KpAdd,	menuMain, NULL},
	{&setMenu2Property, "KI   0         ", NULL, 	KiAdd,	menuMain, NULL},
	{&setMenu2Property, "KD   0         ", NULL, 	KdAdd,	menuMain, NULL},
	{&setMenu2Property, "PWM  0         ", NULL, 	NULL, 	menuMain, NULL},
};
//Time set的子菜单
struct MenuProperty_t setMenu3Property = {8, 4};
struct Menu_t setMenu3[8] =
{
	{&setMenu3Property, "last menu      ", NULL, NULL,			menuMain, NULL},
	{&setMenu3Property, "Hour   0       ", NULL, HourAdd,		menuMain, NULL},
	{&setMenu3Property, "Minute 0       ", NULL, MinuteAdd,	menuMain, NULL},
	{&setMenu3Property, "Second 0       ", NULL, SecondAdd,	menuMain, NULL},
	{&setMenu3Property, "Year   0       ", NULL, YearAdd,		menuMain, NULL},
	{&setMenu3Property, "Month  0       ", NULL, MonthAdd,	menuMain, NULL},
	{&setMenu3Property, "Day    0       ", NULL, DayAdd,		menuMain, NULL},
	{&setMenu3Property, "OK             ", NULL, TimeOK,		menuMain, NULL},
};

void KpSub(){kp--;}
void KpAdd(){kp++;}
void KiAdd(){ki++;}
void KdAdd(){kd++;}

void HourAdd(void)
{
//	myTimeTemp.Hour++;
//	if(myTimeTemp.Hour > 23)
//		myTimeTemp.Hour = 0;	
}

void MinuteAdd(void)
{
//	myTimeTemp.Minute++;
//	if(myTimeTemp.Minute > 59)
//		myTimeTemp.Minute = 0;	
}

void SecondAdd(void)
{
//	myTimeTemp.Second++;
//	if(myTimeTemp.Second > 59)
//		myTimeTemp.Second = 0;
}

void YearAdd(void)
{
//	myTimeTemp.Year++;
}

void MonthAdd(void)
{
//	myTimeTemp.Month++;
//	if(myTimeTemp.Month > 12)
//		myTimeTemp.Month = 1;
}

void DayAdd(void)
{
//	myTimeTemp.Day++;
//	if(myTimeTemp.Day > 30)
//		myTimeTemp.Day = 1;
}

void TimeOK(void)
{
//	myTime = myTimeTemp;
}

void TimeSetInit(void)
{
//	myTimeTemp = myTime;
}

/**
 * @brief 主界面
 * 
 */
void MainUiSet()
{
	int i;
	for(i=1; i<15; i++)
	{
		OLED_ShowString(8*i, 1, 	"-", 8, 1);
		OLED_ShowString(8*i, 188, "-", 8, 1);
	}
	OLED_ShowString(40, 90, "YZBOT", 16, 1);
}

/**
  * @Name    DisplayRefreash
  * @brief   刷新当前菜单页的所有菜单项
  * @param   nowMenu: 当前菜单指针
**			 selectItem: 当前菜单在当前菜单页的索引，指小光标在第几行
**           scrollBar：滚动条所在位置 
  * @retval  void
  * @author  LQH
  * @Data    2022-01-27
  */
static u8 lastSelectItem = 0;		//记录上次索引
void DisplayRefreash(struct Menu_t *nowMenu, u8 selectItem, u8 scrollBar)
{
	int i = 0;

	if(menuPoint != menuLast) OLED_Clear();
	
	if(nowMenu == &MainUI)					//当回到主菜单时，由于没有全占屏，所以全部清屏，再画
	{
		OLED_Clear();
		MainUiSet();
	}
	else 
	{
		OLED_ShowString(0, lastSelectItem*16,	" ", 16, 1);		//去除上次索引
		OLED_ShowString(0, selectItem*16,		 	">", 16, 1);		//画出这次索引 
		
		for(i=0; i<(nowMenu->MenuProperty->MenuLen-nowMenu->MenuProperty->scrollBarLen); i++)
		{
			OLED_ShowString(10, i*16, nowMenu[i+scrollBar].displayString, 16, 1);
		}
	}
	OLED_Refresh();
	lastSelectItem = selectItem;
	menuLast = menuPoint;
}

/**
  * @Name    DisplayRefreashDate
  * @brief   刷新当前菜单页的所有菜单项,主要拿来更新数据
  * @param   nowMenu:    当前菜单指针
**			 selectItem: 当前菜单在当前菜单页的索引，指小光标在第几行
**           scrollBar： 滚动条所在位置 
  * @retval  void
  * @author  LQH
  * @Data    2022-01-27
  */
void DisplayRefreashData(struct Menu_t *nowMenu, u8 selectItem, u8 scrollBar)
{
	int i = 0;
	for(i=0; i<(nowMenu->MenuProperty->MenuLen-nowMenu->MenuProperty->scrollBarLen); i++)
	{
		OLED_ShowString(10, i*16, nowMenu[i+scrollBar].displayString, 16, 1);
	}
	OLED_Refresh();
}

/**
  * @name    MenuInit
  * @brief   一些菜单初始化主要是主菜单页的子菜单确定，由于父菜单结构体初始化时不能初始化子菜单
  * 		 所以在这里初始化
  * @param   : 
  * @retval  void
  * @author  LQH
  * @date    2022-01-27
  */
void MenuInit()
{
	MainUI.childrenMenu = menuMain;
	menuMain[1].childrenMenu = setMenu1;
	menuMain[2].childrenMenu = setMenu2;
	menuMain[3].childrenMenu = setMenu3;
	menuPoint = &MainUI;
	DisplayRefreash(menuPoint, selectItem, scrollBar);
}

/**
  * @name    GuiDataDisplayRefresh
  * @brief   菜单页的数据更新，记得一定要字符串占满15个字符
  * @param   : 
  * @retval  void
  * @author  LQH
  * @date    2022-01-27
  */
void GuiDataDisplayRefresh()
{
	if(menuPoint == setMenu1)
	{
		sprintf((char*)setMenu1[1].displayString, 	"Acc   %.3f     ", (float)stcAcc.a[0]/32768*16);
		sprintf((char*)setMenu1[2].displayString, 	"      %.3f     ", (float)stcAcc.a[1]/32768*16);
		sprintf((char*)setMenu1[3].displayString, 	"      %.3f     ", (float)stcAcc.a[2]/32768*16);
		sprintf((char*)setMenu1[4].displayString,		"Gyro  %.3f     ", (float)stcGyro.w[0]/32768*2000);
		sprintf((char*)setMenu1[5].displayString, 	"      %.3f     ", (float)stcGyro.w[1]/32768*2000);
		sprintf((char*)setMenu1[6].displayString, 	"      %.3f     ", (float)stcGyro.w[2]/32768*2000);
		sprintf((char*)setMenu1[7].displayString, 	"Angle %.3f     ", (float)stcAngle.Angle[0]/32768*180);
		sprintf((char*)setMenu1[8].displayString, 	"      %.3f     ", (float)stcAngle.Angle[1]/32768*180);
		sprintf((char*)setMenu1[9].displayString, 	"      %.3f     ", (float)stcAngle.Angle[2]/32768*180);
		sprintf((char*)setMenu1[10].displayString, 	"Quat  %.5f     ", (float)stcQ.q[0]/32768);
		sprintf((char*)setMenu1[11].displayString, 	"      %.5f     ", (float)stcQ.q[1]/32768);
		sprintf((char*)setMenu1[12].displayString, 	"      %.5f     ", (float)stcQ.q[2]/32768);
		sprintf((char*)setMenu1[13].displayString, 	"      %.5f     ", (float)stcQ.q[3]/32768);
		DisplayRefreashData(menuPoint, selectItem, scrollBar);
	}
	else if(menuPoint == setMenu2)
	{
		sprintf((char*)setMenu2[1].displayString, "KP   %3d      ", kp);
		sprintf((char*)setMenu2[2].displayString, "KI   %3d      ", ki);
		sprintf((char*)setMenu2[3].displayString, "KD   %3d      ", kd);
		sprintf((char*)setMenu2[4].displayString, "PWM  %3d      ", 0);
		DisplayRefreashData(menuPoint, selectItem, scrollBar);
	}
	else if(menuPoint == setMenu3)
	{
//		sprintf((char*)setMenu3[1].displayString, "Hour   %2d    ", myTimeTemp.Hour);	
//		sprintf((char*)setMenu3[2].displayString, "Minute %2d    ", myTimeTemp.Minute);	
//		sprintf((char*)setMenu3[3].displayString, "Second %2d    ", myTimeTemp.Second);	
//		sprintf((char*)setMenu3[4].displayString, "Year   %4d    ", myTimeTemp.Year);
//		sprintf((char*)setMenu3[5].displayString, "Month  %2d    ", myTimeTemp.Month);
//		sprintf((char*)setMenu3[6].displayString, "Day    %2d    ", myTimeTemp.Day);
		DisplayRefreashData(menuPoint, selectItem, scrollBar);
	}
	else if(menuPoint == &MainUI)
	{
		MainUiSet();
		OLED_Refresh();
	}
}

void MenuControl()
{
	if(isKeyUp == 1)//上键按下
	{
		isKeyUp=0;		//标志位清零
		selectItem--;	//当前菜单在当前菜单页的索引--
		if(selectItem<0 && scrollBar!=0)//小于0,但是滚动条不在0，就减滚动条
		{
			selectItem = 0;
			scrollBar--;
		}
		else if(selectItem<0 && scrollBar==0)	//小于0,滚动条也在0，就将索引移到最后，滚动条到最大
		{
			selectItem = menuPoint->MenuProperty->MenuLen-1-menuPoint->MenuProperty->scrollBarLen;
			scrollBar  = menuPoint->MenuProperty->scrollBarLen;
		}
		DisplayRefreash(menuPoint, selectItem, scrollBar);	//刷新显示
	}
	else if(isKeyDown == 1)	//和上键差不多
	{
		isKeyDown = 0;
		selectItem++;
		//假如索引大于最大值，但是滚动条不在最大值，保持索引最大值，滚动条++
		if(selectItem>(menuPoint->MenuProperty->MenuLen-1-menuPoint->MenuProperty->scrollBarLen) && scrollBar!=menuPoint->MenuProperty->scrollBarLen)
		{
			selectItem = menuPoint->MenuProperty->MenuLen-1-menuPoint->MenuProperty->scrollBarLen;
			scrollBar++;
			
		}
		//假如索引大于最大值，滚动条在最大值，移动到第一个位置
		else if(selectItem>(menuPoint->MenuProperty->MenuLen-1-menuPoint->MenuProperty->scrollBarLen) && scrollBar==menuPoint->MenuProperty->scrollBarLen)
		{
			selectItem = 0;
			scrollBar = 0;
		}
		DisplayRefreash(menuPoint, selectItem, scrollBar);
	}
//	else if(isKeyBack == 1)
//	{
//		/**
//		//假如当前菜单的func1不为空，执行相关函数
//		if(menuPoint[selectItem+scrollBar].func1 != NULL)
//		{
//			menuPoint[selectItem+scrollBar].func1();
//		}
//		isKeyBack = 0;
//		DisplayRefreash(menuPoint, selectItem, scrollBar);
//		**/
//		if(menuPoint[selectItem].fatherMenu!=NULL)	//假如索引为零而且父菜单不为空，指向父指针
//		{
//			menuPoint = menuPoint[selectItem].fatherMenu;
//		}
//		isKeyBack = 0;
//		DisplayRefreash(menuPoint, selectItem, scrollBar);
//		
//	}
	else if(isKeyEnter == 1)
	{
		if(selectItem==0 && scrollBar==0 && menuPoint[selectItem].fatherMenu!=NULL)	//假如索引为零而且父菜单不为空，指向父指针
		{
			menuPoint = menuPoint[selectItem].fatherMenu;
		}
		else if(menuPoint[selectItem+scrollBar].childrenMenu != NULL)	//假如该索引子菜单页不为空，指向子菜单
		{
			if(menuPoint[selectItem+scrollBar].func2 != NULL)	//假如当前菜单的func2不为空，执行相关函数
			{
				menuPoint[selectItem+scrollBar].func2();
			}
			menuPoint = menuPoint[selectItem+scrollBar].childrenMenu;
			selectItem = 0;
		}
		else if(menuPoint[selectItem+scrollBar].func2 != NULL)	//假如当前菜单的func2不为空，执行相关函数
		{
			menuPoint[selectItem+scrollBar].func2();
		}
		isKeyEnter = 0;
		DisplayRefreash(menuPoint, selectItem, scrollBar);
	}
	/**
	else if(isKeyOk == 1)
	{
		isKeyOk = 0;
		DisplayRefreash(menuPoint, selectItem, scrollBar);
	}
	**/
	GuiDataDisplayRefresh();
}
