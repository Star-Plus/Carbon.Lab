#pragma once

#include "core.h"
#include "utils/events/BaseEvent.h"

namespace CarbonLab {

    struct AssertFailEventPayload {
        str suiteName, testName;
        str expected, actual;
    };

    class AssertFailEvent : public BaseEvent<AssertFailEventPayload> {};
}