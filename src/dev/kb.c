#include <dev/kb.h>
#include <isaacos.h>
#include <utypes.h>
#include <vga.h>
#include <libc/string.h>
#include <cpu/isr.h>

#define BACKSPACE 0x0E
#define ENTER 0x1C
#define LEFT_SHIFTDOWN 0x2a
#define LEFT_SHIFTUP 0xAA
#define RIGHT_SHIFTDOWN 0x36

#define KEY_RELEASED 0x80
#define KEY_PRESSED 0x7F


void put_kbuffer(uint8 scancode);
void put_sbuffer(uint8 scancode);
static char key_buffer[256];

#define SC_MAX 57



const char *sc_name[] = { "ERROR", "Esc", "1", "2", "3", "4", "5", "6",
    "7", "8", "9", "0", "-", "=", "\b", "Tab", "q", "w", "e",
        "r", "t", "y", "u", "i", "o", "p", "[", "]", "Enter", "Lctrl",
        "a", "s", "d", "f", "g", "h", "j", "k", "l", ";", "'", "`",
        "LShift", "\\", "z", "x", "c", "v", "b", "n", "m", ",", ".",
        "/", "RShift", "Keypad *", "LAlt", "Spacebar"};
const char sc_ascii[] = { '?', '?', '1', '2', '3', '4', '5', '6',
    '7', '8', '9', '0', '-', '=', '?', '?', 'q', 'w', 'e', 'r', 't', 'y',
        'u', 'i', 'o', 'p', '[', ']', '?', '?', 'a', 's', 'd', 'f', 'g',
        'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z', 'x', 'c', 'v',
'b', 'n', 'm', ',', '.', '/', 0, 0, 0, ' '};

const char *usc_name[] = { "ERROR", "Esc", "!", "@", "#", "$", "%", "^",
    "&", "*", "(", ")", "_", "+", "\b", "Tab", "Q", "W", "E",
        "R", "T", "Y", "U", "I", "O", "P", "{", "}", "Enter", "Lctrl",
        "A", "S", "D", "F", "G", "H", "J", "K", "L", ":", "", "~",
        "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", "<", ">",
        "?", "RShift", "Keypad *", "LAlt", "Spacebar"};
const char usc_ascii[] = { '?', '?', '!', '@', '#', '$', '%', '^',
    '&', '*', '(', ')', '_', '+', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y',
        'U', 'I', 'O', 'P', '{', '}', '?', '?', 'A', 'S', 'D', 'F', 'G',
        'H', 'J', 'K', 'L', ':', '\'', '~', '?', '\\', 'Z', 'X', 'C', 'V',
'B', 'N', 'M', '<', '>', '0', '0', '0', '0', ' '};

void put_kbuffer(uint8 scancode)
{
	char letter = usc_ascii[(int)scancode];
    char str[2] = {letter, '\0'};
    append(key_buffer, letter);
    puts(str);
}

void put_buffer(uint8 scancode)
{

	char letter = sc_ascii[(int)scancode];
    char str[2] = {letter, '\0'};
    append(key_buffer, letter);
    puts(str);
}

static void keyboard_callback(registers_t regs) {
    uint8 scancode = inportb(0x60);
    static int state = 0;

    if (scancode >= SC_MAX) return;

    switch(scancode)
    {
        case BACKSPACE:
        {
            backspace(key_buffer);
            put('\b');
            break;
        }
        case ENTER:
        {
            puts("\n");
            user_input(key_buffer);
            key_buffer[0] = '\0';
            break;
        }
        default:
        {
            if(state == 1)
            {
                char letter = usc_ascii[(int)scancode];
                char str[2] = {letter, '\0'};
                append(key_buffer, letter);
                puts(str);
            }
            else
            {
                char letter = sc_ascii[(int)scancode];
                char str[2] = {letter, '\0'};
                append(key_buffer, letter);
                puts(str);
            }
            break;
        }

    }


    UNUSED(regs);
}

void init_keyboard() {
   register_interrupt_handler(IRQ1, keyboard_callback);
}
