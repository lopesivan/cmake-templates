project(date_test)

include_directories(../src)

add_executable(
        date_test
        test_date.cpp
        ../src/Date.cpp
)

target_link_libraries(date_test gtest gtest_main)

enable_testing()
add_test(NAME date_test COMMAND date_test)

