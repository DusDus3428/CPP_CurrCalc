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

double CurrencyDetail::convertAmount(double amount, std::string initialCurrencyName, std::string targetCurrencyName) const {   
    if(targetCurrencyName == m_name){
        return amount / getConversionRateFromEuro(initialCurrencyName);
    } else if(initialCurrencyName == m_name) {
        return amount * getConversionRateFromEuro(targetCurrencyName);
    } else {
        double amountInEuro = amount / getConversionRateFromEuro(initialCurrencyName);
        return amount * getConversionRateFromEuro(targetCurrencyName);
    }
}