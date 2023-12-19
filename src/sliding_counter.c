#include "sliding_counter.h"

#include <assert.h>
#include <stdio.h>

void sliding_counter_init(sliding_counter_t sc, uint8_t* _addr, uint32_t _byte_size)
{
    sc->max_window_size = _byte_size * 8;
    sc->window_size = sc->max_window_size;

    sc->valid_count = 0;
    sc->invalid_count = 0;

    bit_array_init(&sc->bit_arr, _addr, _byte_size);
    sc->bit_arr_cursor = 0;
}

void sliding_counter_clear(sliding_counter_t sc)
{
    sc->valid_count = 0;
    sc->invalid_count = 0;

    bit_array_clear(&sc->bit_arr);
    sc->bit_arr_cursor = 0;
}

bool sliding_counter_set_window_size(sliding_counter_t sc, uint32_t window_size)
{
    if (window_size == 0) return false;
    
    if (window_size > sc->max_window_size) {
        window_size = sc->max_window_size;
    }

    sc->window_size = window_size;

    // 统一重置
    sliding_counter_clear(sc);

    return true;
}

double sliding_counter_get_valid_rate(sliding_counter_t sc)
{
    if (sliding_counter_is_empty(sc)) {
        return 0.0;
    }

    return 
        (double)sc->valid_count / 
        (double)(sc->valid_count + sc->invalid_count); // 不会溢出(和一定小于window_size)
}

bool sliding_counter_is_empty(sliding_counter_t sc)
{
    return (sc->valid_count == 0) && (sc->invalid_count == 0);
}

bool sliding_counter_is_full(sliding_counter_t sc)
{
    // assert((sc->valid_count + sc->invalid_count) <= sc->window_size);
    return (sc->valid_count + sc->invalid_count) == sc->window_size;
}

void sliding_counter_add_valid_count(sliding_counter_t sc)
{
    if (!sliding_counter_is_full(sc)) {
        // 未满
        bit_array_set(&sc->bit_arr, sc->bit_arr_cursor, 1);
        ++sc->valid_count;
    } else {
        // 满, 需要先查询再修改
        uint8_t old_value = bit_array_get(&sc->bit_arr, sc->bit_arr_cursor);
        if (!old_value) {
            bit_array_set(&sc->bit_arr, sc->bit_arr_cursor, 1);
            ++sc->valid_count;
            --sc->invalid_count;
        }
    }

    sc->bit_arr_cursor = (sc->bit_arr_cursor + 1) % sc->window_size;
}

void sliding_counter_add_invalid_count(sliding_counter_t sc)
{
    if (!sliding_counter_is_full(sc)) {
        // 未满
        bit_array_set(&sc->bit_arr, sc->bit_arr_cursor, 0);
        ++sc->invalid_count;
    } else {
        // 满, 需要先查询再修改
        uint8_t old_value = bit_array_get(&sc->bit_arr, sc->bit_arr_cursor);
        if (old_value) {
            bit_array_set(&sc->bit_arr, sc->bit_arr_cursor, 0);
            ++sc->invalid_count;
            --sc->valid_count;
        }
    }

    sc->bit_arr_cursor = (sc->bit_arr_cursor + 1) % sc->window_size;
}

void sliding_counter_test_print(sliding_counter_t sc)
{
    printf("max_window_size: %d, window_size: %d, size:%d, v: %d, iv: %d, bc: %d, rate: %f\r\n", 
        sc->max_window_size,
        sc->window_size,
        sliding_counter_get_current_size(sc),
        sc->valid_count,
        sc->invalid_count,
        sc->bit_arr_cursor,
        sliding_counter_get_valid_rate(sc));

    bit_array_test_print(&sc->bit_arr, -1);
    bit_array_test_print(&sc->bit_arr, sc->window_size);
}
