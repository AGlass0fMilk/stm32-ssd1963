#ifndef GPIO_H
#define GPIO_H
#include <gpio.h>
#endif

void GPIO_Initialization(void)
{
		GPIO_InitTypeDef GPIO_InitDef;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    GPIO_InitDef.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
    GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitDef.GPIO_OType = GPIO_OType_PP;
    GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_InitDef.GPIO_Speed = GPIO_Speed_100MHz;
    //Initialize pins
    GPIO_Init(GPIOA, &GPIO_InitDef);
 
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    GPIO_InitDef.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitDef.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitDef.GPIO_OType = GPIO_OType_PP;
    GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_InitDef.GPIO_Speed = GPIO_Speed_100MHz;
    //Initialize pins
    GPIO_Init(GPIOA, &GPIO_InitDef);
}

void TFT_5V_Enable(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_1);
}

void TFT_5V_Disable(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);
}

void TFT_33V_Enable(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_2);
}

void TFT_33V_Disable(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
}
