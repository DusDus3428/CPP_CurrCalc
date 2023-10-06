#include <currency_detail/currency_detail.h>
#include <exchangerates_api_client/exchangerates_api_client.h>
#include <helper/cpr_wrapper.h>
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
    CurrencyDetail currencyDetail = client.getEuroCurrencyDetail();

    std::vector<std::string> currencyNames = currencyDetail.getAllCurrencyNamesFromExchangeRates();

    int initialCurrencyIndex = getCurrencySelection(currencyNames);
    std::string initalCurrencyName = currencyNames[initialCurrencyIndex];
    int targetCurrencyIndex = getCurrencySelection(currencyNames, initialCurrencyIndex);
    std::string targetCurrencyName = currencyNames[targetCurrencyIndex];

    double conversionAmount = getConversionAmount();

    double convertedAmount = currencyDetail.convertAmount(conversionAmount, initalCurrencyName, targetCurrencyName);

    printResult(conversionAmount, initalCurrencyName, convertedAmount, targetCurrencyName);

    printFarewell();

    return 0;
}