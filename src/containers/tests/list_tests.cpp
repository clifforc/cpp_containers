#include <gtest/gtest.h>

#include <iostream>
#include <list>

#include "../list/s21_list.h"

class ListsTests : public ::testing::Test {
 protected:
  void SetUp() override {}

  void TearDown() override {}
};

TEST_F(ListsTests, default_ctor) {
  s21::List<int> a{2, 3};
  s21::List<int> b{1, 2, 3};
  EXPECT_NE(a.front(), b.front());
}

TEST_F(ListsTests, merge) {
  s21::List<int> a{1, 2};
  a.sort();
  s21::List<int> b{1, 4, 5};
  a.merge(b);
  s21::List<int>::iterator it = a.begin();
  ++it;
  EXPECT_EQ(*it, 1);
}

TEST_F(ListsTests, size) {
  s21::List<int> b{1, 2, 3};
  bool kek = b.size();
  EXPECT_TRUE(kek);
  EXPECT_FALSE(b.empty());
}

TEST_F(ListsTests, insert) {
  s21::List<int> a = {2, 2, 3, 4, 5};
  s21::List<int>::const_iterator it = a.cbegin();
  s21::List<int>::iterator it1 = a.insert(it, 1);
  EXPECT_EQ(*it1, 1);
}

TEST_F(ListsTests, insert_many) {
  s21::List<int> a = {2, 2, 3, 4, 5};
  s21::List<int>::const_iterator it = a.cbegin();
  s21::List<int>::iterator it1 = a.insert_many(it, 1, 1);
  EXPECT_EQ(*it1, 2);
}

TEST_F(ListsTests, insert_many1) {
  s21::List<int> a = {2, 2, 3, 4, 5};
  a.insert_many_back(1, 1);
  a.insert_many_front(1, 1);
  s21::List<int>::const_iterator it = a.cbegin();
  int kek = a.back();
  EXPECT_EQ(*it, 1);
  EXPECT_EQ(kek, 1);
}

TEST_F(ListsTests, erase) {
  s21::List<int> a = {2, 3, 4};
  s21::List<int>::iterator it = a.begin();
  ++it;
  s21::List<int>::const_iterator it3;
  it3 = it;
  a.erase(it3);
  s21::List<int>::iterator it2 = a.begin();
  EXPECT_EQ(*it2, 2);
  ++it2;
  EXPECT_EQ(*it2, 4);
  s21::List<int>::const_iterator it4 = a.cbegin();
  a.erase(it4);
  EXPECT_EQ(*it2, 4);
}

TEST_F(ListsTests, reverse) {
  s21::List<int> a{2, 1, 3};
  a.sort();
  a.reverse();
  s21::List<int>::const_iterator it = a.cbegin();
  EXPECT_EQ(*it, 3);
}

TEST_F(ListsTests, unique) {
  s21::List<int> a{3, 3, 4};
  a.unique();
  s21::List<int>::iterator it = a.begin();
  ++it;
  EXPECT_EQ(*it, 4);
}

TEST_F(ListsTests, swap) {
  s21::List<int> a{3, 3, 4};
  s21::List<int> b{1, 1, 1};
  a.swap(b);
  s21::List<int>::iterator it = a.begin();
  EXPECT_EQ(*it, 1);
}

TEST_F(ListsTests, erase_back) {
  s21::List<int> a{3, 4};
  s21::List<int>::iterator it = a.begin();
  ++it;
  s21::List<int>::const_iterator it1;
  it1 = it;
  a.erase(it1);
  s21::List<int>::iterator it3 = a.begin();
  EXPECT_EQ(*it3, 3);
}

TEST_F(ListsTests, pop_back) {
  s21::List<int> a{3};
  a.pop_back();
  int size = a.size();
  EXPECT_EQ(size, 0);
}

TEST_F(ListsTests, push_front) {
  s21::List<int> a;
  a.push_front(1);
  s21::List<int>::iterator it = a.begin();
  EXPECT_EQ(*it, 1);
  const bool kek = a.max_size();
  EXPECT_TRUE(kek);
}

TEST_F(ListsTests, low_test) { s21::List<int> a; }

TEST_F(ListsTests, front_back_test) {
  const s21::List<int> a{1, 2};
  const int kek = a.front();
  EXPECT_EQ(kek, 1);
  const int lol = a.back();
  EXPECT_EQ(lol, 2);
}

TEST_F(ListsTests, other_tests) {
  s21::List<int> a{1, 2};
  s21::List<int> b;
  s21::List<int> c{1, 2, 3};
  s21::List<int> d;
  b = a;
  b = c;
  d.pop_front();
  d.clear();
  c.merge(d);
  a.pop_back();
  a.pop_front();
  a.sort();
  a.reverse();
  a.unique();
  const bool kek = a.empty();
  EXPECT_TRUE(kek);
}

TEST_F(ListsTests, iterators) {
  s21::List<int> a{1, 2, 3, 4, 5};
  s21::List<int>::iterator it = a.begin();
  ++it;
  --it;
  s21::List<int>::iterator it1 = a.begin();
  s21::List<int>::const_iterator it3;
  s21::List<int>::const_iterator it4 = a.cbegin();
  it3 = it;
  ++it3;
  --it3;
  EXPECT_TRUE(it1 == it);
  EXPECT_TRUE(it3 == it4);
}

TEST_F(ListsTests, otherTests1) {
  const s21::List<int> a{1, 2};
  s21::List<int> kek{1, 2};
  s21::List<int> b{a};
  s21::List<int> c(4);
  s21::List<int> d{std::move(kek)};
  s21::List<int> list1{1, 2};
  s21::List<int> list2;
  list2 = std::move(list1);
  bool wat = list1.size();
  EXPECT_FALSE(wat);
}

TEST_F(ListsTests, low_test23) {
  const s21::List<int> a{1};
  auto it = a.begin();
  auto it1 = a.end();
  EXPECT_TRUE(*it);
  EXPECT_TRUE(it1 == nullptr);
}