#ifndef STM32F4XX_SPI_H
#define STM32F4XX_SPI_H
#include <stm32f4xx_spi.h>
#endif

#ifndef TIMERS_H
#define TIMERS_H
#include <timers.h>
#endif

#ifndef FONTS_H
#define FONTS_H
#include <fonts.h>
#endif

#ifndef PRIMITIVES_H
#define PRIMITIVES_H
#include <primitives.h>
#endif

extern unsigned int tp_int;
extern unsigned int tp_buffer;
extern unsigned int tp_x;
extern unsigned int tp_y;


void MAX11802_Initialization(void);
void TP_Write_Register(unsigned char reg, unsigned char val);
void SET_TP_CS(void);
void RESET_TP_CS(void);
void TP_Get_X(void);
void TP_Get_Y(void);
void TP_Check(void);

