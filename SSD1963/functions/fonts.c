#ifndef FONTS_H
#define FONTS_H
#include <fonts.h>
#endif

//c_height in bits
void TFT_Put_Char(unsigned int x_pos, unsigned int y_pos, unsigned int descriptor_index, unsigned int c_height, const unsigned int c_descriptor[][2], const unsigned int c_bitmap[], unsigned int rgb)
{
	unsigned int i;
	unsigned int j;                                                                                                                       
	unsigned int k;
	
	unsigned int c_index;
	unsigned int c_width;
	unsigned int n_bytes;
	unsigned int c_bytes;
	
	unsigned int bitmask;
	unsigned int bittest;
	
	c_index=c_descriptor[descriptor_index][1]; //0
	c_width=c_descriptor[descriptor_index][0]; //30
	
	if(c_width-8*(c_width/8)!=0)
	{
		c_bytes=(c_width/8)+1; //188
	}
	else
	{
		c_bytes=c_width/8;
	}
	
	n_bytes=c_height*c_bytes;
	
	for(j=0;j<n_bytes;j=j+c_bytes)
	{
		for(i=0;i<c_bytes;i++)
		{
			bitmask=0x80;
			for(k=0;k<8;k++)
			{	
				bittest=c_bitmap[c_index+i+j] & bitmask;
				if(bittest==bitmask)
				{
					TFT_Put_Pixel(x_pos+i*8+k,y_pos+j/c_bytes,rgb);
				}
				bitmask=bitmask>>1;
			}
		}
	}
}


void TFT_Put_String(unsigned int x_pos, unsigned int y_pos, char * str, unsigned int c_height, const unsigned int c_descriptor[][2], const unsigned int c_bitmap[],unsigned int c_space, unsigned int c_interspace, unsigned int rgb)
{
	unsigned int i;
		
	i=0;
	while(str[i]!=0)
	{
		if(str[i]>32)
		{
			TFT_Put_Char(x_pos, y_pos, str[i]-33, c_height, c_descriptor, c_bitmap, rgb);
		}
		else
		{
			x_pos+=c_descriptor[str[i]-33][0]+c_space;
		}
		x_pos+=c_descriptor[str[i]-33][0]+c_interspace;
		i++;
	}
}


unsigned int TenPow(unsigned int e)
{
	switch(e)
	{
		case 0: return 1;
		case 1: return 10;
		case 2: return 100;
		case 3: return 1000;
		case 4: return 10000;
		case 5: return 100000;
		case 6: return 1000000;
		case 7: return 10000000;
		case 8: return 100000000;
		case 9: return 1000000000;
	}
	return 0;
}

void TFT_Put_Figure(unsigned int x_pos, unsigned int y_pos, unsigned int f, unsigned int rgb)
{
	char str[]={0,0,0,0,0,0,0,0,0,0};
	unsigned int i=0;
	unsigned int d=0;
	unsigned int n=0;
	
	while(f>=TenPow(n))
	{
		n++;
	}
	
	if(n!=0)
	{
		i=n;
	}
	else
	{
		n=1;
		i=n;
	}
	
	while(1)
	{
		i--;
		d=f/TenPow(i);
		f=f-d*TenPow(i);
		str[(n-1)-i]=d+48;
		
		if(i==0) break;
	}
	
	TFT_Put_String(x_pos,y_pos,str,15,classicConsole_16ptDescriptors,classicConsole_16ptBitmaps,3,1,rgb);
}


