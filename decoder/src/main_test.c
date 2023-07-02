#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include "decoder.h"
#include "unity.h"

void setUp(void)
{

}

void tearDown(void)
{

}

void test_decodeByte_NullPointer_ReturnsFalse(void)
{
    bool result = decodeByte(0x12, 0x34, NULL);
    TEST_ASSERT_FALSE(result);
}

void test_decodeByte_ValidInput_ReturnsTrueAndDecodedByte(void)
{
    uint8_t decodedByte;
    bool result = decodeByte(0x12, 0x34, &decodedByte);
    TEST_ASSERT_TRUE(result);
    TEST_ASSERT_EQUAL_HEX8(0x24, decodedByte);
}


int main(void)
{
    UnityBegin(0);

    RUN_TEST(test_decodeByte_NullPointer_ReturnsFalse);
    RUN_TEST(test_decodeByte_ValidInput_ReturnsTrueAndDecodedByte);

    return UnityEnd();
}