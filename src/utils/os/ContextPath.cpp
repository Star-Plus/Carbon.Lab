#include "ContextPath.h"

#ifdef _WIN32
    #include <windows.h>
#elif defined(__APPLE__)
    #include <mach-o/dyld.h>
#else
    #include <unistd.h>
    #include <limits.h>
#endif

namespace CarbonLab::ContextPath {

    fpath getExecutablePath() {
        #ifdef _WIN32
            char path[MAX_PATH];
            GetModuleFileNameA(NULL, path, MAX_PATH);
            return strdup(path);
        #elif defined(__linux__)
            char path[PATH_MAX];
            ssize_t len = readlink("/proc/self/exe", path, sizeof(path) - 1);
            if (len != -1) {
                path[len] = '\0';
                return path;
            }
            throw std::runtime_error("Couldn't fetch executable file path");
        #elif defined(__APPLE__)
            char path[PATH_MAX];
            uint32_t size = sizeof(path);
            if (_NSGetExecutablePath(path, &size) == 0) {
                return strdup(path);
            }
            return nullptr;
        #else
            return nullptr; // Unsupported platform
        #endif
    }

}