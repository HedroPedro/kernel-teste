#ifndef FS_H_
#define FS_H_
#include <stdint.h>

enum FS_TYPE {
    DIRECTORY = 0x10,
    FILE = DIRECTORY << 1
};

typedef struct fat {
    //TODO: finish fat
} fat;

typedef struct metadata_fs {
    uint16_t id;
    uint16_t parent_id;
    uint8_t  name[16];
    uint8_t  type_permission;
    disk_blk first_blk;
} __attribute__((packed)) metadata_fs;

typedef struct disk_blk {
    uint16_t id;
    uint16_t next_blk;
    void *block;
} disk_blk;

#endif