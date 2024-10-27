#include <gtest/gtest.h>

#include "../stack/s21_stack.h"

class StackTests : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(StackTests, DefaultConstructorPushPopTop) {
  s21::Stack<int> stack;
  stack.push(100500);
  int num = 1;
  stack.push(num);
  stack.push(100502);
  stack.push(100503);
  EXPECT_EQ(stack.top(), 100503);
  stack.pop();
  EXPECT_EQ(stack.top(), 100502);
  stack.pop();
  EXPECT_EQ(stack.top(), 1);
}

TEST_F(StackTests, InitializerListConstructor) {
  const s21::Stack<int> stack{1, 2, 3, 4, 5};
  EXPECT_EQ(stack.top(), 5);
  s21::Stack<int> stack1 = {1, 2, 3, 4, 6};
  EXPECT_EQ(stack1.top(), 6);
}

TEST_F(StackTests, CopyConstructor) {
  s21::Stack<int> stack1 = {1, 2, 3, 4, 5};
  s21::Stack<int> stack2(stack1);
  EXPECT_EQ(stack1.top(), stack2.top());
  stack1.pop();
  EXPECT_NE(stack1.top(), stack2.top());
}

TEST_F(StackTests, MoveConstructor) {
  s21::Stack<int> stack1 = {1, 2, 3, 4, 5};
  s21::Stack<int> stack2(std::move(stack1));
  EXPECT_EQ(stack2.top(), 5);
}

TEST_F(StackTests, MoveAssignmentOperator) {
  s21::Stack<int> stack1 = {1, 2, 3, 4, 5};
  s21::Stack<int> stack2{};
  stack2 = std::move(stack1);
  for (int i = 5; i > 0; --i) {
    EXPECT_EQ(stack2.top(), i);
    stack2.pop();
  }
}

TEST_F(StackTests, CopyAssignmentOperator) {
  s21::Stack<int> stack1 = {1, 2, 3, 4, 5};
  s21::Stack<int> stack2{};
  stack2 = stack1;
  for (int i = 5; i > 0; --i) {
    EXPECT_EQ(stack2.top(), i);
    stack2.pop();
  }
}

TEST_F(StackTests, Empty) {
  s21::Stack<int> stack{};
  EXPECT_TRUE(stack.empty());
  s21::Stack<int> stack1 = {1, 2, 3, 4, 5};
  EXPECT_FALSE(stack1.empty());
}

TEST_F(StackTests, Size) {
  s21::Stack<char> stack1{};
  EXPECT_EQ(static_cast<int>(stack1.size()), 0);
  stack1.push('h');
  EXPECT_EQ(static_cast<int>(stack1.size()), 1);
}

TEST_F(StackTests, Swap) {
  s21::Stack<char> stack = {'G', 'f', 'G'};
  s21::Stack<char> stack1 = {'M', 'M', 'P'};
  s21::Stack<char> expected_stack = {'M', 'M', 'P'};
  s21::Stack<char> expected_stack1 = {'G', 'f', 'G'};
  stack.swap(stack1);
  for (int i = 0; i < 3; ++i) {
    EXPECT_EQ(stack.top(), expected_stack.top());
    stack.pop();
    expected_stack.pop();
    EXPECT_EQ(stack1.top(), expected_stack1.top());
    stack1.pop();
    expected_stack1.pop();
  }
}

TEST_F(StackTests, InsertManyBack) {
  s21::Stack<int> stack = {1, 2, 3};
  stack.insert_many_back(4, 5, 6);
  s21::Stack<int> stack_expected{1, 2, 3, 4, 5, 6};
  for (int i = 0; i < 6; ++i) {
    EXPECT_EQ(stack.top(), stack_expected.top());
  }
}