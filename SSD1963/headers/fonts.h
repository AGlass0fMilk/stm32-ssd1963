#ifndef PRIMITIVES_H
#define PRIMITIVES_H
#include <primitives.h>
#endif

extern const unsigned int helveticaWorld_24ptBitmaps[];
extern const unsigned int helveticaWorld_24ptDescriptors[][2];

extern const unsigned int classicConsole_16ptBitmaps[];
extern const unsigned int classicConsole_16ptDescriptors[][2];

extern const unsigned int helveticaWorld_16ptBitmaps[];
extern const unsigned int helveticaWorld_16ptDescriptors[][2];


void TFT_Put_Char(unsigned int x_pos, unsigned int y_pos, unsigned int descriptor_index, unsigned int c_height, const unsigned int c_descriptor[][2], const unsigned int c_bitmap[], unsigned int rgb);
void TFT_Put_String(unsigned int x_pos, unsigned int y_pos, char * str, unsigned int c_height, const unsigned int c_descriptor[][2], const unsigned int c_bitmap[],unsigned int c_space, unsigned int c_interspace, unsigned int rgb);
unsigned int TenPow(unsigned int e);
void TFT_Put_Figure(unsigned int x_pos, unsigned int y_pos, unsigned int f, unsigned int rgb);

