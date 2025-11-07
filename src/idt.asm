global isr_table
extern exception_handler
extern get_keyboard_input

%macro isr_err_stub 1
isr_err_stub%+%1:
	call exception_handler
	iret
%endmacro	
%macro isr_no_err_stub 1
isr_no_err_stub%+%1:
	call exception_handler
	iret
%endmacro

isr_table:
%assign i 0
%rep    32
	dd isr_err_stub_%+i
%assign i i+1
%endrep
keyboard_int:
    call get_keyboard_input
    iret

