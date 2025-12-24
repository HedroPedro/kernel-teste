[bits 32]
task_size equ 40
global switch_task
section .text
switch_task:
    pusha
    pushf
    popf
    popa
    ret