#pragma once

#include "core.h"

namespace CarbonLab {

    #define ASSERT(exp, act, res) { if (!res) {} };

    class Assertion {
    public:
        Assertion(str suiteName, str testName) : suiteName(suiteName), testName(testName) {}

        template <typename T>
        void is(T expected, T actual) const { return expected == actual; }

        template <typename T>
        void isNot(T expected, T actual) const { return expected != actual; }

        template <typename T>
        void isLess(T expected, T actual) const { return expected < actual; }

        template <typename T>
        void isGreater(T expected, T actual) const { return expected > actual; }

        template <typename T>
        void isLessOrEqual(T expected, T actual) const { return expected <= actual; }

        template <typename T>
        void isGreaterOrEqual(T expected, T actual) const { return expected >= actual; }

        template <typename T>
        void isBetween(T expected, T min, T max) const { return expected >= min && expected <= max; }

        template <typename T>
        void isNotBetween(T expected, T min, T max) const { return expected < min || expected > max; }

    private:
        str suiteName;
        str testName;
    };

}