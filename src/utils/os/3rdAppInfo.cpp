#include "3rdAppInfo.h"

namespace CarbonLab::OS {
    bool isAppReachable(const str& appName) {
        try {
            int result = system(("which " + appName).c_str());
            return result == 0;
        }
        catch (...) {
            return false;
        }
    }
}