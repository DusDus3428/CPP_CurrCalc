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
            currencyNamesFailureResponse.status_code = 400; // Anything but 200

            currencyDetailSuccessResponse.status_code = 200;
            currencyDetailSuccessResponse.text = "{\"success\":true,\"timestamp\":1519296206,\"base\":\"USD\",\"date\":\"2021-03-17\",\"rates\":{\"USD\":0.54007,\"GBP\":0.75008,\"EUR\":1.44320,\"JPY\":2.54043}}";
            currencyDetailFailureResponse.status_code = 400; // Anything but 200            
        }

        MockCprWrapper cprWrapper;
        ExchangeratesApiClient apiClient(&cprWrapper);

        cpr::Url url{"url"};
        cpr::Parameters parameters{{"key", "value"}};
        std::vector<std::string> currencyNames{"USD", "GBP", "EUR", "JPY"};

        cpr::Response currencyNamesSuccessResponse;
        cpr::Response currencyNamesFailureResponse;

        cpr::Response currencyDetailSuccessResponse;
        cpr::Response currencyDetailFailureResponse;

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

TEST_F(ExchangeratesApiClientTestFixture, ThrowExceptionIfCurrencyNamesCannotBeFetched) {
    EXPECT_CALL(cprWrapper, Get(url, parameters))
        .Times(AtLeast(1));
    ON_CALL(cprWrapper, Get(url, parameters))
        .WillByDefault(Return(currencyNamesFailureResponse));

    EXPECT_THROW(apiClient.getCurrencyNames(), CurrencyNamesNotFetchedException);
}

TEST_F(ExchangeratesApiClientTestFixture, ThrowExceptionIfCurrencyNamesCannotBeFetched) {
    EXPECT_CALL(cprWrapper, Get(url, parameters))
        .Times(AtLeast(3));
    ON_CALL(cprWrapper, Get(url, parameters))
        .WillByDefault(Return(currencyNamesFailureResponse));

    EXPECT_THROW(apiClient.getCurrencyNames(), CurrencyNamesNotFetchedException);
}