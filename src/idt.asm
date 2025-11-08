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
	isr_err_stub%+i:	
%assign i i+1
%endrep
