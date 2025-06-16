//hash.h

#ifndef CRYPTONITE_HASH_H
#define CRYPTONITR_HASH_H

#include <stddef.h>
#include <stdint.h>

int sha256 (const uint8_t *input, size_t len, uint8_t output[32]);

#endif  //CRYPTONITR_HASH_H