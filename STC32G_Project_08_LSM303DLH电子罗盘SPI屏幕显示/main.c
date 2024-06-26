/*-----------------------------------------------------------------------------------------
* 请勿更改此文件编码！
* 必须保持为默认编码GB2312，否则汉字无法正常显示！

* 时钟选择 24MHz
* 按键为 P1.0/1.1/1.3/1.4

* --------------------------I2C-LSM303DLH模块-电子罗盘加速度计-----------------------------
    - 默认使用P3.2/P3.3端口，修改请看 iic.c -> IIC_Init() 函数。

* -----------------------------------SPI-OLED显示屏----------------------------------------
    - 连接屏幕默认使用端口为：
      D0 - P2.5(SCLK)
      D1 - P2.3(MOSI)
      CS - P2.2(CS)
      DC - P2.1(DC)
      RES - P2.0(RES)
      修改请看 spi.h 和 spi.c

* 本实验仅实现SPI-OLED屏幕和LSM303DLH模块的功能，未结合激光测距模块
    
    由于硬件原因，按键KEY4-KEY1和屏幕的横向显示方向是反的，即屏幕左下角按键对应的是KEY4。
    如果需要修改，建议直接修改sbit key的定义。

* 注意：本程序仅供学习参考，请勿用于商业用途。
-----------------------------------------------------------------------------------------*/
#include <STRING.H>
#include <STC32G.H>
#include <STDIO.H>
#include "oled.h"
#include "pic.h"
#include "lsm303.h"

// 定义按键引脚
sbit key1 = P1^0;
sbit key2 = P1^1;
sbit key3 = P1^3;
sbit key4 = P1^4;
unsigned char key1_up_store = 1; // 按键1状态暂存
unsigned char key2_up_store = 1; // 按键2状态暂存
unsigned char key3_up_store = 1; // 按键3状态暂存
unsigned char key4_up_store = 1; // 按键4状态暂存

void OLED_LSM303DLH_Mag_Get_Angle()
{
    double Mag_Angle;
    unsigned char Str[10];
    Mag_Angle = LSM303_Read_Mag_Angle();
    OLED_BuffShowString(0,0,"ANGLE:",0);
    sprintf(Str, "%f", Mag_Angle);
    OLED_BuffShowString(6*8,0,Str,0);
    OLED_BuffShow();
}

void OLED_LSM303DLH_AccX_GetDataNShow()
{
    float Acc;
    unsigned char Str[10];
    Acc = LSM303_Read_Acc('x');
    OLED_BuffShowString(0,2,"ACC X:",0);
    sprintf(Str, "%f", Acc);
    OLED_BuffShowString(6*8,2,Str,0);
    OLED_BuffShow();
}

void OLED_LSM303DLH_AccY_GetDataNShow()
{
    float Acc;
    unsigned char Str[10];
    Acc = LSM303_Read_Acc('y');
    OLED_BuffShowString(0,4,"ACC Y:",0);
    sprintf(Str, "%f", Acc);
    OLED_BuffShowString(6*8,4,Str,0);
    OLED_BuffShow();
}

void OLED_LSM303DLH_AccZ_GetDataNShow()
{
    float Acc;
    unsigned char Str[10];
    Acc = LSM303_Read_Acc('z');
    OLED_BuffShowString(0,6,"ACC Z:",0);
    sprintf(Str, "%f", Acc);
    OLED_BuffShowString(6*8,6,Str,0);
    OLED_BuffShow();
}
void OLED_LSM303DLH_UI_Init()
{
    OLED_BuffClear();                       //清除全部缓存
}

void OLED_Loading()
{
    OLED_BuffClear();                               //清除全部缓存
    OLED_BuffShowString(0,3,"   PLEASE WAIT  ",1);  //显示数据
    OLED_BuffShow();                                //将缓存写入显示屏显示
}

void key1_short_press()
{
    // 短按键1功能
}

void key2_short_press()
{
    // 短按键2功能
}

void key3_short_press()
{
    // 短按键3功能
}

void key4_short_press()
{
    // 短按键4功能
}

void key1_check()
{
    if(key1 == 0 && key1_up_store == 1)
    {
        key1_up_store = 0; // 标记按键被按下
        OLED_BuffShowString(13*8,6,"[-]",1);  //显示数据
        OLED_BuffShow();                    //将缓存写入显示屏显示
    }
    if(key1 == 1 && key1_up_store == 0)
    {
        key1_up_store = 1; // 标记按键被释放
        key1_short_press(); // 触发短按键1功能
        OLED_BuffShowString(13*8,6,"[-]",0);  //显示数据
        OLED_BuffShow();                    //将缓存写入显示屏显示
    }
}

void key2_check()
{
    if(key2 == 0 && key2_up_store == 1)
    {
        key2_up_store = 0; // 标记按键被按下
        OLED_BuffShowString(10*8,6,"[+]",1);  //显示数据
        OLED_BuffShow();                    //将缓存写入显示屏显示
    }
    if(key2 == 1 && key2_up_store == 0)
    {
        key2_up_store = 1; // 标记按键被释放
        key2_short_press(); // 触发短按键2功能
        OLED_BuffShowString(10*8,6,"[+]",0);  //显示数据
        OLED_BuffShow();                    //将缓存写入显示屏显示
    }
}

void key3_check()
{
    if(key3 == 0 && key3_up_store == 1)
    {
        key3_up_store = 0; // 标记按键被按下
    }
    if(key3 == 1 && key3_up_store == 0)
    {
        key3_up_store = 1; // 标记按键被释放
        key3_short_press(); // 触发短按键3功能
    }
}

void key4_check()
{
    if(key4 == 0 && key4_up_store == 1)
    {
        key4_up_store = 0; // 标记按键被按下
    }
    if(key4 == 1 && key4_up_store == 0)
    {
        key4_up_store = 1; // 标记按键被释放
        key4_short_press(); // 触发短按键4功能
    }
}

void Sys_Init()
{
    WTST = 0;  //设置程序指令延时参数，赋值为0可将CPU执行指令的速度设置为最快
    EAXFR = 1; //扩展寄存器(XFR)访问使能
    CKCON = 0; //提高访问XRAM速度

    P0M1 = 0x00;   P0M0 = 0x00;   //设置为准双向口
    P1M1 = 0x00;   P1M0 = 0x00;   //设置为准双向口
    P1M0 = 0xff;   P1M1 = 0x00;   //设置为推挽输出
    P2M1 = 0x00;   P2M0 = 0x00;   //设置为准双向口
    P3M1 = 0x00;   P3M0 = 0x00;   //设置为准双向口
    P4M1 = 0x00;   P4M0 = 0x00;   //设置为准双向口
    P5M1 = 0x00;   P5M0 = 0x00;   //设置为准双向口
    P6M1 = 0x00;   P6M0 = 0x00;   //设置为准双向口
    P7M1 = 0x00;   P7M0 = 0x00;   //设置为准双向口
}

void main(void)
{
    EA = 1;                             //开总中断
    Sys_Init();                         //系统初始化
    SPI_init();                         //SPI初始化
    OLED_Init();                        //OLED初始化
    OLED_BuffClear();                   //清除全部缓存
    OLED_BuffShow();                    //将缓存写入显示屏显示
    IIC_Init();                         //IIC初始化
    LSM303_Init();                      //LSM303初始化
    while (1)
    {
        key1_check();                   //检查按键1
        key2_check();                   //检查按键2
        key3_check();                   //检查按键3
        key4_check();                   //检查按键4
        LSM303_Acc_Init();              //LSM303加速度传感器初始化
        delay_ms(100);                  //延时10ms
        LSM303_Mag_Init();              //LSM303磁场传感器初始化
        OLED_LSM303DLH_Mag_Get_Angle(); //获取磁场角度并显示
        OLED_LSM303DLH_AccX_GetDataNShow(); //获取加速度X数据并显示
        OLED_LSM303DLH_AccY_GetDataNShow(); //获取加速度Y数据并显示
        OLED_LSM303DLH_AccZ_GetDataNShow(); //获取加速度Z数据并显示
        delay_ms(100);                  //延时10ms
    }
}
