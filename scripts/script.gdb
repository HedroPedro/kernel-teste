set architecture i386
target remote | qemu-system-i386 -S -gdb stdio -fda build/boot.img
