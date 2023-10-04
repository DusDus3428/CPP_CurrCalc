#include <cpr/cpr.h>

class CprWrapperInterface {
    public: 
        virtual cpr::Response Get(cpr::Url url, cpr::Parameters) = 0;
};