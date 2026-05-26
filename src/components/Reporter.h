#pragma once

#include "core.h"
#include <map>
#include <memory>
#include "utils/logging/Logger.h"
#include "utils/os/ContextPath.h"

namespace CarbonLab {

    enum class ReportType {
        INFO, WARN, ERROR, DEBUG
    };

    class Reporter {
    public:
        void report(const str& message, const ReportType type = ReportType::INFO);

        static std::shared_ptr<Reporter> getInstance(const str& name) {
            if (instances.find(name) == instances.end()) {
                instances[name] = std::make_shared<Reporter>(Reporter(name));
            }
            return instances[name];
        }

    private:
        explicit Reporter(const str& name) {
            auto ctxPath = ContextPath::getExecutablePath();
            logger = std::make_shared<Logger>((ctxPath.parent_path() / name).replace_extension(".report"), name);
            logger->showCallerLocation(false);
        }

        std::shared_ptr<Logger> logger = nullptr;

        static std::map<str, std::shared_ptr<Reporter>> instances;
    };

}