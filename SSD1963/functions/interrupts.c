#ifndef INTERRUPTS_H
#define INTERRUPTS_H
#include <interrupts.h>
#endif

void TIM3_IRQHandler(void) 
{
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	tim3_cpt++;
}
