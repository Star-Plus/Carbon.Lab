#pragma once

#include "core.h"
#include "core/VirtualSystem.h"
#include <map>

namespace CarbonLab {

    class Environment : public VirtualSystem<Environment> {
    public:
        static void set(const str& key, const str& value);
        static str get(const str& key);
        static void remove(const str& key);

        static std::map<str, str> list();

        virtual void operator += (Environment& other);
    };

}