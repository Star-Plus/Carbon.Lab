#pragma once

#include "CarbonExport.h"

namespace CarbonLab {
    enum class Color {
        RED,
        GREEN,
        BLUE,
        YELLOW,
        CYAN,
        MAGENTA,
        WHITE,
        BLACK,
        RESET
    };

    CARBON_EXPORT void setConsoleColor(Color color);
}