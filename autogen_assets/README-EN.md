# 🚀 AutoGen Assets

> **Embed files directly into C++ executables**

[![C++](https://img.shields.io/badge/C%2B%2B-11%2B-blue.svg)](https://en.cppreference.com/)
[![CMake](https://img.shields.io/badge/CMake-3.20%2B-green.svg)](https://cmake.org/)

CMake module for automatically embedding resource files into C++ projects.

##  Requirements

- **C++11+**
- **CMake 3.20+**  
- Windows/Linux/macOS

## 🔧 How to include in your project

1. Copy the `cmake/autogen_assets.cmake` file to your project
2. Add to your `CMakeLists.txt`:

```cmake
include(cmake/autogen_assets.cmake)
autogen_assets(your_app_name path/to/assets/)
```

## 💻 Usage

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
Loads embedded file. Returns `std::vector<uint8_t>` or empty vector if file not found.
