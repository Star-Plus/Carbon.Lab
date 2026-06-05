#include "Shell.h"
#include <array>
#include <stdexcept>

namespace CarbonLab::OS::Shell {

    str exec(const char* cmd) {
        std::array<char, 128> buffer;
        str result;
        std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
        if (!pipe) {
            throw std::runtime_error("popen() failed!");
        }

        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
            result += buffer.data();
        }

        while (!result.empty() && (result.back() == '\n' || result.back() == '\r')) {
            result.pop_back();
        }

        return result;
    }
}