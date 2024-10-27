#include <gtest/gtest.h>

#include "../multiset/s21_multiset.h"

class MultisetTest : public ::testing::Test {
 public:
  s21::Multiset<int> Multiset;
  s21::Multiset<int> other_tree = {1, 3, 4, 5};
  s21::Multiset<int> other_tree_copy = other_tree;
  std::vector<int> original = {-3, 5, 4, 6, 7, 1};
  std::vector<int> sorted_copy = original;
  // Сортируем копию

 protected:
  void SetUp() override {
    std::sort(sorted_copy.begin(), sorted_copy.end());

    for (auto it = original.begin(); it != original.end(); it++) {
      Multiset.insert(*it);
    }
  }

  void TearDown() override {}
};

// TEST(MultisetTests, InitTest1) { s21::Multiset<int> Multiset; }

TEST(MultisetTests, InitTest2) {
  s21::Multiset<int> Multiset;
  int a = 3;
  int b = 4;
  int c = -6;
  Multiset.insert(a);
  Multiset.insert(b);
  Multiset.insert(c);
}

TEST(MultisetTests, ManyInsertTest) {
  s21::Multiset<int> Multiset;
  auto t = Multiset.insert_many(1, 2);
  EXPECT_EQ(*t.at(0).first, 1);
  EXPECT_EQ(*t.at(1).first, 2);
}

TEST(MultisetTests, ConstructorDefaultTest) {
  s21::Multiset<int> tree1;
  s21::Multiset<double> tree2;
}

TEST(MultisetTests, ConstructorInitilizationTest) {
  int a = 3;
  int b = 4;
  s21::Multiset<int> Multiset1{a, b};
  s21::Multiset<int> Multiset2{-3, 5, 4, 6, 7, 1};
  EXPECT_EQ(*Multiset2.begin(), -3);
  EXPECT_EQ(*(++Multiset2.begin()), 1);
}

TEST(MultisetTests, ConstructorCopyTest) {
  s21::Multiset<int> tree1{1, 2, 3, 4, 5, -5, 3};
  s21::Multiset<int> tree2(tree1);
  for (auto it1 = tree1.begin(), it2 = tree2.begin(); it1 != tree1.end();
       ++it1, ++it2) {
    EXPECT_NE(it1.get_node(), it2.get_node());
    EXPECT_EQ(*it1, *it2);
  }
}

TEST(MultisetTests, ConstructorMoveCopyTest) {
  s21::Multiset<int> tree1{1, 2, 3, 4, 5, -5, 3};
  s21::Multiset<int> tree1_copy{1, 2, 3, 4, 5, -5, 3};
  s21::Multiset<int> tree2(std::move(tree1));
  for (auto it1 = tree1_copy.begin(), it2 = tree2.begin(); it2 != tree2.end();
       ++it1, ++it2) {
    EXPECT_NE(it1.get_node(), it2.get_node());
    EXPECT_EQ(*it1, *it2);
  }
}

TEST(MultisetTests, CopyTest) {
  s21::Multiset<int> tree1{1, 2, 3, 4, 5, -5, 3};
  s21::Multiset<int> tree2;
  tree2 = tree1;
  for (auto it1 = tree1.begin(), it2 = tree2.begin(); it1 != tree1.end();
       ++it1, ++it2) {
    EXPECT_NE(it1.get_node(), it2.get_node());
    EXPECT_EQ(*it1, *it2);
  }
}

TEST(MultisetTests, MoveCopyTest) {
  s21::Multiset<int> tree1{1, 2, 3, 4, 5, -5, 3};
  s21::Multiset<int> tree1_copy{1, 2, 3, 4, 5, -5, 3};
  s21::Multiset<int> tree2;
  tree2 = std::move(tree1);
  for (auto it1 = tree1_copy.begin(), it2 = tree2.begin();
       it1 != tree1_copy.end(); ++it1, ++it2) {
    EXPECT_NE(it1.get_node(), it2.get_node());
    EXPECT_EQ(*it1, *it2);
  }
}

TEST_F(MultisetTest, EraMultisetest1) {
  Multiset.erase(Multiset.begin());
  EXPECT_EQ(*(Multiset.begin()), 1);
}

TEST_F(MultisetTest, IterTest1) {
  int i = 0;
  for (auto it = Multiset.begin(); it != Multiset.end(); ++it) {
    EXPECT_EQ(*it, sorted_copy[i]);
    i++;
  }
}

TEST_F(MultisetTest, IterTest2) {
  int i = 0;
  for (auto it = Multiset.begin(); it != Multiset.end();) {
    EXPECT_EQ(*it, sorted_copy[i]);
    i++;
    ++it;
    --it;
    ++it;
  }
}

TEST(MultisetTests, EmptyTest) {
  s21::Multiset<int> tree1 = {1, 2, 3, 4};
  s21::Multiset<int> tree2;
  EXPECT_EQ(tree1.empty(), false);
  EXPECT_EQ(tree2.empty(), true);
}

TEST(MultisetTests, SizeTest) {
  s21::Multiset<int> tree1 = {1, 2, 3, 4};
  s21::Multiset<int> tree2;
  std::size_t size = 4;
  std::size_t empty_size = 0;
  EXPECT_EQ(tree1.size(), size);
  EXPECT_EQ(tree2.size(), empty_size);
}

TEST(MultisetTests, ClearTest) {
  s21::Multiset<int> tree1 = {1, 2, 3, 4};
  tree1.clear();
  std::size_t empty_size = 0;
  EXPECT_EQ(tree1.size(), empty_size);
}

TEST_F(MultisetTest, SwapTest) {
  Multiset.swap(other_tree);
  int i = 0;
  for (auto it = other_tree.begin(); it != other_tree.end(); ++it) {
    EXPECT_EQ(*it, sorted_copy[i]);
    i++;
  }

  for (auto it = Multiset.begin(), it2 = other_tree_copy.begin();
       it != Multiset.end(); ++it, ++it2) {
    EXPECT_EQ(*it, *it2);
    i++;
  }
}

TEST_F(MultisetTest, MergeTest) {
  Multiset.merge(other_tree);
  EXPECT_EQ(Multiset.size(), other_tree.size() + sorted_copy.size());
}

TEST_F(MultisetTest, FindTest) {
  for (auto it = Multiset.begin(); it != Multiset.end(); ++it) {
    EXPECT_EQ(*it, *Multiset.find(*it));
  }
}

TEST_F(MultisetTest, ContainsTest) {
  for (auto it = Multiset.begin(); it != Multiset.end(); ++it) {
    EXPECT_EQ(true, Multiset.contains(*it));
  }

  EXPECT_EQ(false, Multiset.contains(-1230321));
}

TEST(MultisetTests, IterTest3) {
  s21::Multiset<int> set1 = {1, 2, 3, 3, 4, 5};
  std::vector<int> set2 = {1, 2, 3, 3, 4, 4, 5};
  set1.insert(4);
  int i = 0;
  for (auto it = set1.begin(); it != set1.end(); ++it) {
    EXPECT_EQ(*it, set2[i]);
    i++;
  }
}

TEST(MultisetTests, MergeTest2) {
  s21::Multiset<int> set1 = {1, 3, 2, 2};
  s21::Multiset<int> set2 = {2, 3, 4, 4, 5};
  std::vector<int> set3 = {1, 2, 2, 2, 3, 3, 4, 4, 5};
  set1.merge((set2));

  int i = 0;
  for (auto it = set1.begin(); it != set1.end(); ++it) {
    EXPECT_EQ(*it, set3[i]);
    i++;
  }
}

TEST_F(MultisetTest, countTest) {
  s21::Multiset<int> set1 = {1, 3, 2, 2};
  std::size_t count = set1.count(2);
  std::size_t k = 2;
  EXPECT_EQ(count, k);
}

TEST_F(MultisetTest, lowerBoundTest) {
  s21::Multiset<int> set1 = {1, 3, 2, 2};
  s21::Multiset<int>::iterator it = set1.lower_bound(2);
  s21::Multiset<int>::iterator it1 = set1.begin();
  bool kek = set1.max_size();
  ++it1;
  ++it1;
  EXPECT_EQ(it, it1);
  EXPECT_TRUE(kek);
}

TEST_F(MultisetTest, upperBoundTest) {
  s21::Multiset<int> set1 = {1, 2, 3, 4};
  s21::Multiset<int>::iterator it = set1.upper_bound(2);
  s21::Multiset<int>::iterator it1 = set1.begin();
  ++it1;
  ++it1;
  EXPECT_EQ(it, it1);
}

TEST_F(MultisetTest, notFind) {
  s21::Multiset<int> set1;
  // std::multiset<int> set2;
  s21::Multiset<int>::iterator it = set1.find(1);
  EXPECT_TRUE(it == nullptr);
}