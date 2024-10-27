#pragma once
#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <utility>

namespace s21 {
template <typename T>
class Vector {
 public:  // members
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = T*;
  using const_iterator = const T*;
  using size_type = std::size_t;

 private:  // attributes
  size_type size_;
  size_type capacity_;
  value_type* data_;

 public:  // constructors
  Vector();
  explicit Vector(size_type n);
  Vector(std::initializer_list<value_type> const& items);
  Vector(const Vector& v);      // copy ctor
  Vector(Vector&& v) noexcept;  // move ctor
  ~Vector();

  Vector& operator=(Vector&& v) noexcept;
  Vector& operator=(const Vector& v);

 public:  // accessors
  reference at(size_type pos);
  const_reference at(size_type pos) const;
  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;
  reference front();
  const_reference front() const;
  reference back();
  const_reference back() const;
  T* data() noexcept;
  const T* data() const noexcept;

 public:  // iterators
  iterator begin() noexcept;
  const_iterator begin() const noexcept;
  const_iterator cbegin() const noexcept;
  iterator end() noexcept;
  const_iterator end() const noexcept;
  const_iterator cend() const noexcept;

 public:  // capacity
  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;
  void reserve(size_type new_cap);
  size_type capacity() const noexcept;
  void shrink_to_fit();

 public:  // vector modifiers
  void clear() noexcept;
  iterator insert(const_iterator pos, const_reference value);

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args);
  template <typename... Args>
  void insert_many_back(Args&&... args);
  iterator erase(const_iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(Vector& other) noexcept;
};

template <typename T>
Vector<T>::Vector() : size_(0), capacity_(0), data_(nullptr) {}

template <typename T>
Vector<T>::Vector(size_type n) : size_(n), capacity_(n), data_(new T[n]) {}

template <typename T>
Vector<T>::Vector(std::initializer_list<value_type> const& items)
    : size_(items.size()), capacity_(items.size()), data_(new T[items.size()]) {
  std::copy(items.begin(), items.end(), data_);
}

template <typename T>
Vector<T>::Vector(const Vector& v)
    : size_(v.size_), capacity_(v.capacity_), data_(new T[v.size_]) {
  std::copy(v.data_, v.data_ + v.size_, data_);
}

template <typename T>
Vector<T>::Vector(Vector&& v) noexcept
    : size_(v.size_), capacity_(v.capacity_), data_(v.data_) {
  v.size_ = 0;
  v.capacity_ = 0;
  v.data_ = nullptr;
}

template <typename T>
Vector<T>::~Vector() {
  delete[] data_;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector&& v) noexcept {
  if (this != &v) {
    this->~Vector();

    size_ = v.size_;
    capacity_ = v.capacity_;
    data_ = std::move(v.data_);

    v.size_ = 0;
    v.capacity_ = 0;
    v.data_ = nullptr;
  }
  return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& v) {
  if (this != &v) {
    delete[] data_;
    size_ = v.size_;
    capacity_ = v.capacity_;
    data_ = new T[v.size_];
    if (!data_) {
      throw std::bad_alloc();
    }
    std::copy(v.data_, v.data_ + v.size_, data_);
  }
  return *this;
}

template <typename T>
typename Vector<T>::reference Vector<T>::at(size_type pos) {
  if (pos >= size_) {
    throw std::out_of_range("Index out of range");
  }
  return data_[pos];
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::at(size_type pos) const {
  if (pos >= size_) {
    throw std::out_of_range("Index out of range");
  }
  return data_[pos];
}

template <typename T>
typename Vector<T>::reference Vector<T>::operator[](size_type pos) {
  return data_[pos];
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::operator[](size_type pos) const {
  return data_[pos];
}

template <typename T>
typename Vector<T>::reference Vector<T>::front() {
  return data_[0];
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::front() const {
  return data_[0];
}

template <typename T>
typename Vector<T>::reference Vector<T>::back() {
  return data_[size_ - 1];
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::back() const {
  return data_[size_ - 1];
}

template <typename T>
typename Vector<T>::iterator Vector<T>::data() noexcept {
  return data_;
}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::data() const noexcept {
  return data_;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::begin() noexcept {
  return data_;
}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::begin() const noexcept {
  return data_;
}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::cbegin() const noexcept {
  return data_;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::end() noexcept {
  return data_ + size_;
}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::end() const noexcept {
  return data_ + size_;
}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::cend() const noexcept {
  return data_ + size_;
}

template <typename T>
bool Vector<T>::empty() const noexcept {
  return size_ == 0;
}

template <typename T>
typename Vector<T>::size_type Vector<T>::size() const noexcept {
  return size_;
}

template <typename T>
typename Vector<T>::size_type Vector<T>::max_size() const noexcept {
  return std::numeric_limits<std::size_t>::max() / sizeof(value_type);
}

template <typename T>
void Vector<T>::reserve(size_type new_cap) {
  if (new_cap <= capacity_) {
    throw std::length_error("Error length of new capacity");
  }
  if (new_cap > this->max_size()) {
    throw std::length_error("Error length");
  }
  T* new_data = new value_type[new_cap];
  std::copy(data_, data_ + size_, new_data);
  delete[] data_;
  data_ = new_data;
  capacity_ = new_cap;
}

template <typename T>
typename Vector<T>::size_type Vector<T>::capacity() const noexcept {
  return capacity_;
}

template <typename T>
void Vector<T>::shrink_to_fit() {
  if (size_ < capacity_) {
    iterator new_data = new value_type[size_];
    std::copy(data_, data_ + size_, new_data);
    delete[] data_;
    data_ = new_data;
    capacity_ = size_;
  }
}

template <typename T>
void Vector<T>::clear() noexcept {
  size_ = 0;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::insert(const_iterator pos,
                                               const_reference value) {
  size_type index = pos - data_;

  if (index > size_) {
    throw std::out_of_range("Index is out of range");
  }

  if (size_ + 1 > capacity_) {
    reserve(capacity_ ? capacity_ * 2 : 1);
  }

  std::copy_backward(data_ + index, data_ + size_, data_ + size_ + 1);
  data_[index] = value;
  ++size_;
  return data_ + index;
}

template <typename T>
template <typename... Args>
typename Vector<T>::iterator Vector<T>::insert_many(const_iterator pos,
                                                    Args&&... args) {
  int count = sizeof...(args);
  size_t index = pos - data_;

  if (index > size_) {
    throw std::out_of_range("Index is out of range");
  }

  if (size_ + count > capacity_) {
    reserve(capacity_ ? (capacity_ + count) * 2 : 1);
  }

  std::copy_backward(data_ + index, data_ + size_, data_ + size_ + 1);

  ((data_[index++] = std::forward<T>(args)), ...);
  size_ += count;
  return data_ + index - count;
}
template <typename T>
template <typename... Args>
void Vector<T>::insert_many_back(Args&&... args) {
  insert_many(cend(), args...);
}

template <typename T>
typename Vector<T>::iterator Vector<T>::erase(const_iterator pos) {
  size_type index = pos - data_;
  if (index >= size_) {
    throw std::out_of_range("Index out of range");
  }
  for (size_type i = index; i < size_ - 1; ++i) {
    data_[i] = data_[i + 1];
  }
  --size_;
  if (index == size_) {
    return end();
  } else {
    return data_ + index;
  }
}

template <typename T>
void Vector<T>::push_back(const_reference value) {
  if (size_ >= capacity_) {
    reserve(capacity_ == 0 ? 1 : capacity_ * 2);
  }
  ++size_;
  this->back() = value;
}

template <typename T>
void Vector<T>::pop_back() {
  --size_;
}

template <typename T>
void Vector<T>::swap(Vector& other) noexcept {
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
  std::swap(data_, other.data_);
}
}  // namespace s21