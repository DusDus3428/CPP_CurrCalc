#include <currency_detail/currency_detail.h>
#include <exchangerates_api_client/exchangerates_api_client.h>
#include <helper/cpr_wrapper.h>
#include <iostream>
#include <string>
#include <util/constants.h>
#include <vector>

int main()
{
    CprWrapper CprWrapper;
    ExchangeratesApiClient client(constants::exchangeratesApiBaseUrl, constants::exchangeratesApiAccessKey, &CprWrapper);

    std::vector<std::string> currencyName = client.getCurrencyNames();
    for(auto it : currencyName)
    {
        std::cout << it << '\n';
    }

    CurrencyDetail currencyDetail = client.getCurrencyDetail("USD");
    std::cout << currencyDetail.getName();

    std::vector<ExchangeRate> exchangeRates = currencyDetail.getExchangeRates();

    for(auto it : exchangeRates)
    {
        std::cout << it.getCurrency() << ": " << it.getRate() << '\n';
    }


    return 0;
}