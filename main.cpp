#include "test.h"

int main() {
    test_init_reshape_empty();
    test_reserve();
    test_shrink();
    test_copy();
    test_const();
    test_clear();
    test_move();
    test_init_list();
    test_brackets();
    test_print();
    return 0;
}