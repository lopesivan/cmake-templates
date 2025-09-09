# Baixar Google Test via FetchContent
include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.14.0
)

# Evita conflitos com builds internos do Google Test
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Baixar e incluir Google Test
FetchContent_MakeAvailable(googletest)

# Compilar os testes
add_executable(runTests test_hello.cpp ../src/hello.cpp)
target_link_libraries(runTests gtest gtest_main)

# Registrar os testes no CTest
add_test(NAME runTests COMMAND runTests)
