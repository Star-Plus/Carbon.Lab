#pragma once

#include "core.h"
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid.hpp>

namespace CarbonLab::UUID {

    str generateUUID() {
        boost::uuids::random_generator gen;
        boost::uuids::uuid uuid = gen();
        return uuid.data;
    }
    
}