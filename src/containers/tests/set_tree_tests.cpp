#include <gtest/gtest.h>

#include "../set/s21_set_binary_tree.h"

class BinaryTreeTestSet : public ::testing::Test {
 public:
  s21::BinaryTree<int> tree;
  s21::BinaryTree<int> other_tree = {1, 3, 4, 5};
  s21::BinaryTree<int> other_tree_copy = other_tree;
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

TEST(BinaryTestsSet, InsertTest) {
  s21::BinaryTree<int> tree;
  int a = 3;
  int b = 4;
  int c = -6;

  EXPECT_NO_THROW(tree.insert(a));
  EXPECT_NO_THROW(tree.insert(b));
  EXPECT_NO_THROW(tree.insert(c));
}

TEST(BinaryTestsSet, ConstructorDefaultTest) {
  s21::BinaryTree<int> tree1;
  s21::BinaryTree<double> tree2;
}

TEST(BinaryTestsSet, ConstructorInitilizationTest) {
  int a = 3;
  int b = 4;
  s21::BinaryTree<int> tree1{a, b};
  s21::BinaryTree<int> tree2{-3, 5, 4, 6, 7, 1};
  EXPECT_EQ(*tree2.begin(), -3);
  EXPECT_EQ(*(++tree2.begin()), 1);
}

TEST(BinaryTestsSet, ConstructorCopyTest) {
  s21::BinaryTree<int> tree1{1, 2, 3, 4, 5, -5, 3};
  s21::BinaryTree<int> tree2(tree1);
  for (auto it1 = tree1.begin(), it2 = tree2.begin(); it1 != tree1.end();
       ++it1, ++it2) {
    EXPECT_NE(it1.get_node(), it2.get_node());
    EXPECT_EQ(*it1, *it2);
  }
}

TEST(BinaryTestsSet, ConstructorMoveCopyTest) {
  s21::BinaryTree<int> tree1{1, 2, 3, 4, 5, -5, 3};
  s21::BinaryTree<int> tree1_copy{1, 2, 3, 4, 5, -5, 3};
  s21::BinaryTree<int> tree2(std::move(tree1));
  for (auto it1 = tree1_copy.begin(), it2 = tree2.begin(); it2 != tree2.end();
       ++it1, ++it2) {
    EXPECT_NE(it1.get_node(), it2.get_node());
    EXPECT_EQ(*it1, *it2);
  }
}

TEST(BinaryTestsSet, CopyTest) {
  s21::BinaryTree<int> tree1{1, 2, 3, 4, 5, -5, 3};
  s21::BinaryTree<int> tree2;
  tree2 = tree1;
  for (auto it1 = tree1.begin(), it2 = tree2.begin(); it1 != tree1.end();
       ++it1, ++it2) {
    EXPECT_NE(it1.get_node(), it2.get_node());
    EXPECT_EQ(*it1, *it2);
  }
}

TEST(BinaryTestsSet, MoveCopyTest) {
  s21::BinaryTree<int> tree1{1, 2, 3, 4, 5, -5, 3};
  s21::BinaryTree<int> tree1_copy{1, 2, 3, 4, 5, -5, 3};
  s21::BinaryTree<int> tree2;
  tree2 = std::move(tree1);
  for (auto it1 = tree1_copy.begin(), it2 = tree2.begin();
       it1 != tree1_copy.end(); ++it1, ++it2) {
    EXPECT_NE(it1.get_node(), it2.get_node());
    EXPECT_EQ(*it1, *it2);
  }
}

TEST_F(BinaryTreeTestSet, EraseTest1) {
  tree.erase(tree.begin());
  EXPECT_EQ(*(tree.begin()), 1);
}

TEST(BinaryTestsSet, EraseTest2) {
  s21::BinaryTree<int> tree;
  tree.erase(tree.begin());
}

TEST(BinaryTestsSet, IterInitTest) {
  s21::BinaryTree<int> tree;
  int a = 3;
  int b = 4;
  int c = -6;
  tree.insert(a);
  tree.insert(b);
  tree.insert(c);
}

TEST_F(BinaryTreeTestSet, IterTest1) {
  int i = 0;
  for (auto it = tree.begin(); it != tree.end(); ++it) {
    EXPECT_EQ(*it, sorted_copy[i]);
    i++;
  }
}

TEST_F(BinaryTreeTestSet, IterTest2) {
  int i = 0;
  for (auto it = tree.begin(); it != tree.end();) {
    EXPECT_EQ(*it, sorted_copy[i]);
    i++;
    ++it;
    --it;
    ++it;
  }
}

TEST(BinaryTestsSet, EmptyTest) {
  s21::BinaryTree<int> tree1 = {1, 2, 3, 4};
  s21::BinaryTree<int> tree2;
  EXPECT_EQ(tree1.empty(), false);
  EXPECT_EQ(tree2.empty(), true);
}

TEST(BinaryTestsSet, SizeTest) {
  s21::BinaryTree<int> tree1 = {1, 2, 3, 4};
  s21::BinaryTree<int> tree2;
  std::size_t size = 4;
  std::size_t empty_size = 0;
  EXPECT_EQ(tree1.size(), size);
  EXPECT_EQ(tree2.size(), empty_size);
}

TEST_F(BinaryTreeTestSet, SwapTest) {
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

TEST_F(BinaryTreeTestSet, MergeTest) {
  tree.merge(other_tree);
  EXPECT_EQ(tree.size(), other_tree.size() + sorted_copy.size() - 3);
}

TEST_F(BinaryTreeTestSet, otherTests) {
  s21::BinaryTree<int>::const_iterator it = other_tree.cbegin();
  s21::BinaryTree<int>::const_iterator it1 = other_tree.cbegin();
  ++it;
  --it;
  it.get_node();
  EXPECT_EQ(it, it1);
}

TEST_F(BinaryTreeTestSet, erase1) {
  s21::BinaryTree<int> tree1{1, 1, -1};
  s21::BinaryTree<int>::iterator it = other_tree.begin();
  ++it;
  ++it;
  other_tree.erase(it);
  s21::BinaryTree<int> tree2{1, 1, -1, 2, 3};
  tree2.erase(++tree2.begin());
  tree2.erase(++tree2.begin());
  std::size_t he = 2;
  EXPECT_EQ(tree2.size(), he);
}

TEST_F(BinaryTreeTestSet, emptyBegin) {
  s21::BinaryTree<int> tree1;
  s21::BinaryTree<int> tree{1};
  tree.erase(tree.begin());
  s21::BinaryTree<int>::const_iterator it = tree.cbegin();
  s21::BinaryTree<int>::const_iterator it1 = tree1.cbegin();
  EXPECT_EQ(it, it1);
  ++it1;
  EXPECT_EQ(it, it1);
}

TEST_F(BinaryTreeTestSet, constIter) {
  s21::BinaryTree<int> tree1{1, 1, -1};
  s21::BinaryTree<int>::const_iterator it = tree1.cbegin();
  s21::BinaryTree<int>::const_iterator it1 = tree1.cbegin();
  ++it;
  --it;
  EXPECT_EQ(it, it1);
}

TEST_F(BinaryTreeTestSet, findMin) {
  s21::BinaryTree<int> set1 = {1, 3, 2, 4};
  s21::BinaryTree<int>::iterator it1 = set1.begin();
  ++it1;
  ++it1;
  set1.erase(it1);
  s21::BinaryTree<int> set2 = {1, -1};
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
  s21::BinaryTree<int> set3 = {1, 5, 4, 3};
  s21::BinaryTree<int>::const_iterator it2 = set3.cbegin();
  ++it2;
  --it2;
  s21::BinaryTree<int> set4 = {5, 1, 2, 3};
  s21::BinaryTree<int>::const_iterator it3 = set4.cend();
  --it3;
}

TEST_F(BinaryTreeTestSet, size) {
  s21::BinaryTree<int> tree1{1, 1, -1};
  std::size_t count = tree1.max_size();
  EXPECT_TRUE(count);
}

TEST_F(BinaryTreeTestSet, others) {
  s21::BinaryTree<int> tree1{-1, -2, -3};
  s21::BinaryTree<int>::iterator it2 = tree1.begin();
  ++it2;
  ++it2;
  tree1.erase(it2);
}