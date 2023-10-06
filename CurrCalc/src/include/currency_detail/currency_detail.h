#ifndef CURRENCY_DETAIL_H
#define CURRENCY_DETAIL_H

#include <exchange_rate/exchange_rate.h>
#include <string>
#include <vector>

class CurrencyDetail {
    private:
        std::string m_name;
        std::vector<ExchangeRate> m_exchangeRates;
        double getConversionRateFromEuro(std::string currencyName) const;
    public:
        CurrencyDetail(std::string name, std::vector<ExchangeRate> exchangeRates);
        std::vector<std::string> getAllCurrencyNamesFromExchangeRates() const;
        double convertAmount(double amount, std::string initialCurrencyName, std::string targetCurrencyName) const;
        std::string getName() const {return m_name;}
        std::vector<ExchangeRate> getExchangeRates() const {return m_exchangeRates;}
};

#endif