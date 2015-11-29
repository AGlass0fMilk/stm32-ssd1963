#ifndef MAX11802_H
#define MAX11802_H
#include <max11802.h>
#endif

void MAX11802_Initialization(void)
{
	SPI_InitTypeDef SPI_InitStructure;
	GPIO_InitTypeDef GPIO_InitDef;
	EXTI_InitTypeDef EXTI_InitStruct;
  NVIC_InitTypeDef NVIC_InitStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
 
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	 
	SPI_Init(SPI2, &SPI_InitStructure);
	 
	 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	 
	GPIO_InitDef.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitDef.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitDef.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitDef.GPIO_OType = GPIO_OType_PP;
	GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitDef);
	 
	GPIO_InitDef.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitDef.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitDef.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOB, &GPIO_InitDef);
	 
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_SPI1);
	 
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	

	//Start SPI2 with interrupts
	SPI_Init(SPI2,&SPI_InitStructure);
	NVIC_InitStruct.NVIC_IRQChannel = SPI2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
	
	SPI_I2S_ITConfig(SPI2, SPI_I2S_IT_RXNE, ENABLE);
	
	//Start SPI bus
	SPI_Cmd(SPI2, ENABLE);
	
	delay_1ms(100);
	
	//MAX11802 registers configuration
	TP_Write_Register(0x01,0x00);
	TP_Write_Register(0x02,0x00);
	TP_Write_Register(0x03,0x00);
	TP_Write_Register(0x04,0x00);
	TP_Write_Register(0x05,0x80);
	TP_Write_Register(0x06,0x55);
	TP_Write_Register(0x07,0x10);
	TP_Write_Register(0x08,0x00);
	TP_Write_Register(0x09,0x00);
	TP_Write_Register(0x0A,0x00);
	TP_Write_Register(0x0B,0x00);
	
	
	//--START--INTERRUPT CONFIG (PB0/TIRQ)
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	//External Interrupt as input
	GPIO_InitDef.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitDef.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitDef.GPIO_Speed = GPIO_Speed_50MHz;
	//Initialize pins
	GPIO_Init(GPIOB, &GPIO_InitDef);
	
	/* Tell system that you will use PB0 for EXTI_Line0*/
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource0);
	
	/* PB0 is connected to EXTI_Line0 */
	EXTI_InitStruct.EXTI_Line = EXTI_Line0;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStruct);

	/* Add IRQ vector to NVIC */
	/* PD0 is connected to EXTI_Line0, which has EXTI0_IRQn vector */
	NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
	//--END--INTERRUPT CONFIG (PB0/TIRQ)
	tp_int=0;
}

void TP_Write_Register(unsigned char reg, unsigned char val)
{
    unsigned char byte0;
    byte0=reg<<1;

    SET_TP_CS();
    delay_1ms(1);
    SPI_I2S_SendData(SPI2, byte0);
    delay_1ms(1);
	  SPI_I2S_SendData(SPI2, val);
    delay_1ms(1);
    RESET_TP_CS();
}

void SET_TP_CS(void)
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
}

void RESET_TP_CS(void)
{
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
}

//Ask the controller for X coordinate
void TP_Get_X(void)
{
    unsigned int tp_x_msb=0;
		unsigned int tp_x_lsb=0;
	
	  SET_TP_CS();
    delay_1ms(5);
    SPI_I2S_SendData(SPI2, 0xF0);
    delay_1ms(5);
    RESET_TP_CS();

    delay_1ms(5);

    SET_TP_CS();
    delay_1ms(5);
    SPI_I2S_SendData(SPI2, 0xA5);
    delay_1ms(5);
    SPI_I2S_SendData(SPI2, 0xFF);
    delay_1ms(5);
    tp_x_msb=tp_buffer;
    SPI_I2S_SendData(SPI2, 0xFF);
    delay_1ms(5);
    tp_x_lsb=tp_buffer;
    delay_1ms(5);
    RESET_TP_CS();

    tp_x=(tp_x_msb<<8)|(tp_x_lsb);
}

//Ask the controller for Y coordinate
void TP_Get_Y(void)
{
    unsigned int tp_y_msb=0;
		unsigned int tp_y_lsb=0;
	
	  SET_TP_CS();
    delay_1ms(5);
    SPI_I2S_SendData(SPI2, 0xF4);
    delay_1ms(5);
    RESET_TP_CS();

    delay_1ms(5);

    SET_TP_CS();
    delay_1ms(5);
    SPI_I2S_SendData(SPI2, 0xA9);
    delay_1ms(5);
    SPI_I2S_SendData(SPI2, 0xFF);
    delay_1ms(5);
    tp_y_msb=tp_buffer;
    SPI_I2S_SendData(SPI2, 0xFF);
    delay_1ms(5);
    tp_y_lsb=tp_buffer;
    delay_1ms(5);
    RESET_TP_CS();

    tp_y=(tp_y_msb<<8)|(tp_y_lsb);
}

void TP_Check(void)
{
	TP_Get_X();
	TP_Get_Y();
	TFT_DrawFullRect(0,440,100,40,0x1107);
	TFT_Put_Figure(0,448,tp_x,0xFFFF);
	TFT_Put_Figure(0,464,tp_y,0xFFFF);
}
