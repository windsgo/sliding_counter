add_executable(test_bit_array test_bit_array.c)
add_dependencies(test_bit_array sliding_counter)
target_include_directories(test_bit_array
    PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)
target_link_libraries(test_bit_array PUBLIC sliding_counter)

add_executable(test_sliding_counter test_sliding_counter.c)
add_dependencies(test_sliding_counter sliding_counter)
target_include_directories(test_sliding_counter
    PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)
target_link_libraries(test_sliding_counter PUBLIC sliding_counter)