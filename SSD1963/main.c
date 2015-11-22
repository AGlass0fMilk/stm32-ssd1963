#ifndef GPIO_H
#define GPIO_H
#include <gpio.h>
#endif

#ifndef TIMERS_H
#define TIMERS_H
#include <timers.h>
#endif

#ifndef INTERRUPTS_H
#define INTERRUPTS_H
#include <interrupts.h>
#endif

#ifndef TFT_H
#define TFT_H
#include <tft.h>
#endif

#ifndef PRIMITIVES_H
#define PRIMITIVES_H
#include <primitives.h>
#endif

#ifndef FONTS_H
#define FONTS_H
#include <fonts.h>
#endif

#ifndef VARIABLES_H
#define VARIABLES_H
#include <variables.h>
#endif

#ifndef IMAGES_H
#define IMAGES_H
#include <images.h>
#endif


int main(void) 
{
	GPIO_Initialization();
	TIM3_Initialization();
	
	//Init TFT screen
	TFT_Initialization();
	
	TFT_Fill_Screen(0x0000);

	while(1) 
	{
		TFT_TextTest();
		TFT_ColorTest(10);
		TFT_ImageTest();
	}
}
