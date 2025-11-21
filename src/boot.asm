[bits 16]
%define SMAP 0x0534D4150
section .boot
global boot
jmp boot

write_string:
; si
push ax
push bx
xor bx, bx
mov ah, 0xE
.loop:
 lodsb
 or al, al
 jz .end
 int 0x10
 jmp .loop
.end:
pop bx
pop ax
ret

reset_floppy:
push ax
push dx
xor ah, ah
xor dl, dl
int 0x13
pop dx
pop ax
ret

get_from_floppy:
; al - Sectors to read
; es:bx - Data buffer
; cx - Cylinder number (CL) and sector number (CL)
pusha
mov ah, 0x2
xor dx, dx
clc ; Making sure the carry flag is clear
.loop:
 int 0x13
 jnc .end
 test di, di
 jz error
 call reset_floppy
 dec di
 jmp .loop
.end:
popa
ret

error:
 hlt

boot:
xor ax, ax
mov bx, ax
mov di, ax
mov sp, 0x7C00
xor bp, bp
mov ds, ax
mov es, ax
mov ss, ax

set_A20:
mov ax, 0x2401
int 0x15
jc error

set_VGA:
mov ax, 0x3
int 0x10

xor ax, ax
mov es, ax
mov al, 0x6
mov cx, 0x2
mov bx, 0x7E00
call get_from_floppy

cli
lgdt [gdt_info]
mov eax, cr0
or  eax, 1
mov cr0, eax

jmp CODE_SEG:boot_32

gdt_info:
 dw gdt_end - gdt_start
 dd gdt_start
gdt_start:
 dq 0x0
gdt_code:
 dw 0xFFFF
 dw 0x0
 db 0x0
 db 10011010b
 db 11011111b
 db 0x0
gdt_data:
 dw 0xFF
 dw 0x0
 db 0x0
 db 10010010b
 db 11011111b
 db 0x0 
gdt_end:

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

times (510-($-$$)) db 0
dw 0xAA55
beyond_target:
[bits 32]
extern kmain
boot_32:
 mov ax, DATA_SEG
 mov es, ax
 mov ds, ax
 mov ss, ax
 mov esp, stack_top
 call kmain
 cli
 hlt
 
section .bss
global memory_map
stack_base:
 resb 1024*32
stack_top:
