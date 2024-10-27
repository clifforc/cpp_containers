#include <gtest/gtest.h>

#include "../map/s21_binary_tree_map.h"

class BinaryTreeMapTest : public ::testing::Test {
 public:
  s21::BinaryTreeMap<int, int> map = {
      std::make_pair(1, 1), std::make_pair(2, 2), std::make_pair(3, 3),
      std::make_pair(-1, 4)};
  s21::BinaryTreeMap<int, int> map_copy = map;
  s21::BinaryTreeMap<int, int> other_map = {};
  std::vector<std::pair<int, int>> vector = {
      std::make_pair(-1, 4), std::make_pair(1, 1), std::make_pair(2, 2),
      std::make_pair(3, 3)};
  // Сортируем копию

 protected:
  void SetUp() override {}

  void TearDown() override {}
};

TEST(BinaryBinaryTreeMapTests, ConstructorsTest) {
  // init const
  s21::BinaryTreeMap<int, int> a = {std::make_pair(1, 1), std::make_pair(2, 2),
                                    std::make_pair(3, 3),
                                    std::make_pair(-1, 4)};
  s21::BinaryTreeMap<int, int> a_copy1 = a;
  s21::BinaryTreeMap<int, int> a_copy2 = a;
  // copy const
  s21::BinaryTreeMap<int, int> b = a;
  // move const
  s21::BinaryTreeMap<int, int> c = std::move(a_copy1);
  // operator=
  s21::BinaryTreeMap<int, int> d;
  d = a;
  // move operator=
  s21::BinaryTreeMap<int, int> e;
  e = std::move(a_copy2);
  std::vector<std::pair<int, int>> ans = {
      std::make_pair(-1, 4), std::make_pair(1, 1), std::make_pair(2, 2),
      std::make_pair(3, 3)};

  auto it2 = ans.begin();
  for (auto it = a.begin(); it != a.end(); ++it) {
    EXPECT_EQ((*it).first, (*it2).first);
    EXPECT_EQ((*it).second, (*it2).second);
    ++it2;
  }
  it2 = ans.begin();
  for (auto it = b.begin(); it != b.end(); ++it) {
    EXPECT_EQ((*it).first, (*it2).first);
    EXPECT_EQ((*it).second, (*it2).second);
    ++it2;
  }

  it2 = ans.begin();
  for (auto it = c.begin(); it != c.end(); ++it) {
    EXPECT_EQ((*it).first, (*it2).first);
    EXPECT_EQ((*it).second, (*it2).second);
    ++it2;
  }

  it2 = ans.begin();
  for (auto it = d.begin(); it != d.end(); ++it) {
    EXPECT_EQ((*it).first, (*it2).first);
    EXPECT_EQ((*it).second, (*it2).second);
    ++it2;
  }

  it2 = ans.begin();
  for (auto it = e.begin(); it != e.end(); ++it) {
    EXPECT_EQ((*it).first, (*it2).first);
    EXPECT_EQ((*it).second, (*it2).second);
    ++it2;
  }
}

TEST_F(BinaryTreeMapTest, InsertTest) {
  std::pair<s21::BinaryTreeMap<int, int>::iterator, bool> it_retured =
      map.insert(std::make_pair(-100, -2));
  // Проверка возращаемого итератора с insert
  EXPECT_EQ(it_retured.first == map.begin(), true);

  map.insert(-99, -3);
  vector.insert(vector.begin(), std::make_pair(-100, -2));
  vector.insert(++vector.begin(), std::make_pair(-99, -3));

  map.insert_or_assign(2, 100);
  vector[4].second = 100;

  auto it2 = vector.begin();
  for (auto it = map.begin(); it != map.end(); ++it) {
    EXPECT_EQ((*it).first, (*it2).first);
    EXPECT_EQ((*it).second, (*it2).second);
    ++it2;
  }
}

TEST_F(BinaryTreeMapTest, EraseTest) {
  auto temp_it = (map.begin());
  ++temp_it;
  map.erase(temp_it);
  auto temp_it2 = (vector.begin());
  ++temp_it2;
  vector.erase(temp_it2);

  auto it2 = vector.begin();
  for (auto it = map.begin(); it != map.end(); ++it) {
    EXPECT_EQ((*it).first, (*it2).first);
    EXPECT_EQ((*it).second, (*it2).second);
    ++it2;
  }
  map.erase(s21::BinaryTreeMap<int, int>::SetIterator(nullptr));

  s21::BinaryTreeMap<int, int> tree3{
      std::make_pair(1, 1), std::make_pair(-2, -2), std::make_pair(2, 2),
      std::make_pair(3, 3)};
  tree3.erase(++tree3.begin());
  tree3.erase(++tree3.begin());
  std::size_t he = 2;
  EXPECT_EQ(tree3.size(), he);
}

TEST_F(BinaryTreeMapTest, CapacityTest) {
  s21::BinaryTreeMap<int, int> empty_map;
  EXPECT_EQ(map.empty(), false);
  EXPECT_EQ(empty_map.empty(), true);
  std::size_t count = 4;
  std::size_t empty_count = 0;
  EXPECT_EQ(map.size(), count);
  EXPECT_EQ(empty_map.size(), empty_count);
}

TEST_F(BinaryTreeMapTest, ModifiersTest) {
  map.clear();
  EXPECT_EQ(map.empty(), true);
}

TEST_F(BinaryTreeMapTest, SwapMergeTest) {
  s21::BinaryTreeMap<int, int> tree1 = {
      std::make_pair(1, 1), std::make_pair(2, 2), std::make_pair(3, 3)};
  s21::BinaryTreeMap<int, int> tree2 = {
      std::make_pair(3, 4), std::make_pair(5, 5), std::make_pair(6, 6)};
  std::vector<std::pair<int, int>> vector = {
      std::make_pair(1, 1), std::make_pair(2, 2), std::make_pair(3, 3),
      std::make_pair(5, 5), std::make_pair(6, 6)};

  tree1.merge(tree2);

  auto it2 = vector.begin();
  for (auto it = tree1.begin(); it != tree1.end(); ++it) {
    EXPECT_EQ((*it).first, (*it2).first);
    EXPECT_EQ((*it).second, (*it2).second);
    ++it2;
  }
  tree2.swap(tree1);

  it2 = vector.begin();
  for (auto it = tree2.begin(); it != tree2.end(); ++it) {
    EXPECT_EQ((*it).first, (*it2).first);
    EXPECT_EQ((*it).second, (*it2).second);
    ++it2;
  }
}

TEST(BinaryTreeMapTests, AtAndOperatorTest) {
  s21::BinaryTreeMap<int, int> tree1 = {
      std::make_pair(1, 1), std::make_pair(2, 2), std::make_pair(3, 3)};
  int k = tree1.at(2);
  EXPECT_EQ(k, 2);
  EXPECT_THROW(tree1.at(10), std::out_of_range);

  EXPECT_NO_THROW(tree1[10] = 4);
  k = tree1.at(10);
  EXPECT_EQ(k, 4);
}

TEST_F(BinaryTreeMapTest, ClearTest) { map.clear(); }

TEST(BinaryTreeMapTests, TestErase3) {
  s21::BinaryTreeMap<int, int> map = {std::make_pair(1, 1),
                                      std::make_pair(4, 4)};
  map.erase(map.begin());
  map.erase(map.begin());
  map.insert(std::make_pair(4, 4));
  map.insert(std::make_pair(2, 2));
  map.erase(++map.begin());
  s21::BinaryTreeMap<int, int> map1 = {
      std::make_pair(3, 3), std::make_pair(1, 1), std::make_pair(5, 5),
      std::make_pair(4, 4)};
  map1.erase(++map1.begin());
}

TEST(BinaryTreeMapTests, iteratorTest) {
  s21::BinaryTreeMap<int, int> map = {
      std::make_pair(1, 1), std::make_pair(-2, -2), std::make_pair(2, 2),
      std::make_pair(-3, -3), std::make_pair(3, 3)};
  for (auto it = map.begin(); it != map.end(); ++it) {
    ++it;
    --it;
  };

  for (auto it = map.cbegin(); it != map.cend(); ++it) {
    ++it;
    --it;
  };

  map[2];
}

TEST(BinaryTreeMapTests, throw_test) {
  s21::BinaryTreeMap<int, int> map;
  EXPECT_ANY_THROW(map.at(100));
  s21::BinaryTreeMap<int, int>::SetIterator k =
      s21::BinaryTreeMap<int, int>::SetIterator(nullptr);
  EXPECT_EQ(map.begin(), k);
  s21::BinaryTreeMap<int, int>::ConstSetIterator kj =
      s21::BinaryTreeMap<int, int>::ConstSetIterator(nullptr);
  EXPECT_EQ(map.cbegin(), kj);
}