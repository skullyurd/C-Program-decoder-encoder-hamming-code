#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include "encoder.h"

int main(int argc, char* argv[])
{
    (void)argc;
    FILE* inputFile = fopen(argv[1], "r");
    FILE* outputFile = fopen(argv[2], "w");

    if (inputFile == NULL || outputFile == NULL) {
        printf("Failed to open files.\n");
        printf("Please use the following format: ./output/main.exe <input file> <output file>\n");
        return 1;
    }

    uint8_t inputByte;
    uint8_t encodedByteHigh;
    uint8_t encodedByteLow;

    while (fscanf(inputFile, "%c", &inputByte) != EOF) {
        EncodeByte(inputByte, &encodedByteHigh, &encodedByteLow);
        fprintf(outputFile, "%c%c", encodedByteHigh, encodedByteLow);

        printf("Input byte: %c\n", inputByte);
        printf("Binary representation: ");
        PrintBinary(inputByte);
        printf("\n");

        printf("Encoded byte high: ");
        PrintBinary(encodedByteHigh);
        printf("\n");
        printf("Encoded byte low: ");
        PrintBinary(encodedByteLow);
        printf("\n");
    }

    fclose(inputFile);
    fclose(outputFile);

    printf("Encoding complete.\n");

    return 0;
}