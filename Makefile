AS=nasm
ASFLAGS=-fbin
SRCDIR=src
BUILDDIR=build

.PHONY: clean

make: $(BUILDDIR)/boot.bin 	
	cat $^ > $(BUILDDIR)/kernel.bin 
	dd if=$(BUILDDIR)/kernel.bin of=$(BUILDDIR)/kernel.img

$(BUILDDIR)/boot.bin: $(SRCDIR)/boot.asm $(BUILDDIR)/
	$(AS) $(ASFLAGS) $< -o $@

$(BUILDDIR)/:
	mkdir $(BUILDDIR)

clean:
	rm -f $(BUILDDIR)/*.bin $(BUILDDIR)/*.img
