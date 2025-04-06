%define write_string 0x7C02 ; Hardcoded value for write_string function
%define ENDL 0xD, 0xA, 0x0  ; Equals to the string -> "\r\n\0"

[bits 16]
[org 0x7E00]

main:
mov si, kernel_hi
call write_string
call check_a20
or ax, ax
jnz .enabled
call enable_A20
jc error
.enabled:
mov si, kernel_A20
call write_string
mov al, 0x2
mov cx, 0x2
xor dx, dx
mov bx, new_sect
error:
hlt

check_a20:
; ax - 0 if not enabled; 1 - if enabled
push ds
push es
cli
xor ax, ax
mov es, ax

not ax
mov ds, ax

mov di, 0x0500
mov si, 0x0510

mov al, byte[es:di]
mov ah, byte[ds:si]
push ax

mov byte[es:di], 0x00
mov byte[ds:si], 0xFF
cmp byte[es:di], 0xFF

mov ax, 1
jne .end
xor ax, ax

.end:
pop ax
mov [es:di], al
mov [ds:si], ah
pop es
pop ds
ret

query_A20_support:
mov ax, 0x2403
int 0x15
jc .err
test ah, ah
jnz .err
jmp short .end
.err:
stc
.end:
ret

enable_A20:
clc
call query_A20_support
jc .method2

.method1:
mov ax, 0x2401
int 0x15
jc .method2
test ah, ah
jnz .method2

call check_a20
test ax, ax
jnz .end

.method2:
in al, 0x92
test al, 2
jnz .end
or al, 2
and al, 0xFE
out 0x92, al

call check_a20
test ax, ax
jnz .end
.error:
stc
hlt
.end:
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
; dx - head number (DH) and drive number (DL)
pusha
xor ah, ah
mov di, 0x2 ; Try 3 times
clc ; Making sure the carry flag is clear
.loop:
 int 0x13
 jnc .end
 test di, di
 jz .err
 call reset_floppy
 dec di
 jmp .loop
.end:
popa
ret
.err:
hlt

kernel_hi: db 'Hello from kernel', ENDL
kernel_A20: db 'Line A20 enabled', ENDL

data_size:
times (512-($-$$)) db 0
new_sect:
