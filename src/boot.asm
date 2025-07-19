[bits 16]
[org 0x7C00]
jmp main

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

main:
xor ax, ax
xor bx, bx
xor di, di
mov sp, 0x7C00
mov ds, ax
mov es, ax
mov ss, ax

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

;xor ax, ax
;mov es, ax
;mov al, 0x1
;mov cx, 0x2
;mov bx, 0x7E00
;call get_from_floppy
;mov si, kernel_load2
;call write_string
;jmp past 




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
or ah, ah
jz .end
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

kernel_hi: db 'Hello from boot', ENDL
kernel_A20: db 'Line A20 enabled', ENDL
kernel_load2: db 'Stage 2 loaded at 0x7E00', ENDL
times (510-($-$$)) db 0
dw 0xAA55
past:
