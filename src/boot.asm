section .boot
[bits 16]
[org 0x7C00]
jmp boot

%define ENDL 0xA,0x13,0x0

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
; al - sectors to read
; es:bx - data buffer
; cx - Cylinder number (CL) and sector number (CL)
pusha
mov ah, 0x2
xor dx, dx
mov di, 0x2 ; Try 3 times
stc ; Making sure the carry flag is clear
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
xor bx, bx
xor di, di
mov sp, 0x7C00
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

get_memory_map:
lea di,  [memory_map+2]
mov eax, 0xE820
xor ebx, ebx
mov ecx, 20
mov edx, 'SMAP'
int 0x15
.loop_map:
 or ebx, ebx
 jz .end
 cmp eax, 'SMAP'
 jne error
 mov eax, 0xE820
 int 0x15
 inc word[memory_map]
 jmp .loop_map
.end:

;xor ax, ax
;mov es, ax
;mov al, 0x1
;mov cx, 0x2
;mov bx, 0x7E00
;call get_from_floppy
;mov si, kernel_load2
;call write_string

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

[bits 32]
boot_32:
 sti
 mov si, hello_32
 mov ah, 112
 mov ebx, 0xB8000
 .loop:
  lodsb
  or al, al
  jz .end
  mov [ebx], ax
  add ebx, 2
  jmp .loop
.end:
 cli
 hlt 

hello_32: db 'Hello from 32', 0x0
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

times (510-($-$$)) db 0
dw 0xAA55
memory_map:
