#include "sliding_counter.h"
#include "bit_array.h"

#include <stdio.h>

static uint8_t _impl_byte_array[5];

static struct sliding_counter s_sc;

static void init()
{
    sliding_counter_init(&s_sc, _impl_byte_array, sizeof(_impl_byte_array));
}

#define SET_VALID(sc) { \
    puts("✅ SET VALID: " #sc ); \
    sliding_counter_add_valid_count(&(sc)); \
    sliding_counter_test_print(&(sc)); }

#define SET_INVALID(sc) { \
    puts("❌ SET INVALID: " #sc ); \
    sliding_counter_add_invalid_count(&(sc)); \
    sliding_counter_test_print(&(sc)); }

#define CLEAR(sc) { \
    puts("🔄 CLEAR: " #sc); \
    sliding_counter_clear(&(sc)); \
    sliding_counter_test_print(&(sc));}

static void operate()
{
    for (int i = 0; i < 1000; ++i) {
        if (i % 3 != 0) {
            SET_VALID(s_sc);
        }
        else {
            SET_INVALID(s_sc);
        }

        if (i == 900) {
            sliding_counter_set_window_size(&s_sc, 10);
        }

        // if (i == 4) {
        //     CLEAR(s_sc);
        // }
    }

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