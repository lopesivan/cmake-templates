
#include "Date.h"
#include <cstdio>
#include <iomanip>

Date::Date(short year, Month month, short day) : m_year(year), m_month(month), m_day(day) {
    validate();
}

void Date::validate() {
    m_valid = (m_day >= 1 && m_day <= lastDayOfMonth()) &&
              (m_month >= Month::JANUARY && m_month <= Month::DECEMBER) &&
              (m_year >= YEAR_MIN && m_year <= YEAR_MAX);
}

void Date::change(short year, Month month, short day) {
    m_year = year;
    m_month = month;
    m_day = day;

    validate();
}

short Date::lastDayOfMonth() const {
    short numberOfDays = daysOfMonth[(short) m_month - 1];
    if (m_month == Month::FEBRUARY) {
        if (isLeapYear()) {
            numberOfDays++;
        }
    }
    return numberOfDays;
}

short Date::isLeapYear() const {
    return (m_year % 400 == 0) | ((m_year % 4 == 0) && (m_year % 100));
}

void Date::print() const {
    if (m_valid) {
        std::printf("%04d/%02d/%02d\n", m_year, (short) m_month, m_day);
    } else {
        std::printf("invalid date\n");
    }
}

short Date::day() const { return m_day; }

Date::Month Date::month() const { return m_month; };

short Date::year() const { return m_year; };

bool Date::isValid(void) const {
    return m_valid;
}

/*std::strong_ordering*/ auto Date::operator<=>(const Date &other) const -> std::strong_ordering {
    if (auto cmp = this->m_year <=> other.m_year; cmp != 0) return cmp;
    if (auto cmp = this->m_month <=> other.m_month; cmp != 0) return cmp;
    return this->m_day <=> other.m_day;
}

bool Date::operator==(const Date &other) const {
    return (*this <=> other) == 0;
}

std::ostream &operator<<(std::ostream &os, const Date &date) {
    if (date.isValid()) {
        os << date.m_year << '/'
           << std::setfill('0') << std::setw(2) << static_cast<int>(date.month()) << '/'
           << std::setfill('0') << std::setw(2) << date.day();
    } else {
        os << "Invalid date";
    }
    return os;
}
