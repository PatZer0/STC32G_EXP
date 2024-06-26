#include <STC32G.h>
#define LED_GND P4  // 本实例中LED共阳，GND由单片机控制
// #define MAIN_Fosc 24000000UL    // 主频，本实例中不需要

// 定义按键引脚
sbit key1 = P2^0;
sbit key2 = P2^1;
sbit key3 = P2^2;
sbit key4 = P2^3;

// 计数器要使用int类型，如果使用char(最大值255)会溢出，导致功能异常
unsigned int led_interval_flash = 500; // LED闪烁速度，默认500ms切换一次
unsigned int led_interval_light_up_in_turn = 1000; // LED依次点亮间隔，默认1000ms切换一次
unsigned char led_flash_index = 0; // LED流水起始位置
unsigned char led_flash_mode = 0; // LED流水模式，0为静态全部熄灭，1为静态全部亮，2为依次点亮，3为流水灯
unsigned char led_flash_array[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};  // LED流水数组
unsigned char led_light_up_in_turn[8] = {0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7f, 0xff}; // LED依次点亮数组
unsigned int timer0_counter = 0; // LED流水计数器

unsigned char key1_up_store = 1; // 按键1状态暂存
unsigned char key2_up_store = 1; // 按键2状态暂存
unsigned char key3_up_store = 1; // 按键3状态暂存
unsigned char key4_up_store = 1; // 按键4状态暂存

void key1_short_press()
{
    // 短按键1功能
    // 点亮所有LED
    led_flash_mode = 1;
}

void key2_short_press()
{
    // 短按键2功能
    // 熄灭所有LED
    led_flash_mode = 0;
}

void key3_short_press()
{
    // 短按键3功能
    // LED间隔一秒依次点亮
    led_flash_mode = 2;
}

void key4_short_press()
{
    // 短按键4功能
    // LED流水灯0.5秒
    led_flash_mode = 3;
}

void key1_check() 
{
    if(key1 == 0 && key1_up_store == 1)
    {
        key1_up_store = 0; // 标记按键被按下
    }
    if(key1 == 1 && key1_up_store == 0)
    {
        key1_up_store = 1; // 标记按键被释放
        key1_short_press(); // 触发短按键1功能
    }
}

void key2_check()
{
    if(key2 == 0 && key2_up_store == 1)
    {
        key2_up_store = 0; // 标记按键被按下
    }
    if(key2 == 1 && key2_up_store == 0)
    {
        key2_up_store = 1; // 标记按键被释放
        key2_short_press(); // 触发短按键2功能
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

void led_flash()
{
    // 0为静态全部熄灭，1为静态全部亮，2为依次点亮，3为流水灯
    if(led_flash_mode == 0)
    {
        LED_GND = 0xFF; // 全部熄灭
    }
    else if(led_flash_mode == 1)
    {
        LED_GND = 0x00; // 全部熄灭
    }
    else if(led_flash_mode == 2)
    {
        LED_GND = ~led_light_up_in_turn[led_flash_index]; // 依次点亮
        led_flash_index++;
        if(led_flash_index >= 8)
        {
            led_flash_index = 0;
        }
    }
    else if(led_flash_mode == 3)
    {
        LED_GND = ~led_flash_array[led_flash_index]; // 流水灯
        led_flash_index++;
        if(led_flash_index >= 8)
        {
            led_flash_index = 0;
        }
    }
}

void timer0_isr(void) interrupt 1
{
    timer0_counter++;
    if (led_flash_mode == 0 || led_flash_mode == 1)
    {
        // 0和1为静态模式，不用计时，保证快速响应
        timer0_counter = 0;
        led_flash();
    }
    else if(led_flash_mode == 3 && timer0_counter >= led_interval_flash)
    {
        // 流水模式，每隔led_interval_flash毫秒切换一次LED
        timer0_counter = 0;
        led_flash();
    }
    else if(led_flash_mode == 2 && timer0_counter >= led_interval_light_up_in_turn)
    {
        // 依次点亮模式，每隔led_interval_light_up_in_turn毫秒切换一次LED
        timer0_counter = 0;
        led_flash();
    }
}

void timer0_init(void)		//1毫秒@24.000M
{
	AUXR |= 0x80;			//定时器时钟1T模式
	TMOD &= 0xF0;			//设置定时器模式
	TL0 = 0x40;				//设置定时初始值
	TH0 = 0xA2;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0
	ET0 = 1;				//使能定时器0中断
    EA = 1;			    	//使能总中断
}

// 延时函数，本实例中未使用
// void delay_ms(unsigned char ms)
// {
//      unsigned int i;
//      do{
//           i = MAIN_Fosc / 6000;
//           while(--i);
//      }while(--ms);
// }


void main(void)
{
    P4M0 = 0xff; P4M1 = 0x00;           //配置P4为推挽输出模式
    P2M0 = 0x00; P2M1 = 0x00;           //配置P2为准双向模式
    timer0_init();                      //初始化定时器0
    while(1)
    {
        // 检测按键
        key1_check();
        key2_check();
        key3_check();
        key4_check();
    }
}