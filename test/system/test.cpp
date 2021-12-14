/**
 *
 */

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using testing::Eq;

namespace {
    class testingClass : public testing::Test {
    public:
    };
}// namespace

TEST_F(testingClass, test1) {
    ASSERT_EQ(1, 1);
}
