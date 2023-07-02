#ifndef CHANNEL_NOISE_H
#define CHANNEL_NOISE_H

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

bool TransmitByte(uint8_t encodedByte, uint8_t* transmittedByte);
int GetFlippedBit(uint8_t encodedByte, uint8_t transmittedByte);

#endif // CHANNEL_NOISE_H