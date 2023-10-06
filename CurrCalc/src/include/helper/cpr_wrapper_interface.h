#ifndef CPR_WRAPPER_INTERFACE_H
#define CPR_WRAPPER_INTERFACE_H

#include <cpr/cpr.h>

class CprWrapperInterface {
    public: 
        virtual cpr::Response Get(cpr::Url url, cpr::Parameters) = 0;
};

#endif