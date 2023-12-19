#ifndef __SLIDING_COUNTER_H__
#define __SLIDING_COUNTER_H__

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "bit_array.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

struct sliding_counter {
    uint32_t max_window_size; // = bit_arr 's bit size
    uint32_t window_size; // current window size

    uint32_t valid_count;
    uint32_t invalid_count;

    // 位数组
    struct bit_array bit_arr;
    uint32_t bit_arr_cursor; // 当前指向的位数组序号
};
typedef struct sliding_counter* sliding_counter_t;

/**
 * @brief 初始化, 提供一片字节地址空间, 在初始化后用户不应当再去使用这片地址
 * 
 * @param sc 
 * @param _addr 空间首地址
 * @param _byte_size 空间的字节大小, 是该滑动计数器可以达到的窗口大小的1/8
 */
void sliding_counter_init(sliding_counter_t sc, uint8_t* _addr, uint32_t _byte_size);

void sliding_counter_clear(sliding_counter_t sc);

bool sliding_counter_set_window_size(sliding_counter_t sc, uint32_t window_size);

static inline uint32_t sliding_counter_get_valid_count(sliding_counter_t sc) { return sc->valid_count; }

static inline uint32_t sliding_counter_get_invalid_count(sliding_counter_t sc) { return sc->invalid_count; }

double sliding_counter_get_valid_rate(sliding_counter_t sc);

bool sliding_counter_is_empty(sliding_counter_t sc);

bool sliding_counter_is_full(sliding_counter_t sc);

static inline uint32_t sliding_counter_get_current_size(sliding_counter_t sc)
{ return sc->valid_count + sc->invalid_count; }

void sliding_counter_add_valid_count(sliding_counter_t sc);

void sliding_counter_add_invalid_count(sliding_counter_t sc);

void sliding_counter_test_print(sliding_counter_t sc);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SLIDING_COUNTER_H__
