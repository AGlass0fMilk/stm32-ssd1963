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

#ifndef VARIABLES_H
#define VARIABLES_H
#include <variables.h>
#endif

#ifndef IMAGES_H
#define IMAGES_H
#include <images.h>
#endif

#ifndef MAX11802_H
#define MAX11802_H
#include <max11802.h>
#endif

#ifndef WINDOWS_H
#define WINDOWS_H
#include <windows.h>
#endif

#ifndef DAC_H
#define DAC_H
#include <dac.h>
#endif


int main(void) 
{
	GPIO_Initialization();
	TIM3_Initialization();
	TFT_Initialization();
	MAX11802_Initialization();
	DAC_Initialization();
	
	TFT_MAIN();
	TFT_Backlight_FadeIn(10);
	
	DAC_SetChannel2Data(DAC_Align_12b_R, 0xFFFF);
	
	DAC_SetChannel2Data(DAC_Align_12b_R, 0x000F);

	DAC_SetChannel2Data(DAC_Align_12b_R, 0x0FFF);			
	
	while(1) 
	{
		TP_PROCESS();
	}
}
