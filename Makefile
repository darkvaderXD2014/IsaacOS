
C_SOURCES := $(shell find . -name "*.c")
C_SOURCES := $(filter-out $(EXCLUDE), $(C_SOURCES))
C_OBJECTS = $(patsubst %.c, %.c.o, $(C_SOURCES))
S_SOURCES = $(shell find . -name "*.s")
S_OBJECTS = $(patsubst %.s, %.s.o, $(S_SOURCES))
AS_SOURCES = $(shell find . -name "*.asm")
AS_OBJECTS = $(patsubst %.asm, %.asm.o, $(AS_SOURCES))


CC = i686-elf-gcc
LD = i686-elf-ld
ASM = i686-elf-as
NASM = nasm

INCDIR := -I./src/include 

C_FLAGS = -c -Wall -m32 -ggdb -gstabs+ -nostdinc -fno-builtin -fno-stack-protector $(INCDIR)
LD_FLAGS = -T ./src/boot/linker.ld -m elf_i386 -nostdlib
ASM_FLAGS = --32
NASM_FLAGS = -Werror -felf

all: $(S_OBJECTS) $(C_OBJECTS) $(AS_OBJECTS) link
	@echo "DONE!"

%.c.o: %.c
	@echo "Compiling C" $< ...
	$(CC) $(C_FLAGS) $< -o $@

%.s.o: %.s
	@echo "Compiling Assembly" $< ...
	$(ASM) $(ASM_FLAGS) -o $@ $<
%.asm.o: %.asm 
	@echo "Compiling NASM" $< ...
	$(NASM) $(NASM_FLAGS) -o $@ $<

link:
	@echo "Making the kernel."
	@$(LD) $(LD_FLAGS) $(S_OBJECTS) $(C_OBJECTS) $(AS_OBJECTS) -o kernel.bin

isoimage: compile
	cp kernel.bin iso/boot/.
	genisoimage -R \
		-b boot/grub/stage2_eltorito \
		-no-emul-boot				 \
		-boot-load-size 4			 \
		-A isaacos					 \
		-input-charset utf8			 \
		-quiet						 \
		-boot-info-table			 \
		-o isaacos.iso				 \
iso
.PHONY:compile
compile: $(S_OBJECTS) $(C_OBJECTS) $(AS_OBJECTS) link

.PHONY:clean
clean:
	@echo "Removing All Objectfiles and kernel."
	$(RM) $(S_OBJECTS) $(C_OBJECTS) $(AS_OBJECTS) kernel.bin isaacos.iso
.PHONY:qemu-kernel
qemu-kernel:
	@echo "Debugging kernel mode"
	@qemu-system-i386 -kernel kernel.bin
.PHONY:toolchain
toolchain: 
	@bash tools/build.sh
