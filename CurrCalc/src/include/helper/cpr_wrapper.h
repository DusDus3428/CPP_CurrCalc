#ifndef CPR_WRAPPER_H
#define CPR_WRAPPER_H

#include <cpr/cpr.h>
#include <helper/cpr_wrapper_interface.h>

class CprWrapper : public CprWrapperInterface {
    public: 
        cpr::Response Get(cpr::Url url, cpr::Parameters parameters) { return cpr::Get(url, parameters);}
};

#endif