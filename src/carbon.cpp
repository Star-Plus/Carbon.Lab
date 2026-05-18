#include "carbon.h"
#include "components/ConfigurationParser.h"

Carbon Carbon::init(const fpath& c14Path) {

    if (!std::filesystem::exists(c14Path)) {
        throw std::runtime_error("C14 file not found");
    }

    CarbonLab::ConfigurationParser parser(c14Path);
    auto carbon = parser.load();

    if (carbon.fs)
        carbon.fs->commit();

    return carbon;
}