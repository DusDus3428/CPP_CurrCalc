#include <exchangerates_api_client/exchangerates_api_client.h>
#include <iostream>

int main()
{
    std::cout << "All your base are belong to us.\n";

    cpr::Response r = getRequestTest();
    std::cout << r.status_code << '\n';

    return 0;
}