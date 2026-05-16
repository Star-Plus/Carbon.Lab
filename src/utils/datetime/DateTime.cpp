//
// Created by Ahmed Mustafa on 3/22/2026.
//

#include "DateTime.h"

namespace CarbonLab
{
    DateTime::DateTime()
    {
        rawTime = time(nullptr);
    }

    DateTime::DateTime(const str& strDate, const str& format)
    {
        std::tm tm = {};
        std::stringstream ss(strDate);

        ss >> std::get_time(&tm, format.c_str());

        if (ss.fail())
        {
            throw std::invalid_argument("Invalid Date");
        }

        rawTime = std::mktime(&tm);
    }

    str DateTime::toStr(const str& format) const
    {
        char buf[64];
        strftime(buf, sizeof(buf), format.c_str(), localtime(&rawTime));
        return std::string(buf);
    }

    bool DateTime::operator==(const DateTime& dateTime) const
    {
        return rawTime == dateTime.rawTime;
    }

    bool DateTime::operator<(const DateTime& dateTime) const
    {
        return rawTime < dateTime.rawTime;
    }

    void operator<<(std::ostream& out, const DateTime& dateTime)
    {
        out << dateTime.toStr();
    }

    str operator+(const str& prefix, const DateTime& dateTime)
    {
        return prefix + dateTime.toStr();
    }
} // Split