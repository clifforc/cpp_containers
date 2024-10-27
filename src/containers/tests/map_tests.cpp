#include <gtest/gtest.h>

#include "../map/s21_map.h"

class MapTest : public ::testing::Test {
 public:
  s21::Map<int, int> map = {std::make_pair(1, 1), std::make_pair(2, 2),
                            std::make_pair(3, 3), std::make_pair(-1, 4)};
  s21::Map<int, int> map_copy = map;
  s21::Map<int, int> other_map = {};
  std::vector<std::pair<int, int>> vector = {
      std::make_pair(-1, 4), std::make_pair(1, 1), std::make_pair(2, 2),
      std::make_pair(3, 3)};
  // Сортируем копию

 protected:
  void SetUp() override {}

  void TearDown() override {}
};

TEST(MapTests, ConstructorsTest) {
  // init const
  s21::Map<int, int> a = {std::make_pair(1, 1), std::make_pair(2, 2),
                          std::make_pair(3, 3), std::make_pair(-1, 4)};
  s21::Map<int, int> a_copy1 = a;
  s21::Map<int, int> a_copy2 = a;
  // copy const
  s21::Map<int, int> b = a;
  // move const
  s21::Map<int, int> c = std::move(a_copy1);
  // operator=
  s21::Map<int, int> d;
  d = a;
  // move operator=
  s21::Map<int, int> e;
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

TEST_F(MapTest, InsertTest) {
  std::pair<s21::Map<int, int>::iterator, bool> it_retured =
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

TEST_F(MapTest, EraseTest) {
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
}

TEST_F(MapTest, CapacityTest) {
  s21::Map<int, int> empty_map;
  EXPECT_EQ(map.empty(), false);
  EXPECT_EQ(empty_map.empty(), true);
  std::size_t count = 4;
  std::size_t empty_count = 0;
  EXPECT_EQ(map.size(), count);
  EXPECT_EQ(empty_map.size(), empty_count);
}

TEST_F(MapTest, ModifiersTest) {
  map.clear();
  EXPECT_EQ(map.empty(), true);
}

TEST_F(MapTest, SwapMergeTest) {
  s21::Map<int, int> tree1 = {std::make_pair(1, 1), std::make_pair(2, 2),
                              std::make_pair(3, 3)};
  s21::Map<int, int> tree2 = {std::make_pair(3, 4), std::make_pair(5, 5),
                              std::make_pair(6, 6)};
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

TEST(MapTests, AtAndOperatorTest) {
  s21::Map<int, int> tree1 = {std::make_pair(1, 1), std::make_pair(2, 2),
                              std::make_pair(3, 3)};
  int k = tree1.at(2);
  EXPECT_EQ(k, 2);
  EXPECT_THROW(tree1.at(10), std::out_of_range);

  EXPECT_NO_THROW(tree1[10] = 4);
  k = tree1.at(10);
  EXPECT_EQ(k, 4);
}

TEST_F(MapTest, ClearTest) { map.clear(); }

TEST(MapTests, ManyInsertTest) {
  s21::Map<int, int> map;
  auto t = map.insert_many(std::make_pair(1, 1), std::make_pair(2, 2));
  EXPECT_EQ((*(t.at(0).first)).first, 1);
  EXPECT_EQ((*(t.at(1).first)).first, 2);
}

TEST_F(MapTest, BoolTests) {
  s21::Map<int, int> map = {std::make_pair(1, 1)};
  bool kek = map.max_size();
  bool lol = map.contains(1);
  bool not_hehe = map.contains(150000000);
  EXPECT_TRUE(kek);
  EXPECT_TRUE(lol);
  EXPECT_FALSE(not_hehe);
}