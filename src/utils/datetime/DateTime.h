//
// Created by Ahmed Mustafa on 3/22/2026.
//

#ifndef SPLITVCS_DATETIME_H
#define SPLITVCS_DATETIME_H

#include "core.h"
#include <ctime>

namespace CarbonLab
{
    class DateTime
    {
        time_t rawTime = 0;
    public:
        DateTime();
        DateTime(const str& strDate, const str& format = "%Y-%m-%d %H:%M:%S");

        str toStr(const str& format = "%Y-%m-%d %H:%M:%S") const;

        bool operator== (const DateTime& dateTime) const;
        bool operator< (const DateTime& dateTime) const;

    };

    void operator<< (std::ostream& out, const DateTime& dateTime);
    str operator+ (const str& prefix, const DateTime& dateTime);
} // Split

#endif //SPLITVCS_DATETIME_H