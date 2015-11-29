#ifndef PRIMITIVES_H
#define PRIMITIVES_H
#include <primitives.h>
#endif

#define ABS(X)  ((X) > 0 ? (X) : -(X)) 

/*Sets horizontal filling range*/
void Set_Column(unsigned long SC, unsigned long EC)
{
		SSD1963__set_column_address(SC>>8,SC & 0x00FF,EC>>8,EC & 0x00FF);
}

/*Sets vertical filling range*/
void Set_Page(unsigned long SP, unsigned long EP)
{
	SSD1963__set_page_address(SP>>8,SP & 0x00FF,EP>>8,EP & 0x00FF);
}

void TFT_Backlight_FadeIn(unsigned int delay_ms)
{
	unsigned int i;
	
	for(i=SSD1963__get_pwm_conf(2);i<0xFF;i++)
	{
		SSD1963__set_pwm_conf(0x06,i,0x01,0xF0,0x00,0x00);
		delay_1ms(delay_ms);
	}
}

void TFT_Backlight_FadeOut(unsigned int delay_ms)
{
	unsigned int i;
	
	for(i=SSD1963__get_pwm_conf(2);i>0x00;i--)
	{
		SSD1963__set_pwm_conf(0x06,i,0x01,0xF0,0x00,0x00);
		delay_1ms(delay_ms);
	}
}

/*Fill the entire screen with RGB color.*/
//rgb     :   RGB color (565 format)
void TFT_Fill_Screen(unsigned int rgb)
{
    unsigned long pixel=0;

    Set_Column(0,799);
    Set_Page(0,479);

    //Start Write Command
    SSD1963__write_memory_start();

    for(pixel=0;pixel<384000;pixel++)
    {
        TFT_RAM=rgb;
    }
}

void TFT_Put_Pixel(unsigned int x_pos, unsigned int y_pos, unsigned int rgb)
{
	Set_Column(x_pos,x_pos);
  Set_Page(y_pos,y_pos);
	
	//Start Write Command
  SSD1963__write_memory_start();
	TFT_RAM=rgb;
}


void TFT_DrawRect(uint16_t Xpos, uint16_t Ypos, uint16_t Height, uint16_t Width, uint16_t rgb)
{
 int x,y;
 x=0;
 y=0;
 while(x<Height+1)
 {
   TFT_Put_Pixel(Xpos+x,Ypos,rgb);
   TFT_Put_Pixel(Xpos+x,Ypos+Width,rgb);
   x++;
 }
 while(y<Width+1)
 {
   TFT_Put_Pixel(Xpos,Ypos+y,rgb);
   TFT_Put_Pixel(Xpos+Height,Ypos+y,rgb);
   y++;
 }
}

void TFT_DrawSquare(uint16_t Xpos, uint16_t Ypos, uint16_t a, uint16_t rgb)
{
 int x,y;
 x=0;
 y=0;
 while(x<a+1)
 {
   TFT_Put_Pixel(Xpos+x,Ypos,rgb);
   TFT_Put_Pixel(Xpos+x,Ypos+a,rgb);
   x++;
 }
 while(y<a+1)
 {
   TFT_Put_Pixel(Xpos,Ypos+y,rgb);
   TFT_Put_Pixel(Xpos+a,Ypos+y,rgb);
   y++;
 }
}

void TFT_DrawFullRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height, uint16_t rgb)
{
  int x,y;
  x=0;
  y=0;
  while(x<Width)
  {
    while(y<Height)
    {
      TFT_Put_Pixel(Xpos+x,Ypos+y,rgb);
      y++;
    }
    y=0;
    x++;
  }
}

void TFT_DrawFullSquare(uint16_t Xpos, uint16_t Ypos, uint16_t a, uint16_t rgb)
{
  int x,y;
  x=0;
  y=0;
  while(x<a)
  {
    while(y<a)
    {
      TFT_Put_Pixel(Xpos+x,Ypos+y,rgb);
      y++;
    }
    y=0;
    x++;
  }
}


void TFT_DrawUniLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t rgb)
{
  int16_t deltax = 0, deltay = 0, x = 0, y = 0, xinc1 = 0, xinc2 = 0, 
  yinc1 = 0, yinc2 = 0, den = 0, num = 0, numadd = 0, numpixels = 0, 
  curpixel = 0;
  
  deltax = ABS(x2 - x1);        /* The difference between the x's */
  deltay = ABS(y2 - y1);        /* The difference between the y's */
  x = x1;                       /* Start x off at the first pixel */
  y = y1;                       /* Start y off at the first pixel */
  
  if (x2 >= x1)                 /* The x-values are increasing */
  {
    xinc1 = 1;
    xinc2 = 1;
  }
  else                          /* The x-values are decreasing */
  {
    xinc1 = -1;
    xinc2 = -1;
  }
  
  if (y2 >= y1)                 /* The y-values are increasing */
  {
    yinc1 = 1;
    yinc2 = 1;
  }
  else                          /* The y-values are decreasing */
  {
    yinc1 = -1;
    yinc2 = -1;
  }
  
  if (deltax >= deltay)         /* There is at least one x-value for every y-value */
  {
    xinc1 = 0;                  /* Don't change the x when numerator >= denominator */
    yinc2 = 0;                  /* Don't change the y for every iteration */
    den = deltax;
    num = deltax / 2;
    numadd = deltay;
    numpixels = deltax;         /* There are more x-values than y-values */
  }
  else                          /* There is at least one y-value for every x-value */
  {
    xinc2 = 0;                  /* Don't change the x for every iteration */
    yinc1 = 0;                  /* Don't change the y when numerator >= denominator */
    den = deltay;
    num = deltay / 2;
    numadd = deltax;
    numpixels = deltay;         /* There are more y-values than x-values */
  }
  
  for (curpixel = 0; curpixel <= numpixels; curpixel++)
  {
    TFT_Put_Pixel(x, y, rgb);   /* Draw the current pixel */
    num += numadd;              /* Increase the numerator by the top of the fraction */
    if (num >= den)             /* Check if numerator >= denominator */
    {
      num -= den;               /* Calculate the new numerator value */
      x += xinc1;               /* Change the x as appropriate */
      y += yinc1;               /* Change the y as appropriate */
    }
    x += xinc2;                 /* Change the x as appropriate */
    y += yinc2;                 /* Change the y as appropriate */
  }
}

void TFT_DrawFullCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius, uint16_t rgb)
{
  int16_t  D;
  uint16_t  CurX;
  uint16_t  CurY;
  D = 3 - (Radius << 1);
  CurX = 0;
  CurY = Radius;
  
  while (CurX <= CurY)
  {
    TFT_DrawUniLine(Xpos + CurX, Ypos + CurY,Xpos + CurX, Ypos - CurY, rgb);
    TFT_DrawUniLine(Xpos - CurX, Ypos + CurY,Xpos - CurX, Ypos - CurY, rgb);
    TFT_DrawUniLine(Xpos + CurY, Ypos + CurX,Xpos + CurY, Ypos - CurX, rgb);
    TFT_DrawUniLine(Xpos - CurY, Ypos + CurX,Xpos - CurY, Ypos - CurX, rgb);
    
    if (D < 0)
    { 
      D += (CurX << 2) + 6;
    }
    else
    {
      D += ((CurX - CurY) << 2) + 10;
      CurY--;
    }
    CurX++;
  }
}

void TFT_DrawCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius, uint16_t rgb)
{
  int16_t  D;/* Decision Variable */ 
  uint16_t  CurX;/* Current X Value */
  uint16_t  CurY;/* Current Y Value */ 
  D = 3 - (Radius << 1);
  CurX = 0;
  CurY = Radius;
  while (CurX <= CurY)
  {
    TFT_Put_Pixel(Xpos + CurX, Ypos + CurY, rgb);
    TFT_Put_Pixel(Xpos + CurX, Ypos - CurY, rgb);
    TFT_Put_Pixel(Xpos - CurX, Ypos + CurY, rgb);
    TFT_Put_Pixel(Xpos - CurX, Ypos - CurY, rgb);
    TFT_Put_Pixel(Xpos + CurY, Ypos + CurX, rgb);
    TFT_Put_Pixel(Xpos + CurY, Ypos - CurX, rgb);
    TFT_Put_Pixel(Xpos - CurY, Ypos + CurX, rgb);
    TFT_Put_Pixel(Xpos - CurY, Ypos - CurX, rgb);
    if (D < 0)
    { 
      D += (CurX << 2) + 6;
    }
    else
    {
      D += ((CurX - CurY) << 2) + 10;
      CurY--;
    }
    CurX++;
  }
}

//Draw a bitmap (16bit 565 format) on the screen
void TFT_DrawImage(unsigned int x_pos, unsigned int y_pos, unsigned int x_len, unsigned int y_len, unsigned short * image)
{
	unsigned int i=0;
	unsigned int j=0;

	for(j=0;j<y_len;j++)
	{
		for(i=0;i<x_len;i++)
		{
			TFT_Put_Pixel(x_pos+i,y_pos+j,image[i+j*x_len]);
		}
	}
	
}

void TFT_ImageTest(void)
{
	unsigned i=0;
	unsigned j=0;
	
	TFT_Fill_Screen(0xFFFF);
	
	for(j=0;j<5;j++)
	{
		for(i=0;i<4;i++)
		{
			TFT_DrawImage(i*200,j*96,200,96,pic_cortex_logo);
		}
	}
	delay_1ms(2000);
}

//Displays a color gradient on the screen
void TFT_ColorTest(uint16_t d)
{
	unsigned int i=0;
	unsigned int rgb=0xF800;
	
	for(i=0;i<32;i++)
	{
		//TFT_DrawFullSquare(350,190,100,(rgb & 0xFFE0) | i);
		TFT_Fill_Screen((rgb & 0xFFE0) | i);
		delay_1ms(d);
	}
	rgb=0xF81F;
	for(i=31;i>0;i--)
	{
		//TFT_DrawFullSquare(350,190,100,(rgb & 0x07FF) | (i<<11));
		TFT_Fill_Screen((rgb & 0x07FF) | (i<<11));
		delay_1ms(d);
	}
	rgb=0x001F;
	for(i=0;i<32;i++)
	{
		//TFT_DrawFullSquare(350,190,100,(rgb & 0xF81F) | (i<<6));
		TFT_Fill_Screen((rgb & 0xF81F) | (i<<6));
		delay_1ms(d);
	}
	rgb=0x07FF;
	for(i=31;i>0;i--)
	{
		//TFT_DrawFullSquare(350,190,100,(rgb & 0xFFE0) | i);
		TFT_Fill_Screen((rgb & 0xFFE0) | i);
		delay_1ms(d);
	}
	rgb=0x07E0;
	for(i=0;i<32;i++)
	{
		//TFT_DrawFullSquare(350,190,100,(rgb & 0x07FF) | (i<<11));
		TFT_Fill_Screen((rgb & 0x07FF) | (i<<11));
		delay_1ms(d);
	}
	rgb=0xFFE0;
	for(i=31;i>0;i--)
	{
		//TFT_DrawFullSquare(350,190,100,(rgb & 0xF81F) | (i<<6));
		TFT_Fill_Screen((rgb & 0xF81F) | (i<<6));
		delay_1ms(d);
	}
	rgb=0xF800;
}

void TFT_DrawCross(unsigned int x_pos, unsigned y_pos, unsigned int rgb)
{
	TFT_DrawUniLine(x_pos-10,y_pos,x_pos+10,y_pos,rgb);
	TFT_DrawUniLine(x_pos,y_pos-10,x_pos,y_pos+10,rgb);
}

void TFT_DrawProgressBar(unsigned int x_pos, unsigned int y_pos, unsigned int x_len, unsigned int y_len, unsigned int d, unsigned int rgb, unsigned int rgb_bk)
{
	TFT_DrawRect(x_pos,y_pos,x_len,y_len,rgb);
	TFT_DrawFullRect(x_pos+2,y_pos+2,x_len-3,y_len-3,rgb_bk);
	TFT_DrawFullRect(x_pos+2,y_pos+2,(d*(x_len-3))/100,y_len-3,rgb);
}


void TFT_Update_CSV(unsigned int x_pos, unsigned int y_pos)
{
	//Update progress bars
	TFT_Put_String(x_pos,y_pos,"VS_1 = ",15,classicConsole_16ptDescriptors,classicConsole_16ptBitmaps,3,1,0xFFFF);
	TFT_DrawProgressBar(x_pos,y_pos+15,200,20,20,0xFFFF,0x1107);
	
	TFT_Put_String(x_pos,y_pos+50,"VS_2 = ",15,classicConsole_16ptDescriptors,classicConsole_16ptBitmaps,3,1,0xFFFF);
	TFT_DrawProgressBar(x_pos,y_pos+50+15,200,20,30,0xFFFF,0x1107);
	
	TFT_Put_String(x_pos,y_pos+100,"VS_3 = ",15,classicConsole_16ptDescriptors,classicConsole_16ptBitmaps,3,1,0xFFFF);
	TFT_DrawProgressBar(x_pos,y_pos+100+15,200,20,40,0xFFFF,0x1107);
	
	TFT_Put_String(x_pos,y_pos+150,"VS_4 = ",15,classicConsole_16ptDescriptors,classicConsole_16ptBitmaps,3,1,0xFFFF);
	TFT_DrawProgressBar(x_pos,y_pos+150+15,200,20,50,0xFFFF,0x1107);
	
	TFT_Put_String(x_pos,y_pos+200,"VS_5 = ",15,classicConsole_16ptDescriptors,classicConsole_16ptBitmaps,3,1,0xFFFF);
	TFT_DrawProgressBar(x_pos,y_pos+200+15,200,20,60,0xFFFF,0x1107);
}

