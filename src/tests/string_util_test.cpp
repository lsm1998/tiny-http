//
// Created by Administrator on 2023/12/10.
//

#include <gtest/gtest.h>
#include "string_util.h"

TEST(StringUtilTest_split, PositiveInput)
{
    std::string str = "l 2l l2 l2";

    auto l1 = split(str, " ", 1);
    EXPECT_EQ(l1.size(), 1);
    auto l2 = split(str, " ", 2);
    EXPECT_EQ(l2.size(), 2);
    auto l3 = split(str, " ", 3);
    EXPECT_EQ(l3.size(), 3);
    auto l4 = split(str, " ", 4);
    EXPECT_EQ(l4.size(), 4);
    auto l5 = split(str, " ", 5);
    EXPECT_EQ(l5.size(), 4);
    auto l6 = split(str, " ");
    EXPECT_EQ(l6.size(), 4);
}

TEST(StringUtilTest_toString, PositiveInput)
{
    std::string str = "hello";
    EXPECT_EQ(toString(str), "hello");

    std::vector<std::string> list = {"1", "2", "3"};
    EXPECT_EQ(toString(list), "[1,2,3]");
}

//int main(int argc, char **argv)
//{
//    ::testing::InitGoogleTest(&argc, argv);
//    return RUN_ALL_TESTS();
//}