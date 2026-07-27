#pragma once

#include "core.h"
#include "utils/events/Event.h"
#include "utils/events/MultiEventChannel.h"
#include "CarbonExport.h"

namespace CarbonLab {

    struct CARBON_EXPORT TestUnitUpEventPayload {
        str name;
        str suite;
    };

    class CARBON_EXPORT TestUnitUpEvent : public Event<TestUnitUpEventPayload> {};
    class CARBON_EXPORT TestUnitDownEvent : public Event<TestUnitUpEventPayload> {};

    enum class TestUnitEventType {
        TestUnitUp,
        TestUnitDown
    };

    class CARBON_EXPORT TestUnitEventChannel : public MultiEventChannel<TestUnitEventChannel, TestUnitEventType> {};
}