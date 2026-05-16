#include "utils/generators/StringSeeds.h"
#include <random>

namespace CarbonLab::Seeds {

    str generateRandomString(size_t length) {
        const str characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_int_distribution<> distribution(0, characters.size() - 1);

        str randomString;
        for (size_t i = 0; i < length; ++i) {
            randomString += characters[distribution(generator)];
        }

        return randomString;
    }

}