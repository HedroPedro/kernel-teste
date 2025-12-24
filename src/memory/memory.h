#ifndef MEMORY_H_
#define MEMORY_H_
#define USABLE_PORTION 1
#define RESERVED_PORTION UINT32_MAX ^ USABLE_PORTION
#include <stdint.h>

typedef struct {
    uint32_t base_lw;
    uint32_t base_hg;
    uint32_t len_lw;
    uint32_t len_hg;
    uint32_t type;
} int_memory_registry;

typedef struct {
    uint32_t base;
    uint32_t len;
} memory_blk;

extern int_memory_registry *registers;
extern uint32_t memory_size;
extern memory_blk *blocks;
#endif