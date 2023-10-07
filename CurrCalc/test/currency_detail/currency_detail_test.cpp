#include <currency_detail/currency_detail.h>
#include <exchange_rate/exchange_rate.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <vector>

class CurrencyDetailTestFixture : public ::testing::Test {
    protected: 
        void SetUp() {
            exchangeRates = {ExchangeRate("GBP", 0.87000), ExchangeRate("USD", 1.06000)};
            currencyDetail = new CurrencyDetail("EUR", exchangeRates);
        }

        std::vector<ExchangeRate> exchangeRates;
        CurrencyDetail* currencyDetail;
};

using ::testing::ElementsAre;

TEST_F(CurrencyDetailTestFixture, GetCurrencyNamesFromExchangeRates)
{
    EXPECT_THAT(currencyDetail->getAllCurrencyNamesFromExchangeRates(), ElementsAre("GBP", "USD"));
}

TEST_F(CurrencyDetailTestFixture, ConvertAmount)
{
    EXPECT_NEAR(currencyDetail->convertAmount(500.0, "USD", "GBP"), 410.37735, 0.00001);
}