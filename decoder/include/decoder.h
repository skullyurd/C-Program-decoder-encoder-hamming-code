#ifndef DECODER_H
#define DECODER_H

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

bool decodeByte(uint8_t transmittedByteHigh, uint8_t transmittedByteLow, uint8_t* decodedByte);
void printBinary(uint8_t byte);
uint8_t calculateParityBit(unsigned char byte, uint8_t p0, uint8_t p1, uint8_t p2);
int calculateWrongBitPos(unsigned char byte, uint8_t p0, uint8_t p1, uint8_t p2);
unsigned char flipBit(unsigned char byte, int bitPos);

#endif // DECODER_H