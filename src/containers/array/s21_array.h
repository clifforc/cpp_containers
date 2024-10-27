#ifndef ARRAY_H
#define ARRAY_H

#include <algorithm>
#include <stdexcept>
#include <utility>

namespace s21 {
template <typename T, std::size_t N>
class Array {
 public:
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = value_type *;
  using const_iterator = const value_type *;
  using size_type = std::size_t;

 private:
  size_type size_;
  value_type arr_[N];

 public:
  Array() noexcept;
  Array(std::initializer_list<value_type> const &items) noexcept;
  Array(const Array &a);
  Array(Array &&a) noexcept;
  ~Array();
  Array<T, N> &operator=(Array &&a) noexcept;
  Array<T, N> &operator=(const Array &a) noexcept;

  reference at(size_type pos);
  reference operator[](size_type pos);
  reference front();
  reference back();
  iterator data() noexcept;

  const_reference at(size_type pos) const;
  const_reference operator[](size_type pos) const;
  const_reference front() const;
  const_reference back() const;
  const_iterator data() const noexcept;

  iterator begin() noexcept;
  iterator end() noexcept;
  const_iterator begin() const noexcept;
  const_iterator cbegin() const noexcept;
  const_iterator end() const noexcept;
  const_iterator cend() const noexcept;

  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  void swap(Array &other) noexcept;
  void fill(const_reference value);
};

template <typename T, std::size_t N>
Array<T, N>::Array() noexcept : size_(N) {
  std::fill(arr_, arr_ + size_, value_type());
}

template <typename T, std::size_t N>
Array<T, N>::Array(std::initializer_list<value_type> const &items) noexcept
    : Array() {
  std::copy(items.begin(), items.end(), arr_);
}

template <typename T, std::size_t N>
Array<T, N>::Array(const Array &a) : size_(a.size_) {
  std::copy(a.arr_, a.arr_ + a.size_, arr_);
}

template <typename T, std::size_t N>
Array<T, N>::Array(Array &&a) noexcept : size_(a.size_) {
  std::move(a.arr_, a.arr_ + a.size_, arr_);
}

template <typename T, std::size_t N>
Array<T, N>::~Array(){};

template <typename T, std::size_t N>
Array<T, N> &Array<T, N>::operator=(Array &&a) noexcept {
  if (this != &a) {
    size_ = a.size_;
    std::move(a.arr_, a.arr_ + a.size_, arr_);
  }
  return *this;
}

template <typename T, std::size_t N>
Array<T, N> &Array<T, N>::operator=(const Array &a) noexcept {
  if (this != &a) {
    size_ = a.size_;
    std::copy(a.arr_, a.arr_ + a.size_, arr_);
  }
  return *this;
}

template <typename T, std::size_t N>
typename Array<T, N>::reference Array<T, N>::at(size_type pos) {
  if (pos >= size_ || size_ == 0) {
    throw std::out_of_range("Index out of range");
  }
  return arr_[pos];
}

template <typename T, std::size_t N>
typename Array<T, N>::const_reference Array<T, N>::at(size_type pos) const {
  if (pos >= size_ || size_ == 0) {
    throw std::out_of_range("Index out of range");
  }
  return arr_[pos];
}

template <typename T, std::size_t N>
typename Array<T, N>::reference Array<T, N>::operator[](size_type pos) {
  return arr_[pos];
}

template <typename T, std::size_t N>
typename Array<T, N>::const_reference Array<T, N>::operator[](
    size_type pos) const {
  return arr_[pos];
}

template <typename T, std::size_t N>
typename Array<T, N>::reference Array<T, N>::front() {
  return arr_[0];
}

template <typename T, std::size_t N>
typename Array<T, N>::const_reference Array<T, N>::front() const {
  return arr_[0];
}

template <typename T, std::size_t N>
typename Array<T, N>::reference Array<T, N>::back() {
  return arr_[size_ - 1];
}

template <typename T, std::size_t N>
typename Array<T, N>::const_reference Array<T, N>::back() const {
  return arr_[size_ - 1];
}

template <typename T, std::size_t N>
typename Array<T, N>::iterator Array<T, N>::data() noexcept {
  return arr_;
}

template <typename T, std::size_t N>
typename Array<T, N>::const_iterator Array<T, N>::data() const noexcept {
  return arr_;
}

template <typename T, std::size_t N>
typename Array<T, N>::iterator Array<T, N>::begin() noexcept {
  return arr_;
}

template <typename T, std::size_t N>
typename Array<T, N>::const_iterator Array<T, N>::begin() const noexcept {
  return arr_;
}

template <typename T, std::size_t N>
typename Array<T, N>::const_iterator Array<T, N>::cbegin() const noexcept {
  return arr_;
}

template <typename T, std::size_t N>
typename Array<T, N>::iterator Array<T, N>::end() noexcept {
  return arr_ + size_;
}

template <typename T, std::size_t N>
typename Array<T, N>::const_iterator Array<T, N>::end() const noexcept {
  return arr_ + size_;
}

template <typename T, std::size_t N>
typename Array<T, N>::const_iterator Array<T, N>::cend() const noexcept {
  return arr_ + size_;
}

template <typename T, std::size_t N>
bool Array<T, N>::empty() const noexcept {
  return size_ == 0;
}

template <typename T, std::size_t N>
typename Array<T, N>::size_type Array<T, N>::size() const noexcept {
  return size_;
}

template <typename T, std::size_t N>
typename Array<T, N>::size_type Array<T, N>::max_size() const noexcept {
  return size_;
}

template <typename T, std::size_t N>
void Array<T, N>::swap(Array &other) noexcept {
  std::swap(arr_, other.arr_);
}

template <typename T, std::size_t N>
void Array<T, N>::fill(const_reference value) {
  std::fill_n(arr_, size_, value);
}
}  // namespace s21

#endif