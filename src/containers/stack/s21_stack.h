#ifndef STACK_H
#define STACK_H

#include <utility>

#include "../vector/s21_vector.h"

namespace s21 {
template <typename T, typename Container = s21::Vector<T>>
class Stack {
 public:
  using value_type = typename Container::value_type;
  using reference = typename Container::reference;
  using const_reference = typename Container::const_reference;
  using size_type = typename Container::size_type;

 private:
  Container c_;

 public:
  Stack() = default;
  Stack(std::initializer_list<value_type> const &items) noexcept;
  Stack(const Stack &s) = default;
  Stack(Stack &&s) = default;
  ~Stack() = default;
  Stack<T, Container> &operator=(Stack &&s) noexcept;
  Stack<T, Container> &operator=(const Stack &s) noexcept;

  reference top();
  const_reference top() const;

  bool empty() const noexcept;
  size_type size() const noexcept;

  void push(const_reference value);
  void pop();
  void swap(Stack &other) noexcept;

  template <typename... Args>
  void insert_many_back(Args &&...args);
};

template <typename T, typename Container>
typename Stack<T, Container>::reference Stack<T, Container>::top() {
  return c_.back();
};

template <typename T, typename Container>
typename Stack<T, Container>::const_reference Stack<T, Container>::top() const {
  return c_.back();
};

template <typename T, typename Container>
Stack<T, Container>::Stack(
    std::initializer_list<value_type> const &items) noexcept
    : Stack() {
  for (size_type i = 0; i < items.size(); ++i) {
    c_.insert(c_.begin() + i, *(items.begin() + i));
  }
}

template <typename T, typename Container>
Stack<T, Container> &Stack<T, Container>::operator=(Stack &&s) noexcept {
  if (this != &s) {
    c_ = std::move(s.c_);
  }
  return *this;
}

template <typename T, typename Container>
Stack<T, Container> &Stack<T, Container>::operator=(const Stack &s) noexcept {
  if (this != &s) {
    c_ = s.c_;
  }
  return *this;
}

template <typename T, typename Container>
bool Stack<T, Container>::empty() const noexcept {
  return c_.size() == 0;
}

template <typename T, typename Container>
typename Stack<T, Container>::size_type Stack<T, Container>::size()
    const noexcept {
  return c_.size();
}

template <typename T, typename Container>
void Stack<T, Container>::push(const_reference value) {
  c_.push_back(value);
}

template <typename T, typename Container>
void Stack<T, Container>::pop() {
  c_.pop_back();
}

template <typename T, typename Container>
void Stack<T, Container>::swap(Stack &other) noexcept {
  std::swap(c_, other.c_);
}

template <typename T, typename Container>
template <typename... Args>
void Stack<T, Container>::insert_many_back(Args &&...args) {
  c_.insert_many(c_.cend(), args...);
}
}  // namespace s21

#endif