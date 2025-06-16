#ifndef CRYPTONITE_SHA256_H
#define CRYPTONITE_SHA256_H

#include <stdint.h>
#include <stddef.h>

/**
 * @brief Computes SHA-256 hash of the input data
 * 
 * @param input Pointer to the input data
 * @param len Length of the input data in bytes
 * @param hash Output buffer (must be at least 32 bytes)
 * @return int 1 on success, 0 on failure
 */
int sha256(const uint8_t *input, size_t len, uint8_t hash[32]);

/**
 * @brief Prints a hash in hexadecimal format
 * 
 * @param hash The hash to print (32 bytes)
 */
void print_hash(uint8_t hash[32]);

#endif // CRYPTONITE_SHA256_H