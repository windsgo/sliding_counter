#include "bit_array.h"

#include <string.h>
#include <stdio.h>

// #define INDEX_OVERFLOW_WARN

void bit_array_init(bit_array_t bit_arr, uint8_t* byte_arr, uint32_t byte_arr_size)
{
    bit_arr->byte_array = byte_arr;
    bit_arr->byte_array_size = byte_arr_size;

    memset(byte_arr, 0, byte_arr_size);
}

void bit_array_clear(bit_array_t bit_arr)
{
    memset(bit_arr->byte_array, 0, bit_arr->byte_array_size);
}

void bit_array_set(bit_array_t bit_arr, uint32_t bit_index, uint8_t bit)
{
#ifdef INDEX_OVERFLOW_WARN
    if (bit_index >= bit_arr->byte_array_size * 8) {
        printf("bit_index set overflow: %d >= %d\r\n", bit_index, bit_arr->byte_array_size * 8);
    }
#endif // INDEX_OVERFLOW_WARN

    bit_index = bit_index % (bit_arr->byte_array_size * 8);

    uint32_t byte_index = bit_index / 8; // 字节序号
    uint8_t bit_index_in_byte = bit_index % 8; // 在字节中的位序号

    uint8_t* p_byte = &bit_arr->byte_array[byte_index];
    if (bit) {
        *p_byte = (*p_byte) | (1 << bit_index_in_byte);
    } else {
        *p_byte = (*p_byte) & (~(1 << bit_index_in_byte));
    }
}

uint8_t bit_array_get(bit_array_t bit_arr, uint32_t bit_index)
{
#ifdef INDEX_OVERFLOW_WARN
    if (bit_index >= bit_arr->byte_array_size * 8) {
        printf("bit_index get overflow: %d >= %d\r\n", bit_index, bit_arr->byte_array_size * 8);
    }
#endif // INDEX_OVERFLOW_WARN
    bit_index = bit_index % (bit_arr->byte_array_size * 8);

    uint32_t byte_index = bit_index / 8; // 字节序号
    uint8_t bit_index_in_byte = bit_index % 8; // 在字节中的位序号

    return !!(bit_arr->byte_array[byte_index] & (1 << bit_index_in_byte));
}

void bit_array_test_print(bit_array_t bit_arr, int size)
{
    if (!bit_arr || !bit_arr->byte_array) return;

    int printed_size = 0;
    bool finish_flag = false;

    for (uint32_t i = 0; i < bit_arr->byte_array_size; ++i) {
        uint8_t* p_byte = &bit_arr->byte_array[i];
        for (uint8_t j = 0; j < 8; ++j) {
            printf("%d", (!!( (*p_byte) & (1 << j) )) ? 1 : 0);
            ++printed_size;

            if (size > 0 && printed_size >= size) {
                finish_flag = true;
                break;
            }
        }
        if (finish_flag) {
            break;
        }

        putchar(' ');
    }

    puts(""); // \n
}
