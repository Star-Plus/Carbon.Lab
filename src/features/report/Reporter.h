#pragma once

#include "core.h"
#include <map>
#include <memory>
#include <vector>
#include "utils/datetime/DateTime.h"
#include "utils/logging/Logger.h"
#include "utils/os/ContextPath.h"
#include "core/TestStatus.enum.h"

namespace CarbonLab {

    struct TestSheet {
        str testName;
        DateTime startedAt, finishedAt;
        TestStatus status;

        struct Failure {
            str message;
            std::vector<str> stackTrace;
            str expected, actual;
            std::vector<str> logs;
        } failure;
    };

    class Reporter {
    public:

        static std::shared_ptr<Reporter> getInstance(const str& name) {
            if (instances.find(name) == instances.end()) {
                instances[name] = std::make_shared<Reporter>(Reporter(name));
            }
            return instances[name];
        }

        void serializeToMarkdown();
        
    private:
        explicit Reporter(const str& name) {
            auto ctxPath = ContextPath::getExecutablePath();
            logger = std::make_shared<Logger>((ctxPath.parent_path() / name).replace_extension(".report"), name);
            logger->showCallerLocation(false);
        }

        std::shared_ptr<Logger> logger = nullptr;

        static std::map<str, std::shared_ptr<Reporter>> instances;

        DateTime startedAt, finishedAt;

        str suiteName;
        std::vector<TestSheet> tests;

        str os, arch, runtime;

        std::map<str, str> deps;

    };

}