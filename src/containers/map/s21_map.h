#pragma once
#include "s21_binary_tree_map.h"
namespace s21 {

template <typename Key, typename T>
class Map {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = std::size_t;
  using iterator = typename BinaryTreeMap<Key, T>::iterator;
  using const_iterator = typename BinaryTreeMap<Key, T>::const_iterator;

 private:
  BinaryTreeMap<Key, T> tree_;

 public:
  Map();
  Map(std::initializer_list<value_type> const& items);
  Map(const Map& s);
  Map(Map&& s);
  ~Map() = default;

 public:
  Map& operator=(Map&& b);
  Map& operator=(Map& b);

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
  std::pair<iterator, bool> insert(const Key& key, const T& obj);
  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj);
  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args);
  void erase(iterator pos);
  void swap(Map& other);
  void merge(Map& other);

 public:
  bool contains(const Key& key);

 public:
  T& at(const Key& key);
  T& operator[](const Key& key);
};

// Constructors
template <typename Key, typename T>
Map<Key, T>::Map() : tree_(){};

template <typename Key, typename T>
Map<Key, T>::Map(std::initializer_list<value_type> const& items)
    : tree_(items) {}

template <typename Key, typename T>
Map<Key, T>::Map(const Map& s) : tree_(s.tree_){};

template <typename Key, typename T>
Map<Key, T>::Map(Map&& s) : tree_(s.tree_) {}

// OPERATORS
template <typename Key, typename T>
class Map<Key, T>::Map& Map<Key, T>::operator=(Map& b) {
  tree_.operator=(b.tree_);
  return *this;
}

template <typename Key, typename T>
class Map<Key, T>::Map& Map<Key, T>::operator=(Map&& b) {
  tree_.operator=(b.tree_);

  return *this;
}

// Iters
template <typename Key, typename T>
typename Map<Key, T>::iterator Map<Key, T>::begin() {
  return tree_.begin();
}

template <typename Key, typename T>
typename Map<Key, T>::iterator Map<Key, T>::end() {
  return tree_.end();
}

template <typename Key, typename T>
bool Map<Key, T>::empty() {
  return tree_.empty();
}

template <typename Key, typename T>
typename Map<Key, T>::size_type Map<Key, T>::size() {
  return tree_.size();
}

template <typename Key, typename T>
typename Map<Key, T>::size_type Map<Key, T>::max_size() {
  return tree_.max_size();
}

template <typename Key, typename T>
void Map<Key, T>::clear() {
  tree_.clear();
}

// Modife
template <typename Key, typename T>
std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::insert(
    const_reference value) {
  return tree_.insert(value);
}

template <typename Key, typename T>
std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::insert(
    const Key& key, const T& obj) {
  return tree_.insert(key, obj);
}

template <typename Key, typename T>
std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::insert_or_assign(
    const Key& key, const T& obj) {
  return tree_.insert_or_assign(key, obj);
}

template <typename Key, typename T>
void Map<Key, T>::erase(iterator pos) {
  tree_.erase(pos);
}

template <typename Key, typename T>
void Map<Key, T>::swap(Map& other) {
  tree_.swap(other.tree_);
}

template <typename Key, typename T>
void Map<Key, T>::merge(Map& other) {
  tree_.merge(other.tree_);
}

template <typename Key, typename T>
bool Map<Key, T>::contains(const Key& key) {
  for (iterator it = tree_.begin(); it != tree_.end(); ++it) {
    if ((*it).first == key) {
      return true;  // Возвращаем итератор на найденный элемент
    }
  }
  return false;  // Если элемент не найден
}

template <typename Key, typename T>
T& Map<Key, T>::at(const Key& key) {
  return tree_.at(key);
}

template <typename Key, typename T>
T& Map<Key, T>::operator[](const Key& key) {
  return tree_[key];
}

template <typename Key, typename T>
template <typename... Args>
std::vector<std::pair<typename Map<Key, T>::iterator, bool>>
Map<Key, T>::insert_many(Args&&... args) {
  std::vector<std::pair<iterator, bool>> results;
  for (const auto& arg : {args...}) {
    results.push_back(insert(arg));
  }
  return results;
}

}  // namespace s21