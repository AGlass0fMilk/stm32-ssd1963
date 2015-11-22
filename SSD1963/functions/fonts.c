#ifndef FONTS_H
#define FONTS_H
#include <fonts.h>
#endif

void TFT_Put_Char(unsigned int x_pos, unsigned int y_pos, unsigned int start_index, unsigned int rgb)
{
	unsigned int j;
	unsigned int i;
	unsigned int bitmask;
	unsigned int bittest;
	
	
	for(j=start_index;j<start_index+15;j++)
	{
		bitmask=0x80;
		for(i=0;i<8;i++)
		{
			bittest=classicConsole_16ptBitmaps[j] & bitmask;
			if(bittest==bitmask)
			{
				TFT_Put_Pixel(x_pos+i,y_pos+j-start_index,rgb);
			}
			bitmask=bitmask>>1;	
		}
	}
}

void TFT_Put_String(unsigned int x_pos, unsigned int y_pos, char str[], unsigned int rgb)
{
	unsigned int i;
	
	i=0;
	while(str[i]!=0)
	{
		TFT_Put_Char(x_pos,y_pos-15,classicConsole_16ptDescriptors[str[i]-32][1],rgb);
		x_pos+=classicConsole_16ptDescriptors[str[i]-32][0]+1;
		i++;
	}
}

void TFT_TextTest(void)
{
	unsigned int i;
	TFT_Fill_Screen(0x0000);
	for(i=0;i<32;i++)
	{
		TFT_Put_String(0,15*(i+1),"The quick brown fox jumps over the lazy dog. 1234567890",0xFFFF);
		delay_1ms(60);
	}
	TFT_Fill_Screen(0x0000);
	for(i=0;i<32;i++)
	{
		TFT_Put_String(0,15*(i+1),"Cozy lummox gives smart squid who asks for job pen. 1234567890",0xFFFF);
		delay_1ms(60);
	}
	TFT_Fill_Screen(0x0000);
	for(i=0;i<32;i++)
	{
		TFT_Put_String(0,15*(i+1),"Grumpy wizards make toxic brew for the evil queen and jack. 1234567890",0xFFFF);
		delay_1ms(60);
	}
	TFT_Fill_Screen(0x0000);
	for(i=0;i<32;i++)
	{
		TFT_Put_String(0,15*(i+1),"How razorback-jumping frogs can level six piqued gymnasts! 1234567890",0xFFFF);
		delay_1ms(60);
	}
}
