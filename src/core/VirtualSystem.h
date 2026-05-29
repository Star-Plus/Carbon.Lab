#pragma once

namespace CarbonLab {

    template <class TSystem>
    class VirtualSystem {
    public:
        virtual void operator += (TSystem& other) = 0;
    };

}