#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#include "channelNoise.h"

int main(int argc, char* argv[])
{
    (void)argc;
    const char* inputFile = argv[1];
    const char* outputFile = argv[2];

    FILE* input = fopen(inputFile, "rb");
    FILE* output = fopen(outputFile, "wb");

    if (input == NULL || output == NULL) {
        printf("Failed to open files.\n");
        return 1;
    }

    srand(time(NULL)); 

    uint8_t encodedByte;
    uint8_t transmittedByte;

    while (fread(&encodedByte, sizeof(uint8_t), 1, input) == 1) {
        TransmitByte(encodedByte, &transmittedByte);

        printf("encodedByte: %d, transmittedByte: %d\n", encodedByte, transmittedByte);


        fwrite(&transmittedByte, sizeof(uint8_t), 1, output);
    }

    fclose(input);
    fclose(output);

    printf("Transmission complete.\n");

    return 0;
}
