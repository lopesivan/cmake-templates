# 🚀 AutoGen Assets

> **Встраивание ресурсов в C++ исполняемые файлы**

[![C++](https://img.shields.io/badge/C%2B%2B-11%2B-blue.svg)](https://en.cppreference.com/)
[![CMake](https://img.shields.io/badge/CMake-3.20%2B-green.svg)](https://cmake.org/)

CMake-модуль для автоматического встраивания ресурсов в C++ проекты.

##  Требования

- **C++11+**
- **CMake 3.20+**
- Windows/Linux/macOS

## 🔧 Как включить в проект

1. Скопируйте файл `cmake/autogen_assets.cmake` в ваш проект
2. В `CMakeLists.txt` добавьте:

```cmake
include(cmake/autogen_assets.cmake)
autogen_assets(your_app_name path/to/assets/)
```

## 💻 Использование

```cpp
#include <assets/assets.hpp>

int main() {
    auto data = assets::load("/hello.txt");
    if (!data.empty()) {
        std::string content(data.begin(), data.end());
        std::cout << content << std::endl;
    }
    return 0;
}
```

## 📚 API

### `assets::load(const std::string& path)`
Загружает встроенный файл. Возвращает `std::vector<uint8_t>` или пустой вектор если файл не найден.
