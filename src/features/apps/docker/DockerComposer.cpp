#include "DockerComposer.h"
#include "utils/os/3rdAppInfo.h"
#include <algorithm>
#include <string>
#include "utils/docker/ContainerUtils.h"
#include "utils/os/Shell.h"
#include <thread>

namespace CarbonLab {

    bool DockerComposer::dependencyCheck() {
        return OS::isAppReachable("docker");
    }

    DockerComposer::DockerComposer() {
        if (!dependencyCheck()) {
            throw std::runtime_error("Docker is not installed or not reachable Please make sure Docker is available.");
        }
    }

    DockerComposer::DockerComposer(const std::vector<DockerAppRequest>& apps) {
        if (!dependencyCheck()) {
            throw std::runtime_error("Docker is not installed or not reachable Please make sure Docker is available.");
        }

        for (auto& app : apps) {
            requests.push(std::make_shared<DockerAppRequest>(app));
        }
    }

    DockerComposer::~DockerComposer() {
        for (auto& app : liveApps) {
            tearDown(app.first);
        }
    }

    void DockerComposer::commit() {
        while (requests.size() > 0) {
            wakeUp(*requests.front());
            requests.pop();
        }
    }

    str DockerComposer::connect(const str& name, const str& port) {
        if (liveApps.find(name) == liveApps.end()) {
            throw std::runtime_error("App not found: " + name);
        }
        
        if (port == "") {
            return name;
        }

        if (liveApps[name]->ports.size() == 0) {
            throw std::runtime_error("App not running: " + name);
        }

        if (liveApps[name]->ports.find(port) == liveApps[name]->ports.end()) {
            throw std::runtime_error("Port not found: " + port);
        }

        return name + ":" + std::to_string(liveApps[name]->ports[port]);
    }

    void DockerComposer::wakeUp(const DockerAppRequest& req) {
        if (liveApps.find(req.name) != liveApps.end()) {
            return;
        }

        logger.debug("Running app " + req.name + "...");

        str randomPortMappingArgument = "";
        for (auto& port : req.ports) {
            randomPortMappingArgument += "-p " + std::to_string(port.second) + " ";
        }

        int result = system(("docker run -d " + randomPortMappingArgument + "--name " + req.name + " " + req.image + " sleep " + std::to_string(req.minLifetime)).c_str());

        if (result != 0) {
            throw std::runtime_error("Failed to run app: " + req.name);
        }

        std::map<int, int> containerPorts;
        for (int i = 0; i < 10; i++) {
            containerPorts = CarbonLab::Docker::getMappedHostPorts(req.name);
            if (!containerPorts.empty()) break;
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }

        auto containerId = CarbonLab::OS::Shell::exec(("docker ps -f name=" + req.name + " -q").c_str());
        logger.debug("Container ID: " + containerId);

        std::map<str, int> ports;
        for (auto& port : req.ports) {
            ports.insert({port.first, containerPorts[port.second]});
        }

        if (!req.initFiles.empty()) {
            system(("docker exec " + containerId + " mkdir -p /init").c_str());

            for (auto& file : req.initFiles) {
                str path = file.string();
                if (path.rfind("\\\\?\\", 0) == 0) {
                    path = path.substr(4);
                }
                std::replace(path.begin(), path.end(), '\\', '/');

                system(("docker cp \"" + path + "\" " + containerId + ":/init/").c_str());
            }
        }

        if (!req.initCommand.empty()) {
            system(("docker exec " + containerId + " sh -c \"" + req.initCommand + "\"").c_str());
        }

        liveApps[req.name] = std::make_shared<DockerApp>(ports, req.env, req.name, req.image, containerId);
    }

    void DockerComposer::tearDown(const str& name) {
        system(("docker rm -f " + name).c_str());
    }

    void DockerComposer::operator += (DockerComposer& other) {
        for (auto& app : other.liveApps) {
            liveApps[app.first] = app.second;
        }

        while (other.requests.size() > 0) {
            requests.push(other.requests.front());
            other.requests.pop();
        }

        other.liveApps.clear();
    }
}