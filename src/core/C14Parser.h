#pragma once

#include <yaml-cpp/yaml.h>

#include "CarbonExport.h"

namespace CarbonLab {

    class CARBON_EXPORT IC14Parser {
    public:
        virtual ~IC14Parser() = default;
    };

    template<class T>
    class C14Parser : public IC14Parser {
    public:
        virtual std::unique_ptr<T> parse(const YAML::Node& node) = 0;
    };
}