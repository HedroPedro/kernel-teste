AS=nasm
ASFLAGS=-fbin
SRCDIR=src
BUILDDIR=build

.PHONY: clean

make: $(BUILDDIR)/boot.bin $(BUILDDIR)/kernel.bin 
	cat $^ > $(BUILDDIR)/out.bin 
	dd if=$(BUILDDIR)/out.bin of=$(BUILDDIR)/boot.img

$(BUILDDIR)/boot.bin: $(SRCDIR)/boot.asm $(BUILDDIR)/
	$(AS) $(ASFLAGS) $< -o $@

$(BUILDDIR)/kernel.bin: $(SRCDIR)/kernel.asm $(BUILDDIR)/ 
	$(AS) $(ASFLAGS) $< -o $@

$(BUILDDIR)/:
	mkdir $(BUILDDIR)

clean:
	rm -f $(BUILDDIR)/*.bin $(BUILDDIR)/boot.img
