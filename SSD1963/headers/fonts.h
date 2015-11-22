#ifndef PRIMITIVES_H
#define PRIMITIVES_H
#include <primitives.h>
#endif

extern unsigned int classicConsole_16ptBitmaps[];
extern unsigned int classicConsole_16ptDescriptors[95][2];

void TFT_Put_Char(unsigned int x_pos, unsigned int y_pos, unsigned int start_index, unsigned int rgb);
void TFT_Put_String(unsigned int x_pos, unsigned int y_pos, char str[], unsigned int rgb);
void TFT_TextTest(void);
