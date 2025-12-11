global isr_table
extern exception_handler
extern get_key
extern get_service

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
isr_no_err_stub%+i:
keyboard_int:
	call get_key
%assign i 34
%rep 46
	isr_err_stub%+i:
%assign i i+1
%endrep
os_call:
	call get_service
