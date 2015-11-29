#ifndef WINDOWS_H
#define WINDOWS_H
#include <windows.h>
#endif

void TP_PROCESS(void)
{
	if(tp_int)
	{
		//Get coordinates
		TP_Get_X();
		TP_Get_Y();
		
		switch(w_index)
		{
			case 0: TP_MAIN(); break;
		}
		delay_1ms(100);
		tp_int=0;
	}
}

/* ##### WINDOWS and TP DEFINITIONS ##### */
void TFT_MAIN(void)
{
	w_index=0;
	TFT_Fill_Screen(0x3596);
}

void TP_MAIN(void)
{
	//No action for now...
}

