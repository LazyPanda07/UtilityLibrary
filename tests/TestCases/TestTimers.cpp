#include <gtest/gtest.h>

#include <sstream>
#include <chrono>
#include <thread>

#include "Timers.h"

using namespace std;

#ifndef NO_TIMERS
TEST(Timers, Timer)
{
    double result;
    stringbuf buffer;
    iostream out(&buffer);

    {
        utility::timers::Timer timer(out, utility::timers::OutputTimeType::milliseconds);

        this_thread::sleep_for(1000ms);
    }

    out >> result;

    ASSERT_TRUE(result >= 1.0);

    {
        utility::timers::Timer timer(out, utility::timers::OutputTimeType::seconds);

        this_thread::sleep_for(1s);
    }

    out >> result;

    ASSERT_TRUE(result >= 1.0);

    {
        utility::timers::Timer timer(out, utility::timers::OutputTimeType::nanoseconds);

        this_thread::sleep_for(1'000'000'000ns);
    }

    out >> result;

    ASSERT_TRUE(result >= 1.0);

    {
        utility::timers::Timer timer(out, utility::timers::OutputTimeType::minutes);

        this_thread::sleep_for(0.1min);
    }

    out >> result;

    ASSERT_TRUE(result >= 6.0);
    
    {
        utility::timers::Timer timer(out, utility::timers::OutputTimeType::hours);

        this_thread::sleep_for(0.001h);
    }

    out >> result;

    ASSERT_TRUE(result >= 3.6);
}

TEST(Timers, AccumulatingTimer)
{
    double result = 0.0;

    {
        utility::timers::AccumulatingTimer timer(result, utility::timers::OutputTimeType::milliseconds);

        this_thread::sleep_for(1000ms);
    }

    ASSERT_TRUE(result >= 1.0);

    {
        utility::timers::AccumulatingTimer timer(result, utility::timers::OutputTimeType::seconds);

        this_thread::sleep_for(1s);
    }

    ASSERT_TRUE(result >= 2.0);

    {
        utility::timers::AccumulatingTimer timer(result, utility::timers::OutputTimeType::nanoseconds);

        this_thread::sleep_for(1'000'000'000ns);
    }

    ASSERT_TRUE(result >= 3.0);

    {
        utility::timers::AccumulatingTimer timer(result, utility::timers::OutputTimeType::minutes);

        this_thread::sleep_for(0.1min);
    }

    ASSERT_TRUE(result >= 9.0);

    {
        utility::timers::AccumulatingTimer timer(result, utility::timers::OutputTimeType::hours);

        this_thread::sleep_for(0.001h);
    }

    ASSERT_TRUE(result >= 12.6);
}
#endif
