#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "cryptonite/sha256.h"

void print_hex(const uint8_t *data, size_t len) {
    for (size_t i = 0; i < len; i++) {
        printf("%02x", data[i]);
    }
    printf("\n");
}

int main() {
    const char *vectors[][2] = {
        {"", "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855"},
        {"abc", "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad"}
    };

    uint8_t hash[32];
    int passed = 0;
    
    for (size_t i = 0; i < sizeof(vectors)/sizeof(vectors[0]); i++) {
        sha256((const uint8_t *)vectors[i][0], strlen(vectors[i][0]), hash);
        
        char result[65];
        for (int j = 0; j < 32; j++) {
            sprintf(result + j*2, "%02x", hash[j]);
        }
        
        if (strcmp(result, vectors[i][1]) == 0) {
            passed++;
        } else {
            printf("Test %zu failed!\n", i+1);
            printf("Expected: %s\n", vectors[i][1]);
            printf("Got:      %s\n", result);
        }
    }
    
    printf("SHA-256 Tests: %d/%zu passed\n", passed, sizeof(vectors)/sizeof(vectors[0]));
    return passed == sizeof(vectors)/sizeof(vectors[0]) ? 0 : 1;
}