#ifndef __BIT_ARRAY_H__
#define __BIT_ARRAY_H__

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

struct bit_array {
    uint8_t* byte_array; // 字节数组(静态初始化的指针)
    uint32_t byte_array_size; // 字节数组的大小 (等于其长度, 等于sizeof), 等于位长度的1/8
};
typedef struct bit_array* bit_array_t;

void bit_array_init(bit_array_t bit_arr, uint8_t* byte_arr, uint32_t byte_arr_size);

void bit_array_clear(bit_array_t bit_arr);

void bit_array_set(bit_array_t bit_arr, uint32_t bit_index, uint8_t bit);

uint8_t bit_array_get(bit_array_t bit_arr, uint32_t bit_index);

static inline uint32_t bit_array_byte_size(bit_array_t bit_arr)
{ return bit_arr->byte_array_size; }

static inline uint32_t bit_array_bit_size(bit_array_t bit_arr)
{ return bit_arr->byte_array_size * 8; }

void bit_array_test_print(bit_array_t bit_arr, int size);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __BIT_ARRAY_H__
