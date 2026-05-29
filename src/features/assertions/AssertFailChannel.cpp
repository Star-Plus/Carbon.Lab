#include "AssertFailChannel.h"

namespace CarbonLab {

    AssertFailChannel::AssertFailChannel() : EventChannel<AssertFailChannel, AssertFailEventPayload>(AssertFailEvent()) {}

}