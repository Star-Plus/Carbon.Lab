#include "CarbonExport.h"

namespace Split {

    enum class TimeUnit {
        MICRO_SECONDS,
        MILLI_SECONDS,
        SECONDS
    };

    CARBON_EXPORT double convertTime(double , TimeUnit, TimeUnit);
}