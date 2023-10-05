#include <algorithm>
#include <currency_detail/currency_detail.h>
#include <exchange_rate/exchange_rate.h>
#include <stdexcept>

CurrencyDetail::CurrencyDetail(std::string name, std::vector<ExchangeRate> exchangeRates) {
    m_name = name;
    m_exchangeRates = exchangeRates;
}

double CurrencyDetail::convertAmount(double amount, std::string targetCurrencyName) const {
    auto it = std::find_if(m_exchangeRates.begin(), m_exchangeRates.end(), [&targetCurrencyName](const ExchangeRate& exchangeRate){return exchangeRate.getCurrency() == targetCurrencyName;});

    if(it != m_exchangeRates.end()){
        return it->getRate() * amount;
    } else {
        throw std::runtime_error("Could not find an exchange rate for the target currency " + targetCurrencyName);
    }
}