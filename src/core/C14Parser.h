#pragma once

#include <yaml-cpp/yaml.h>

namespace CarbonLab {

    class IC14Parser {
    public:
        virtual ~IC14Parser() = default;
    };

    template<class T>
    class C14Parser : public IC14Parser {
    public:
        virtual std::unique_ptr<T> parse(const YAML::Node& node) = 0;
    };
}