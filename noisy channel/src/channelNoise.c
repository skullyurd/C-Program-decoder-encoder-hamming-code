#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#include "channelNoise.h"

bool TransmitByte(uint8_t encodedByte, uint8_t* transmittedByte)
{
    if (transmittedByte == NULL)
    {
        return false;
    }

    uint8_t* pEncodedByte = &encodedByte;
    uint8_t* pTransmittedByte = transmittedByte;
    *pTransmittedByte = *pEncodedByte;

    int bitPosition = rand() % 8;
    int* pBitPosition = &bitPosition;

    *pTransmittedByte ^= (1 << *pBitPosition);

    return true;
}

int GetFlippedBit(uint8_t encodedByte, uint8_t transmittedByte)
{
    int flippedBit = 0;
    int* pFlippedBit = &flippedBit;

    uint8_t xor = encodedByte ^ transmittedByte;
    while (xor > 0) {
        if (xor & 1) {
            return *pFlippedBit;
        }
        xor >>= 1;
        (*pFlippedBit)++;
    }

    return -1;
}
