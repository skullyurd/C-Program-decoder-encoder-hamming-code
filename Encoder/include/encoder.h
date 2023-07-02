#ifndef ENCODER_H
#define ENCODER_H

#include <stdint.h>
#include <stdbool.h>

bool EncodeByte(uint8_t inputByte, uint8_t* encodedByteHigh, uint8_t* encodedByteLow);
void PrintBinary(uint8_t byte);

#endif