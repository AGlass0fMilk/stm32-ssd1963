#ifndef STM32F4XX_H
#define STM32F4XX_H
#include <stm32f4xx.h>
#endif

#ifndef STM32F4XX_RCC_H
#define STM32F4XX_RCC_H
#include <stm32f4xx_rcc.h>
#endif

#ifndef STM32F4XX_GPIO_H
#define STM32F4XX_GPIO_H
#include <stm32f4xx_gpio.h>
#endif

void GPIO_Initialization(void);
void TFT_5V_Enable(void);
void TFT_5V_Disable(void);
void TFT_33V_Enable(void);
void TFT_33V_Disable(void);

