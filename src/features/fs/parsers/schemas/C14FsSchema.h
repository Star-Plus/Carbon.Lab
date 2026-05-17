#pragma once

#include "core.h"
#include <vector>
#include "yaml-cpp/node/node.h"

namespace CarbonLab {

    struct C14FsSchema {
        struct File {
            str name;
            str vpath;
            str seedType;
            str seed;
            unsigned int seedLength = 30;
            bool preRunWrite = false;
        };

        std::vector<File> files;
    };

}



namespace YAML {
    template <>
    struct convert<CarbonLab::C14FsSchema> {
        static bool decode(const Node& node, CarbonLab::C14FsSchema& rhs) {
            rhs.files = node["files"].as<std::vector<CarbonLab::C14FsSchema::File>>();
            return true;
        }
    };

    template <>
    struct convert<CarbonLab::C14FsSchema::File> {
        static bool decode(const Node& node, CarbonLab::C14FsSchema::File& rhs) {

            if (node.IsNull()) return false;
            if (!node.IsMap()) return false;

            if (!node["name"].IsDefined()) return false;
            if (!node["seed_type"].IsDefined()) return false;

            rhs.name = node["name"].as<str>();
            rhs.seedType = node["seed_type"].as<str>();

            if (node["vpath"].IsDefined()) rhs.vpath = node["vpath"].as<str>();
            else rhs.vpath = rhs.name;

            if (node["pre_run_write"].IsDefined()) rhs.preRunWrite = node["pre_run_write"].as<bool>();

            if (rhs.seedType == "random") {
                if (node["seed_length"].IsDefined()) rhs.seedLength = node["seed_length"].as<unsigned int>();
                else return false;
            }
            else {
                if (node["seed"].IsDefined()) rhs.seed = node["seed"].as<str>();
                else return false;
            }

            return true;
        }
    };
}