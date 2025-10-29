AS=nasm
ASFLAGS=-felf32
CC=i686-elf-gcc
CCFLAGS=-lgcc -nostdlib -masm=intel -ffreestanding -std=gnu99 -Wextra -Wall -T
SRCDIR=src
BUILDDIR=build
SCRIPTDIR=scripts

.PHONY: clean

make: $(BUILDDIR)/os.bin
	dd if=$< of=$(BUILDDIR)/os.img

$(BUILDDIR)/os.bin: $(BUILDDIR)/boot.o $(SRCDIR)/kernel.c $(SRCDIR)/graphics/terminal.c
	$(CC) $^ -o $@ $(CCFLAGS) $(SCRIPTDIR)/boot.ld

$(BUILDDIR)/boot.o: $(SRCDIR)/boot.asm $(BUILDDIR)/
	$(AS) $(ASFLAGS) $< -o $@

$(BUILDDIR)/:
	mkdir $(BUILDDIR)

clean:
	rm -f $(BUILDDIR)/*.bin $(BUILDDIR)/*.img $(BUILDDIR)/*.o
