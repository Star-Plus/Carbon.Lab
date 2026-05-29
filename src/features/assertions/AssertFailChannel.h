#pragma once

#include "utils/events/EventChannel.h"
#include "AssertFailEvent.h"

namespace CarbonLab {

    class AssertFailChannel : public EventChannel<AssertFailChannel, AssertFailEventPayload> {
    public:
        AssertFailChannel();
    };

}