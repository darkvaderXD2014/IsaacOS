#ifndef ISAACOS_H
#define ISAACOS_H

#include "utypes.h"

struct regs
{
    unsigned int gs, fs, es, ds; 
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax; 
    unsigned int int_no, err_code; 
    unsigned int eip, cs, eflags, useresp, ss; 
};


extern unsigned char *memcpy(unsigned char *dest, const unsigned char *src, int count);
extern unsigned char *memset(unsigned char *dest, unsigned char val, int count);
extern unsigned short *memsetw(unsigned short *dest, unsigned short val, int count);
extern size_t strlen(const char *str);
extern unsigned char inportb (unsigned short _port);
void outportw (uint16 port, uint16 data);
extern void outportb (unsigned short _port, unsigned char _data);
void int_to_ascii(int n, char str[]);
void * malloc(int nbytes);
void user_input(char *input);



#define UNUSED(x) (void)(x)

#endif
