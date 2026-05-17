#include <string>
#include <vector>

namespace CarbonLab {

    namespace Format {
        inline std::vector<std::string> split(const std::string& input, const std::string& delimiter)
        {
            std::vector<std::string> tokens;
            size_t start = 0;
            size_t end = input.find(delimiter);
            while (end != std::string::npos) {
                tokens.push_back(input.substr(start, end - start));
                start = end + delimiter.length();
                end = input.find(delimiter, start);
            }
            tokens.push_back(input.substr(start));
            return tokens;
        }
    }

}