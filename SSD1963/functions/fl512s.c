#ifndef FL512S_H
#define FL512S_H
#include <fl512s.h>
#endif


void FL512S_Initialization(void)
{
	SPI_InitTypeDef SPI_InitStructure;
	GPIO_InitTypeDef GPIO_InitDef;
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
	 
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_SPI2);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_SPI2);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_SPI2);
	 
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
}

void SET_FLASH_CS(void)
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
}

void RESET_FLASH_CS(void)
{
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
}

/*Send the byte "cmd" over the configured SPIx bus. "clkout" is the number of dummy bytes required after "cmd".*/
void Flash_Send_Command(unsigned char cmd, unsigned long clkout)
{
    unsigned int i;

    //SET_FLASH_CS();
		SPI_I2S_SendData(SPI2, cmd);

    //Clock-out cycles if necessary
    for(i=0;i<clkout;i++)
    {
      SPI_I2S_SendData(SPI2, 0xFF);
    }
    
    //RESET_FLASH_CS();
}

void FL_RDID(void)
{
	unsigned int i;
	
	flash_buffer_enable=0;
	
	SET_FLASH_CS();
	delay_1ms(1);
	
	SPI_I2S_SendData(SPI2, 0x05);
  //SPI_I2S_SendData(SPI2, 0xFF);
	//SPI_I2S_SendData(SPI2, 0xFF);
	//SPI_I2S_SendData(SPI2, 0xFF);

	flash_buffer_enable=1;
	
	for(i=0;i<10;i++)
	{
		flash_index=i;
		SPI_I2S_SendData(SPI2, 0xFF);
	}
	
	flash_buffer_enable=0;
	
	delay_1ms(1);
	RESET_FLASH_CS();
	
}
