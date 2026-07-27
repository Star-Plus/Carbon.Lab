#pragma once

#include "core.h"
#include "utils/events/Event.h"

#include "CarbonExport.h"

namespace CarbonLab {

    struct CARBON_EXPORT AssertFailEventPayload {
        str suiteName, testName;
        str expected, actual;
    };

    class CARBON_EXPORT AssertFailEvent : public Event<AssertFailEventPayload> {};
}