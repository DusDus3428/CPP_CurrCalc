#include <currency_detail/currency_detail.h>
#include <exchange_rate/exchange_rate.h>
#include <gtest/gtest.h>
#include <vector>

class CurrencyDetailTestFixture : public ::testing::Test {
    protected: 
        void SetUp() {
            exchangeRates = {ExchangeRate("GBP", 2.00000), ExchangeRate("EUR", 3.00000)};
            currencyDetail = new CurrencyDetail("USD", exchangeRates);
        }

        std::vector<ExchangeRate> exchangeRates;
        CurrencyDetail* currencyDetail;
};

TEST_F(CurrencyDetailTestFixture, ConvertAmount)
{
    EXPECT_EQ(currencyDetail->convertAmount(500.0, "GBP"), 1000.0);
}