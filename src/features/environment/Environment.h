#pragma once

#include "core.h"
#include <stdlib.h>

namespace CarbonLab {

    class Environment {
    public:
        static void set(const str& key, const str& value) {
            #ifdef _WIN32
            _putenv_s(key.c_str(), value.c_str());
            #else
            setenv(key.c_str(), value.c_str(), 1);
            #endif
        }

        static str get(const str& key) {
            const char* value = getenv(key.c_str());
            return value ? value : "";
        }

        static void remove(const str& key) {
            #ifdef _WIN32
            _putenv_s(key.c_str(), "");
            #else
            unsetenv(key.c_str());
            #endif
        }
    };

}