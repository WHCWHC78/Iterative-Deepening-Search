#include <stdlib.h>

#include "hash.h"

#define HASH_SIZE 36344968000L

// exact value of 0x0876543210: 36 344 967 696
static uint8_t hash_map[HASH_SIZE] = {0};

uint64_t hash(uint8_t *state)
{
    uint64_t index = 0;
    uint8_t count;

    for (count = 9; count; --count)
        index |= state[count - 1] << (4 * (count - 1));

    return index;
}

uint8_t insert_hash(uint64_t index)
{
    if (hash_map[index] != 0)
        return 0;
    else {
        hash_map[index] = 1;
    }

    return 1;
}

// This is not a good idea
void clear_hash(void)
{
    uint64_t count;

    for (count = HASH_SIZE + 1; count; --count)
        hash_map[count - 1] = 0;
}

