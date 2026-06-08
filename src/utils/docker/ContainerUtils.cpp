#include "ContainerUtils.h"
#include <string>
#include "utils/logging/Logger.h"
#include "utils/os/Shell.h"

namespace CarbonLab::Docker {

    std::vector<str> split(const str& s, char delimiter) {
        std::vector<str> tokens;
        std::string token;
        std::istringstream tokenStream(s);
        while (std::getline(tokenStream, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }

    std::map<int, int> getMappedHostPorts(const str& containerId) {
        Logger logger("ContainerUtils");

        str cmd = "docker port " + containerId;

        try {
            str output = OS::Shell::exec(cmd.c_str());

            if (output == "") {
                return {};
            }

            logger.debug("Mapped ports: " + output);

            std::map<int, int> ports;
            for (const auto& line : split(output, '\n')) {
                if (line.empty()) continue;

                auto arrowPos = line.find(" -> ");
                if (arrowPos == str::npos) continue;

                str containerPart = line.substr(0, arrowPos);
                str hostPart      = line.substr(arrowPos + 4);

                auto slashPos = containerPart.find('/');
                auto colonPos = hostPart.rfind(':');
                if (slashPos == str::npos || colonPos == str::npos) continue;

                int containerPort = std::stoi(containerPart.substr(0, slashPos));
                int hostPort      = std::stoi(hostPart.substr(colonPos + 1));

                ports[containerPort] = hostPort;
            }
            return ports;
        }
        catch (std::exception& e) {
            logger.log("Failed to get mapped port: " + std::string(e.what()), Color::RED);
            return {};
        }
    }

    void launchDocker() {
        try {
            int result = system("docker info > /dev/null 2>&1");
    
            if (result != 0) {
                #ifdef _WIN32
                    system("docker desktop start");
                #elif defined(__linux__)
                    system("sudo systemctl start docker");
                #endif
            }
        }
        catch (std::exception& e) {
            Logger("ContainerUtils").log("Failed to launch docker: " + std::string(e.what()), Color::RED);
            throw e;
        }
    }
}