#include "AppDataDir.h"

#ifdef _WIN32
    #include <windows.h>
    #include <shlobj.h>
#else
    #include <cstdlib>
    #include <pwd.h>
    #include <sys/types.h>
#endif

namespace CarbonLab::OS::AppData {

    const str APP_NAME = "CarbonLab";
    
    fpath GetAppDataDir() {
        fpath appDir;

    #ifdef _WIN32
        char path[MAX_PATH];
        if (!SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, 0, path))) {
            throw std::runtime_error("Failed to get AppData directory");
        }

        appDir = fpath(path) / APP_NAME;
    #elif __APPLE__
        const char* homeDir = getenv("HOME");
        if (!homeDir) {
            throw std::runtime_error("Failed to get home directory");
        }
        
        appDir = fpath(homeDir) / "Library" / "Application Support" / APP_NAME;
    #else // Linux and other Unix-like systems
        const char* xdgData = getenv("XDG_DATA_HOME");
        if (xdgData && *xdgData) {
            appDir = fpath(xdgData) / APP_NAME;
        }
        
        const char* homeDir = getenv("HOME");
        if (!homeDir) {
            homeDir = getpwuid(getuid())->pw_dir;
        }
        appDir = fpath(homeDir) / ".local" / "share" / APP_NAME;
    #endif

        std::filesystem::create_directories(appDir);
        return appDir;
    }
}