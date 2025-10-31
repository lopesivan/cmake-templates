#include <iostream>
#include <assets/assets.hpp>

int main()
{
    auto data = assets::load("/hello.txt");
    
    if (!data.empty()) {
        std::cout << std::string(data.begin(), data.end()) << std::endl;
    }

    return 0;
}