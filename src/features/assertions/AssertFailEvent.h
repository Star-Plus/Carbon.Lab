#pragma once

#include "core.h"
#include "utils/events/Event.h"

namespace CarbonLab {

    struct AssertFailEventPayload {
        str suiteName, testName;
        str expected, actual;
    };

    class AssertFailEvent : public Event<AssertFailEventPayload> {};
}