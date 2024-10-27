#include <gtest/gtest.h>

#include "../queue/s21_queue.h"

class QueueTests : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(QueueTests, DefaultConstructorPushPopFront) {
  s21::Queue<int> queue;
  queue.push(100500);
  int num = 1;
  queue.push(num);
  queue.push(100502);
  queue.push(100503);
  EXPECT_EQ(queue.back(), 100503);
  queue.pop();
  EXPECT_EQ(queue.front(), 1);
  queue.pop();
  EXPECT_EQ(queue.front(), 100502);
}

TEST_F(QueueTests, InitializerListConstructor) {
  s21::Queue<int> queue{1, 2, 3, 4, 5};
  EXPECT_EQ(queue.front(), 1);
  s21::Queue<int> queue1 = {1, 2, 3, 4, 6};
  EXPECT_EQ(queue1.back(), 6);
}

TEST_F(QueueTests, CopyConstructor) {
  s21::Queue<int> queue1 = {1, 2, 3, 4, 5};
  s21::Queue<int> queue2(queue1);
  EXPECT_EQ(queue1.front(), queue2.front());
}

TEST_F(QueueTests, MoveConstructor) {
  s21::Queue<int> queue1 = {1, 2, 3, 4, 5};
  s21::Queue<int> queue2(std::move(queue1));
  EXPECT_EQ(queue2.back(), 5);
}

TEST_F(QueueTests, MoveAssignmentOperator) {
  s21::Queue<int> queue1 = {1, 2, 3, 4, 5};
  s21::Queue<int> queue2{};
  queue2 = std::move(queue1);
  EXPECT_EQ(queue2.back(), 5);
}

TEST_F(QueueTests, CopyAssignmentOperator) {
  s21::Queue<int> queue1 = {1, 2, 3, 4, 5};
  s21::Queue<int> queue2{};
  queue2 = queue1;
  EXPECT_EQ(queue2.back(), 5);
}

TEST_F(QueueTests, Empty) {
  s21::Queue<int> queue{};
  EXPECT_TRUE(queue.empty());
  s21::Queue<int> queue1 = {1, 2, 3, 4, 5};
  EXPECT_FALSE(queue1.empty());
}

TEST_F(QueueTests, Size) {
  s21::Queue<char> queue1{};
  EXPECT_EQ(static_cast<int>(queue1.size()), 0);
  queue1.push('h');
  EXPECT_EQ(static_cast<int>(queue1.size()), 1);
}

TEST_F(QueueTests, Swap) {
  s21::Queue<char> queue = {'G', 'f', 'G'};
  s21::Queue<char> queue1 = {'M', 'M', 'P'};
  s21::Queue<char> expected_queue = {'M', 'M', 'P'};
  s21::Queue<char> expected_queue1 = {'G', 'f', 'G'};
  queue.swap(queue1);
  for (int i = 0; i < 3; ++i) {
    EXPECT_EQ(queue.front(), expected_queue.front());
    queue.pop();
    expected_queue.pop();
    EXPECT_EQ(queue1.front(), expected_queue1.front());
    queue1.pop();
    expected_queue1.pop();
  }
}

TEST_F(QueueTests, InsertManyBack) {
  s21::Queue<int> queue = {1, 2, 3};
  queue.insert_many_back(4, 5, 6);
  s21::Queue<int> queue_expected{1, 2, 3, 4, 5, 6};
  for (int i = 0; i < 6; ++i) {
    EXPECT_EQ(queue.front(), queue_expected.front());
  }
}