#include <gtest/gtest.h>

#include "../set/s21_set.h"

class SetTest : public ::testing::Test {
 public:
  s21::Set<int> set;
  s21::Set<int> other_tree = {1, 3, 4, 5};
  s21::Set<int> other_tree_copy = other_tree;
  std::vector<int> original = {-3, 5, 4, 6, 7, 1};
  std::vector<int> sorted_copy = original;
  // Сортируем копию

 protected:
  void SetUp() override {
    std::sort(sorted_copy.begin(), sorted_copy.end());

    for (auto it = original.begin(); it != original.end(); it++) {
      set.insert(*it);
    }
  }

  void TearDown() override {}
};

// TEST(SetTests, InitTest1) { s21::Set<int> set; }

TEST(SetTests, InitTest2) {
  s21::Set<int> set;
  int a = 3;
  int b = 4;
  int c = -6;
  set.insert(a);
  set.insert(b);
  set.insert(c);
}

TEST(SetTests, ManyInsertTest) {
  s21::Set<int> set;
  auto t = set.insert_many(1, 2);
  EXPECT_EQ(*t.at(0).first, 1);
  EXPECT_EQ(*t.at(1).first, 2);
}

TEST(SetTests, ConstructorDefaultTest) {
  s21::Set<int> tree1;
  s21::Set<double> tree2;
}

TEST(SetTests, ConstructorInitilizationTest) {
  int a = 3;
  int b = 4;
  s21::Set<int> set1{a, b};
  s21::Set<int> set2{-3, 5, 4, 6, 7, 1};
  EXPECT_EQ(*set2.begin(), -3);
  EXPECT_EQ(*(++set2.begin()), 1);
}

TEST(SetTests, ConstructorCopyTest) {
  s21::Set<int> tree1{1, 2, 3, 4, 5, -5, 3};
  s21::Set<int> tree2(tree1);
  for (auto it1 = tree1.begin(), it2 = tree2.begin(); it1 != tree1.end();
       ++it1, ++it2) {
    EXPECT_NE(it1.get_node(), it2.get_node());
    EXPECT_EQ(*it1, *it2);
  }
}

TEST(SetTests, ConstructorMoveCopyTest) {
  s21::Set<int> tree1{1, 2, 3, 4, 5, -5, 3};
  s21::Set<int> tree1_copy{1, 2, 3, 4, 5, -5, 3};
  s21::Set<int> tree2(std::move(tree1));
  for (auto it1 = tree1_copy.begin(), it2 = tree2.begin(); it2 != tree2.end();
       ++it1, ++it2) {
    EXPECT_NE(it1.get_node(), it2.get_node());
    EXPECT_EQ(*it1, *it2);
  }
}

TEST(SetTests, CopyTest) {
  s21::Set<int> tree1{1, 2, 3, 4, 5, -5, 3};
  s21::Set<int> tree2;
  tree2 = tree1;
  for (auto it1 = tree1.begin(), it2 = tree2.begin(); it1 != tree1.end();
       ++it1, ++it2) {
    EXPECT_NE(it1.get_node(), it2.get_node());
    EXPECT_EQ(*it1, *it2);
  }
}

TEST(SetTests, MoveCopyTest) {
  s21::Set<int> tree1{1, 2, 3, 4, 5, -5, 3};
  s21::Set<int> tree1_copy{1, 2, 3, 4, 5, -5, 3};
  s21::Set<int> tree2;
  tree2 = std::move(tree1);
  for (auto it1 = tree1_copy.begin(), it2 = tree2.begin();
       it1 != tree1_copy.end(); ++it1, ++it2) {
    EXPECT_NE(it1.get_node(), it2.get_node());
    EXPECT_EQ(*it1, *it2);
  }
}

TEST_F(SetTest, EraseTest1) {
  set.erase(set.begin());
  EXPECT_EQ(*(set.begin()), 1);
}

TEST_F(SetTest, IterTest1) {
  int i = 0;
  for (auto it = set.begin(); it != set.end(); ++it) {
    EXPECT_EQ(*it, sorted_copy[i]);
    i++;
  }
}

TEST_F(SetTest, IterTest2) {
  int i = 0;
  for (auto it = set.begin(); it != set.end();) {
    EXPECT_EQ(*it, sorted_copy[i]);
    i++;
    ++it;
    --it;
    ++it;
  }
}

TEST(SetTests, EmptyTest) {
  s21::Set<int> tree1 = {1, 2, 3, 4};
  s21::Set<int> tree2;
  EXPECT_EQ(tree1.empty(), false);
  EXPECT_EQ(tree2.empty(), true);
}

TEST(SetTests, SizeTest) {
  s21::Set<int> tree1 = {1, 2, 3, 4};
  s21::Set<int> tree2;
  std::size_t size = 4;
  std::size_t empty_size = 0;
  EXPECT_EQ(tree1.size(), size);
  EXPECT_EQ(tree2.size(), empty_size);
}

TEST(SetTests, ClearTest) {
  s21::Set<int> tree1 = {1, 2, 3, 4};
  tree1.clear();
  std::size_t empty_size = 0;
  EXPECT_EQ(tree1.size(), empty_size);
}

TEST_F(SetTest, SwapTest) {
  set.swap(other_tree);
  int i = 0;
  for (auto it = other_tree.begin(); it != other_tree.end(); ++it) {
    EXPECT_EQ(*it, sorted_copy[i]);
    i++;
  }

  for (auto it = set.begin(), it2 = other_tree_copy.begin(); it != set.end();
       ++it, ++it2) {
    EXPECT_EQ(*it, *it2);
    i++;
  }
}

TEST_F(SetTest, MergeTest) {
  set.merge(other_tree);
  EXPECT_EQ(set.size(), other_tree.size() + sorted_copy.size() - 3);
}

TEST_F(SetTest, FindTest) {
  for (auto it = set.begin(); it != set.end(); ++it) {
    EXPECT_EQ(*it, *set.find(*it));
  }
}
TEST_F(SetTest, ContainsTest) {
  for (auto it = set.begin(); it != set.end(); ++it) {
    EXPECT_EQ(true, set.contains(*it));
  }

  EXPECT_EQ(false, set.contains(-1230321));
}

TEST_F(SetTest, notFind) {
  s21::Set<int> set1;
  s21::Set<int>::iterator it = set1.find(1);
  EXPECT_TRUE(it == nullptr);
}

TEST_F(SetTest, insert) {
  s21::Set<int> set1{1};
  s21::Set<int>::iterator it = set1.begin();
  set1.insert(1);
  EXPECT_EQ(*it, 1);
}