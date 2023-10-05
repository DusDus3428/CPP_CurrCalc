#ifndef EXCHANGE_RATE_H
#define EXCHANGE_RATE_H

#include <string>

class ExchangeRate {
    private:
        std::string m_currency;
        double m_rate;
    public:
        ExchangeRate(std::string currency, double rate);
        std::string getCurrency() const {return m_currency;}
        double getRate() const {return m_rate;}
};

#endif