[bits 16]
[org 0x7E00]

main:
 mov ax, cr0
 or ax, 0x1
 mov cr0
 lgdt 


gdt_start:

gdt_end:

gdt_info:
 dw gdt_end - gdt_start




table_list:
