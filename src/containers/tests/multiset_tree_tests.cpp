#include <gtest/gtest.h>

#include "../multiset/s21_binary_tree_multiset.h"

class BinaryTreeMultisetTest : public ::testing::Test {
 public:
  s21::BinaryTreeMultiset<int> tree;
  s21::BinaryTreeMultiset<int> other_tree = {1, 3, 4, 5};
  s21::BinaryTreeMultiset<int> other_tree_copy = other_tree;
  std::vector<int> original = {-3, 5, 4, 6, 7, 1};
  std::vector<int> sorted_copy = original;
  // Сортируем копию

 protected:
  void SetUp() override {
    std::sort(sorted_copy.begin(), sorted_copy.end());

    for (auto it = original.begin(); it != original.end(); it++) {
      tree.insert(*it);
    }
  }

  void TearDown() override {}
};

TEST(BinaryTests, InsertTest) {
  s21::BinaryTreeMultiset<int> tree;
  int a = 3;
  int b = 4;
  int c = -6;

  EXPECT_NO_THROW(tree.insert(a));
  EXPECT_NO_THROW(tree.insert(b));
  EXPECT_NO_THROW(tree.insert(c));
}

TEST(BinaryTests, ConstructorDefaultTest) {
  s21::BinaryTreeMultiset<int> tree1;
  s21::BinaryTreeMultiset<double> tree2;
}

TEST(BinaryTests, ConstructorInitilizationTest) {
  int a = 3;
  int b = 4;
  s21::BinaryTreeMultiset<int> tree1{a, b};
  s21::BinaryTreeMultiset<int> tree2{-3, 5, 4, 6, 7, 1};
  EXPECT_EQ(*tree2.begin(), -3);
  EXPECT_EQ(*(++tree2.begin()), 1);
}

TEST(BinaryTests, ConstructorCopyTest) {
  s21::BinaryTreeMultiset<int> tree1{1, 2, 3, 4, 5, -5, 3};
  s21::BinaryTreeMultiset<int> tree2(tree1);
  for (auto it1 = tree1.begin(), it2 = tree2.begin(); it1 != tree1.end();
       ++it1, ++it2) {
    EXPECT_NE(it1.get_node(), it2.get_node());
    EXPECT_EQ(*it1, *it2);
  }
}

TEST(BinaryTests, ConstructorMoveCopyTest) {
  s21::BinaryTreeMultiset<int> tree1{1, 2, 3, 4, 5, -5, 3};
  s21::BinaryTreeMultiset<int> tree1_copy{1, 2, 3, 4, 5, -5, 3};
  s21::BinaryTreeMultiset<int> tree2(std::move(tree1));
  for (auto it1 = tree1_copy.begin(), it2 = tree2.begin(); it2 != tree2.end();
       ++it1, ++it2) {
    EXPECT_NE(it1.get_node(), it2.get_node());
    EXPECT_EQ(*it1, *it2);
  }
}

TEST(BinaryTests, CopyTest) {
  s21::BinaryTreeMultiset<int> tree1{1, 2, 3, 4, 5, -5, 3};
  s21::BinaryTreeMultiset<int> tree2;
  tree2 = tree1;
  for (auto it1 = tree1.begin(), it2 = tree2.begin(); it1 != tree1.end();
       ++it1, ++it2) {
    EXPECT_NE(it1.get_node(), it2.get_node());
    EXPECT_EQ(*it1, *it2);
  }
}

TEST(BinaryTests, MoveCopyTest) {
  s21::BinaryTreeMultiset<int> tree1{1, 2, 3, 4, 5, -5, 3};
  s21::BinaryTreeMultiset<int> tree1_copy{1, 2, 3, 4, 5, -5, 3};
  s21::BinaryTreeMultiset<int> tree2;
  tree2 = std::move(tree1);
  for (auto it1 = tree1_copy.begin(), it2 = tree2.begin();
       it1 != tree1_copy.end(); ++it1, ++it2) {
    EXPECT_NE(it1.get_node(), it2.get_node());
    EXPECT_EQ(*it1, *it2);
  }
}

TEST_F(BinaryTreeMultisetTest, EraseTest1) {
  tree.erase(tree.begin());
  EXPECT_EQ(*(tree.begin()), 1);
}

TEST(BinaryTests, EraseTest2) {
  s21::BinaryTreeMultiset<int> tree;
  tree.erase(tree.begin());
}

TEST(BinaryTests, IterInitTest) {
  s21::BinaryTreeMultiset<int> tree;
  int a = 3;
  int b = 4;
  int c = -6;
  tree.insert(a);
  tree.insert(b);
  tree.insert(c);
}

TEST_F(BinaryTreeMultisetTest, IterTest1) {
  int i = 0;
  for (auto it = tree.begin(); it != tree.end(); ++it) {
    EXPECT_EQ(*it, sorted_copy[i]);
    i++;
  }
}

TEST_F(BinaryTreeMultisetTest, IterTest2) {
  int i = 0;
  for (auto it = tree.begin(); it != tree.end();) {
    EXPECT_EQ(*it, sorted_copy[i]);
    i++;
    ++it;
    --it;
    ++it;
  }
}

TEST(BinaryTests, EmptyTest) {
  s21::BinaryTreeMultiset<int> tree1 = {1, 2, 3, 4};
  s21::BinaryTreeMultiset<int> tree2;
  EXPECT_EQ(tree1.empty(), false);
  EXPECT_EQ(tree2.empty(), true);
}

TEST(BinaryTests, SizeTest) {
  s21::BinaryTreeMultiset<int> tree1 = {1, 2, 3, 4};
  s21::BinaryTreeMultiset<int> tree2;
  std::size_t size = 4;
  std::size_t empty_size = 0;
  EXPECT_EQ(tree1.size(), size);
  EXPECT_EQ(tree2.size(), empty_size);

  tree1.erase(tree1.begin());
  size--;
  EXPECT_EQ(tree1.size(), size);

  s21::BinaryTreeMultiset<int> tree3{1, 1, -1, 2, 3};
  tree3.erase(++tree3.begin());
  tree3.erase(++tree3.begin());
  std::size_t he = 3;
  EXPECT_EQ(tree3.size(), he);
}

TEST_F(BinaryTreeMultisetTest, SwapTest) {
  tree.swap(other_tree);
  int i = 0;
  for (auto it = other_tree.begin(); it != other_tree.end(); ++it) {
    EXPECT_EQ(*it, sorted_copy[i]);
    i++;
  }

  for (auto it = tree.begin(), it2 = other_tree_copy.begin(); it != tree.end();
       ++it, ++it2) {
    EXPECT_EQ(*it, *it2);
    i++;
  }
}

TEST_F(BinaryTreeMultisetTest, MergeTest) {
  tree.merge(other_tree);
  EXPECT_EQ(tree.size(), other_tree.size() + sorted_copy.size());
}

TEST_F(BinaryTreeMultisetTest, otherTests) {
  s21::BinaryTreeMultiset<int>::const_iterator it = other_tree.cbegin();
  s21::BinaryTreeMultiset<int>::const_iterator it1 = other_tree.cbegin();
  ++it;
  --it;
  it.get_node();
  EXPECT_EQ(it, it1);
}

TEST_F(BinaryTreeMultisetTest, erase1) {
  s21::BinaryTreeMultiset<int> tree1{1, 1, -1};
  s21::BinaryTreeMultiset<int>::iterator it = other_tree.begin();
  ++it;
  ++it;
  other_tree.erase(it);
}

TEST_F(BinaryTreeMultisetTest, emptyBegin) {
  s21::BinaryTreeMultiset<int> tree1;
  s21::BinaryTreeMultiset<int> tree{1};
  tree.erase(tree.begin());
  s21::BinaryTreeMultiset<int>::const_iterator it = tree.cbegin();
  s21::BinaryTreeMultiset<int>::const_iterator it1 = tree1.cbegin();
  EXPECT_EQ(it, it1);
  ++it1;
  EXPECT_EQ(it, it1);
}

TEST_F(BinaryTreeMultisetTest, constIter) {
  s21::BinaryTreeMultiset<int> tree1{1, 1, -1};
  s21::BinaryTreeMultiset<int>::const_iterator it = tree1.cbegin();
  s21::BinaryTreeMultiset<int>::const_iterator it1 = tree1.cbegin();
  ++it;
  ++it;
  --it;
  --it;
  EXPECT_EQ(it, it1);
}

TEST_F(BinaryTreeMultisetTest, findMin) {
  s21::BinaryTreeMultiset<int> set1 = {1, 3, 2, 4};
  s21::BinaryTreeMultiset<int>::iterator it1 = set1.begin();
  ++it1;
  ++it1;
  set1.erase(it1);
  s21::BinaryTreeMultiset<int> set2 = {1, -1};
  it1 = set2.begin();
  set2.erase(it1);
  set2.insert(1);
  set2.erase(set2.begin());
  set2.insert(-2);
  set2.erase(++set2.begin());
  set2.insert(1);
  set2.insert(1);
  it1 = set2.begin();
  ++it1;
  --it1;
  s21::BinaryTreeMultiset<int> set3 = {1, 5, 4, 3};
  s21::BinaryTreeMultiset<int>::const_iterator it2 = set3.cbegin();
  ++it2;
  --it2;
  s21::BinaryTreeMultiset<int> set4 = {5, 1, 2, 3};
  s21::BinaryTreeMultiset<int>::const_iterator it3 = set4.cend();
  --it3;
}