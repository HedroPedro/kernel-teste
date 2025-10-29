#ifndef FS_H_
#define FS_H_
#include <stdint.h>

enum FS_TYPE {
    DIRECTORY = 0x10,
    FILE = DIRECTORY << 1
};

enum FLAGS {
    DELETE = 0,
    CREATE = 1,
    UPDATE = CREATE << 1
};

typedef struct file {
    uint16_t id;
    uint16_t parent_id;
    uint8_t  type_permission;
    char name[16];
    uint32_t next_sector;
    uint32_t next_track;
} __attribute__((packed)) File;

void read_from_disk(void *buff, uint32_t sector, uint32_t track);
void write_to_disk(void *buff, uint32_t len, uint32_t sector, uint32_t track);
#endif
