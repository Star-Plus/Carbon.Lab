#pragma once

#include "core.h"
#include "features/apps/docker/models/DockerApp.h"
#include "yaml-cpp/node/node.h"
#include <map>

namespace YAML {
    using namespace CarbonLab;

    template<>
    struct convert<CarbonLab::DockerAppRequest> {
        static bool decode(const Node& node, CarbonLab::DockerAppRequest& rhs) {
            if (node["ports"].IsDefined()) 
                rhs.ports = node["ports"].as<std::map<str, int>>();

            if (node["env"].IsDefined())
                rhs.env = node["env"].as<std::map<str, str>>();

            if (node["init_files"].IsDefined()){
                auto initFiles = node["init_files"].as<std::vector<str>>();
                for (auto& file : initFiles) {
                    rhs.initFiles.push_back(file);
                }
            }

            if (node["init_command"].IsDefined())
                rhs.initCommand = node["init_command"].as<str>();
            
            if (node["min_lifetime"].IsDefined())
                rhs.minLifetime = node["min_lifetime"].as<uint64_t>();

            if (!node["image"].IsDefined() || !node["name"].IsDefined())
                return false;

            rhs.image = node["image"].as<str>();
            rhs.name = node["name"].as<str>();
            return true;
        }
    };
}