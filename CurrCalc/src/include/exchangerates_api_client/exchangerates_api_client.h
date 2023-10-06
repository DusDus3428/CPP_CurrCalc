#ifndef EXCHANGERATES_API_CLIENT_H
#define EXCHANGERATES_API_CLIENT_H

#include <cpr/cpr.h>
#include <currency_detail/currency_detail.h>
#include <helper/cpr_wrapper_interface.h>
#include <util/constants.h>
#include <string>
#include <vector>

cpr::Response getRequestTest();

class ExchangeratesApiClient {
    private:
        std::string m_url;
        std::string m_accessKey;
        CprWrapperInterface* m_cprWrapper;
        CurrencyDetail getCurrencyDetailFromResponse(std::string responseBody) const;
    public:
        ExchangeratesApiClient(std::string url, std::string accessKey, CprWrapperInterface* cprWrapper);
        CurrencyDetail getEuroCurrencyDetail() const;
        std::string getUrl() const {return m_url;}
        std::string getAccessKey() const {return m_accessKey;}
        CprWrapperInterface* getCprWrapper() const {return m_cprWrapper;}
};

#endif