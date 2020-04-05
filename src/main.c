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
    puts("isaacOS> ");


}

void motd(void)
{
    puts_colored("Isaac", WHITE,BLACK);
    puts_colored("OS ", LIGHT_BLUE,BLACK);
    puts("0.01\n");
    puts("Made by Isaac Sapelino. \n\n");
    puts("Type 'help' for commands.\n");
    puts("\n");
}

void user_input(char *input)
{
    do
    {

        if (strcmp(input,"help") == 0) {
            puts("\nThese are the listed commands: \n");
            puts("clear - clears the screen text. \n");
            puts("motd - prints the message of the day. \n");
            puts("end - to shutdown CPU \n");
        } else if (strcmp(input,"clear") == 0)
        {
            cls();
        }
        else if (strcmp(input,"motd") == 0)
        {
            motd();
        }
        else
        {
            puts_colored("Unknown command:", WHITE, RED);
            puts(" ");
            puts(input);
            puts("\n");
        }
        puts("isaacOS> ");
    } while(strcmp(input, "end") == 0);
}




