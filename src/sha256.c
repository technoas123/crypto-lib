#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h> 
#include "sha256_internal.h"

static uint8_t* pad_message(const uint8_t *input, size_t len, size_t *padded_len_out) {
    size_t bit_len = len * 8;
    size_t pad_len = (56- (len + 1) % 64) % 64;
    size_t total_len = len + 1 + pad_len + 8;
    uint8_t *msg = malloc(total_len);
    if (!input || !padded_len_out) return NULL;
    if (!msg) return NULL;
    memcpy(msg, input, len);
    msg[len] = 0x80;
    memset(msg + len + 1, 0x00, pad_len);
    for (int i = 0; i < 8; i++){
        msg[total_len - 8 + i] = (bit_len >> (56 - 8 * i)) & 0xFF;
    }
    if (padded_len_out) *padded_len_out = total_len;
    return msg;   
}

void prepare_message_schedule(const uint8_t block[64], uint32_t W[64]){
    for (int i = 0; i < 16; i++){
        W[i] = (((uint32_t)block[4*i] << 24 )|
                 ((uint32_t)block[4*i + 1] << 16)|
                  ((uint32_t)block[4*i + 2] << 8)|
                   ((uint32_t)block[4*i + 3])
                );
            }

    for (int i = 16; i < 64; i++){
        W[i] = sigma1(W[i-2]) + W[i-7] + sigma0(W[i-15]) + W[i-16]; 
    }
}

void sha256_compress(uint32_t H[8], const uint8_t block[64]){
    if (!block || !H) return;
    uint32_t W[64];
    prepare_message_schedule(block, W);

    uint32_t a = H[0], b = H[1], c = H[2], d = H[3];
    uint32_t e = H[4], f = H[5], g = H[6], h = H[7];

    for(int i = 0; i < 64; i++ ){
        uint32_t T1 = h + SIGMA1(e) + CH(e, f, g) + K[i] + W[i];
        uint32_t T2 = SIGMA0(a) + MAJ(a, b, c);

        h = g;
        g = f;
        f = e;
        e = d + T1;
        d = c;
        c = b;
        b = a;
        a = T1 + T2;
    }

        H[0] += a;
        H[1] += b;
        H[2] += c;
        H[3] += d;
        H[4] += e;
        H[5] += f;
        H[6] += g;
        H[7] += h;
    
}

int sha256(const uint8_t *input, size_t len, uint8_t hash[32]){
    if (!input || !hash) return 0;

    uint32_t H[8];
    memcpy(H, H0, sizeof(H0));

    size_t padded_len;
    uint8_t *padded = pad_message(input, len, &padded_len);
    if (!padded) return 0;

    for (size_t t = 0; t < padded_len; t+=64){
        sha256_compress(H, padded + t);
    }

    for (int i = 0; i < 8; i++){
        hash[4*i] = (H[i] >> 24 ) & 0xFF;
        hash[4*i + 1] = (H[i] >> 16 ) & 0xFF;
        hash[4*i + 2] = (H[i] >> 8 ) & 0xFF;
        hash[4*i + 3] = (H[i]) & 0xFF;
    }

    free(padded);

    return 1;
}

void print_hash(uint8_t hash[32]) {
    for (int i = 0; i < 32; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");
}


int main() {

    const char *msg = "abc";
    uint8_t hash[32];

    int result = sha256((const uint8_t *)msg, strlen(msg), hash);
    if (!result) {
        printf("Error computing hash\n");
        return 1;
    }

    print_hash(hash);
    return 0;
}
