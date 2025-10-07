#include <stdio.h>
#include <string.h>
#include "bigint.h"

void big_val(BigInt res, long val) {
    memset(res, 0, NUM_BITS / 8);
    for (int i = 0; i < NUM_BITS / 8; i++) {
        res[i] = (val >> (i * 8)) & 0xFF;
    }
}

void big_comp2(BigInt res, BigInt a) {
    BigInt one = {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    BigInt temp;

    for (int i = 0; i < NUM_BITS / 8; i++) {
        temp[i] = ~a[i];
    }

    big_sum(res, temp, one);
}

void big_sum(BigInt res, BigInt a, BigInt b) {
    int carry = 0;
    for (int i = 0; i < NUM_BITS / 8; i++) {
        int sum = a[i] + b[i] + carry;
        res[i] = sum & 0xFF;
        carry = (sum >> 8) & 0x01;
    }
}

void big_sub(BigInt res, BigInt a, BigInt b) {
    BigInt neg_b;
    big_comp2(neg_b, b);
    big_sum(res, a, neg_b);
}

