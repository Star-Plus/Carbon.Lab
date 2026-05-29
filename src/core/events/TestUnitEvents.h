#pragma once

#include "core.h"
#include "utils/events/Event.h"
#include "utils/events/MultiEventChannel.h"

namespace CarbonLab {

    struct TestUnitUpEventPayload {
        str name;
        str suite;
    };

    class TestUnitUpEvent : public Event<TestUnitUpEventPayload> {};
    class TestUnitDownEvent : public Event<TestUnitUpEventPayload> {};

    enum class TestUnitEventType {
        TestUnitUp,
        TestUnitDown
    };

    class TestUnitEventChannel : public MultiEventChannel<TestUnitEventChannel, TestUnitEventType> {};
}