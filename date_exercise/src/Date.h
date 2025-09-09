#ifndef DATE_DATE_H
#define DATE_DATE_H

#include <array>
#include <ostream>
#include <compare>

class Date {
public:

    enum {
        YEAR_MIN = 1900, YEAR_MAX = 2100
    };

    enum class Month {
        JANUARY = 1, FEBRUARY, MARCH, APRIL, MAY, JUNE, JULY, AUGUST, SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER
    };

    Date() = default;

    Date(short year, Month month, short day);

    void validate();

    void change(short day, Month month, short year);

    short lastDayOfMonth() const;

    short isLeapYear() const;

    void print() const;

    short day() const;

    Month month() const;

    short year() const;

    bool isValid(void) const;

    bool operator==(const Date &other) const ;

    auto operator<=>(const Date &other) const -> std::strong_ordering;

    friend std::ostream &operator<<(std::ostream &os, const Date &date);
private:
    short m_year;
    Month m_month;
    short m_day;
    bool m_valid{false};

    const std::array<short, 12> daysOfMonth{31, 28, 31, 30, 31, 30, 30, 31, 30, 31, 30, 31};
};

#endif //DATE_DATE_H
