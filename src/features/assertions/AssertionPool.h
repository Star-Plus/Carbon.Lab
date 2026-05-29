#pragma once

#include "AssertFailChannel.h"
#include "core.h"
#include <string>

namespace CarbonLab {

    #define ASSERT_INVOKE(descPrefix, pass) { \
        if (!pass) {\
            failChannel->push({suiteName, testName, descPrefix + std::to_string(expected), std::to_string(actual)});\
        }\
        return pass;\
    }

    class AssertionPool {
    public:
        AssertionPool(str testName="All", str suiteName="All") : suiteName(suiteName), testName(testName) {}

        template <typename T>
        bool is(T expected, T actual) const { ASSERT_INVOKE("", expected == actual) }

        template <typename T>
        bool isNot(T expected, T actual) const { ASSERT_INVOKE("Not ", expected != actual) }

        template <typename T>
        bool isLess(T expected, T actual) const {  ASSERT_INVOKE("Less than ", expected < actual) }

        template <typename T>
        void isGreater(T expected, T actual) const { ASSERT_INVOKE("Greater than ", expected > actual) }

        template <typename T>
        void isLessOrEqual(T expected, T actual) const { ASSERT_INVOKE("Less than or equal to ", expected <= actual) }

        template <typename T>
        void isGreaterOrEqual(T expected, T actual) const { ASSERT_INVOKE("Greater than or equal to ", expected >= actual) }

        template <typename T>
        void isBetween(T expected, T min, T max) const { isLessOrEqual(expected, max) && isGreaterOrEqual(expected, min); }

        template <typename T>
        void isNotBetween(T expected, T min, T max) const { !isBetween(expected, min, max); }

    private:
        str suiteName;
        str testName;

        AssertFailChannel* failChannel;
    };

}