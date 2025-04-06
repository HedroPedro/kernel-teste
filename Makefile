AS=nasm
ASFLAGS=-fbin
SRCDIR=src
BUILDDIR=build

.PHONY: clean

build: $(BUILDDIR)/boot.bin $(BUILDDIR)/main.bin
	cat $^ > $(BUILDDIR)/kernel.bin 
	dd if=$(BUILDDIR)/kernel.bin of=$(BUILDDIR)/boot.img

$(BUILDDIR)/boot.bin: $(SRCDIR)/boot.asm
	$(AS) $(ASFLAGS) $< -o $@

$(BUILDDIR)/main.bin: $(SRCDIR)/main.asm
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -f $(BUILDDIR)/*.bin $(BUILDDIR)/boot.img
