#include <algorithm>
#include <currency_detail/currency_detail.h>
#include <exchange_rate/exchange_rate.h>
#include <stdexcept>

double CurrencyDetail::getConversionRateFromEuro(std::string currencyName) const {
    auto it = std::find_if(
        m_exchangeRates.begin(), 
        m_exchangeRates.end(), 
        [&currencyName](const ExchangeRate& exchangeRate){return exchangeRate.getCurrency() == currencyName;}
    );

    if(it != m_exchangeRates.end()){
        return it->getRate();
    } else {
        throw std::runtime_error("Could not find an exchange rate for the currency " + currencyName);
    }
}

CurrencyDetail::CurrencyDetail(std::string name, std::vector<ExchangeRate> exchangeRates) {
    m_name = name;
    m_exchangeRates = exchangeRates;
}

std::vector<std::string> CurrencyDetail::getAllCurrencyNamesFromExchangeRates() const {
    std::vector<std::string> currencyNames;
    
    for(auto er : m_exchangeRates) {
        currencyNames.push_back(er.getCurrency());
    }

    return currencyNames;
}

double CurrencyDetail::convertAmount(double amount, std::string initialCurrencyName, std::string targetCurrencyName) const {   
    double convertedAmount{};
    if(targetCurrencyName == m_name){
        convertedAmount = amount / getConversionRateFromEuro(initialCurrencyName);
    } else if(initialCurrencyName == m_name) {
        convertedAmount = amount * getConversionRateFromEuro(targetCurrencyName);
    } else {
        double amountInEuro = amount / getConversionRateFromEuro(initialCurrencyName);
        convertedAmount = amountInEuro * getConversionRateFromEuro(targetCurrencyName);
    }

    return convertedAmount;
}