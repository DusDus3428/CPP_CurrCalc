#include <exchangerates_api_client/exchangerates_api_client.h>

cpr::Response getRequestTest()
{
    return cpr::Get(cpr::Url{"http://www.httpbin.org/get"});
}