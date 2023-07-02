#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include "encoder.h"
#include "unity.h"

void setUp(void)
{

}

void tearDown(void)
{

}

void test_EncodeByte(void)
{
    //arrange
    uint8_t inputByte = 0b01000001;
    uint8_t encodedByteHigh;
    uint8_t encodedByteLow;
    bool actualResultSuccess;
    bool actualResultFail;
    bool expectedSucces = true;
    bool expectedFail = false;
    uint8_t expectedHigh = 0b01100100;
    uint8_t expectedLow = 0b01110001;

    //act
    actualResultSuccess = EncodeByte(inputByte, &encodedByteHigh, &encodedByteLow);
    actualResultFail = EncodeByte(inputByte, NULL, &encodedByteLow);
    PrintBinary(encodedByteHigh);
    printf("\n");
    PrintBinary(encodedByteLow);

    //assert
    TEST_ASSERT_EQUAL_UINT8(expectedHigh, encodedByteHigh);
    TEST_ASSERT_EQUAL_UINT8(expectedLow, encodedByteLow);
    TEST_ASSERT_EQUAL(expectedSucces, actualResultSuccess);
    TEST_ASSERT_EQUAL(expectedFail, actualResultFail);
}

int main(void)
{
    UnityBegin(0);

    RUN_TEST(test_EncodeByte);

    return UnityEnd();
}