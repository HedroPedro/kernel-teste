#ifndef SLAB_H_
#define SLAB_H_
#include <stdint.h>

typedef struct slab_info {
    void *address;
    uint32_t bytes_allocated;
} slab_info;


extern slab_info *slabs;
extern uint8_t size;

extern void create_slab();
#endif