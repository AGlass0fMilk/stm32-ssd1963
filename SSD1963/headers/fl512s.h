#ifndef STM32F4XX_SPI_H
#define STM32F4XX_SPI_H
#include <stm32f4xx_spi.h>
#endif

#ifndef TIMERS_H
#define TIMERS_H
#include <timers.h>
#endif

extern unsigned int flash_dummy;
extern unsigned int flash_buffer_enable;
extern unsigned int flash_buffer[1024];
extern unsigned int flash_index;

void FL512S_Initialization(void);
void SET_FLASH_CS(void);
void RESET_FLASH_CS(void);
void Flash_Send_Command(unsigned char cmd, unsigned long clkout);

void FL_RDID(void);


