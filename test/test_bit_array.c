#include "sliding_counter.h"
#include "bit_array.h"

#include <stdio.h>

static uint8_t _impl_byte_array[2];

static struct bit_array s_bit_arr;

static void init()
{
    printf("init: byte array size: %lu\n", sizeof(_impl_byte_array));
    bit_array_init(&s_bit_arr, _impl_byte_array, sizeof(_impl_byte_array));
}

#define TEST_SET(arr, bit_idx, value) \
    printf("SET: " #arr "[%d] = %d\n", (bit_idx), (value)); \
    bit_array_set(&(arr), (bit_idx), (value));

#define TEST_GET(arr, bit_idx) \
    printf("GET: " #arr "[%d] = %d\n", (bit_idx), bit_array_get(&(arr), (bit_idx)));

static void operate()
{
//     TEST_SET(s_bit_arr, 1, 1);
//     TEST_SET(s_bit_arr, 2, 0);
//     TEST_SET(s_bit_arr, 3, 1);
//     TEST_SET(s_bit_arr, 8, 1);
    TEST_SET(s_bit_arr, 17, 1);

    TEST_GET(s_bit_arr, 1);
    TEST_GET(s_bit_arr, 2);
    TEST_GET(s_bit_arr, 3);
    TEST_GET(s_bit_arr, 8);
    TEST_GET(s_bit_arr, 16);


    bit_array_test_print(&s_bit_arr, -1);
    bit_array_clear(&s_bit_arr);
    bit_array_test_print(&s_bit_arr, -1);
}

static void test()
{
    init();
    operate();
}

int main (int argc, char** argv)
{
    
    test();    
    
    return 0;
}