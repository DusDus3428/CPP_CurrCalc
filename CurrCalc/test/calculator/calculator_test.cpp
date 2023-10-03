#include <calculator/calculator.h>
#include <gtest/gtest.h>

TEST(CalculatorTest, AddTwoValues)
{
    ASSERT_EQ(testAddFunction(1, 2), 3);
}