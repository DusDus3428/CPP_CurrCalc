#include "../mock/mock_cpr_wrapper.h"
#include <cpr/cpr.h>
#include <currency_detail/currency_detail.h>
#include <exchangerates_api_client/exchangerates_api_client.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#include <vector>

class ExchangeratesApiClientTestFixture : public ::testing::Test {
    protected:
        void SetUp() override {
            apiClient = new ExchangeratesApiClient(urlString, accessKeyString, &cprWrapper);

            currencyNamesSuccessResponse.status_code = 200;
            currencyNamesSuccessResponse.text = "{\"success\":true,\"symbols\":{\"USD\":\"United States Dollar\",\"GBP\":\"Great Britain Pound\",\"EUR\":\"Euro\",\"JPY\":\"Japanese Yen\"}}";
            currencyNames = {"EUR", "GBP", "JPY", "USD"};
            
            currencyNamesAbsoluteFailureResponse.status_code = 404; // Check Potential Errors table: https://exchangeratesapi.io/documentation/
            currencyNamesRetryFailureResponse.status_code = 500; // We should retry for 408, 425, 429, or 500 - https://stackoverflow.com/questions/51770071/what-are-the-http-codes-to-automatically-retry-the-request

            currencyDetailSuccessResponse.status_code = 200;
            currencyDetailSuccessResponse.text = "{\"success\":true,\"timestamp\":1519296206,\"base\":\"USD\",\"date\":\"2021-03-17\",\"rates\":{\"GBP\":0.75008,\"EUR\":1.44320,\"JPY\":2.54043}}";
            exchangeRates = {ExchangeRate("GBP", 0.75008), ExchangeRate("EUR", 1.44320), ExchangeRate("JPY", 2.54043)};
            currencyDetail = new CurrencyDetail("USD", exchangeRates);

            currencyDetailAbsoluteFailureResponse.status_code = 404; // Check Potential Errors table: https://exchangeratesapi.io/documentation/
            currencyDetailRetryFailureResponse.status_code = 500; // We should retry for 408, 425, 429, or 500 - https://stackoverflow.com/questions/51770071/what-are-the-http-codes-to-automatically-retry-the-request 
        }

        std::string urlString{"url"};
        std::string accessKeyString{"accessKey"};
        cpr::Url url{urlString};
        cpr::Parameters parameters{{"access_key", accessKeyString}};

        // Mock object and test object
        MockCprWrapper cprWrapper;
        ExchangeratesApiClient* apiClient;

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
using ::testing::ReturnPointee;
using ::testing::ElementsAre;
using ::testing::_;

TEST_F(ExchangeratesApiClientTestFixture, GetCurrencyNames) {
    ON_CALL(cprWrapper, Get(_, _))
        .WillByDefault(ReturnPointee(&currencyNamesSuccessResponse));
    EXPECT_CALL(cprWrapper, Get(_, _))
        .Times(AtLeast(1));

    EXPECT_THAT(apiClient->getCurrencyNames(), ElementsAre("EUR", "GBP", "JPY", "USD"));
}

TEST_F(ExchangeratesApiClientTestFixture, ThrowExceptionIfCurrencyNamesNotFetched) {
    ON_CALL(cprWrapper, Get(_, _))
        .WillByDefault(ReturnPointee(&currencyNamesAbsoluteFailureResponse));
    EXPECT_CALL(cprWrapper, Get(_, _))
        .Times(AtLeast(1));

    EXPECT_THROW(apiClient->getCurrencyNames(), std::runtime_error);
}

TEST_F(ExchangeratesApiClientTestFixture, ThrowExceptionIfCurrencyNamesNotFetchedAfterRetries) {
    ON_CALL(cprWrapper, Get(_, _))
        .WillByDefault(ReturnPointee(&currencyNamesRetryFailureResponse));
    EXPECT_CALL(cprWrapper, Get(_, _))
        .Times(AtLeast(3));

    EXPECT_THROW(apiClient->getCurrencyNames(), std::runtime_error);
}

TEST_F(ExchangeratesApiClientTestFixture, GetCurrencyDetail) {
    ON_CALL(cprWrapper, Get(_, _))
        .WillByDefault(ReturnPointee(&currencyDetailSuccessResponse));
    EXPECT_CALL(cprWrapper, Get(_, _))
        .Times(AtLeast(1));

    CurrencyDetail result = apiClient->getCurrencyDetail("CUR");
    
    EXPECT_EQ(result.getName(), currencyDetail->getName());
    EXPECT_EQ(result.getExchangeRates()[0].getCurrency(), "EUR");
    EXPECT_EQ(result.getExchangeRates()[0].getRate(), 1.44320);
    EXPECT_EQ(result.getExchangeRates()[1].getCurrency(), "GBP");
    EXPECT_EQ(result.getExchangeRates()[1].getRate(), 0.75008);
    EXPECT_EQ(result.getExchangeRates()[2].getCurrency(), "JPY");
    EXPECT_EQ(result.getExchangeRates()[2].getRate(), 2.54043);
}

TEST_F(ExchangeratesApiClientTestFixture, ThrowExceptionIfCurrencyDetailNotFetched) {
    ON_CALL(cprWrapper, Get(_, _))
        .WillByDefault(ReturnPointee(&currencyDetailAbsoluteFailureResponse));
    EXPECT_CALL(cprWrapper, Get(_, _))
        .Times(AtLeast(1));

    EXPECT_THROW(apiClient->getCurrencyDetail("CUR"), std::runtime_error);
}

TEST_F(ExchangeratesApiClientTestFixture, ThrowExceptionIfCurrencyDetailNotFetchedAfterRetries) {
    ON_CALL(cprWrapper, Get(_, _))
        .WillByDefault(ReturnPointee(&currencyDetailRetryFailureResponse));
    EXPECT_CALL(cprWrapper, Get(_, _))
        .Times(AtLeast(3));

    EXPECT_THROW(apiClient->getCurrencyDetail("CUR"), std::runtime_error);
}