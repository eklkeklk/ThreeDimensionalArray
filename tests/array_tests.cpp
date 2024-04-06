#include <../lib/Three-Dim_Array.h>
#include <gtest/gtest.h>
#include <tuple>

TEST(ConvertingTestsSuite, EqualTest0) {
ThreeDimensionalArray test{9, 10, 7};

test[3][2][1] = 5;
int32_t res = 5;

ASSERT_EQ(static_cast<int>(test[3][2][1]), res);
}

TEST(ConvertingTestsSuite, EqualTest1) {
ThreeDimensionalArray test{4, 5, 7};

test[2][3][1] = 1;
test[3][2][1] = 0;
test[2][1][6] = 2;
test[1][4][5] = 4;
test[0][2][3] = 5;
int32_t res = 1;

ASSERT_EQ(static_cast<int>(test[2][3][1]), res);
}

TEST(ConvertingTestsSuite, EqualTest2) {
ThreeDimensionalArray test{4, 3, 2};

test[0][0][0] = 453;
int32_t res = 0;

ASSERT_EQ(static_cast<int>(test[0][0][1]), res);
}

TEST(ConvertingTestsSuite, EqualTest3) {
ThreeDimensionalArray test{3, 4, 5};

test[1][2][3] = 45;
test[2][2][3] = 34;
int32_t res = 45;

ASSERT_EQ(static_cast<int>(test[1][2][3]), res);
}

TEST(ThreeDimensionalArrayTest, SumTest) {
ThreeDimensionalArray test1{2, 2, 2};

test1[0][0][0] = 121;
test1[0][0][1] = 372;
test1[0][1][0] = 383;
test1[0][1][1] = 632;
test1[1][0][0] = 83;
test1[1][0][1] = 32;
test1[1][1][0] = 11;
test1[1][1][1] = 10;

ThreeDimensionalArray test2{2, 2, 2};

test2[0][0][0] = 1;
test2[0][0][1] = 1;
test2[0][1][0] = 1;
test2[0][1][1] = 1;
test2[1][0][0] = 1;
test2[1][0][1] = 1;
test2[1][1][0] = 1;
test2[1][1][1] = 1;

ThreeDimensionalArray test = test1 + test2;

EXPECT_EQ(static_cast<int>(test[0][0][0]), 122);
EXPECT_EQ(static_cast<int>(test[0][0][1]), 373);
EXPECT_EQ(static_cast<int>(test[0][1][0]), 384);
EXPECT_EQ(static_cast<int>(test[0][1][1]), 633);
EXPECT_EQ(static_cast<int>(test[1][0][0]), 84);
EXPECT_EQ(static_cast<int>(test[1][0][1]), 33);
EXPECT_EQ(static_cast<int>(test[1][1][0]), 12);
EXPECT_EQ(static_cast<int>(test[1][1][1]), 11);
}

TEST(ThreeDimensionalArrayTest, SubTest) {
ThreeDimensionalArray ThreeDimensionalArray1{2, 2, 2};
ThreeDimensionalArray ThreeDimensionalArray2{2, 2, 2};

ThreeDimensionalArray1[1][0][1] = 13;
ThreeDimensionalArray1[1][1][1] = 53;
ThreeDimensionalArray2[1][0][1] = 10;
ThreeDimensionalArray2[1][1][0] = 6;

ThreeDimensionalArray result = ThreeDimensionalArray1 - ThreeDimensionalArray2;

EXPECT_EQ(static_cast<int>(result[1][0][1]), 3);
}

TEST(ThreeDimensionalArrayTest, MultiTest0) {
ThreeDimensionalArray test{3, 3, 3};

test[0][0][0] = 2;
test[1][1][1] = 3;

int multiplier = 4;

ThreeDimensionalArray result = test * multiplier;

EXPECT_EQ(static_cast<int>(result[0][0][0]), 8);
EXPECT_EQ(static_cast<int>(result[1][1][1]), 12);
}

TEST(ThreeDimensionalArrayTest, MultiTest1) {
ThreeDimensionalArray test{2, 2, 2};

test[1][0][1] = 15;
test[1][1][1] = 32;

int multiplier = 5;

ThreeDimensionalArray result = test * multiplier;

EXPECT_EQ(static_cast<int>(result[1][1][1]), 160);
EXPECT_EQ(static_cast<int>(result[1][0][1]), 75);
}

TEST(ThreeDimensionalArrayTest, ZeroMultiplication) {
ThreeDimensionalArray test{2, 2, 2};

test[0][0][0] = 8732;
test[1][1][1] = 1253;

int multiplier = 0;

ThreeDimensionalArray result = test * multiplier;

EXPECT_EQ(static_cast<int>(result[0][0][0]), 0);
EXPECT_EQ(static_cast<int>(result[1][1][1]), 0);
}