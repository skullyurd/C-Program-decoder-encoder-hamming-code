#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include "decoder.h"


bool decodeByte(uint8_t transmittedByteHigh, uint8_t transmittedByteLow, uint8_t* decodedByte)
{
    if (decodedByte == NULL)
    {
        return false;
    }

    uint8_t p0, p1, p2;
    uint8_t* ptr = &transmittedByteLow;

    p0 = (*ptr >> 5) & 0x01;
    p1 = (*ptr >> 4) & 0x01;
    p2 = (*ptr >> 3) & 0x01;

    // Check for flipped bits
    if (p0 == ((*ptr >> 5) & 0x01)) {
        *decodedByte = *ptr & 0x0F;
    } else {
        *decodedByte = *ptr & 0x1F;
    }

    if (p1 == ((*ptr >> 4) & 0x01)) {
        *decodedByte |= (*ptr & 0x0F);
    } else {
        *decodedByte |= (*ptr & 0x1F);
    }

    if (p2 == ((*ptr >> 3) & 0x01)) {
        *decodedByte |= (*ptr & 0x07);
    } else {
        *decodedByte |= (*ptr & 0x0F);
    }

    *decodedByte |= (transmittedByteHigh << 4);

    return true;
}


void printBinary(uint8_t byte) {
    uint8_t* ptr = &byte;
    for (int8_t i = 7; i >= 0; --i)
    {
        printf("%d", (*ptr >> i) & 0x01);
    }
}

uint8_t calculateParityBit(unsigned char byte, uint8_t p0, uint8_t p1, uint8_t p2)
{
    unsigned char* ptr = &byte;
    uint8_t d0 = (*ptr >> 0) & 1;
    uint8_t d1 = (*ptr >> 1) & 1;
    uint8_t d2 = (*ptr >> 2) & 1;
    uint8_t d3 = (*ptr >> 3) & 1;

    uint8_t parity0 = (d0 + d1 + d3) % 2;
    uint8_t parity1 = (d0 + d1 + d2) % 2;
    uint8_t parity2 = (d0 + d2 + d3) % 2;

    if (parity0 == p0 && parity1 == p1 && parity2 == p2)
    {
        return 0; // No error
    }
    else
    {
        return 1; // Error detected
    }
}

int calculateWrongBitPos(unsigned char byte, uint8_t p0, uint8_t p1, uint8_t p2)
{
    unsigned char* ptr = &byte;
    uint8_t d0 = (*ptr >> 0) & 1;
    uint8_t d1 = (*ptr >> 1) & 1;
    uint8_t d2 = (*ptr >> 2) & 1;
    uint8_t d3 = (*ptr >> 3) & 1;

    uint8_t parity0 = (d0 + d1 + d3) % 2;
    uint8_t parity1 = (d0 + d1 + d2) % 2;
    uint8_t parity2 = (d0 + d2 + d3) % 2;

    if (p0 != parity0 && p1 != parity1 && p2 != parity2)
    {
        return 0;
    }
    else if (p0 != parity0 && p1 != parity1)
    {
        return 1;
    }
    else if (p1 != parity1 && p2 != parity2)
    {
        return 2;
    }
    else if (p0 != parity0 && p2 != parity2)
    {
        return 3;
    }
    return -1;
}


unsigned char flipBit(unsigned char byte, int bitPos)
{
    unsigned char* ptr = &byte;
    *ptr ^= (1 << bitPos);
    return byte;
}
