#include <utypes.h>
#include <isaacos.h>
#include <colors.h>

unsigned short *vgamemptr;
int attrib = 0xF;

int cursor_x = 0;
int cursor_y = 0;


void puts_backspace()
{
     putch(0x80, BLACK, WHITE);   
}

void scroll(void)
{
    unsigned blank, temp;
    blank = 0x20 | (attrib << 8);


    if(cursor_y >= 25)
    {
       
        temp = cursor_y - 25 + 1;
        memcpy (vgamemptr, vgamemptr + temp * 80, (25 - temp) * 80 * 2);
        memsetw (vgamemptr + (25 - temp) * 80, blank, 80);
        cursor_y = 25 - 1;
    }
}


void move_csr(void)
{
    unsigned temp;

     temp = cursor_y * 80 + cursor_x;

    outportb(0x3D4, 14);
    outportb(0x3D5, temp >> 8);
    outportb(0x3D4, 15);
    outportb(0x3D5, temp);
}


void cls()
{
    unsigned blank;
    int i;


    blank = 0x20 | (attrib << 8);


    for(i = 0; i < 25; i++)
        memsetw (vgamemptr + i * 80, blank, 80);


    cursor_x = 0;
    cursor_y = 0;
    move_csr();
}


void putch(char c, uint8 backcolor, uint8 forecolor)
{
    uint8 attributeByte = (backcolor << 4) | (forecolor & 0x0F);
    unsigned short *where;
    unsigned att = attrib << 8;
    
    if (c == 0x08 && cursor_x)
	{
		if (cursor_x > 0)
		{
			cursor_x--;
			put(' ');
			cursor_x--;
		}
	}
    else if(c == 0x09)
    {
        cursor_x = (cursor_x + 8) & ~(8 - 1);
    }
    else if(c == '\r')
    {
        cursor_x = 0;
    }
    else if(c == '\n')
    {
        cursor_x = 0;
        cursor_y++;
    }
    else if(c >= ' ')
    {
        where = vgamemptr + (cursor_y * 80 + cursor_x);
        *where = c | att;	
        cursor_x++;
    }
    if(cursor_x >= 80)
    {
        cursor_x = 0;
        cursor_y++;
    }
    scroll();
    move_csr();
}

void put(const char c)
{
    unsigned short *where;
    unsigned att = attrib << 8;
    
    if (c == 0x08 && cursor_x)
	{
		if (cursor_x > 0)
		{
			cursor_x--;
			put(' ');
			cursor_x--;
		}
	}
    else if(c == 0x09)
    {
        cursor_x = (cursor_x + 8) & ~(8 - 1);
    }
    else if(c == '\r')
    {
        cursor_x = 0;
    }
    else if(c == '\n')
    {
        cursor_x = 0;
        cursor_y++;
    }
    else if(c == '\b')
    {
        cursor_x--;
    }
    else if(c >= ' ')
    {
        where = vgamemptr + (cursor_y * 80 + cursor_x);
        *where = c | att;	
        cursor_x++;
    }
    if(cursor_x >= 80)
    {
        cursor_x = 0;
        cursor_y++;
    }
    scroll();
    move_csr();
}

void puts(unsigned char *text)
{
    int i;

    for (i = 0; i < strlen(text); i++)
    {
        putch(text[i], BLACK, DARK_GREY);
    }
}

void settextcolor(int forecolor, int backcolor)
{

    attrib = (backcolor << 4) | (forecolor);
}

void setcurrentcolor(int color_code)
{
        attrib = color_code;
}

void puts_colored(unsigned char *text, int forecolor, int backcolor)
{
    int current_color = attrib;
    settextcolor(forecolor, backcolor);
    puts(text);
    setcurrentcolor(current_color);
}   
void init_video(void)
{
    vgamemptr = (unsigned short *)0xB8000;
    cls();
}
