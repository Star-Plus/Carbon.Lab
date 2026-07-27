//
// Created by Ahmed Mustafa on 3/22/2026.
//

#ifndef SPLITVCS_DATETIME_H
#define SPLITVCS_DATETIME_H

#include "core.h"
#include <ctime>
#include "CarbonExport.h"

namespace CarbonLab
{
    class CARBON_EXPORT DateTime
    {
        time_t rawTime = 0;
    public:
        DateTime();
        DateTime(const str& strDate, const str& format = "%Y-%m-%d %H:%M:%S");

        str toStr(const str& format = "%Y-%m-%d %H:%M:%S") const;

        bool operator== (const DateTime& dateTime) const;
        bool operator< (const DateTime& dateTime) const;

    };

    CARBON_EXPORT void operator<< (std::ostream& out, const DateTime& dateTime);
    CARBON_EXPORT str operator+ (const str& prefix, const DateTime& dateTime);
} // Split

#endif //SPLITVCS_DATETIME_H