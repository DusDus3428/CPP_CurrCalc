#include <chrono>
#include <currency_detail/currency_detail.h>
#include <cpr/cpr.h>
#include <exchangerates_api_client/exchangerates_api_client.h>
#include <helper/cpr_wrapper_interface.h>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <string>
#include <thread>         
#include <vector>
#include <iostream>

using json = nlohmann::json;

ExchangeratesApiClient::ExchangeratesApiClient(std::string url, std::string accessKey, CprWrapperInterface* cprWrapper) {
    m_url = url;
    m_accessKey = accessKey;
    m_cprWrapper = cprWrapper;
}

CurrencyDetail ExchangeratesApiClient::getCurrencyDetailFromResponse(std::string responseBody) const {
    json data = json::parse(responseBody);

    std::vector<ExchangeRate> exchangeRates; 

    for (auto& el : data["rates"].items())
    {
        exchangeRates.push_back(ExchangeRate(el.key(), el.value()));
    }

    return CurrencyDetail(data["base"], exchangeRates);
};

CurrencyDetail ExchangeratesApiClient::getEuroCurrencyDetail() const {
    int attempts{0};
    cpr::Response response;
    do {
        response = getCprWrapper()->Get(
            cpr::Url{getUrl().append("latest")},
            cpr::Parameters{
                {"access_key", m_accessKey}
            }
        );

        switch(response.status_code){
            case 200:
                return getCurrencyDetailFromResponse(response.text);
            case 408:
            case 425:
            case 429:
            case 500:
                attempts++;
                std::this_thread::sleep_for (std::chrono::seconds(3));
                continue;
            default:
                throw std::runtime_error("Could not get currency detail. Response code: " + std::to_string(response.status_code)); 
        }
    } while (attempts < 4);

    throw std::runtime_error("Could not get currency detail after " + std::to_string(attempts) + ". Last response code: " + std::to_string(response.status_code));
}