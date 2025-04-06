%include 'src/macros.inc'

[bits 16]
[org 0x7E00]

%define write_string 0x7C02

mov si, msg
call write_string
hlt

msg: db 'Hello boot 2',0
