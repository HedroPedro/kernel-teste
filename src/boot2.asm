mov esp, stack_end
call kmain

kmain:
jmp $

section .bss
stack_init: resb 16 * 1024
stack_end:
