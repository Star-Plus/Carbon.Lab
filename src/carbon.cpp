#include "carbon.h"
#include "components/ConfigurationParser.h"

Carbon Carbon::init(const fpath& c14Path) {
    CarbonLab::ConfigurationParser parser(c14Path);
    return parser.load();
}