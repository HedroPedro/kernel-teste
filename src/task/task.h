#ifndef TASK_H_
#define TASK_H_
#include <stdint.h>
extern void init_tasking();
extern void *alloca(uint32_t size);
typedef struct {
    uint32_t eax, ebx, ecx, edx, 
        esi, edi, esp, ebp, eip,
        eflags;
} registers;

typedef struct task {
    registers regs;
    struct Task *next;
} task;
extern void create_task(task *, void(*)(), uint32_t);
extern void yield();
extern void switch_task(registers *old, registers *new);
#endif