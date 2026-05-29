#include "Environment.h"

#include <map>
#include <stdlib.h>

namespace CarbonLab {

     void Environment::set(const str& key, const str& value) {
        #ifdef _WIN32
        _putenv_s(key.c_str(), value.c_str());
        #else
        setenv(key.c_str(), value.c_str(), 1);
        #endif
    }

    str Environment::get(const str& key) {
        const char* value = getenv(key.c_str());
        return value ? value : "";
    }

    void Environment::remove(const str& key) {
        #ifdef _WIN32
        _putenv_s(key.c_str(), "");
        #else
        unsetenv(key.c_str());
        #endif
    }

    std::map<str, str> Environment::list() {
        std::map<str, str> result;
        char** env = environ;
        while (*env) {
            str key = *env++;
            str value = *env++;
            result[key] = value;
        }
        return result;
    }

    void Environment::operator += (Environment& other) {
        for (const auto& [key, value] : other.list()) {
            set(key, value);
        }
    }
}