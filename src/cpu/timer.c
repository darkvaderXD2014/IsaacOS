#include <cpu/timer.h>
#include <vga.h>
#include <utypes.h>
#include <isaacos.h>
#include <cpu/isr.h>

uint32 tick = 0;

static void timer_callback(registers_t regs) {
    UNUSED(regs);
}

void init_timer(uint32 freq) {

    register_interrupt_handler(IRQ0, timer_callback);

    uint32 divisor = 1193180 / freq;
    uint8 low  = (uint8)(divisor & 0xFF);
    uint8 high = (uint8)( (divisor >> 8) & 0xFF);
    outportb(0x43, 0x36); 
    outportb(0x40, low);
    outportb(0x40, high);
}

