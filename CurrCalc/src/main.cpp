#include <currency_detail/currency_detail.h>
#include <exchangerates_api_client/exchangerates_api_client.h>
#include <helper/cpr_wrapper.h>
#include <util/vector_utils.h>
#include <iostream>
#include <string>
#include <util/constants.h>
#include <util/input_output_utils.h>
#include <vector>

int main()
{
    printWelcome();

    CprWrapper CprWrapper;
    ExchangeratesApiClient client(constants::exchangeratesApiBaseUrl, constants::exchangeratesApiAccessKey, &CprWrapper);
    std::vector<std::string> initialCurrencies = client.getCurrencyNames();

    bool isInitialCurrencySelection{true};
    int initialCurrencySelection = getCurrencySelection(isInitialCurrencySelection, initialCurrencies);

    CurrencyDetail currencyDetail = client.getCurrencyDetail(initialCurrencies[initialCurrencySelection-1]);

    std::vector<std::string> targetCurrencies = listOfExchangeRateToListOfString(currencyDetail.getExchangeRates());
    std::vector<ExchangeRate> exchangeRates = currencyDetail.getExchangeRates();

    int targetCurrencySelection = getCurrencySelection(!isInitialCurrencySelection, targetCurrencies);

    double initialConversionAmount = getConversionAmount();

    double convertedAmount = currencyDetail.convertAmount(initialConversionAmount, targetCurrencies[targetCurrencySelection-1]);

    printResult(currencyDetail, targetCurrencies[targetCurrencySelection], initialConversionAmount, convertedAmount);

    printFarewell();

    return 0;
}