#include "spi.h"

//========================================================================
// 函数名称: SPI_Init
// 函数功能: SPI初始化
// 入口参数: 无
// 函数返回: 无
// 当前版本: VER1.0
// 修改日期: 2023 - 6 - 7
// 当前作者: ZCF
// 其他备注: 这里SPI的引脚选择要通过P_SW1寄存器切换
//========================================================================
void SPI_Init(void)
{
	P_SW1 = (P_SW1 & ~0x0c) | 0x04;		//SPI: SS(P2.2), MOSI(P2.3), MISO(P2.4), SCLK(P2.5)
    SSIG = 1;                           //忽略 SS 引脚功能，使用 MSTR 确定器件是主机还是从机
    SPEN = 1;                           //使能 SPI 功能
    DORD = 0;                           //先发送/接收数据的高位（MSB）
    MSTR = 1;                           //设置主机模式
    CPOL = 0;                           //SCLK 空闲时为低电平，SCLK 的前时钟沿为上升沿，后时钟沿为下降沿
    CPHA = 0;                           //数据 SS 管脚为低电平驱动第一位数据并在 SCLK 的后时钟沿改变数据
    SPCTL = (SPCTL & ~3) | 3;           //SPI 时钟频率选择, 0: 4T, 1: 8T,  2: 16T,  3: 2T
    
    SPI_SCK = 0;                        //初始化 SPI 信号线
    SPI_MOSI = 1;                       //初始化 SPI 信号线
    SPIF = 1;                           //清SPIF标志
    WCOL = 1;                           //清WCOL标志
}


//========================================================================
// 函数名称: SPI_WriteByte
// 函数功能: SPI写一个八位数据
// 入口参数: 无
// 函数返回: 无
// 当前版本: VER1.0
// 修改日期: 2023 - 6 - 7
// 当前作者: ZCF
// 其他备注: 
//========================================================================
void SPI_WriteByte(unsigned char out)
{
    SPDAT = out;
    while(SPIF == 0);
    SPIF = 1;                           //清SPIF标志
    WCOL = 1;                           //清WCOL标志
}

