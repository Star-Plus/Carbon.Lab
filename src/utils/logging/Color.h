#pragma once

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

    void setConsoleColor(Color color);
}