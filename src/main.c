#include <isaacos.h>
#include <vga.h>
#include <cpu/isr.h>
#include <cpu/idt.h>
#include <libc/string.h>
#include <cpu/timer.h>
#include <dev/kb.h>

// PRIVATE FUNCTIONS
void motd(void);

void isaacos_main(struct multiboot *mboot_ptr)
{
    isr_install();    
    asm volatile("sti");    
    init_timer(50);    
    init_keyboard();
    init_video();
    
    motd();
    
    
}

void motd(void)
{
    puts("ISAACOS Alpha 1\n");
    puts("Type HELP for help.\n");
    puts("isaacOS> ");   
}

void user_input(char *input) 
{
    do
    {
        
        if (strcmp(input,"HELP") == 0) {
            puts("\nThis is are the listed commands: \n");
            puts("END - to shutdown CPU \n");
        } else if (strcmp(input,"CLEAR") == 0) 
        {
            cls();
        }
        else if (strcmp(input,"MOTD") == 0) 
        {
            motd();
        }
        else
        {
            puts("Unknown command: ");
            puts(input);
            puts("\n");
        }
        puts("isaacOS> ");
    } while(strcmp(input, "END") == 0);  
}




