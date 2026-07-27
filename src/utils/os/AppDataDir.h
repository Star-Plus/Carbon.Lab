#pragma once

#include <core.h>
#include "CarbonExport.h"

namespace CarbonLab::OS::AppData {
    CARBON_EXPORT [[nodiscard]] fpath GetAppDataDir();
}