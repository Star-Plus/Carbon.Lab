#include "Reporter.h"

namespace CarbonLab {

    std::map<str, std::shared_ptr<Reporter>> Reporter::instances;

    void Reporter::report(const str& message, const ReportType type) {
        switch (type) {
            case ReportType::INFO: logger->info(message); break;
            case ReportType::WARN: logger->warning(message); break;
            case ReportType::ERROR: logger->error(message); break;
            case ReportType::DEBUG: logger->debug(message); break;
        }
    }

}