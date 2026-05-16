#pragma once

#include "core.h"
#include <uuid.h>

namespace CarbonLab::UUID {

    inline str generateUUID() {
        std::random_device rd;
        auto seed_data = std::array<int, std::mt19937::state_size>{};
        std::generate(seed_data.begin(), seed_data.end(), std::ref(rd));
        std::seed_seq seq(seed_data.begin(), seed_data.end());
        std::mt19937 engine(seq);

        uuids::uuid_random_generator gen{engine};
        return uuids::to_string(gen());
    }
    
}