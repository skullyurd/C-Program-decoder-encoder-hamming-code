#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#include "channelNoise.h"
#include "unity.h"

void setUp(void)
{

}

void tearDown(void)
{

}

void Test_TransmitByte()
{
    //arrange
    uint8_t encodedByte = 0b01100001;
    uint8_t transmittedByte = 0b00000000;
    bool expectedSucces = true;
    bool expectedFailure = false;
    bool actualSucces = false;
    bool actualFailure = false;
    int flipCount[8] = {0};
    const int numTrials = 100; 

    //act
    actualSucces = TransmitByte(encodedByte, &transmittedByte);
    actualFailure = TransmitByte(encodedByte, NULL);
    for (int i = 0; i < numTrials; i++) {
        bool actualSuccess = TransmitByte(encodedByte, &transmittedByte);
        TEST_ASSERT_TRUE(actualSuccess);

        // Check the flipped bit position and update the flip count array
        int flippedBit = GetFlippedBit(encodedByte, transmittedByte);
        flipCount[flippedBit]++;
        printf("encodedByte: %d, transmittedByte: %d, flippedBit: %d\n", encodedByte, transmittedByte, flippedBit);
    }

    //assert
    TEST_ASSERT_EQUAL(expectedSucces, actualSucces);
    TEST_ASSERT_EQUAL(expectedFailure, actualFailure);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(Test_TransmitByte);

    return UNITY_END();
}