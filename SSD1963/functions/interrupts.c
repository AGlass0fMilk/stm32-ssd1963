#ifndef INTERRUPTS_H
#define INTERRUPTS_H
#include <interrupts.h>
#endif

/* Handle TIM3 interrupt */
void TIM3_IRQHandler(void) 
{
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	tim3_cpt++;
}

/* Handle PD0 interrupt */
void EXTI0_IRQHandler(void) {
    /* Make sure that interrupt flag is set */
    if (EXTI_GetITStatus(EXTI_Line0) != RESET) 
		{
		  tp_int=1;
			EXTI_ClearITPendingBit(EXTI_Line0);
    }
}

void SPI2_IRQHandler(void)
{
	if (SPI_I2S_GetITStatus(SPI2, SPI_I2S_IT_RXNE) == SET)
	{
		tp_buffer=SPI_I2S_ReceiveData(SPI2);
	}
}

