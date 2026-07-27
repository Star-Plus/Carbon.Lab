#pragma once

#include "core/VirtualSystem.h"
#include "models/DockerApp.h"
#include "utils/logging/Logger.h"
#include <map>
#include <memory>
#include <queue>
#include <vector>

#include "CarbonExport.h"

namespace CarbonLab {

    class CARBON_EXPORT DockerComposer : public VirtualSystem<DockerComposer> {
    public:
        DockerComposer();
        ~DockerComposer();

        DockerComposer(const std::vector<DockerAppRequest>& apps);
        void commit();

        str connect(const str& name, const str& port="");

        void operator += (DockerComposer& other);

        std::vector<str> getLiveApps() { 
            std::vector<str> names;
            for (auto& app : liveApps) {
                names.push_back(app.first);
            }
            return names;
        }

    private:
        Logger logger{"DockerComposer"};
        std::map<str, std::shared_ptr<DockerApp>> liveApps;
        std::queue<std::shared_ptr<DockerAppRequest>> requests;

        bool dependencyCheck();
        void wakeUp(const DockerAppRequest& req);
        void tearDown(const str& name);
    };
}