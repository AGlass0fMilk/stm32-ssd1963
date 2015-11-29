#ifndef FONTS_H
#define FONTS_H
#include <fonts.h>
#endif

#ifndef PRIMITIVES_H
#define PRIMITIVES_H
#include <primitives.h>
#endif

#ifndef MAX11802_H
#define MAX11802_H
#include <max11802.h>
#endif

extern unsigned int w_index;
extern unsigned int tp_int;
extern unsigned int tp_x;
extern unsigned int tp_y;

extern unsigned int adc_cs1;
extern unsigned int adc_cs2;

void TP_PROCESS(void);
void TFT_MAIN(void);
void TP_MAIN(void);
void TFT_BATCONFIG(void);
void TP_BATCONFIG(void);
