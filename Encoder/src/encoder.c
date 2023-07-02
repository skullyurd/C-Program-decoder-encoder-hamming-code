#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include "encoder.h"

bool EncodeByte(uint8_t inputByte, uint8_t* encodedByteHigh, uint8_t* encodedByteLow)
{
    if (encodedByteHigh == NULL || encodedByteLow == NULL) {
        return false;
    }

    uint8_t p0, p1, p2;
    uint8_t d0, d1, d2, d3;

    unsigned char* ptr = &inputByte;

    d0 = (*ptr >> 0) & 0x01;
    d1 = (*ptr >> 1) & 0x01;
    d2 = (*ptr >> 2) & 0x01;
    d3 = (*ptr >> 3) & 0x01;

    p0 = d0 ^ d1 ^ d3;
    p1 = d0 ^ d1 ^ d2;
    p2 = d0 ^ d2 ^ d3;

    // Encode low nibble
    *encodedByteLow = inputByte & 0x0F;
    *encodedByteLow = *encodedByteLow | (p0 << 4);
    *encodedByteLow = *encodedByteLow | (p1 << 5);
    *encodedByteLow = *encodedByteLow | (p2 << 6);

    // Encode high nibble
    d0 = (*ptr >> 4) & 0x01;
    d1 = (*ptr >> 5) & 0x01;
    d2 = (*ptr >> 6) & 0x01;
    d3 = (*ptr >> 7) & 0x01;

    p0 = d0 ^ d1 ^ d3;
    p1 = d0 ^ d1 ^ d2;
    p2 = d0 ^ d2 ^ d3;

    *encodedByteHigh = (inputByte >> 4) & 0x0F;
    *encodedByteHigh = *encodedByteHigh | (p0 << 4);
    *encodedByteHigh = *encodedByteHigh | (p1 << 5);
    *encodedByteHigh = *encodedByteHigh | (p2 << 6);

    return true;
}

void PrintBinary(uint8_t byte)
{
    uint8_t* pByte = &byte;

    for (int8_t i = 7; i >= 4; --i)
    {
        printf("%d", (*pByte >> i) & 0x01);
    }
    printf(" ");
    for (int8_t i = 3; i >= 0; --i)
    {
        printf("%d", (*pByte >> i) & 0x01);
    }
}
