/**
*
*/

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using testing::Eq;

namespace {
   class testingClass1 : public testing::Test {
   public:
   };
}// namespace

TEST_F(testingClass1, test1) {
   ASSERT_EQ(1, 1);
}
