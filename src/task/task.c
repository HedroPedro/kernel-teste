#include "task.h"

static task *running_task;

void init_tasking() {
    
}

void create_task(task *task, void(*main)(), uint32_t flags) {
    task->regs.eax = 0;
    task->regs.ebp = 0;
    task->regs.ecx = 0;
    task->regs.edx = 0;
    task->regs.esi = 0;
    task->regs.edi = 0;
    task->regs.eflags = flags;
    task->regs.eip = (uint32_t) main;
    task->next = 0;
}

void yield() {
    task *last = running_task;
    running_task = last->next;
    switch_task(&last->regs, &running_task->regs);
}