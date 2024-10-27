#pragma once
#include "s21_binary_tree_multiset.h"
namespace s21 {

template <typename Key>
class Multiset {
 public:
  class MultisetIterator;
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename BinaryTreeMultiset<Key>::iterator;
  using const_iterator = typename BinaryTreeMultiset<Key>::const_iterator;
  using size_type = size_t;

 private:
  BinaryTreeMultiset<Key> tree_;

 public:
  Multiset();
  Multiset(std::initializer_list<value_type> const& items);
  Multiset(const Multiset& s);
  Multiset(Multiset&& s);
  ~Multiset() = default;

 public:
  Multiset& operator=(Multiset&& b);
  Multiset& operator=(Multiset& b);

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
  void swap(Multiset& other);
  void merge(Multiset& other);

 public:
  iterator find(const Key& key);
  bool contains(const Key& key);

  iterator lower_bound(const Key& key);
  iterator upper_bound(const Key& key);
  size_type count(const Key& key) const;
};

// Constructors
template <typename Key>
Multiset<Key>::Multiset() : tree_(){};

template <typename Key>
Multiset<Key>::Multiset(std::initializer_list<value_type> const& items)
    : tree_(items) {}

template <typename Key>
Multiset<Key>::Multiset(const Multiset& s) : tree_(s.tree_){};

template <typename Key>
Multiset<Key>::Multiset(Multiset&& s) : tree_(s.tree_) {}

// OPERATORS
template <typename Key>
class Multiset<Key>::Multiset& Multiset<Key>::operator=(Multiset& b) {
  tree_.operator=(b.tree_);
  return *this;
}

template <typename Key>
class Multiset<Key>::Multiset& Multiset<Key>::operator=(Multiset&& b) {
  tree_.operator=(b.tree_);

  return *this;
}

// Iters
template <typename Key>
typename Multiset<Key>::iterator Multiset<Key>::begin() {
  return tree_.begin();
}

template <typename Key>
typename Multiset<Key>::iterator Multiset<Key>::end() {
  return tree_.end();
}

template <typename Key>
bool Multiset<Key>::empty() {
  return tree_.empty();
}

template <typename Key>
typename Multiset<Key>::size_type Multiset<Key>::size() {
  return tree_.size();
}

template <typename Key>
typename Multiset<Key>::size_type Multiset<Key>::max_size() {
  return tree_.max_size();
}

template <typename Key>
void Multiset<Key>::clear() {
  tree_.clear();
}

// Modife
template <typename Key>
std::pair<typename Multiset<Key>::iterator, bool> Multiset<Key>::insert(
    const_reference value) {
  // Если элемент не найден, вставляем его
  tree_.insert(value);
  // Возвращаем итератор на вставленный элемент и true
  auto it = find(value);  // После вставки находим его местоположение
  return std::make_pair(it, true);
}

template <typename T>
template <typename... Args>
std::vector<std::pair<typename Multiset<T>::iterator, bool>>
Multiset<T>::insert_many(Args&&... args) {
  std::vector<std::pair<iterator, bool>> results;
  for (const auto& arg : {args...}) {
    results.push_back(insert(arg));
  }
  return results;
}

template <typename Key>
void Multiset<Key>::erase(iterator pos) {
  tree_.erase(pos);
}

template <typename Key>
void Multiset<Key>::swap(Multiset& other) {
  tree_.swap(other.tree_);
}

template <typename Key>
void Multiset<Key>::merge(Multiset& other) {
  tree_.merge(other.tree_);
}

template <typename Key>
typename Multiset<Key>::iterator Multiset<Key>::find(const Key& key) {
  for (iterator it = tree_.begin(); it != tree_.end(); ++it) {
    if (*it == key) {
      return it;  // Возвращаем итератор на найденный элемент
    }
  }
  return tree_.end();  // Если элемент не найден
}

template <typename Key>
bool Multiset<Key>::contains(const Key& key) {
  for (iterator it = tree_.begin(); it != tree_.end(); ++it) {
    if (*it == key) {
      return true;  // Возвращаем итератор на найденный элемент
    }
  }
  return false;  // Если элемент не найден
}

template <typename Key>
typename Multiset<Key>::iterator Multiset<Key>::lower_bound(const Key& key) {
  auto it = tree_.begin();
  auto end = tree_.end();
  while (it != end && *it < key) ++it;
  return it;
}

template <typename Key>
typename Multiset<Key>::iterator Multiset<Key>::upper_bound(const Key& key) {
  auto it = lower_bound(key);
  auto end = tree_.end();
  while (it != end && *it == key) ++it;
  return it;
}

template <typename Key>
typename Multiset<Key>::size_type Multiset<Key>::count(const Key& key) const {
  const_iterator it = tree_.cbegin();
  const_iterator end = tree_.cend();
  size_type count = 0;
  for (; it != end; ++it) {
    if (*it == key) ++count;
  }
  return count;
}

}  // namespace s21