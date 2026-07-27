#pragma once
#include <memory>
#include <chrono>
#include <fstream>
#include <source_location>


#include "Color.h"
#include "core.h"
#include "CarbonExport.h"

namespace CarbonLab {

    class CARBON_EXPORT Logger {
    public:
        Logger();
        Logger(str name);
        Logger(const fpath& path, str name);

        Logger& info(const str& message, const std::source_location& location = std::source_location::current());
        Logger& warning(const str& message, const std::source_location& location = std::source_location::current());
        Logger& error(const str& message, const std::source_location& location = std::source_location::current());
        Logger& debug(const str& message, const std::source_location& location = std::source_location::current());

        Logger& log(const str& message, Color color = Color::WHITE, const std::source_location& location = std::source_location::current());

        void showCallerLocation(bool show) { this->showLocation = show; }

    private:
        str name;
        std::chrono::steady_clock::time_point checkPointTime;
        mutable std::shared_ptr<std::ofstream> logFile;

        bool showLocation = true;
    };

}