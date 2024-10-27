#ifndef Queue_H
#define Queue_H

#include <utility>

#include "../list/s21_list.h"

namespace s21 {
template <typename T, typename Container = s21::List<T>>
class Queue {
 public:
  using value_type = typename Container::value_type;
  using reference = typename Container::reference;
  using const_reference = typename Container::const_reference;
  using size_type = typename Container::size_type;

 private:
  Container c_;

 public:
  Queue() = default;
  Queue(std::initializer_list<value_type> const &items) noexcept;
  Queue(const Queue &s) = default;
  Queue(Queue &&s) = default;
  ~Queue() = default;
  Queue<T, Container> &operator=(Queue &&s) noexcept;
  Queue<T, Container> &operator=(const Queue &s) noexcept;

  reference front();
  reference back();
  const_reference front() const;
  const_reference back() const;

  bool empty() const noexcept;
  size_type size() const noexcept;

  void push(const_reference value);
  void pop();
  void swap(Queue &other) noexcept;

  template <typename... Args>
  void insert_many_back(Args &&...args);
};

template <typename T, typename Container>
typename Queue<T, Container>::reference Queue<T, Container>::front() {
  return c_.front();
}

template <typename T, typename Container>
typename Queue<T, Container>::const_reference Queue<T, Container>::front()
    const {
  return c_.front();
}

template <typename T, typename Container>
typename Queue<T, Container>::reference Queue<T, Container>::back() {
  return c_.back();
};

template <typename T, typename Container>
typename Queue<T, Container>::const_reference Queue<T, Container>::back()
    const {
  return c_.back();
};

template <typename T, typename Container>
Queue<T, Container>::Queue(
    std::initializer_list<value_type> const &items) noexcept
    : Queue() {
  for (auto i = items.begin(); i < items.end(); ++i) {
    c_.push_back(*i);
  }
}

template <typename T, typename Container>
Queue<T, Container> &Queue<T, Container>::operator=(Queue &&s) noexcept {
  if (this != &s) {
    c_ = std::move(s.c_);
  }
  return *this;
}

template <typename T, typename Container>
Queue<T, Container> &Queue<T, Container>::operator=(const Queue &s) noexcept {
  if (this != &s) {
    c_ = s.c_;
  }
  return *this;
}

template <typename T, typename Container>
bool Queue<T, Container>::empty() const noexcept {
  return c_.size() == 0;
}

template <typename T, typename Container>
typename Queue<T, Container>::size_type Queue<T, Container>::size()
    const noexcept {
  return c_.size();
}

template <typename T, typename Container>
void Queue<T, Container>::push(const_reference value) {
  c_.push_back(value);
}

template <typename T, typename Container>
void Queue<T, Container>::pop() {
  c_.pop_front();
}

template <typename T, typename Container>
void Queue<T, Container>::swap(Queue &other) noexcept {
  std::swap(c_, other.c_);
}

template <typename T, typename Container>
template <typename... Args>
void Queue<T, Container>::insert_many_back(Args &&...args) {
  c_.insert_many(c_.cend(), args...);
}
}  // namespace s21

#endif