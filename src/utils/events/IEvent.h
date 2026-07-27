#pragma once

#include "CarbonExport.h"

namespace CarbonLab {
    class CARBON_EXPORT IEvent {
    public:
        virtual ~IEvent() = default;
    };
}