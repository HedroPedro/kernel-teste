AS=nasm
ASFLAGS=-felf32
CC=i686-elf-gcc
CCFLAGS=-lgcc -nostdlib -masm=intel -ffreestanding -std=gnu99 -Wextra -Wall -T
SRCDIR=src
BUILDDIR=build
SCRIPTDIR=scripts

C_SRC=$(wildcard $(SRCDIR)/**/*.c) $(wildcard $(SRCDIR)/*.c)
ASM_SRC=$(wildcard $(SRCDIR)/**/*.asm) $(wildcard $(SRCDIR)/*.asm)

ASM_OBJ=$(patsubst $(SRCDIR)/%.asm,$(BUILDDIR)/%.o,$(ASM_SRC))
.PHONY: all clean

all: $(BUILDDIR)/os.bin
	dd if=$< of=$(BUILDDIR)/os.img

$(BUILDDIR)/os.bin: $(ASM_OBJ) $(C_SRC)
	$(CC) $^ -o $@ $(CCFLAGS) $(SCRIPTDIR)/boot.ld

$(BUILDDIR)/%.o: $(SRCDIR)/%.asm | $(BUILDDIR)/
	$(AS) $(ASFLAGS) $< -o $@


$(BUILDDIR)/:
	mkdir $(BUILDDIR)

clean:
	rm -f $(BUILDDIR)/*.bin $(BUILDDIR)/*.img $(BUILDDIR)/*.o
