#include "Color.h"
#include <iostream>

namespace CarbonLab {
    void setConsoleColor(Color color) {
        static std::string colorCode;
        switch (color) {
            case Color::RED:
                colorCode = "\033[31m";
                break;
            case Color::GREEN:
                colorCode = "\033[32m";
                break;
            case Color::BLUE:
                colorCode = "\033[34m";
                break;
            case Color::YELLOW:
                colorCode = "\033[33m";
                break;
            case Color::CYAN:
                colorCode = "\033[36m";
                break;
            case Color::MAGENTA:
                colorCode = "\033[35m";
                break;
            case Color::WHITE:
                colorCode = "\033[37m";
                break;
            case Color::BLACK:
                colorCode = "\033[30m";
                break;
            case Color::RESET:
                colorCode = "\033[0m";
                break;
        }

        std::cerr << colorCode;
        
    }
}