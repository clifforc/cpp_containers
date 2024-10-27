#pragma once

#include <algorithm>

namespace s21 {
template <typename T>
class List {
 public:  // node
  struct Node {
    T data_;
    Node *next_ = nullptr;
    Node *prev_ = nullptr;
    explicit Node(T data) noexcept : data_(data){};

    template <typename... Args>
    explicit Node(Args &&...args) : data_(std::forward<Args>(args)...){};
  };

 public:  // internal classes
  class ListIterator;
  class ListConstIterator;

 public:  // members
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using pointer = Node *;
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;
  using size_type = std::size_t;

 private:  // attributes
  size_type size_ = 0;
  pointer head_;
  pointer tail_;

 public:  // constructors
  List();
  explicit List(size_type n);
  List(std::initializer_list<value_type> const &items);
  List(const List &l);
  List(List &&l) noexcept;
  List &operator=(List &&l) noexcept;
  List &operator=(const List &l) noexcept;
  ~List();

 public:  // accessors
  reference front();
  const_reference front() const;
  reference back();
  const_reference back() const;

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

 public:  // modifiers
  void clear() noexcept;
  iterator insert(const_iterator pos, const_reference value);

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);
  template <typename... Args>
  void insert_many_back(Args &&...args);
  template <typename... Args>
  void insert_many_front(Args &&...args);

  iterator erase(const_iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(List &other) noexcept;
  void merge(List &other);
  void splice(const_iterator pos, List &other);
  void reverse() noexcept;
  void unique();
  void sort();
};

template <typename T>
class List<T>::ListIterator {
  friend class List;

 public:
  ListIterator() = default;
  ListIterator(pointer it) : it_(it){};
  ListIterator(ListConstIterator &other) : it_(other.it_){};
  ListIterator(ListIterator &&other) noexcept : it_(other.it_) {
    other.it_ = nullptr;
  }
  ~ListIterator() = default;

  iterator &operator++() {
    it_ = it_->next_;
    return *this;
  }

  iterator &operator--() {
    it_ = it_->prev_;
    return *this;
  }

  reference operator*() { return it_->data_; }

  iterator &operator=(const const_iterator &other) {
    it_ = other.it_;
    return *this;
  }

  iterator &operator=(const iterator &other) {
    it_ = other.it_;
    return *this;
  }

  bool operator==(const iterator &other) { return it_ == other.it_; }

  bool operator!=(const iterator &other) { return it_ != other.it_; }

 private:
  pointer it_;
};

template <typename T>
class List<T>::ListConstIterator {
  friend class List;

 public:
  ListConstIterator() = default;
  ListConstIterator(pointer it) : it_(it){};
  ListConstIterator(ListConstIterator &other) : it_(other.it_){};
  ListConstIterator(ListConstIterator &&other) noexcept : it_(other.it_) {
    other.it_ = nullptr;
  }
  ~ListConstIterator() = default;

  const_iterator &operator++() {
    it_ = it_->next_;
    return *this;
  }

  const_iterator &operator--() {
    it_ = it_->prev_;
    return *this;
  }

  const_reference operator*() { return it_->data_; }

  const_iterator &operator=(const iterator &other) {
    it_ = other.it_;
    return *this;
  }

  bool operator==(const const_iterator &other) { return it_ == other.it_; }

  bool operator!=(const const_iterator &other) { return it_ != other.it_; }

 private:
  pointer it_;
};

template <typename T>
List<T>::List() : size_(0), head_(nullptr), tail_(nullptr) {}

template <typename T>
List<T>::List(size_type n) : List() {
  for (size_type i = 0; i < n; ++i) {
    push_back(0);
  }
}

template <typename T>
List<T>::List(std::initializer_list<value_type> const &items) : List() {
  for (auto i = items.begin(); i != items.end(); ++i) {
    push_back(*i);
  }
}

template <typename T>
List<T>::List(const List &l) : List() {
  for (auto i = l.cbegin(); i != l.cend(); ++i) {
    push_back(*i);
  }
}

template <typename T>
List<T>::List(List &&l) noexcept
    : size_(l.size_), head_(l.head_), tail_(l.tail_) {
  l.size_ = 0;
  l.head_ = nullptr;
  l.tail_ = nullptr;
}

template <typename T>
List<T> &List<T>::operator=(List &&l) noexcept {
  if (this != &l) {
    this->~List();
    size_ = l.size_;
    head_ = l.head_;
    tail_ = l.tail_;

    l.size_ = 0;
    l.head_ = nullptr;
    l.tail_ = nullptr;
  }
  return *this;
}

template <typename T>
List<T> &List<T>::operator=(const List &l) noexcept {
  if (head_) clear();
  for (auto i = l.cbegin(); i != l.cend(); ++i) {
    push_back(*i);
  }
  return *this;
}

template <typename T>
List<T>::~List() {
  clear();
}

template <typename T>
typename List<T>::reference List<T>::front() {
  return head_->data_;
}

template <typename T>
typename List<T>::const_reference List<T>::front() const {
  return head_->data_;
}

template <typename T>
typename List<T>::reference List<T>::back() {
  return tail_->data_;
}

template <typename T>
typename List<T>::const_reference List<T>::back() const {
  return tail_->data_;
}

template <typename T>
typename List<T>::iterator List<T>::begin() noexcept {
  return iterator(head_);
}

template <typename T>
typename List<T>::const_iterator List<T>::begin() const noexcept {
  return const_iterator(head_);
}

template <typename T>
typename List<T>::const_iterator List<T>::cbegin() const noexcept {
  return const_iterator(head_);
}

template <typename T>
typename List<T>::iterator List<T>::end() noexcept {
  return iterator(tail_->next_);
}

template <typename T>
typename List<T>::const_iterator List<T>::end() const noexcept {
  return const_iterator(tail_->next_);
}

template <typename T>
typename List<T>::const_iterator List<T>::cend() const noexcept {
  return const_iterator(tail_->next_);
}

template <typename T>
bool List<T>::empty() const noexcept {
  return size_ == 0;
}

template <typename T>
typename List<T>::size_type List<T>::size() const noexcept {
  return size_;
}

template <typename T>
typename List<T>::size_type List<T>::max_size() const noexcept {
  return std::numeric_limits<std::size_t>::max() / sizeof(Node);
}

template <typename T>
void List<T>::clear() noexcept {
  while (head_) {
    pop_front();
  }
}

template <typename T>
typename List<T>::iterator List<T>::insert(const_iterator pos,
                                           const_reference value) {
  if (pos == cend()) {
    push_back(value);
    return iterator(tail_);
  }
  if (pos == cbegin()) {
    push_front(value);
    return iterator(head_);
  } else {
    pointer cur_node = pos.it_;
    Node *new_node = new Node(value);
    new_node->next_ = cur_node;
    new_node->prev_ = cur_node->prev_;
    cur_node->prev_->next_ = new_node;
    cur_node->prev_ = new_node;
    ++size_;
    return iterator(new_node);
  }
}

template <typename T>
template <typename... Args>
typename List<T>::iterator List<T>::insert_many(const_iterator pos,
                                                Args &&...args) {
  for (const auto &arg : {args...}) {
    insert(pos, arg);
  }
  return pos;
}

template <typename T>
template <typename... Args>
void List<T>::insert_many_back(Args &&...args) {
  for (const auto &arg : {args...}) {
    push_back(arg);
  }
}

template <typename T>
template <typename... Args>
void List<T>::insert_many_front(Args &&...args) {
  for (const auto &arg : {args...}) {
    push_front(arg);
  }
}

template <typename T>
typename List<T>::iterator List<T>::erase(const_iterator pos) {
  if (pos.it_ == head_) {
    pop_front();
    return pos;
  } else if (pos.it_ == tail_) {
    pop_back();
    return end();
  } else {
    pointer tmp = pos.it_;
    tmp->next_->prev_ = tmp->prev_;
    tmp->prev_->next_ = tmp->next_;
    delete tmp;
    --size_;
    return pos.it_;
  }
}

template <typename T>
void List<T>::push_back(const_reference value) {
  Node *new_node = new Node(value);
  if (empty()) {
    head_ = tail_ = new_node;
  } else {
    tail_->next_ = new_node;
    new_node->prev_ = tail_;
    tail_ = new_node;
  }
  ++size_;
}

template <typename T>
void List<T>::push_front(const_reference value) {
  Node *new_node = new Node(value);
  if (empty()) {
    head_ = tail_ = new_node;
  } else {
    head_->prev_ = new_node;
    new_node->next_ = head_;
    head_ = new_node;
  }
  ++size_;
}

template <typename T>
void List<T>::pop_front() {
  if (size_ == 1) {
    delete head_;
    head_ = tail_ = nullptr;
    size_ = 0;
  }
  if (size_ > 1) {
    head_ = head_->next_;
    delete head_->prev_;
    head_->prev_ = nullptr;
    --size_;
  }
}

template <typename T>
void List<T>::pop_back() {
  if (size_ == 1) {
    delete tail_;
    head_ = tail_ = nullptr;
    size_ = 0;
  }
  if (size_ > 1) {
    tail_ = tail_->prev_;
    delete tail_->next_;
    tail_->next_ = nullptr;
    --size_;
  }
}

template <typename T>
void List<T>::swap(List &other) noexcept {
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
  std::swap(size_, other.size_);
}

template <typename T>
void List<T>::merge(List &other) {
  if (other.head_) {
    const_iterator it = cend();
    splice(it, other);
    sort();
  }
}

template <typename T>
void List<T>::splice(const_iterator pos, List &other) {
  const_iterator it = const_iterator(pos.it_);
  for (auto iter = other.begin(); iter != other.end(); ++iter) {
    insert(it, *iter);
  }
}

template <typename T>
void List<T>::sort() {
  if (size_ <= 1) return;

  bool swapped;
  auto it1 = head_;
  const Node *it2 = nullptr;

  do {
    swapped = false;
    while (it1->next_ != it2) {
      if (it1->data_ > it1->next_->data_) {
        std::swap(it1->data_, it1->next_->data_);
        swapped = true;
      }
      it1 = it1->next_;
    }
    it2 = it1;
    it1 = head_;
  } while (swapped);
}

template <typename T>
void List<T>::reverse() noexcept {
  if (size_ > 1) {
    Node *tmp = head_;
    for (size_type i = 0; i < size_; ++i) {
      std::swap(tmp->prev_, tmp->next_);
      tmp = tmp->prev_;
    }

    std::swap(head_, tail_);
  }
}

template <typename T>
void List<T>::unique() {
  if (size_ > 1) {
    iterator cur = begin();
    iterator next = begin();
    ++next;
    while (next != end()) {
      if (*cur == *next) {
        const_iterator err;
        err = next;
        erase(err);
        next = cur;
        ++next;
      } else {
        cur = ++next;
      }
    }
  }
}

}  // namespace s21