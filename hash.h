#ifndef _HASH_H
#define _HASH_H

#include <stdint.h>

uint8_t insert_hash(uint64_t index);
void clear_hash(void);
uint64_t hash(uint8_t *state);

#endif /* ifndef _HASH_H */
