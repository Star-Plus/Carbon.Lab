#pragma once
#include <string>
#include <chrono>
#include <fstream>
#include <source_location>


#include "Color.h"

namespace CarbonLab {

    class Logger {
    public:
        Logger();
        Logger(std::string name="");
        Logger(Logger&&) = default;
        Logger& operator=(Logger&&) = default;
        ~Logger();

        void info(const std::string& message, const std::source_location& location = std::source_location::current()) const;
        void warning(const std::string& message, const std::source_location& location = std::source_location::current()) const;
        void error(const std::string& message, const std::source_location& location = std::source_location::current()) const;
        void debug(const std::string& message, const std::source_location& location = std::source_location::current()) const;

        void setCheckPoint(const std::string& message="");

        void log(const std::string& message, Color color = Color::WHITE, const std::source_location& location = std::source_location::current()) const;
        void log(const std::wstring& message, Color color = Color::WHITE) const;

    private:
        std::string name;
        std::chrono::steady_clock::time_point checkPointTime;
        mutable std::unique_ptr<std::fstream> logFile;
    };

}