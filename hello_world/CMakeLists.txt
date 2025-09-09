cmake_minimum_required(VERSION 3.10)
project(MeuProjeto LANGUAGES CXX)

# Usar C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Diretórios
include_directories(include)

# Compila a aplicação principal
add_executable(meu_projeto src/main.cpp src/hello.cpp)

# Ativar testes
enable_testing()
add_subdirectory(tests)
