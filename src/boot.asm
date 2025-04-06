[bits 16]
[org 0x7C00]

jmp boot

write_text:
; si - string
push ax
push bx
mov ah, 0xE
xor bx, bx
.loop:
  lodsb
  or al, 0x0
  jz .end
  int 0x10
  jmp .loop
.end:
  pop bx
  pop ax
ret

read_floppy:
; al - amount of sectors to read
; bx - address
; cx - sector and track
pusha
mov ah, 0x2
xor dx, dx
stc
int 0x13
popa
ret

boot:
xor ax, ax
mov sp, 0x7C00
mov ss, ax
mov ds, ax
mov es, ax
mov si, hello_msg
call write_text

mov al, 1
mov bx, 0x7E00
mov cx, 0x0002
call read_floppy

jmp 0x7E00
hlt

hello_msg: db 'Hello World', 0xD, 0xA, 0
times (510-($-$$)) db 0
dw 0xAA55
