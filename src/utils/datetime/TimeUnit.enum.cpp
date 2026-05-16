#include "TimeUnit.enum.h"
#include <stdexcept>

namespace Split {

    double uniformToSeconds(double val, TimeUnit currentUnit) {
        switch (currentUnit) {
            case TimeUnit::MICRO_SECONDS:
                return val * 1e-6;
            case TimeUnit::MILLI_SECONDS:
                return val * 1e-3;

            default:
                throw std::runtime_error("Unsupported time unit");
        }
    }

    double convertSeconds(double val, TimeUnit targetUnit) {
        switch (targetUnit) {
            case TimeUnit::MICRO_SECONDS:
                return val * 1e6;
            case TimeUnit::MILLI_SECONDS:
                return val * 1e3;

            default:
                throw std::runtime_error("Unsupported time unit");
        }
    }

    double convertTime(double val, TimeUnit currentUnit, TimeUnit targetUnit) {
        if (currentUnit == targetUnit)
            return val;

        if (currentUnit == TimeUnit::SECONDS) {
            return convertSeconds(val, targetUnit);
        }

        if (targetUnit == TimeUnit::SECONDS){
            return uniformToSeconds(val, currentUnit);
        }

        auto inSecs = uniformToSeconds(val, currentUnit);
        return convertSeconds(inSecs, targetUnit);
    }

}