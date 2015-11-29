#ifndef MISC_H
#define MISC_H
#include <misc.h>
#endif

#ifndef PRIMITIVES_H
#define PRIMITIVES_H
#include <primitives.h>
#endif

extern unsigned int tim3_cpt;
extern unsigned int debug_var;
extern unsigned int tp_int;
extern unsigned int tp_buffer;
extern unsigned int tp_x;
extern unsigned int tp_y;

void TIM3_IRQHandler(void) ;
void EXTI0_IRQHandler(void);
void SPI2_IRQHandler(void);



