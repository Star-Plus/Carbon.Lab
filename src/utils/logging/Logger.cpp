#include <iostream>

#include <utility>
#include "Logger.h"

#include <filesystem>
#include "Format.h"

#include "utils/os/AppDataDir.h"


namespace CarbonLab {

    Logger::Logger()
    {
        const auto appDir = OS::AppData::GetAppDataDir();

        logFile = std::make_shared<std::ofstream>();
        logFile->open(appDir/"logs/ALL.log", std::ios::out | std::ios::app);
    }
    
    Logger::Logger(std::string name) : name(std::move(name))
    {
        const auto appDir = OS::AppData::GetAppDataDir();
        const auto logFileName = this->name.empty() ? "ALL.log" : this->name + ".log";

        logFile = std::make_shared<std::ofstream>();
        logFile->open(appDir / "logs" / logFileName, std::ios::out | std::ios::trunc);
    }

    Logger::Logger(const fpath& path, str name) : name(std::move(name)) {
        logFile = std::make_shared<std::ofstream>();
        logFile->open(path, std::ios::out | std::ios::trunc);
    }

    Logger& Logger::info(const std::string& message, const std::source_location& location) {
        return log(message, Color::GREEN, location);
    }

    Logger& Logger::warning(const std::string& message, const std::source_location& location) {
        return log(message, Color::YELLOW, location);
    }

    Logger& Logger::error(const std::string& message, const std::source_location& location) {
        return log(message, Color::RED, location);
    }

    Logger& Logger::debug(const std::string& message, const std::source_location& location) {
        return log(message, Color::CYAN, location);
    }

    Logger& Logger::log(const std::string& message, const Color color, const std::source_location& location) {
        const time_t now = time(nullptr);
        char timeBuf[20];
        strftime(timeBuf, sizeof(timeBuf), "%Y-%m-%d %H:%M:%S", localtime(&now));

        #ifndef NDEBUG
            setConsoleColor(color);
            std::cout 
                    << "(" << name << ") "
                    << "[" << Format::split(location.file_name(), "/").back()
                    << ":" << location.line() << "] "
                    << "[" << std::string(timeBuf) << "] "
                    << message << std::endl;

            setConsoleColor(Color::RESET);
        #endif

        if (showLocation)
            *logFile << "[" << Format::split(location.file_name(), "\\/").back()
            << ":" << location.line() << "] ";


        *logFile << "(" << name << ") "
        << "[" << std::string(timeBuf) << "] "
        << message << "\n";

        return *this;
    }
}

CarbonLab::Logger& operator<<(CarbonLab::Logger& logger, const std::string& message) {
    return logger.log(message);
}