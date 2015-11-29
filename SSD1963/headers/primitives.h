#ifndef TFT_H
#define TFT_H
#include <tft.h>
#endif

#ifndef FONTS_H
#define FONTS_H
#include <fonts.h>
#endif

extern unsigned short pic_cortex_logo[];

void Set_Column(unsigned long SC, unsigned long EC);
void Set_Page(unsigned long SP, unsigned long EP);
void TFT_Backlight_FadeIn(unsigned int delay_ms);
void TFT_Backlight_FadeOut(unsigned int delay_ms);
void TFT_Fill_Screen(unsigned int rgb);
void TFT_Put_Pixel(unsigned int x_pos, unsigned int y_pos, unsigned int rgb);
void TFT_DrawSquare(uint16_t Xpos, uint16_t Ypos, uint16_t a, uint16_t rgb);
void TFT_DrawRect(uint16_t Xpos, uint16_t Ypos, uint16_t Height, uint16_t Width, uint16_t rgb);
void TFT_DrawFullRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height, uint16_t rgb);
void TFT_DrawFullSquare(uint16_t Xpos, uint16_t Ypos, uint16_t a, uint16_t rgb);
void TFT_DrawUniLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t rgb);
void TFT_DrawFullCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius, uint16_t rgb);
void TFT_DrawCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius, uint16_t rgb);
void TFT_DrawImage(unsigned int x_pos, unsigned int y_pos, unsigned int x_len, unsigned int y_len, unsigned short * image);
void TFT_ImageTest(void);
void TFT_ColorTest(uint16_t d);
void TFT_DrawCross(unsigned int x_pos, unsigned y_pos, unsigned int rgb);
void TFT_DrawProgressBar(unsigned int x_pos, unsigned int y_pos, unsigned int x_len, unsigned int y_len, unsigned int d, unsigned int rgb, unsigned int rgb_bk);
void TFT_Update_CSV(unsigned int x_pos, unsigned int y_pos);





