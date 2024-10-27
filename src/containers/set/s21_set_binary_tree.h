#pragma once
#include <iostream>
#include <vector>
namespace s21 {
template <typename T>
class BinaryTree {
 public:
  // Iterator
  class SetIterator;
  class ConstSetIterator;

  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
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
  BinaryTree();
  BinaryTree(std::initializer_list<value_type> const& items);
  BinaryTree(const BinaryTree& b);
  BinaryTree(BinaryTree&& b);
  ~BinaryTree();

 public:
  BinaryTree& operator=(BinaryTree&& b);
  BinaryTree& operator=(BinaryTree& b);

 public:
  // addition foo
  void insert(const_reference data);
  void erase(iterator pos);
  bool empty();
  void swap(BinaryTree& other);
  void merge(BinaryTree& other);
  size_type size();
  size_type max_size();
  void clear();

  // Вспомогательные функции
 private:
  void delete_tree(Node*& node);
  Node* insert(Node* node, Node* parent_node, const_reference data);
  void replace_node(Node* old_node, Node* new_node);
  Node* find_min(Node* node) const;

 public:  // iterators
  iterator begin();
  const_iterator cbegin() const;
  iterator end();
  const_iterator cend() const;
};

template <typename T>
class BinaryTree<T>::SetIterator {
 private:
  typename BinaryTree<T>::Node* current;  // Указатель на текущий узел

 public:
  // Конструктор
  SetIterator(typename BinaryTree<T>::Node* node);

  // Оператор разыменования
  typename BinaryTree<T>::const_reference operator*();

  // Оператор инкремента
  SetIterator& operator++();
  SetIterator& operator--();
  bool operator==(const SetIterator& other) const;
  bool operator!=(const SetIterator& other) const;

  typename BinaryTree<T>::Node* get_node();
};

template <typename T>
class BinaryTree<T>::ConstSetIterator {
 private:
  const typename BinaryTree<T>::Node*
      current;  // Константный указатель на текущий узел

 public:
  // Конструктор
  ConstSetIterator(const typename BinaryTree<T>::Node* node);

  // Оператор разыменования
  typename BinaryTree<T>::const_reference operator*() const;

  // Оператор инкремента (префиксный)
  ConstSetIterator& operator++();

  // Оператор декремента (префиксный)
  ConstSetIterator& operator--();

  // Оператор сравнения
  bool operator==(const ConstSetIterator& other) const;
  bool operator!=(const ConstSetIterator& other) const;

  // Получение текущего узла (const Node*)
  const typename BinaryTree<T>::Node* get_node() const;
};

template <typename T>
BinaryTree<T>::BinaryTree() : size_(0), root_(nullptr){};

template <typename T>
BinaryTree<T>::BinaryTree(std::initializer_list<value_type> const& items)
    : BinaryTree() {
  for (auto it = items.begin(); it != items.end(); ++it) {
    insert(*it);
  }
}

template <typename T>
BinaryTree<T>::BinaryTree(const BinaryTree& b) : BinaryTree() {
  for (auto it = b.cbegin(); it != b.cend(); ++it) {
    insert(*it);
  }
}

template <typename T>
BinaryTree<T>::BinaryTree(BinaryTree&& b) : size_(b.size_), root_(b.root_) {
  b.root_ = nullptr;
}

template <typename T>
BinaryTree<T>::~BinaryTree() {
  clear();
}

// OPERATORS
template <typename T>
class BinaryTree<T>::BinaryTree& BinaryTree<T>::operator=(BinaryTree&& b) {
  if (this != &b) {
    root_ = b.root_;
    size_ = b.size_;
    b.root_ = nullptr;
  }
  return *this;
}

template <typename T>
class BinaryTree<T>::BinaryTree& BinaryTree<T>::operator=(BinaryTree& b) {
  if (this != &b) {
    this->~BinaryTree();
    for (auto it = b.begin(); it != b.end(); ++it) {
      insert(*it);
    }
  }
  return *this;
}

template <typename T>
void BinaryTree<T>::delete_tree(Node*& node) {
  if (node) {
    delete_tree(node->left);
    delete_tree(node->right);
    delete node;
    node = nullptr;
  }
}

template <typename T>
void BinaryTree<T>::insert(const_reference data) {
  root_ = insert(root_, nullptr, data);
}

template <typename T>
bool BinaryTree<T>::empty() {
  bool flag = false;
  if (!root_) flag = true;
  return flag;
}

template <typename T>
void BinaryTree<T>::swap(BinaryTree<T>& other) {
  Node* temp = root_;
  size_type temp_size = size_;
  root_ = other.root_;
  size_ = other.size_;
  other.root_ = temp;
  other.size_ = temp_size;
}

template <typename T>
void BinaryTree<T>::merge(BinaryTree& other) {
  for (auto it = other.begin(); it != other.end(); ++it) {
    insert(*it);
  }
}

template <typename T>
typename BinaryTree<T>::size_type BinaryTree<T>::size() {
  return size_;
}

template <typename T>
typename BinaryTree<T>::size_type BinaryTree<T>::max_size() {
  return std::numeric_limits<size_type>::max() / sizeof(value_type);
}

template <typename T>
void BinaryTree<T>::clear() {
  size_ = 0;
  delete_tree(root_);
}

template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::insert(
    typename BinaryTree<T>::Node* node,
    typename BinaryTree<T>::Node* parent_node, const_reference data) {
  if (!node) {
    ++size_;
    return new Node(data, parent_node);
  }
  if (data < node->data_) {
    node->left = insert(node->left, node, data);
  } else if (data > node->data_)  // !! для повторяющихся значений не пройдет
  {
    node->right = insert(node->right, node, data);
  }

  return node;
}

template <typename T>
void BinaryTree<T>::erase(SetIterator pos) {
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
    ++size_;
    // Ищем наименьший элемент в правом поддереве (заменяющий узел)
    Node* successor = find_min(node_to_remove->right);

    // Копируем данные successor в node_to_remove
    node_to_remove->data_ = successor->data_;

    // Удаляем successor (так как у него не может быть более одного ребёнка)
    erase(SetIterator(successor));
  }
}

template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::find_min(Node* node) const {
  while (node->left) {
    node = node->left;
  }
  return node;
}

template <typename T>
void BinaryTree<T>::replace_node(Node* old_node, Node* new_node) {
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

template <typename T>
typename BinaryTree<T>::iterator BinaryTree<T>::begin() {
  if (root_ == nullptr) {
    return SetIterator(nullptr);
  }
  Node* current = root_;
  while (current->left) {
    current = current->left;
  }
  return SetIterator{current};
}

template <typename T>
typename BinaryTree<T>::const_iterator BinaryTree<T>::cbegin() const {
  if (root_ == nullptr) {
    return ConstSetIterator(nullptr);
  }
  Node* current = root_;
  while (current->left) {
    current = current->left;
  }
  return ConstSetIterator(current);
}

template <typename T>
typename BinaryTree<T>::iterator BinaryTree<T>::end() {
  return SetIterator(nullptr);
}

template <typename T>
typename s21::BinaryTree<T>::const_iterator s21::BinaryTree<T>::cend() const {
  return ConstSetIterator(nullptr);
}

// SET ITERATOR CLASS
template <typename T>
BinaryTree<T>::SetIterator::SetIterator(BinaryTree<T>::Node* node)
    : current(node) {}

template <typename T>
typename BinaryTree<T>::const_reference
BinaryTree<T>::SetIterator::operator*() {
  return current->data_;
}

template <typename T>
typename BinaryTree<T>::SetIterator& BinaryTree<T>::SetIterator::operator++() {
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

template <typename T>
typename BinaryTree<T>::SetIterator& BinaryTree<T>::SetIterator::operator--() {
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

template <typename T>
bool BinaryTree<T>::SetIterator::operator==(const SetIterator& other) const {
  return current == other.current;
}

template <typename T>
bool BinaryTree<T>::SetIterator::operator!=(const SetIterator& other) const {
  return !(*this == other);
}

template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::SetIterator::get_node() {
  return current;
}

// CONST SET ITERATOR CLASS
template <typename T>
BinaryTree<T>::ConstSetIterator::ConstSetIterator(
    const BinaryTree<T>::Node* node)
    : current(node) {}

template <typename T>
typename BinaryTree<T>::const_reference
BinaryTree<T>::ConstSetIterator::operator*() const {
  return current->data_;
}

template <typename T>
typename BinaryTree<T>::ConstSetIterator&
BinaryTree<T>::ConstSetIterator::operator++() {
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

template <typename T>
typename BinaryTree<T>::ConstSetIterator&
BinaryTree<T>::ConstSetIterator::operator--() {
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

template <typename T>
bool BinaryTree<T>::ConstSetIterator::operator==(
    const ConstSetIterator& other) const {
  return current == other.current;
}

template <typename T>
bool BinaryTree<T>::ConstSetIterator::operator!=(
    const ConstSetIterator& other) const {
  return !(*this == other);
}

template <typename T>
const typename BinaryTree<T>::Node* BinaryTree<T>::ConstSetIterator::get_node()
    const {
  return current;
}

}  // namespace s21