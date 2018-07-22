#include <chrono>
#include <iostream>
#include <iterator>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "InitializableArray.hpp"

using namespace arr;
using namespace ::testing;

TEST(InitializableArrayTest, TestInitialization) {
    const int defaultValue = 1;
    const size_t size = 100;

    InitializableArray<std::decay<decltype(defaultValue)>::type> a(size, defaultValue);

    ASSERT_EQ(a.size(), 100);
    ASSERT_THAT(a, Each(defaultValue));
}


TEST(InitializableArrayTest, TestSetPosition) {
    const int defaultValue = 1;
    const size_t size = 100;

    InitializableArray<std::decay<decltype(defaultValue)>::type> a(size, defaultValue);

    const int newValue = 120;
    const size_t newPosition = 50;
    a.set(newPosition, newValue);
    ASSERT_THAT(a, Contains(newValue));
}



TEST(InitializableArrayTest, TestClear) {
    const int defaultValue = 1;
    const size_t size = 100;

    InitializableArray<std::decay<decltype(defaultValue)>::type> a(size, defaultValue);

    const int newValue = 120;
    const size_t newPosition = 50;
    a.set(newPosition, newValue);

    a.clear();
    ASSERT_THAT(a, Each(defaultValue));

    a.set(newPosition, newValue);
    a.clear(newPosition);
    ASSERT_THAT(a, Each(defaultValue));

}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}