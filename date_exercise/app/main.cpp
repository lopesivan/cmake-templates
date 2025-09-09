#include <iostream>
#include "Date.h"

int main() {

    Date date(2000, Date::Month::FEBRUARY, 05);

    std::cout << date.year() << " " << (date.isLeapYear() ? "is leap year" : "isn't leap year") << std::endl;
    std::cout << "Hello, World!" << std::endl;

    return 0;
}
