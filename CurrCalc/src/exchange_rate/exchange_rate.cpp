#include <exchange_rate/exchange_rate.h>
#include <string>

ExchangeRate::ExchangeRate(std::string currency, double rate) {
    m_currency = currency;
    m_rate = rate;
};
