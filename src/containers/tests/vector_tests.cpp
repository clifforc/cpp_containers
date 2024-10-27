#include <gtest/gtest.h>

#include <iostream>

#include "../vector/s21_vector.h"

class VectorTests : public ::testing::Test {
 protected:
  void SetUp() override {}

  void TearDown() override {}
};

TEST_F(VectorTests, DefaultConstructor) {
  s21::Vector<int> a{1, 2};
  EXPECT_EQ(a[0], 1);
}

TEST_F(VectorTests, DefaultConstructorCopy) {
  s21::Vector<int> a;
  s21::Vector<int> b{1, 2, 3};
  s21::Vector<int> c{1, 2, 3};
  a = b;
  b = c;
  EXPECT_EQ(a[0], 1);
}

TEST_F(VectorTests, paramConstructor) {
  s21::Vector<int> a(5);
  a = {0, 1, 2, 3, 4};
  EXPECT_EQ(a[0], 0);
}

TEST_F(VectorTests, copyConstructor) {
  s21::Vector<int> a{1, 2};
  s21::Vector<int> b = a;
  EXPECT_EQ(b[0], 1);
}

TEST_F(VectorTests, moveConstructor) {
  s21::Vector<int> a{1, 2};
  s21::Vector<int> b(std::move(a));
  EXPECT_EQ(b[0], 1);
}

TEST_F(VectorTests, moveConstructor1) {
  s21::Vector<int> a{1, 2};
  s21::Vector<int> b{1, 2, 3, 4};
  a = (std::move(b));
  EXPECT_EQ(a[2], 3);
}

TEST_F(VectorTests, assignmentMoveOperator) {
  s21::Vector<int> a{1, 2};
  s21::Vector<int> b{1, 2, 3};
  a = std::move(b);
  EXPECT_EQ(a[0], 1);
}

TEST_F(VectorTests, assignmentCopyOperator) {
  s21::Vector<int> a{1, 2};
  s21::Vector<int> b{1, 2, 3};
  a = b;
  EXPECT_EQ(a[0], 1);
}

TEST_F(VectorTests, swap) {
  s21::Vector<int> a{1, 2, 3};
  s21::Vector<int> b{4, 5, 6};
  a.swap(b);
  EXPECT_EQ(a[0], 4);
}

TEST_F(VectorTests, accessor) {
  s21::Vector<int> a{1, 2};
  int x = a.at(0);
  int y = a.front();
  EXPECT_EQ(x, y);
}

TEST_F(VectorTests, constAccessor) {
  const s21::Vector<int> a{1, 2};
  const int x = a.at(0);
  const int y = a.front();
  EXPECT_EQ(x, y);
}

TEST_F(VectorTests, accessorBack) {
  s21::Vector<int> a{1, 2};
  int x = a.at(1);
  int y = a.back();
  EXPECT_EQ(x, y);
}

TEST_F(VectorTests, constAccessorBack) {
  const s21::Vector<int> a{1, 2};
  const int x = a.at(1);
  const int y = a.back();
  EXPECT_EQ(x, y);
}

TEST_F(VectorTests, data) {
  s21::Vector<int> a{1, 2};
  auto it = a.data();
  EXPECT_EQ(*it, 1);
}

TEST_F(VectorTests, constData) {
  const s21::Vector<int> a{1, 2};
  const auto it = a.data();
  EXPECT_EQ(*it, 1);
}

TEST_F(VectorTests, reserve) {
  s21::Vector<int> a{1, 2};
  a.reserve(10);
  EXPECT_EQ(a[3], 0);
}

TEST_F(VectorTests, begin) {
  s21::Vector<int> a{1, 2, 3, 4, 5};
  s21::Vector<int>::iterator it1 = a.begin();
  EXPECT_EQ(*it1, 1);
}

TEST_F(VectorTests, begins) {
  s21::Vector<int> a{1, 2, 3, 4, 5};
  const s21::Vector<int> b{1, 2, 3, 4, 5};
  s21::Vector<int>::iterator it1 = a.begin();
  const int *it2 = a.cbegin();
  const int *it3 = b.begin();
  EXPECT_EQ(*it1, 1);
  EXPECT_EQ(*it2, 1);
  EXPECT_EQ(*it3, 1);
}

TEST_F(VectorTests, ends) {
  s21::Vector<int> a{1, 2, 3, 4, 5};
  const s21::Vector<int> b{1, 2, 3, 4, 5};
  s21::Vector<int>::iterator it1 = a.end() - 1;
  const int *it2 = a.cend() - 1;
  const int *it3 = b.end() - 1;
  EXPECT_EQ(*it1, 5);
  EXPECT_EQ(*it2, 5);
  EXPECT_EQ(*it3, 5);
}

TEST_F(VectorTests, clear) {
  s21::Vector<int> a{1, 2, 3, 4, 5};
  a.clear();
  EXPECT_THROW(a.at(1), std::out_of_range);
}

TEST_F(VectorTests, empty) {
  s21::Vector<int> a{1, 2, 3, 4, 5};
  EXPECT_FALSE(a.empty());
  bool ex_size = a.size();
  EXPECT_TRUE(ex_size);
}

TEST_F(VectorTests, insert) {
  s21::Vector<int> a{1, 2, 3, 4, 5};
  s21::Vector<int>::iterator it1 = a.begin();
  a.insert(it1, 100);
  EXPECT_EQ(a[0], 100);
}

TEST_F(VectorTests, pop) {
  s21::Vector<int> a{1, 2, 3};
  a.pop_back();
  EXPECT_NE(a.size(), a.capacity());
}

TEST_F(VectorTests, shrink) {
  s21::Vector<int> a{2, 3, 4};
  a.pop_back();
  a.shrink_to_fit();
  EXPECT_EQ(a.size(), a.capacity());
}

TEST_F(VectorTests, constOperator) {
  const s21::Vector<int> a{2, 3, 4};
  EXPECT_EQ(a.at(2), a[2]);
}

TEST_F(VectorTests, insert_many) {
  s21::Vector<int> a{1, 2, 3, 4, 5};
  const s21::Vector<int>::iterator it1 = a.begin();
  a.insert_many(it1, 100, 200, 300, 400);
  EXPECT_EQ(a[1], 200);
}

TEST_F(VectorTests, insert_many_back) {
  s21::Vector<int> a{1, 2, 3, 4, 5};
  a.insert_many_back(100, 200, 300, 400);
  EXPECT_EQ(a[5], 100);
}

TEST_F(VectorTests, erase) {
  s21::Vector<int> a{1, 2, 3, 4, 5};
  s21::Vector<int>::iterator it1 = a.begin();
  a.erase(it1);
  EXPECT_EQ(a[0], 2);
  s21::Vector<int>::iterator it2 = a.end();
  --it2;
  ;
  a.erase(it2);
  EXPECT_EQ(it2, a.end());
}

TEST_F(VectorTests, push_back) {
  s21::Vector<int> a{1, 2, 3, 4, 5};
  a.push_back(6);
  EXPECT_EQ(a[5], 6);
}

TEST_F(VectorTests, push_back1) {
  s21::Vector<int> a{};
  a.push_back(6);
  EXPECT_EQ(a[0], 6);
}

TEST_F(VectorTests, throw1) {
  s21::Vector<int> a{1, 2};
  const s21::Vector<int> b{1, 2};
  s21::Vector<int>::iterator it1 = a.end() + 1;
  EXPECT_THROW(a.at(5), std::out_of_range);
  EXPECT_THROW(b.at(5), std::out_of_range);
  EXPECT_THROW(a.reserve(1), std::length_error);
  EXPECT_THROW(a.insert(it1, 10), std::out_of_range);
  EXPECT_THROW(a.insert_many(it1, 10), std::out_of_range);
  EXPECT_THROW(a.erase(it1), std::out_of_range);
}