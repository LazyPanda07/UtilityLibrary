#include <gtest/gtest.h>

#include <sstream>
#include <chrono>
#include <thread>

#include "Timers.h"

using namespace std;

TEST(Timers, Timer)
{
    double result;

    {
        stringbuf buffer;
        iostream out(&buffer);
        utility::timers::Timer timer(out, utility::timers::OutputTimeType::seconds);

        this_thread::sleep_for(1s);

        out >> result;
    }

    ASSERT_TRUE(result >= 1.0);
}

TEST(Timers, AccumulatingTimer)
{
    double result = 0.0;

    {
        utility::timers::AccumulatingTimer timer(result, utility::timers::OutputTimeType::seconds);

        this_thread::sleep_for(1s);
    }

    ASSERT_TRUE(result >= 1.0);

    {
        utility::timers::AccumulatingTimer timer(result, utility::timers::OutputTimeType::seconds);

        this_thread::sleep_for(1s);
    }

    ASSERT_TRUE(result >= 2.0);

    {
        utility::timers::AccumulatingTimer timer(result, utility::timers::OutputTimeType::seconds);

        this_thread::sleep_for(1s);
    }

    ASSERT_TRUE(result >= 3.0);
}
