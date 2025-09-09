
#include "gtest/gtest.h"
#include "Date.h"
#include <sstream>

TEST(date_test, validateInvalidTest) {
    Date date(2024, Date::Month::FEBRUARY, 30);
    ASSERT_EQ(date.isValid(), false);
}

TEST(date_test, validateValidTest) {
    Date date(2024, Date::Month::FEBRUARY, 20);
    ASSERT_EQ(date.isValid(), true);
}

TEST(date_test, IsLapYearTest) {
    Date date(2024, Date::Month::FEBRUARY, 20);
    ASSERT_EQ(date.isLeapYear(), true);
}

TEST(date_test, IsNotLapYearTest) {
    Date date(2021, Date::Month::FEBRUARY, 20);
    ASSERT_EQ(date.isLeapYear(), false);
}

TEST(date_test, ChangeDayValidTest) {
    Date date(2021, Date::Month::FEBRUARY, 20);
    date.change(2021, Date::Month::FEBRUARY, 28);
    ASSERT_EQ(date.isValid(), true);
}

TEST(date_test, ChangeDayInValidTest) {
    Date date(2021, Date::Month::FEBRUARY, 20);
    date.change(2021, Date::Month::FEBRUARY, 30);
    ASSERT_EQ(date.isValid(), false);
}

TEST(date_test, ChangeDayLapYearValidTest) {
    Date date(2020, Date::Month::FEBRUARY, 28);
    date.change(2020, Date::Month::FEBRUARY, 29);
    ASSERT_EQ(date.isValid(), true);
}

TEST(date_test, ChangeDayLapYearInValidTest) {
    Date date(2021, Date::Month::FEBRUARY, 28);
    date.change(2021, Date::Month::FEBRUARY, 29);
    ASSERT_EQ(date.isValid(), false);
}

TEST(date_test, ChangeMonthValidTest) {
    Date date(2020, Date::Month::FEBRUARY, 28);
    date.change(2020, Date::Month::MARCH, 28);
    ASSERT_EQ(date.isValid(), true);
}

TEST(date_test, ChangeMonthInValidTest) {
    Date date(2020, Date::Month::JANUARY, 31);
    date.change(2020, Date::Month::APRIL, 31);
    ASSERT_EQ(date.isValid(), false);
}

TEST(date_test, LowerMemberOperatorFunction1_Test) {
    Date dateLeft(2020, Date::Month::JANUARY, 31);
    Date dateRight(2020, Date::Month::JANUARY, 1);
    ASSERT_EQ(dateLeft < dateRight, false);
}

TEST(date_test, LowerMemberOperatorFunction2_Test) {
    Date dateLeft(2020, Date::Month::JANUARY, 1);
    Date dateRight(2020, Date::Month::JANUARY, 2);
    ASSERT_EQ(dateLeft < dateRight, true);
}

TEST(date_test, EqualMemberOperatorFunction1_Test) {
    Date dateLeft(2020, Date::Month::JANUARY, 31);
    Date dateRight(2020, Date::Month::JANUARY, 31);
    ASSERT_EQ(dateLeft == dateRight, true);
}

TEST(date_test, DiffMemberOperatorFunction1_Test) {
    Date dateLeft(2020, Date::Month::JANUARY, 31);
    Date dateRight(2020, Date::Month::JANUARY, 1);
    ASSERT_EQ(dateLeft != dateRight, true);
}

TEST(date_test, LowerEqualMemberOperatorFunction1_Test) {
    Date dateLeft(2020, Date::Month::JANUARY, 1);
    Date dateRight(2020, Date::Month::JANUARY, 31);
    ASSERT_EQ(dateLeft <= dateRight, true);
}

TEST(date_test, LowerEqualMemberOperatorFunction2_Test) {
    Date dateLeft(2020, Date::Month::JANUARY, 1);
    Date dateRight(2020, Date::Month::JANUARY, 1);
    ASSERT_EQ(dateLeft <= dateRight, true);
}

TEST(date_test, LowerEqualMemberOperatorFunction3_Test) {
    Date dateLeft(2020, Date::Month::JANUARY, 1);
    Date dateRight(2020, Date::Month::JANUARY, 2);
    ASSERT_EQ(dateLeft <= dateRight, true);
}

TEST(date_test, GreatherMemberOperatorFunction1_Test) {
    Date dateLeft(2020, Date::Month::JANUARY, 1);
    Date dateRight(2020, Date::Month::JANUARY, 31);
    ASSERT_EQ(dateLeft > dateRight, false);
}

TEST(date_test, GreatherMemberOperatorFunction2_Test) {
    Date dateLeft(2020, Date::Month::JANUARY, 2);
    Date dateRight(2020, Date::Month::JANUARY, 1);
    ASSERT_EQ(dateLeft > dateRight, true);
}

TEST(date_test, GreatherEqualMemberOperatorFunction1_Test) {
    Date dateLeft(2020, Date::Month::JANUARY, 1);
    Date dateRight(2020, Date::Month::JANUARY, 31);
    ASSERT_EQ(dateLeft >= dateRight, false);
}

TEST(date_test, GreatherEqualMemberOperatorFunction2_Test) {
    Date dateLeft(2020, Date::Month::JANUARY, 1);
    Date dateRight(2020, Date::Month::JANUARY, 1);
    ASSERT_EQ(dateLeft >= dateRight, true);
}

TEST(date_test, GreatherEqualMemberOperatorFunction3_Test) {
    Date dateLeft(2020, Date::Month::JANUARY, 31);
    Date dateRight(2020, Date::Month::JANUARY, 2);
    ASSERT_EQ(dateLeft >= dateRight, true);
}

TEST(date_test, GreatherEqualMemberOperatorFunction4_Test) {
    Date dateLeft(2020, Date::Month::JANUARY, 31);
    Date dateRight(2020, Date::Month::JANUARY, 2);

    ASSERT_EQ(dateLeft >= dateRight, true);
}

TEST(date_test, osstreamOperatorFunction_Test1) {
    Date date(2020, Date::Month::JANUARY, 2);
    std::ostringstream os;
    os << date;

    ASSERT_EQ(os.str(), "2020/01/02");
}

TEST(date_test, osstreamOperatorFunction_Test2) {
    Date date(2021, Date::Month::FEBRUARY, 29);
    std::ostringstream os;
    os << date;

    ASSERT_EQ(os.str(), "Invalid date");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
