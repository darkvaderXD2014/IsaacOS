ENTRY(start)

SECTIONS
{
	      . = 1M;

         .text BLOCK(4K): ALIGN(4K) {
               code = .;
               *(.text)
         }

         .data BLOCK(4K): ALIGN(4K) {
               data = .;
               *(.data)
               *(.rodata)
         }

         .bss BLOCK(4K): ALIGN(4K) {
              bss = .;
              *(.bss)
         }

        end = .;
} 
