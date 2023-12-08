#include <gtest/gtest.h>

#include <sstream>
#include <chrono>
#include <thread>

#include "Timers.h"

using namespace std;

TEST(Timers, Timer)
{
    cout << chrono::high_resolution_clock::period::den << endl;

    double result;

    {
        stringbuf buffer;
        iostream out(&buffer);
        utility::timers::Timer timer(out, utility::timers::OutputTimeType::seconds);

        this_thread::sleep_for(1s);

        out >> result;
    }

    ASSERT_TRUE(result >= 1.0) << result;

    {
        stringbuf buffer;
        iostream out(&buffer);
        utility::timers::Timer timer(out, utility::timers::OutputTimeType::milliseconds);

        this_thread::sleep_for(100ms);

        out >> result;
    }

    ASSERT_TRUE(result >= 0.1) << result;
}

TEST(Timers, AccumulatingTimer)
{
    cout << chrono::high_resolution_clock::period::den << endl;

    double result = 0.0;

    {
        utility::timers::AccumulatingTimer timer(result, utility::timers::OutputTimeType::seconds);

        this_thread::sleep_for(1s);
    }

    ASSERT_TRUE(result >= 1.0) << result;

    {
        utility::timers::AccumulatingTimer timer(result, utility::timers::OutputTimeType::seconds);

        this_thread::sleep_for(1s);
    }

    ASSERT_TRUE(result >= 2.0) << result;

    {
        utility::timers::AccumulatingTimer timer(result, utility::timers::OutputTimeType::seconds);

        this_thread::sleep_for(1s);
    }

    ASSERT_TRUE(result >= 3.0) << result;
}
