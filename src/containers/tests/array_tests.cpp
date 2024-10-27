#include <gtest/gtest.h>

#include <array>

#include "../array/s21_array.h"

class ArrayTests : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(ArrayTests, DefaultConstructor) {
  s21::Array<int, 5> arr{};
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(arr[i], 0);
  }
}

TEST_F(ArrayTests, InitializerListConstructor) {
  s21::Array<int, 5> arr = {1, 2, 3, 4, 5};
  EXPECT_EQ(arr[0], 1);
  EXPECT_EQ(arr[1], 2);
  EXPECT_EQ(arr[2], 3);
  EXPECT_EQ(arr[3], 4);
  EXPECT_EQ(arr[4], 5);
}

TEST_F(ArrayTests, CopyConstructor) {
  s21::Array<int, 5> arr1 = {1, 2, 3, 4, 5};
  s21::Array<int, 5> arr2(arr1);
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(arr1[i], arr2[i]);
  }
}

TEST_F(ArrayTests, MoveConstructor) {
  s21::Array<int, 5> arr1 = {1, 2, 3, 4, 5};
  s21::Array<int, 5> arr2(std::move(arr1));
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(arr2[i], i + 1);
  }
}

TEST_F(ArrayTests, MoveAssignmentOperator) {
  s21::Array<int, 5> arr1 = {1, 2, 3, 4, 5};
  s21::Array<int, 5> arr2{};
  arr2 = std::move(arr1);
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(arr2[i], i + 1);
  }
}

TEST_F(ArrayTests, CopyAssignmentOperator) {
  s21::Array<int, 5> arr1 = {1, 2, 3, 4, 5};
  s21::Array<int, 5> arr2{};
  arr2 = arr1;
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(arr1[i], arr2[i]);
  }
}

TEST_F(ArrayTests, ValidAtAccess) {
  s21::Array<int, 5> arr1 = {1, 2, 3, 4, 5};
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(arr1.at(i), i + 1);
  }
}

TEST_F(ArrayTests, ValidConstAtAccess) {
  const s21::Array<int, 5> arr1 = {1, 2, 3, 4, 5};
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(arr1.at(i), i + 1);
  }
}

TEST_F(ArrayTests, OutOfRangeAtAccess) {
  s21::Array<int, 5> arr1 = {1, 2, 3, 4, 5};
  EXPECT_THROW(arr1.at(5), std::out_of_range);
  EXPECT_THROW(arr1.at(-1), std::out_of_range);
  s21::Array<int, 5> arr2{};
  EXPECT_THROW(arr2.at(20), std::out_of_range);
}

TEST_F(ArrayTests, OutOfRangeConstAtAccess) {
  const s21::Array<int, 5> arr1 = {1, 2, 3, 4, 5};
  EXPECT_THROW(arr1.at(5), std::out_of_range);
  EXPECT_THROW(arr1.at(-1), std::out_of_range);
  const s21::Array<int, 5> arr2{};
  EXPECT_THROW(arr2.at(20), std::out_of_range);
}

TEST_F(ArrayTests, SquareBracketsOperator) {
  s21::Array<int, 5> arr1 = {1, 2, 3, 4, 5};
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(arr1[i], i + 1);
  }
}

TEST_F(ArrayTests, ConstSquareBracketsOperator) {
  const s21::Array<int, 5> arr1 = {1, 2, 3, 4, 5};
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(arr1[i], i + 1);
  }
}

TEST_F(ArrayTests, Front) {
  s21::Array<int, 5> arr1 = {1, 2, 3, 4, 5};
  EXPECT_EQ(arr1.front(), arr1[0]);
}

TEST_F(ArrayTests, ConstFront) {
  const s21::Array<int, 5> arr1 = {1, 2, 3, 4, 5};
  EXPECT_EQ(arr1.front(), arr1[0]);
}

TEST_F(ArrayTests, Back) {
  s21::Array<int, 5> arr1 = {1, 2, 3, 4, 5};
  EXPECT_EQ(arr1.back(), arr1[4]);
}

TEST_F(ArrayTests, ConstBack) {
  const s21::Array<int, 5> arr1 = {1, 2, 3, 4, 5};
  EXPECT_EQ(arr1.back(), arr1[4]);
}

TEST_F(ArrayTests, IteratorData) {
  s21::Array<int, 5> arr1 = {1, 2, 3, 4, 5};
  auto it = arr1.data();
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(*it++, arr1[i]);
  }
}

TEST_F(ArrayTests, ConstIteratorData) {
  const s21::Array<int, 5> arr1 = {1, 2, 3, 4, 5};
  auto it = arr1.data();
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(*it++, arr1[i]);
  }
}

TEST_F(ArrayTests, IteratorBegin) {
  s21::Array<int, 5> arr1 = {1, 2, 3, 4, 5};
  auto it = arr1.begin();
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(*it++, arr1[i]);
  }
}

TEST_F(ArrayTests, ConstIteratorBegin) {
  const s21::Array<int, 5> arr1 = {1, 2, 3, 4, 5};
  auto it = arr1.begin();
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(*it++, arr1[i]);
  }
}

TEST_F(ArrayTests, IteratorCBegin) {
  s21::Array<int, 5> arr1 = {1, 2, 3, 4, 5};
  auto it = arr1.cbegin();
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(*it++, arr1[i]);
  }
}

TEST_F(ArrayTests, IteratorEnd) {
  s21::Array<int, 5> arr1 = {1, 2, 3, 4, 5};
  auto it = arr1.end();
  EXPECT_EQ(it, arr1.data() + arr1.size());
  for (int i = 5; i > 0; --i) {
    --it;
    EXPECT_EQ(*it, arr1[i - 1]);
  }
}

TEST_F(ArrayTests, ConstIteratorEnd) {
  const s21::Array<int, 5> arr1 = {1, 2, 3, 4, 5};
  auto it = arr1.end();
  EXPECT_EQ(it, arr1.data() + arr1.size());
  for (int i = 5; i > 0; --i) {
    --it;
    EXPECT_EQ(*it, arr1[i - 1]);
  }
}

TEST_F(ArrayTests, IteratorCEnd) {
  s21::Array<int, 5> arr1 = {1, 2, 3, 4, 5};
  auto it = arr1.cend();
  EXPECT_EQ(it, arr1.data() + arr1.size());
  for (int i = 5; i > 0; --i) {
    --it;
    EXPECT_EQ(*it, arr1[i - 1]);
  }
}

TEST_F(ArrayTests, Empty) {
  s21::Array<int, 5> arr1 = {1, 2, 3, 4, 5};
  EXPECT_FALSE(arr1.empty());
}

TEST_F(ArrayTests, SizeMaxSize) {
  s21::Array<char, 5> arr1{};
  EXPECT_EQ(static_cast<int>(arr1.size()), 5);
  EXPECT_EQ(static_cast<int>(arr1.max_size()), 5);
}

TEST_F(ArrayTests, Swap) {
  s21::Array<char, 3> arr = {'G', 'f', 'G'};
  s21::Array<char, 3> arr1 = {'M', 'M', 'P'};
  s21::Array<char, 3> expected_arr = {'M', 'M', 'P'};
  s21::Array<char, 3> expected_arr1 = {'G', 'f', 'G'};
  arr.swap(arr1);
  for (int i = 0; i < 3; ++i) {
    EXPECT_EQ(arr[i], expected_arr[i]);
    EXPECT_EQ(arr1[i], expected_arr1[i]);
  }
}

TEST_F(ArrayTests, Fill) {
  s21::Array<int, 5> arr{};
  arr.fill(100500);
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(arr[i], 100500);
  }
}
