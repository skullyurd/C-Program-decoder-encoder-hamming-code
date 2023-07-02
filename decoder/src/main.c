#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include "decoder.h"

int main(int argc, char* argv[]) {
    (void)argc;
    const char* transmittedFile = argv[1];
    const char* decodedFile = argv[2];
    const char* fixedDataFile = "./fixed_data.txt";

    FILE* transmittedData = fopen(transmittedFile, "rb");
    FILE* fixedData = fopen(fixedDataFile, "wb");
    FILE* decodedData = fopen(decodedFile, "wb");


    if (transmittedData == NULL || decodedData == NULL) {
        printf("Failed to open files.\n");
        printf("please use the format: ./decoder <transmitted_file> <decoded_file>\n");
        return 1;
    }

    uint8_t transmittedByteHigh;
    uint8_t transmittedByteLow;
    uint8_t decodedByte;
    uint8_t bytesRead;
    unsigned char byte;

    while ((bytesRead = fread(&byte, sizeof(byte), 1, transmittedData)) > 0)
    {
        uint8_t p0 = (byte >> 4) & 1;
        uint8_t p1 = (byte >> 5) & 1;
        uint8_t p2 = (byte >> 6) & 1;

        if (calculateParityBit(byte, p0, p1, p2) == 1) {
            
            printf("Before fixing: ");
            printBinary(byte);
            printf("\n");

            int bitPosition = calculateWrongBitPos(byte, p0, p1, p2);
            if (bitPosition != -1)
            {
                byte ^= (1 << bitPosition);
            }

            printf("\nAfter fixing: ");
            printBinary(byte);
            printf("\n");
        }


        fwrite(&byte, sizeof(byte), 1, fixedData);
    }

    // Reset file pointer to beginning of file
    fclose(fixedData);
    fixedData = fopen(fixedDataFile, "rb");

    while ((bytesRead = fread(&byte, sizeof(byte), 1, fixedData)) > 0) {
        transmittedByteHigh = byte;
        bytesRead = fread(&byte, sizeof(byte), 1, fixedData);
        transmittedByteLow = byte;

        decodeByte(transmittedByteHigh, transmittedByteLow, &decodedByte);
        fwrite(&decodedByte, sizeof(decodedByte), 1, decodedData);
    }

    fclose(transmittedData);
    fclose(decodedData);
    fclose(fixedData);

    printf("Decoding complete.\n");

    return 0;
}
