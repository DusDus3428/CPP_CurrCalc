#include <currency_detail/currency_detail.h>
#include <exchange_rate/exchange_rate.h>
#include <gtest/gtest.h>

TEST(CurrencyDetailTest, AddTwoValues)
{
    ASSERT_EQ(testAddFunction(1, 2), 3);
}