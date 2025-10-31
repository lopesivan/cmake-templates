
cmake_minimum_required(VERSION 3.20)
project(example)

add_executable(${PROJECT_NAME} example/main.cpp)

include(cmake/autogen_assets.cmake)
autogen_assets(${PROJECT_NAME} example/assets/)
