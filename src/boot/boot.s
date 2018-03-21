.set ISAACOS_ALIGN,         1 << 0
.set ISAACOS_MEMINFO,       1 << 1
.set ISAACOS_FLAGS,         ISAACOS_ALIGN | ISAACOS_MEMINFO
.set ISAACOS_MAGIC_CODE,    0x1BADB002
.set ISAACOS_CHECKSUM,      -(ISAACOS_MAGIC_CODE + ISAACOS_FLAGS)

  .global mboot
  .extern code
  .extern bss
  .extern end
mboot:
  .long ISAACOS_MAGIC_CODE
  .long ISAACOS_FLAGS
  .long ISAACOS_CHECKSUM
  .long mboot
  .long code
  .long bss
  .long end
  .long start

  .global start
  .extern isaacos_main
start:
  push %ebx
  cli
  call isaacos_main
hang:
  jmp hang
 
