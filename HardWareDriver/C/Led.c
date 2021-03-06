/*
      ____                      _____                  +---+
     / ___\                     / __ \                 | R |
    / /                        / /_/ /                 +---+
   / /   ________  ____  ___  / ____/___  ____  __   __
  / /  / ___/ __ `/_  / / _ \/ /   / __ \/ _  \/ /  / /
 / /__/ /  / /_/ / / /_/  __/ /   / /_/ / / / / /__/ /
 \___/_/   \__,_/ /___/\___/_/    \___ /_/ /_/____  /
                                                 / /
                                            ____/ /
                                           /_____/
led.c file
编写者：小马  (Camel)
作者E-mail：375836945@qq.com
编译环境：MDK-Lite  Version: 4.23
初版时间: 2014-01-28
------------------------------------
*/

#include "Led.h"
#include "UART1.h"
#include "config.h"

/********************************************
              Led初始化函数
功能：
1.配置Led接口IO输出方向
2.关闭所有Led(开机默认方式)
描述：
对应IO=1，灯亮
********************************************/
void LedInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC->APB2ENR|=1<<2;    //使能PORTA时钟
    RCC->APB2ENR|=1<<3;    //使能PORTB时钟
    RCC->APB2ENR|=1<<0;    //使能复用时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);


    GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
    GPIOA->CRH&=0XF0F0FFFF;  //PA12,14推挽输出
    GPIOA->CRH|=0X03030000;
    GPIOA->ODR|=3<<12;        //PA12,14上拉


    GPIOB->CRL&=0X0F00FFFF;  //PB4,5,7推挽输出
    GPIOB->CRL|=0X30330000;
    GPIOB->ODR|=11<<4;        //PB4,5,7上拉

    //AFIO->MAPR|=2<<24;      //关闭JATG,千万不能讲SWD也关闭，否则芯片作废，亲测!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //PB4 默认是JNTRST接口,属于调试接口，复用功能为PB4 IO口
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);


#ifdef NEWC03
    GPIOA->CRH&=0XFFF0FFFF;  //PA12推挽输出
    GPIOA->CRH|=0X01010000;
    GPIOA->ODR|=1<<12;        //PA12上拉
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_10 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_SetBits(GPIOB, GPIO_Pin_10);
#else
    GPIOA->CRH&=0XF0F0FFFF;  //PA12,14推挽输出
    GPIOA->CRH|=0X03030000;
    GPIOA->ODR|=3<<12;        //PA12,14上拉
    GPIO_SetBits(GPIOA, GPIO_Pin_14);
#endif
    GPIO_ResetBits(GPIOB, GPIO_Pin_7);
    GPIO_ResetBits(GPIOA, GPIO_Pin_12);
    GPIO_ResetBits(GPIOB, GPIO_Pin_4);
    GPIO_ResetBits(GPIOB, GPIO_Pin_5);
}

void LedSet(u8 ch,char sta)
{
    switch(ch)
    {
    case signalLED:
        if(sta == 1) GPIO_SetBits(GPIOA, GPIO_Pin_12);
        else  GPIO_ResetBits(GPIOA, GPIO_Pin_12);
        break;

    case led2:
        if(sta == 1) GPIO_SetBits(GPIOB, GPIO_Pin_4);
        else  GPIO_ResetBits(GPIOB, GPIO_Pin_4);
        break;

    case led3:
        if(sta == 1) GPIO_SetBits(GPIOB, GPIO_Pin_5);
        else  GPIO_ResetBits(GPIOB, GPIO_Pin_5);
        break;

    case led4:
        if(sta == 1) GPIO_SetBits(GPIOB, GPIO_Pin_6);
        else  GPIO_ResetBits(GPIOB, GPIO_Pin_6);
        break;

    case led5:
        if(sta) GPIO_SetBits(GPIOB, GPIO_Pin_7);
        else  GPIO_ResetBits(GPIOB, GPIO_Pin_7);
        break;
    }

}

