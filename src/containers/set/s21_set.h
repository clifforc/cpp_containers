#pragma once
#include "s21_set_binary_tree.h"
namespace s21 {

template <typename Key>
class Set {
 public:
  class SetIterator;
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename BinaryTree<Key>::iterator;
  using size_type = size_t;

 private:
  BinaryTree<Key> tree_;

 public:
  Set();
  Set(std::initializer_list<value_type> const& items);
  Set(const Set& s);
  Set(Set&& s);
  ~Set() = default;

 public:
  Set& operator=(Set&& b);
  Set& operator=(Set& b);

 public:
  iterator begin();
  iterator end();

 public:
  bool empty();
  size_type size();
  size_type max_size();

 public:
  void clear();
  std::pair<iterator, bool> insert(const_reference value);
  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args);
  void erase(iterator pos);
  void swap(Set& other);
  void merge(Set& other);

 public:
  iterator find(const Key& key);
  bool contains(const Key& key);
};

// Constructors
template <typename Key>
Set<Key>::Set() : tree_(){};

template <typename Key>
Set<Key>::Set(std::initializer_list<value_type> const& items) : tree_(items) {}

template <typename Key>
Set<Key>::Set(const Set& s) : tree_(s.tree_){};

template <typename Key>
Set<Key>::Set(Set&& s) : tree_(s.tree_) {}

// OPERATORS
template <typename Key>
class Set<Key>::Set& Set<Key>::operator=(Set& b) {
  tree_.operator=(b.tree_);
  return *this;
}

template <typename Key>
class Set<Key>::Set& Set<Key>::operator=(Set&& b) {
  tree_.operator=(b.tree_);

  return *this;
}

// Iters
template <typename Key>
typename Set<Key>::iterator Set<Key>::begin() {
  return tree_.begin();
}

template <typename Key>
typename Set<Key>::iterator Set<Key>::end() {
  return tree_.end();
}

template <typename Key>
bool Set<Key>::empty() {
  return tree_.empty();
}

template <typename Key>
typename Set<Key>::size_type Set<Key>::size() {
  return tree_.size();
}

template <typename Key>
typename Set<Key>::size_type Set<Key>::max_size() {
  return tree_.max_size();
}

template <typename Key>
void Set<Key>::clear() {
  tree_.clear();
}

// Modife
template <typename Key>
std::pair<typename Set<Key>::iterator, bool> Set<Key>::insert(
    const_reference value) {
  // Сначала пытаемся найти элемент
  iterator it = find(value);
  if (it != end()) {
    // Если элемент найден, возвращаем итератор на него и false
    return std::make_pair(it, false);
  } else {
    // Если элемент не найден, вставляем его
    tree_.insert(value);
    // Возвращаем итератор на вставленный элемент и true
    it = find(value);  // После вставки находим его местоположение
    return std::make_pair(it, true);
  }
}

template <typename T>
template <typename... Args>
std::vector<std::pair<typename Set<T>::iterator, bool>> Set<T>::insert_many(
    Args&&... args) {
  std::vector<std::pair<iterator, bool>> results;
  for (const auto& arg : {args...}) {
    results.push_back(insert(arg));
  }
  return results;
}

template <typename Key>
void Set<Key>::erase(iterator pos) {
  tree_.erase(pos);
}

template <typename Key>
void Set<Key>::swap(Set& other) {
  tree_.swap(other.tree_);
}

template <typename Key>
void Set<Key>::merge(Set& other) {
  tree_.merge(other.tree_);
}

template <typename Key>
typename Set<Key>::iterator Set<Key>::find(const Key& key) {
  for (iterator it = tree_.begin(); it != tree_.end(); ++it) {
    if (*it == key) {
      return it;  // Возвращаем итератор на найденный элемент
    }
  }
  return tree_.end();  // Если элемент не найден
}

template <typename Key>
bool Set<Key>::contains(const Key& key) {
  for (iterator it = tree_.begin(); it != tree_.end(); ++it) {
    if (*it == key) {
      return true;  // Возвращаем итератор на найденный элемент
    }
  }
  return false;  // Если элемент не найден
}

}  // namespace s21