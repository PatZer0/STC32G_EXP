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

#include	"STC32G_SPI.h"

//========================================================================
//                               本地变量声明
//========================================================================

u8 	SPI_RxCnt;

//========================================================================
// 函数: SPI_ISR_Handler
// 描述: SPI中断函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2020-09-23
//========================================================================
void SPI_ISR_Handler() interrupt SPI_VECTOR
{
	if(MSTR)	//主机模式
	{
		B_SPI_Busy = 0;
	}
	else							//从机模式
	{
		if(SPI_RxCnt >= SPI_BUF_LENTH)		SPI_RxCnt = 0;
		SPI_RxBuffer[SPI_RxCnt++] = SPDAT;
		SPI_RxTimerOut = 5;
	}
	SPI_ClearFlag();	//清0 SPIF和WCOL标志
}

