#pragma once
#include <iostream>
#include <vector>
namespace s21 {
template <typename Key, typename T>
class BinaryTreeMap {
 public:
  // Iterator
  class SetIterator;
  class ConstSetIterator;

  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = std::size_t;
  using iterator = SetIterator;
  using const_iterator = ConstSetIterator;

 private:  // attributes
  size_type size_;
  struct Node {
    value_type data_;
    Node* left;
    Node* right;
    Node* parent;

    Node(const_reference data, Node* parent_c = nullptr)
        : data_(data), left(nullptr), right(nullptr), parent(parent_c) {}
  };

  Node* root_;

 public:  // constructors
  BinaryTreeMap();
  BinaryTreeMap(std::initializer_list<value_type> const& items);
  BinaryTreeMap(const BinaryTreeMap& b);
  BinaryTreeMap(BinaryTreeMap&& b);
  ~BinaryTreeMap();

 public:
  BinaryTreeMap& operator=(BinaryTreeMap&& b);
  BinaryTreeMap& operator=(BinaryTreeMap& b);

 public:
  // addition foo
  std::pair<iterator, bool> insert(const_reference data);
  std::pair<iterator, bool> insert(const Key& key, const T& obj);
  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj);
  void erase(iterator pos);
  bool empty();
  void swap(BinaryTreeMap& other);
  void merge(BinaryTreeMap& other);
  size_type size();
  size_type max_size();
  void clear();

  // Вспомогательные функции
 private:
  void delete_tree(Node*& node);
  std::pair<iterator, bool> insert(Node*& node, Node* parent_node,
                                   const_reference data, bool assign);
  void replace_node(Node* old_node, Node* new_node);
  Node* find_min(Node* node) const;
  Node* find_node(Node* node, const Key& key) const;

 public:  // iterators
  iterator begin();
  const_iterator cbegin() const;
  iterator end();
  const_iterator cend() const;

 public:
  T& at(const Key& key);
  T& operator[](const Key& key);
};

template <typename Key, typename T>
class BinaryTreeMap<Key, T>::SetIterator {
 private:
  typename BinaryTreeMap<Key, T>::Node* current;  // Указатель на текущий узел

 public:
  // Конструктор
  SetIterator(typename BinaryTreeMap<Key, T>::Node* node);

  // Оператор разыменования
  typename BinaryTreeMap<Key, T>::value_type operator*();

  // Оператор инкремента
  SetIterator& operator++();
  SetIterator& operator--();
  bool operator==(const SetIterator& other) const;
  bool operator!=(const SetIterator& other) const;

  typename BinaryTreeMap<Key, T>::Node* get_node();
};

template <typename Key, typename T>
class BinaryTreeMap<Key, T>::ConstSetIterator {
 private:
  const typename BinaryTreeMap<Key, T>::Node*
      current;  // Константный указатель на текущий узел

 public:
  // Конструктор
  ConstSetIterator(const typename BinaryTreeMap<Key, T>::Node* node);

  // Оператор разыменования
  typename BinaryTreeMap<Key, T>::value_type operator*() const;

  // Оператор инкремента (префиксный)
  ConstSetIterator& operator++();

  // Оператор декремента (префиксный)
  ConstSetIterator& operator--();

  // Оператор сравнения
  bool operator==(const ConstSetIterator& other) const;
  bool operator!=(const ConstSetIterator& other) const;

  // Получение текущего узла (const Node*)
  const typename BinaryTreeMap<Key, T>::Node* get_node() const;
};

template <typename Key, typename T>
BinaryTreeMap<Key, T>::BinaryTreeMap() : size_(0), root_(nullptr){};

template <typename Key, typename T>
BinaryTreeMap<Key, T>::BinaryTreeMap(
    std::initializer_list<value_type> const& items)
    : BinaryTreeMap() {
  for (auto it = items.begin(); it != items.end(); ++it) {
    insert(*it);
  }
}

template <typename Key, typename T>
BinaryTreeMap<Key, T>::BinaryTreeMap(const BinaryTreeMap& b) : BinaryTreeMap() {
  for (auto it = b.cbegin(); it != b.cend(); ++it) {
    insert(*it);
  }
}

template <typename Key, typename T>
BinaryTreeMap<Key, T>::BinaryTreeMap(BinaryTreeMap&& b)
    : size_(b.size_), root_(b.root_) {
  b.root_ = nullptr;
}

template <typename Key, typename T>
BinaryTreeMap<Key, T>::~BinaryTreeMap() {
  clear();
}

// OPERATORS
template <typename Key, typename T>
class BinaryTreeMap<Key, T>::BinaryTreeMap& BinaryTreeMap<Key, T>::operator=(
    BinaryTreeMap&& b) {
  if (this != &b) {
    root_ = b.root_;
    size_ = b.size_;
    b.root_ = nullptr;
  }
  return *this;
}

template <typename Key, typename T>
class BinaryTreeMap<Key, T>::BinaryTreeMap& BinaryTreeMap<Key, T>::operator=(
    BinaryTreeMap& b) {
  if (this != &b) {
    this->~BinaryTreeMap();
    for (auto it = b.begin(); it != b.end(); ++it) {
      insert(*it);
    }
  }
  return *this;
}

template <typename Key, typename T>
void BinaryTreeMap<Key, T>::delete_tree(Node*& node) {
  if (node) {
    delete_tree(node->left);
    delete_tree(node->right);
    delete node;
    node = nullptr;
  }
}

template <typename Key, typename T>
std::pair<typename BinaryTreeMap<Key, T>::iterator, bool>
BinaryTreeMap<Key, T>::insert(const_reference data) {
  return insert(root_, nullptr, data, false);
}

template <typename Key, typename T>
std::pair<typename BinaryTreeMap<Key, T>::iterator, bool>
BinaryTreeMap<Key, T>::insert(const Key& key, const T& obj) {
  return insert(root_, nullptr, std::make_pair(key, obj), false);
}

template <typename Key, typename T>
std::pair<typename BinaryTreeMap<Key, T>::iterator, bool>
BinaryTreeMap<Key, T>::insert_or_assign(const Key& key, const T& obj) {
  return insert(root_, nullptr, std::make_pair(key, obj), true);
}

template <typename Key, typename T>
bool BinaryTreeMap<Key, T>::empty() {
  bool flag = false;
  if (!root_) flag = true;
  return flag;
}

template <typename Key, typename T>
void BinaryTreeMap<Key, T>::swap(BinaryTreeMap<Key, T>& other) {
  Node* temp = root_;
  size_type temp_size = size_;
  root_ = other.root_;
  size_ = other.size_;
  other.root_ = temp;
  other.size_ = temp_size;
}

template <typename Key, typename T>
void BinaryTreeMap<Key, T>::merge(BinaryTreeMap& other) {
  for (auto it = other.begin(); it != other.end(); ++it) {
    insert(*it);
  }
}

template <typename Key, typename T>
typename BinaryTreeMap<Key, T>::size_type BinaryTreeMap<Key, T>::size() {
  return size_;
}

template <typename Key, typename T>
typename BinaryTreeMap<Key, T>::size_type BinaryTreeMap<Key, T>::max_size() {
  return std::numeric_limits<size_type>::max() / sizeof(value_type);
}

template <typename Key, typename T>
void BinaryTreeMap<Key, T>::clear() {
  size_ = 0;
  delete_tree(root_);
}

template <typename Key, typename T>
std::pair<typename BinaryTreeMap<Key, T>::iterator, bool>
BinaryTreeMap<Key, T>::insert(typename BinaryTreeMap<Key, T>::Node*& node,
                              typename BinaryTreeMap<Key, T>::Node* parent_node,
                              const_reference data, bool assign) {
  auto ans = std::make_pair(SetIterator(nullptr), true);
  if (!node) {
    ++size_;
    node = new Node(data, parent_node);
    ans.first = SetIterator(node);
    ans.second = true;
    return ans;
  }
  if (data.first < node->data_.first) {
    ans = insert(node->left, node, data, assign);
  } else if (data.first >
             node->data_.first)  // !! для повторяющихся значений не пройдет
  {
    ans = insert(node->right, node, data, assign);
  } else {
    if (!assign) {
      ans = std::make_pair(SetIterator(node), false);
    } else {
      ans = std::make_pair(SetIterator(node), true);
      node->data_.second = data.second;
    }
  }

  return ans;
}

template <typename Key, typename T>
void BinaryTreeMap<Key, T>::erase(SetIterator pos) {
  Node* node_to_remove = pos.get_node();
  if (!node_to_remove)
    return;  // Проверяем, что итератор указывает на допустимый элемент
  --size_;
  // 1. Узел не имеет детей
  if (node_to_remove->left == nullptr && node_to_remove->right == nullptr) {
    replace_node(node_to_remove, nullptr);
    delete node_to_remove;
  }
  // 2. Узел имеет только одного ребёнка
  else if (node_to_remove->left == nullptr) {
    replace_node(node_to_remove, node_to_remove->right);
    delete node_to_remove;
  } else if (node_to_remove->right == nullptr) {
    replace_node(node_to_remove, node_to_remove->left);
    delete node_to_remove;
  }
  // 3. Узел имеет двух детей
  else {
    // Ищем наименьший элемент в правом поддереве (заменяющий узел)
    Node* successor = find_min(node_to_remove->right);

    // Заменяем node_to_remove на successor (заменяющий узел)
    if (successor->parent != node_to_remove) {
      replace_node(successor,
                   successor->right);  // Перемещаем потомков заменяющего узла
      successor->right = node_to_remove->right;  // Переставляем правого ребёнка
      if (successor->right) {
        successor->right->parent = successor;
      }
    }
    replace_node(node_to_remove, successor);  // Перемещаем заменяющий узел
    successor->left = node_to_remove->left;  // Переставляем левого ребёнка
    if (successor->left) {
      successor->left->parent = successor;
    }
    delete node_to_remove;
  }
}

template <typename Key, typename T>
typename BinaryTreeMap<Key, T>::Node* BinaryTreeMap<Key, T>::find_min(
    Node* node) const {
  while (node->left) {
    node = node->left;
  }
  return node;
}

template <typename Key, typename T>
void BinaryTreeMap<Key, T>::replace_node(Node* old_node, Node* new_node) {
  if (old_node->parent) {
    if (old_node == old_node->parent->left) {
      old_node->parent->left = new_node;
    } else {
      old_node->parent->right = new_node;
    }
  } else {
    root_ = new_node;
  }

  if (new_node) {
    new_node->parent = old_node->parent;
  }
}

template <typename Key, typename T>
typename BinaryTreeMap<Key, T>::iterator BinaryTreeMap<Key, T>::begin() {
  if (root_ == nullptr) {
    return SetIterator(nullptr);
  }
  Node* current = root_;
  while (current->left) {
    current = current->left;
  }
  return SetIterator{current};
}

template <typename Key, typename T>
typename BinaryTreeMap<Key, T>::const_iterator BinaryTreeMap<Key, T>::cbegin()
    const {
  if (root_ == nullptr) {
    return ConstSetIterator(nullptr);
  }
  Node* current = root_;
  while (current->left) {
    current = current->left;
  }
  return ConstSetIterator(current);
}

template <typename Key, typename T>
typename BinaryTreeMap<Key, T>::iterator BinaryTreeMap<Key, T>::end() {
  return SetIterator(nullptr);
}

template <typename Key, typename T>
typename s21::BinaryTreeMap<Key, T>::const_iterator
s21::BinaryTreeMap<Key, T>::cend() const {
  return ConstSetIterator(nullptr);
}

template <typename Key, typename T>
T& BinaryTreeMap<Key, T>::at(const Key& key) {
  Node* node = find_node(root_, key);
  if (node) {
    return node->data_.second;
  } else {
    throw std::out_of_range("Key not found in the map.");
  }
}

template <typename Key, typename T>
T& BinaryTreeMap<Key, T>::operator[](const Key& key) {
  Node* node = find_node(root_, key);
  if (node) {
    return node->data_.second;
  } else {
    // If the key is not found, insert a new node with default value
    auto result = insert(std::make_pair(key, T()));
    return result.first.get_node()->data_.second;
  }
}

template <typename Key, typename T>
typename BinaryTreeMap<Key, T>::Node* BinaryTreeMap<Key, T>::find_node(
    Node* node, const Key& key) const {
  while (node) {
    if (key < node->data_.first) {
      node = node->left;
    } else if (key > node->data_.first) {
      node = node->right;
    } else {
      return node;
    }
  }
  return nullptr;
}

// SET ITERATOR CLASS
template <typename Key, typename T>
BinaryTreeMap<Key, T>::SetIterator::SetIterator(
    BinaryTreeMap<Key, T>::Node* node)
    : current(node) {}

template <typename Key, typename T>
typename BinaryTreeMap<Key, T>::value_type
BinaryTreeMap<Key, T>::SetIterator::operator*() {
  return current->data_;
}

template <typename Key, typename T>
typename BinaryTreeMap<Key, T>::SetIterator&
BinaryTreeMap<Key, T>::SetIterator::operator++() {
  if (current == nullptr) {
    return *this;
  }
  if (current->right) {
    current = current->right;
    while (current->left) {
      current = current->left;
    }
  } else {
    Node* parent = current->parent;
    while (parent && parent->right == current) {
      current = parent;
      parent = current->parent;
    }
    current = parent;
  }

  return *this;
}

template <typename Key, typename T>
typename BinaryTreeMap<Key, T>::SetIterator&
BinaryTreeMap<Key, T>::SetIterator::operator--() {
  if (current == nullptr) return *this;

  if (current->left) {
    current = current->left;
    while (current->right) {
      current = current->right;
    }
  } else {
    Node* parent = current->parent;
    while (parent && current == parent->left) {
      current = parent;
      parent = parent->parent;
    }
    current = parent;
  }
  return *this;
}

template <typename Key, typename T>
bool BinaryTreeMap<Key, T>::SetIterator::operator==(
    const SetIterator& other) const {
  return current == other.current;
}

template <typename Key, typename T>
bool BinaryTreeMap<Key, T>::SetIterator::operator!=(
    const SetIterator& other) const {
  return !(*this == other);
}

template <typename Key, typename T>
typename BinaryTreeMap<Key, T>::Node*
BinaryTreeMap<Key, T>::SetIterator::get_node() {
  return current;
}

// CONST SET ITERATOR CLASS
template <typename Key, typename T>
BinaryTreeMap<Key, T>::ConstSetIterator::ConstSetIterator(
    const BinaryTreeMap<Key, T>::Node* node)
    : current(node) {}

template <typename Key, typename T>
typename BinaryTreeMap<Key, T>::value_type
BinaryTreeMap<Key, T>::ConstSetIterator::operator*() const {
  return current->data_;
}

template <typename Key, typename T>
typename BinaryTreeMap<Key, T>::ConstSetIterator&
BinaryTreeMap<Key, T>::ConstSetIterator::operator++() {
  if (current == nullptr) {
    return *this;
  }
  if (current->right) {
    current = current->right;
    while (current->left) {
      current = current->left;
    }
  } else {
    const Node* parent = current->parent;
    while (parent && parent->right == current) {
      current = parent;
      parent = current->parent;
    }
    current = parent;
  }

  return *this;
}

template <typename Key, typename T>
typename BinaryTreeMap<Key, T>::ConstSetIterator&
BinaryTreeMap<Key, T>::ConstSetIterator::operator--() {
  if (current == nullptr) return *this;

  if (current->left) {
    current = current->left;
    while (current->right) {
      current = current->right;
    }
  } else {
    const Node* parent = current->parent;
    while (parent && current == parent->left) {
      current = parent;
      parent = parent->parent;
    }
    current = parent;
  }
  return *this;
}

template <typename Key, typename T>
bool BinaryTreeMap<Key, T>::ConstSetIterator::operator==(
    const ConstSetIterator& other) const {
  return current == other.current;
}

template <typename Key, typename T>
bool BinaryTreeMap<Key, T>::ConstSetIterator::operator!=(
    const ConstSetIterator& other) const {
  return !(*this == other);
}

}  // namespace s21