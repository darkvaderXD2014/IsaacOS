#ifndef VGA_H
#define VGA_H

#include "utypes.h"
#include "colors.h"

void putch(char c, uint8 backcolor, uint8 forecolor);
void put(const char c);
void puts(unsigned char *text);
void init_video(void);
void cls();

#endif
