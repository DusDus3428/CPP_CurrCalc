#include <cpr/cpr.h>
#include <gmock/gmock.h>
#include <helper/cpr_wrapper_interface.h>

class MockCprWrapper : public CprWrapperInterface {
    public: 
    MOCK_METHOD(cpr::Response, Get, (cpr::Url url, cpr::Parameters parameters), (override));
};