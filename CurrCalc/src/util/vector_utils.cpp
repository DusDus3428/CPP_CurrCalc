#include <exchange_rate/exchange_rate.h>
#include <string>
#include <util/vector_utils.h>
#include <vector>

std::vector<std::string> listOfExchangeRateToListOfString(std::vector<ExchangeRate> exchangeRates) {
    std::vector<std::string> targetCurrencies;
    
    for(auto er : exchangeRates) {
        targetCurrencies.push_back(er.getCurrency());
    }

    return targetCurrencies;
} 
