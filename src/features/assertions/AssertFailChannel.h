#pragma once

#include "utils/events/EventChannel.h"
#include "AssertFailEvent.h"
#include "CarbonExport.h"

namespace CarbonLab {

    class CARBON_EXPORT AssertFailChannel : public EventChannel<AssertFailChannel, AssertFailEventPayload> {
    public:
        AssertFailChannel();
    };

}