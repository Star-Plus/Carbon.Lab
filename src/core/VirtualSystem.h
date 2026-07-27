#pragma once

#include "CarbonExport.h"

namespace CarbonLab {

    template <class TSystem>
    class CARBON_EXPORT VirtualSystem {
    public:
        virtual void operator += (TSystem& other) = 0;
    };

}