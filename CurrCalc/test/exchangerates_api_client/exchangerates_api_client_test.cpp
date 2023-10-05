#include "../mock/mock_cpr_wrapper.h"
#include <cpr/cpr.h>
#include <exchangerates_api_client/exchangerates_api_client.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <string>
#include <vector>

class ExchangeratesApiClientTestFixture : public ::testing::Test {
    protected:
        void SetUp() override {
            currencyNamesSuccessResponse.status_code = 200;
            currencyNamesSuccessResponse.text = "{\"success\":true,\"symbols\":{\"USD\":\"United States Dollar\",\"GBP\":\"Great Britain Pound\",\"EUR\":\"Euro\",\"JPY\":\"Japanese Yen\"}}";
            currencyNames = {"USD", "GBP", "EUR", "JPY"};
            
            currencyNamesAbsoluteFailureResponse.status_code = 404; // Check Potential Errors table: https://exchangeratesapi.io/documentation/
            currencyNamesRetryFailureResponse.status_code = 500; // We should retry for 408, 425, 429, or 500 - https://stackoverflow.com/questions/51770071/what-are-the-http-codes-to-automatically-retry-the-request

            currencyDetailSuccessResponse.status_code = 200;
            currencyDetailSuccessResponse.text = "{\"success\":true,\"timestamp\":1519296206,\"base\":\"USD\",\"date\":\"2021-03-17\",\"rates\":{\"GBP\":0.75008,\"EUR\":1.44320,\"JPY\":2.54043}}";
            exchangeRates = {ExchangeRate("GBP", 0.75008), ExchangeRate("EUR", 1.44320), ExchangeRate("JPY", 2.54043)};
            currencyDetail = new CurrencyDetail("USD", exchangeRates);

            currencyDetailAbsoluteFailureResponse.status_code = 404; // Check Potential Errors table: https://exchangeratesapi.io/documentation/
            currencyDetailRetryFailureResponse.status_code = 500; // We should retry for 408, 425, 429, or 500 - https://stackoverflow.com/questions/51770071/what-are-the-http-codes-to-automatically-retry-the-request 
        }

        // Mock object and test object
        MockCprWrapper cprWrapper;
        ExchangeratesApiClient apiClient(&cprWrapper);

        // Test values the mock client will use for the fake requests 
        cpr::Url url{"url"};
        cpr::Parameters parameters{{"key", "value"}};

        // Success response for fetching currency names and the list of currency names
        cpr::Response currencyNamesSuccessResponse;
        std::vector<std::string> currencyNames;

        // Absolute and retriable failure responses for fetching currency names
        cpr::Response currencyNamesAbsoluteFailureResponse;
        cpr::Response currencyNamesRetryFailureResponse;

        // Success response for fetching currency detail and the currency detail object
        cpr::Response currencyDetailSuccessResponse;
        std::vector<ExchangeRate> exchangeRates;
        CurrencyDetail* currencyDetail;

        // Absolute and retriable failure responses for fetching currency detail
        cpr::Response currencyDetailAbsoluteFailureResponse;
        cpr::Response currencyDetailRetryFailureResponse;
};

using ::testing::AtLeast;
using ::testing::Return;

TEST_F(ExchangeratesApiClientTestFixture, GetCurrencyNames) {
    EXPECT_CALL(cprWrapper, Get(url, parameters))
        .Times(AtLeast(1));
    ON_CALL(cprWrapper, Get(url, parameters))
        .WillByDefault(Return(currencyNamesSuccessResponse));

    EXPECT_EQ(apiClient.getCurrencyNames(), currencyNames);
}

TEST_F(ExchangeratesApiClientTestFixture, ThrowExceptionIfCurrencyNamesNotFetched) {
    EXPECT_CALL(cprWrapper, Get(url, parameters))
        .Times(AtLeast(1));
    ON_CALL(cprWrapper, Get(url, parameters))
        .WillByDefault(Return(currencyNamesAbsoluteFailureResponse));

    EXPECT_THROW(apiClient.getCurrencyNames(), CurrencyNamesNotFetchedException);
}

TEST_F(ExchangeratesApiClientTestFixture, ThrowExceptionIfCurrencyNamesNotFetchedAfterRetries) {
    EXPECT_CALL(cprWrapper, Get(url, parameters))
        .Times(AtLeast(3));
    ON_CALL(cprWrapper, Get(url, parameters))
        .WillByDefault(Return(currencyNamesRetryFailureResponse));

    EXPECT_THROW(apiClient.getCurrencyNames(), CurrencyNamesNotFetchedException);
}

TEST_F(ExchangeratesApiClientTestFixture, GetCurrencyDetail) {
    EXPECT_CALL(cprWrapper, Get(url, parameters))
        .Times(AtLeast(1));
    ON_CALL(cprWrapper, Get(url, parameters))
        .WillByDefault(Return(currencyDetailSuccessResponse));

    EXPECT_EQ(apiClient.getCurrencyDetail(), currencyDetail);
}

TEST_F(ExchangeratesApiClientTestFixture, ThrowExceptionIfCurrencyDetailNotFetched) {
    EXPECT_CALL(cprWrapper, Get(url, parameters))
        .Times(AtLeast(1));
    ON_CALL(cprWrapper, Get(url, parameters))
        .WillByDefault(Return(currencyDetailAbsoluteFailureResponse));

    EXPECT_THROW(apiClient.getCurrencyDetail(), CurrencyDetailNotFetchedException);
}

TEST_F(ExchangeratesApiClientTestFixture, ThrowExceptionIfCurrencyDetailNotFetchedAfterRetries) {
    EXPECT_CALL(cprWrapper, Get(url, parameters))
        .Times(AtLeast(3));
    ON_CALL(cprWrapper, Get(url, parameters))
        .WillByDefault(Return(currencyDetailRetryFailureResponse));

    EXPECT_THROW(apiClient.getCurrencyDetail(), CurrencyDetailNotFetchedException);
}