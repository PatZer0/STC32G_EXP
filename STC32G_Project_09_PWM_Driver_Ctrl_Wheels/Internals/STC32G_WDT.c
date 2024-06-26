/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC 1T Series MCU Demo Programme -------------------------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ------------------------*/
/* --- Web: www.STCAI.com ---------------------------------------------*/
/* --- Web: www.STCMCUDATA.com  ---------------------------------------*/
/* --- BBS: www.STCAIMCU.com  -----------------------------------------*/
/* --- QQ:  800003751 -------------------------------------------------*/
/* 如果要在程序中使用此代码,请在程序中注明使用了STC的资料及程序            */
/*---------------------------------------------------------------------*/

#include	"STC32G_WDT.h"

//========================================================================
// 函数: void WDT_Inilize(WDT_InitTypeDef *WDT)
// 描述: 看门狗初始化程序.
// 参数: WDT: 结构参数,请参考WDT.h里的定义.
// 返回: none.
// 版本: V1.0, 2020-09-16
//========================================================================
void WDT_Inilize(WDT_InitTypeDef *WDT)
{
	if(WDT->WDT_Enable == ENABLE)		EN_WDT = 1;	//使能看门狗

	WDT_PS_Set(WDT->WDT_PS);	//看门狗定时器时钟分频系数		WDT_SCALE_2,WDT_SCALE_4,WDT_SCALE_8,WDT_SCALE_16,WDT_SCALE_32,WDT_SCALE_64,WDT_SCALE_128,WDT_SCALE_256
	if(WDT->WDT_IDLE_Mode == WDT_IDLE_STOP)	IDL_WDT = 0;	//IDLE模式停止计数
	else									IDL_WDT = 1;	//IDLE模式继续计数
}

/********************* 清除看门狗函数 *************************/
void WDT_Clear (void)
{
	CLR_WDT = 1;    // 喂狗
}
