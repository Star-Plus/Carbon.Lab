#include <iostream>

#ifdef _WIN32
    #include <windows.h>
    #include <shlobj.h>
#else
    #include <cstdlib>
    #include <pwd.h>
    #include <unistd.h>
    #include <sys/types.h>
#endif

#include <utility>
#include "Logger.h"

#include <filesystem>
#include "Format.h"


namespace CarbonLab {

    Logger::Logger()
    {
        const std::string APP_NAME = "SplitVCS";
        std::filesystem::path appDir;

    #ifdef _WIN32
        char path[MAX_PATH];
        if (!SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, 0, path))) {
            throw std::runtime_error("Failed to get AppData directory");
        }

        appDir = std::filesystem::path(path) / APP_NAME;
    #elif __APPLE__
        const char* homeDir = getenv("HOME");
        if (!homeDir) {
            throw std::runtime_error("Failed to get home directory");
        }
        
        appDir = std::filesystem::path(homeDir) / "Library" / "Application Support" / APP_NAME;
    #else // Linux and other Unix-like systems
        const char* xdgData = getenv("XDG_DATA_HOME");
        if (xdgData && *xdgData) {
            appDir = std::filesystem::path(xdgData) / APP_NAME;
        }
        
        const char* homeDir = getenv("HOME");
        if (!homeDir) {
            homeDir = getpwuid(getuid())->pw_dir;
        }
        appDir = std::filesystem::path(homeDir) / ".local" / "share" / APP_NAME;
    #endif

        std::filesystem::create_directories(appDir/"logs");
        
        logFile = std::make_shared<std::ofstream>();
        logFile->open(appDir/"logs/ALL.log", std::ios::out | std::ios::app);
    }
    
    Logger::Logger(std::string name) : name(std::move(name))
    {
        const std::string APP_NAME = "CarbonLab";
        std::filesystem::path appDir;

    #ifdef _WIN32
        char path[MAX_PATH];
        if (!SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, 0, path))) {
            throw std::runtime_error("Failed to get AppData directory");
        }

        appDir = std::filesystem::path(path) / APP_NAME;
    #elif __APPLE__
        const char* homeDir = getenv("HOME");
        if (!homeDir) {
            throw std::runtime_error("Failed to get home directory");
        }
        
        appDir = std::filesystem::path(homeDir) / "Library" / "Application Support" / APP_NAME;
    #else // Linux and other Unix-like systems
        const char* xdgData = getenv("XDG_DATA_HOME");
        if (xdgData && *xdgData) {
            appDir = std::filesystem::path(xdgData) / APP_NAME;
        }
        
        const char* homeDir = getenv("HOME");
        if (!homeDir) {
            homeDir = getpwuid(getuid())->pw_dir;
        }
        appDir = std::filesystem::path(homeDir) / ".local" / "share" / APP_NAME;
    #endif

        std::filesystem::create_directories(appDir/"logs");
        const auto logFileName = this->name.empty() ? "ALL.log" : this->name + ".log";

        logFile = std::make_shared<std::ofstream>();
        logFile->open(appDir / "logs" / logFileName, std::ios::out | std::ios::trunc);
    }

    void Logger::info(const std::string& message, const std::source_location& location) const {
        log(message, Color::GREEN, location);
    }

    void Logger::warning(const std::string& message, const std::source_location& location) const {
        log(message, Color::YELLOW, location);
    }

    void Logger::error(const std::string& message, const std::source_location& location) const {
        log(message, Color::RED, location);
    }

    void Logger::debug(const std::string& message, const std::source_location& location) const {
        log(message, Color::CYAN, location);
    }


    void Logger::setCheckPoint(const std::string& message)
    {
        checkPointTime = std::chrono::steady_clock::now();
        info("Set an checkout point " + message, std::source_location::current());
    }

    void Logger::log(const std::string& message, const Color color, const std::source_location& location) const {
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

        *logFile << "[" << Format::split(location.file_name(), "\\/").back()
        << ":" << location.line() << "] "
        << "(" << name << ") "
        << "[" << std::string(timeBuf) << "] "
        << message << "\n";
    }

}