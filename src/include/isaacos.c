#include "utypes.h"
#include "isaacos.h"
#include "libc/string.h"
unsigned char *memcpy(unsigned char *dest, const unsigned char *src, int count)
{
	char *csrc = (char *)src;
	char *cdest = (char *)dest;

	for (int i=0;i < count;i++)
	{
		cdest[i] = csrc[i];
	}
	return dest;
}

unsigned char *memset(unsigned char *dest, unsigned char val, int count)
{
    char *cdest = (char *)dest;

    while(*cdest && count > 0)
    {
    	*cdest = val;
    	cdest++;
    	count--;
    }
    return dest;
}

unsigned short *memsetw(unsigned short *dest, unsigned short val, int count)
{
    unsigned short *cdest = (unsigned short *)dest;
    while(*cdest && count > 0)
    {
    	*cdest = val;
    	cdest++;
    	count--;
    }
    return dest;
}

string int_to_string(int n)
{
	string ch = malloc(50);
	int_to_ascii(n,ch);
	int len = strlen(ch);
	int i = 0;
	int j = len - 1;
	while(i<(len/2 + len%2))
	{
		char tmp = ch[i];
		ch[i] = ch[j];
		ch[j] = tmp;
		i++;
		j--;
	}
	return ch;
}

int str_to_int(string ch)
{
	int n = 0;
	int p = 1;
	int stringLen = strlen(ch);
	int i;
	for (i = stringLen-1;i>=0;i--)
	{
		n += ((int)(ch[i] - '0')) * p;
		p *= 10;
	}
	return n;
}

unsigned char int_to_hex(uint8 in)
{
    uint32 rmd, q, dn=0, m, l;
    int i=1,j,tmp;
    char s;
    q = in;
    for(l=q; l>0; l=l/16)
    {
        tmp = l % 16;
        if(tmp < 10)
            tmp = tmp + 48; else
            tmp = tmp + 55;
            dn=dn*100+tmp;
    }
    for(m=dn; m>0; m=m/100)
    {
        s=m % 100;
    }
    return s;
}

void * malloc(int nbytes)
{
	char variable[nbytes];
	return &variable;
}

unsigned char inportb (unsigned short _port)
{
    unsigned char rv;
    __asm__ __volatile__("inb %%dx, %%al" : "=a" (rv) : "dN" (_port));
    return rv;
}

void outportb (unsigned short _port, unsigned char _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

void outportw (uint16 port, uint16 data)
{
   asm volatile ("outw %w0, %w1" : : "a" (data), "Nd" (port));
}
