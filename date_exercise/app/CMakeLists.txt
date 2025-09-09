project(app)

include_directories(../src)

add_executable(
        date_example
        main.cpp
        ../src/Date.cpp
)
