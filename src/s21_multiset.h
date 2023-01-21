#ifndef CONTAINERS_SRC_MULTISET_H_
#define CONTAINERS_SRC_MULTISET_H_

#include <stdlib.h>

#include <iostream>

#include "./general.h"
#include "./s21_vector.h"

namespace s21 {

template <class T, class Compare = std::less<T>>
class multiset;

template <class T>
struct StructMultiset {
  StructMultiset<T> *left;
  StructMultiset<T> *right;
  StructMultiset<T> *parent;
  T value;
  size_t count;
  bool is_red;
};

template <class T, class Compare, class ConstType = T,
          class Struct = StructMultiset<T>>
class MultisetIterator {
  friend class multiset<T, Compare>;

 public:
  using value_type = ConstType;
  using pointer = ConstType *;
  using reference = ConstType &;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::bidirectional_iterator_tag;

  MultisetIterator() {}
  MultisetIterator(StructMultiset<T> *address) : address_(address), count(0) {}
  MultisetIterator(const MultisetIterator &other)
      : address_(other.address_), count(other.count) {}
  MultisetIterator(MultisetIterator &&other) {
    address_ = std::move(other.address_);
    count = std::move(other.count);
  }
  MultisetIterator &operator=(const MultisetIterator &other) {
    if (this != &other) {
      address_ = other.address_;
      count = other.count;
    }
    return *this;
  }
  MultisetIterator &operator=(MultisetIterator &&other) {
    if (this != &other) {
      address_ = std::move(other.address_);
      count = std::move(other.count);
    }
    return *this;
  }
  ~MultisetIterator() {}
  reference operator*() const { return address_->value; }
  MultisetIterator &operator++() {
    if (count < address_->count) {
      count++;
    } else {
      address_ = ClosestRight(address_);
      count = 0;
    }
    return *this;
  }
  MultisetIterator operator++(int) {
    MultisetIterator result = *this;
    if (count < address_->count) {
      count++;
    } else {
      address_ = ClosestRight(address_);
      count = 0;
    }
    return result;
  }
  MultisetIterator &operator--() {
    if (count > 0) {
      count--;
    } else {
      address_ = ClosestLeft(address_);
      count = address_->count;
    }
    return *this;
  }
  MultisetIterator operator--(int) {
    MultisetIterator result = *this;
    if (count > 0) {
      count--;
    } else {
      address_ = ClosestLeft(address_);
      count = address_->count;
    }
    return result;
  }
  bool operator==(const MultisetIterator it) const {
    return address_ == it.address_ && count == it.count;
  }
  bool operator!=(const MultisetIterator it) const {
    return address_ != it.address_ || count != it.count;
  }

 private:
  Struct *address_;
  size_t count = 0;
};

template <class T, class Compare>
class multiset {
 public:
  using iterator = MultisetIterator<T, Compare>;
  using const_iterator =
      MultisetIterator<T, Compare, const T, const StructMultiset<T>>;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  multiset();
  multiset(std::initializer_list<T> init_list);
  template <class InputIterator>
  multiset(InputIterator first, InputIterator last);
  multiset(multiset &&right);
  multiset(const multiset &right);
  multiset &operator=(const multiset &right);
  multiset &operator=(multiset &&right);
  ~multiset();
  bool operator<(multiset &other) const { return ComparisonList(other) == -1; }
  bool operator>(multiset &other) const { return ComparisonList(other) == 1; }
  bool operator==(multiset &other) const { return !ComparisonList(other); }
  bool operator!=(multiset &other) const { return ComparisonList(other); }
  bool operator<=(multiset &other) const {
    return !ComparisonList(other) || ComparisonList(other) == -1;
  }
  bool operator>=(multiset &other) const {
    return !ComparisonList(other) || ComparisonList(other) == 1;
  }
  template <class... Types>
  vector<std::pair<iterator, bool>> emplace(Types &&...args);
  std::pair<iterator, bool> insert(const T &value);
  void insert(std::initializer_list<T> init_list);
  iterator insert(iterator where, const T &value);
  template <class InputIterator>
  void insert(InputIterator first, InputIterator last);
  iterator begin();
  const_iterator begin() const;
  const_iterator cbegin() const;
  iterator end();
  const_iterator end() const;
  const_iterator cend() const;
  reverse_iterator rbegin();
  const_reverse_iterator rbegin() const;
  const_reverse_iterator crbegin() const;
  reverse_iterator rend();
  const_reverse_iterator rend() const;
  const_reverse_iterator crend() const;
  iterator erase(iterator where);
  iterator erase(iterator first, iterator last);
  size_t erase(const T &value);
  size_t size() const;
  bool empty() const;
  size_t count(const T &value) const;
  iterator find(const T &value);
  const_iterator find(const T &value) const;
  iterator lower_bound(const T &value);
  const_iterator lower_bound(const T &value) const;
  iterator upper_bound(const T &value);
  const_iterator upper_bound(const T &value) const;
  void clear();
  void swap(multiset &right);
  std::pair<iterator, iterator> equal_range(const T &value);
  std::pair<const_iterator, const_iterator> equal_range(const T &value) const;

 private:
  StructMultiset<T> *anchor_ = CreateAnchor();
  Compare comp_;
  size_t size_ = 0;
  StructMultiset<T> *Erase(StructMultiset<T> *where);
  void Adjustment(StructMultiset<T> *value);
  StructMultiset<T> *CreatePart();
  StructMultiset<T> *FindPosition(StructMultiset<T> *root,
                                  const T &value) const;
  StructMultiset<T> *Smallest(StructMultiset<T> *value) const;
  StructMultiset<T> *CreateAnchor();
  void SwapColors(StructMultiset<T> *value);
  void LeftTurn(StructMultiset<T> *value);
  void RightTurn(StructMultiset<T> *value);
  void FreeSet(StructMultiset<T> *root);
  int ComparisonList(const multiset &other) const;
  void CopySet(const multiset &right);
  void AddList(std::initializer_list<T> init_list);
  StructMultiset<T> *InsertStandart(StructMultiset<T> *wheere, const T &value);
  inline void ArgumentParser(
      [[maybe_unused]] vector<std::pair<iterator, bool>> &result) {}
  template <class... Other>
  void ArgumentParser(vector<std::pair<iterator, bool>> &result, T first,
                      Other... other);
};

template <class T, class Compare>
template <class... Types>
vector<std::pair<typename multiset<T, Compare>::iterator, bool>>
multiset<T, Compare>::emplace(Types &&...args) {
  vector<std::pair<iterator, bool>> result;
  ArgumentParser(result, args...);
  return result;
}

template <class T, class Compare>
template <class... Other>
void multiset<T, Compare>::ArgumentParser(
    vector<std::pair<iterator, bool>> &result, T first, Other... other) {
  result.push_back(insert(first));
  ArgumentParser(result, other...);
}

template <class T, class Compare>
typename multiset<T, Compare>::iterator multiset<T, Compare>::insert(
    iterator where, const T &value) {
  StructMultiset<T> *res = InsertStandart(where.address_, value);
  return res ? res : anchor_;
}

template <class T, class Compare>
template <class InputIterator>
void multiset<T, Compare>::insert(InputIterator first, InputIterator last) {
  while (first != last) {
    if (!InsertStandart(anchor_->right, *first)) return;
    first++;
  }
}

template <class T, class Compare>
void multiset<T, Compare>::insert(std::initializer_list<T> init_list) {
  AddList(init_list);
}

template <class T, class Compare>
std::pair<typename multiset<T, Compare>::iterator, bool>
multiset<T, Compare>::insert(const T &value) {
  bool second = true;
  iterator first = anchor_;
  StructMultiset<T> *tmp = InsertStandart(anchor_->right, value);
  if (tmp) first = tmp;
  std::pair<iterator, bool> result(first, second);
  return result;
}

template <class T, class Compare>
class std::pair<typename multiset<T, Compare>::iterator,
                typename multiset<T, Compare>::iterator>
multiset<T, Compare>::equal_range(const T &value) {
  iterator first = lower_bound(value);
  iterator second = upper_bound(value);
  std::pair<iterator, iterator> result(first, second);
  return result;
}

template <class T, class Compare>
class std::pair<typename multiset<T, Compare>::const_iterator,
                typename multiset<T, Compare>::const_iterator>
multiset<T, Compare>::equal_range(const T &value) const {
  const_iterator first = lower_bound(value);
  const_iterator second = upper_bound(value);
  std::pair<const_iterator, const_iterator> result(first, second);
  return result;
}

template <class T, class Compare>
void multiset<T, Compare>::AddList(std::initializer_list<T> init_list) {
  T *ptr = (T *)init_list.begin();
  for (int i = 0; i < static_cast<int>(init_list.size()); i++, ptr++) {
    if (!InsertStandart(anchor_->right, *ptr)) {
      clear();
      return;
    }
  }
}

template <class T, class Compare>
void multiset<T, Compare>::swap(multiset &right) {
  std::swap(anchor_, right.anchor_);
  std::swap(size_, right.size_);
}

template <class T, class Compare>
multiset<T, Compare> &multiset<T, Compare>::operator=(const multiset &right) {
  multiset tmp(right);
  swap(tmp);
  return *this;
}

template <class T, class Compare>
multiset<T, Compare> &multiset<T, Compare>::operator=(multiset &&right) {
  swap(right);
  return *this;
}

template <class T, class Compare>
void multiset<T, Compare>::clear() {
  if (anchor_->right != nullptr) FreeSet(anchor_->right);
  anchor_->left = anchor_->right = nullptr;
  size_ = 0;
}

template <class T, class Compare>
typename multiset<T, Compare>::iterator multiset<T, Compare>::upper_bound(
    const T &value) {
  iterator result = end();
  if (anchor_->right != nullptr) {
    StructMultiset<T> *position = FindPosition(anchor_->right, value);
    if (comp_(position->value, value) || position->value == value)
      result = ClosestRight(position);
    else
      result = position;
  }
  return result;
}

template <class T, class Compare>
typename multiset<T, Compare>::const_iterator multiset<T, Compare>::upper_bound(
    const T &value) const {
  const_iterator result = end();
  if (anchor_->right != nullptr) {
    StructMultiset<T> *position = FindPosition(anchor_->right, value);
    if (comp_(position->value, value) || position->value == value)
      result = ClosestRight(position);
    else
      result = position;
  }
  return result;
}

template <class T, class Compare>
typename multiset<T, Compare>::iterator multiset<T, Compare>::lower_bound(
    const T &value) {
  iterator result = end();
  if (anchor_->right != nullptr) {
    StructMultiset<T> *position = FindPosition(anchor_->right, value);
    if (comp_(position->value, value))
      result = ClosestRight(position);
    else
      result = position;
  }
  return result;
}

template <class T, class Compare>
typename multiset<T, Compare>::const_iterator multiset<T, Compare>::lower_bound(
    const T &value) const {
  const_iterator result = end();
  if (anchor_->right != nullptr) {
    StructMultiset<T> *position = FindPosition(anchor_->right, value);
    if (comp_(position->value, value))
      result = ClosestRight(position);
    else
      result = position;
  }
  return result;
}

template <class T, class Compare>
typename multiset<T, Compare>::iterator multiset<T, Compare>::find(
    const T &value) {
  iterator result = end();
  if (anchor_->right != nullptr) {
    StructMultiset<T> *position = FindPosition(anchor_->right, value);
    if (position->value == value) result = position;
  }
  return result;
}

template <class T, class Compare>
typename multiset<T, Compare>::const_iterator multiset<T, Compare>::find(
    const T &value) const {
  const_iterator result = end();
  if (anchor_->right != nullptr) {
    StructMultiset<T> *position = FindPosition(anchor_->right, value);
    if (position->value == value) result = position;
  }
  return result;
}

template <class T, class Compare>
size_t multiset<T, Compare>::count(const T &value) const {
  size_t result = 0;
  if (anchor_->right != nullptr) {
    StructMultiset<T> *position = FindPosition(anchor_->right, value);
    if (position->value == value) result = position->count + 1;
  }
  return result;
}

template <class T, class Compare>
bool multiset<T, Compare>::empty() const {
  return !size_;
}

template <class T, class Compare>
multiset<T, Compare>::multiset() {}

template <class T, class Compare>
multiset<T, Compare>::multiset(std::initializer_list<T> init_list) {
  AddList(init_list);
}

template <class T, class Compare>
template <class InputIterator>
multiset<T, Compare>::multiset(InputIterator first, InputIterator last) {
  while (first != last) {
    if (!InsertStandart(anchor_->right, *first)) {
      clear();
      return;
    }
    first++;
  }
}

template <class T, class Compare>
void multiset<T, Compare>::CopySet(const multiset &right) {
  const_iterator begin = right.begin(), end = right.end();
  while (begin != end) {
    if (!InsertStandart(anchor_->right, *begin)) {
      clear();
      return;
    }
    begin++;
  }
}

template <class T, class Compare>
inline multiset<T, Compare>::multiset(multiset &&right) {
  swap(right);
}

template <class T, class Compare>
inline multiset<T, Compare>::multiset(const multiset &right) {
  CopySet(right);
}

template <class T, class Compare>
size_t multiset<T, Compare>::size() const {
  return size_;
}

template <class T, class Compare>
int multiset<T, Compare>::ComparisonList(const multiset &other) const {
  int res = 0, size1 = size(), size2 = other.size();
  const_iterator our_it = begin();
  const_iterator other_it = other.begin();
  for (int i = 0; i < size1 && i < size2; i++, our_it++, other_it++) {
    if (*our_it != *other_it) {
      res = *our_it > *other_it ? 1 : -1;
      break;
    }
  }
  if (res == 0 && size1 != size2) res = size1 > size2 ? 1 : -1;
  return res;
}

template <class T, class Compare>
typename multiset<T, Compare>::iterator multiset<T, Compare>::erase(
    iterator first, iterator last) {
  while (first != last) first = erase(first);
  return first;
}

template <class T, class Compare>
size_t multiset<T, Compare>::erase(const T &value) {
  size_t result = 0;
  if (anchor_->right != nullptr) {
    StructMultiset<T> *position = FindPosition(anchor_->right, value);
    if (value == position->value) {
      result = position->count;
      Erase(position);
    }
  }
  return result;
}

template <class T, class Compare>
typename multiset<T, Compare>::iterator multiset<T, Compare>::erase(
    iterator where) {
  iterator res;
  if (where.address_->count) {
    where.address_->count--;
    size_--;
    if (where.address_->count < where.count) {
      res = ++where;
    } else {
      res = where;
    }
  } else {
    res = Erase(where.address_);
  }
  return res;
}

template <class T, class Compare>
StructMultiset<T> *multiset<T, Compare>::Erase(StructMultiset<T> *position) {
  if (position == anchor_) return anchor_;
  StructMultiset<T> *parent = position->parent;
  StructMultiset<T> *result = ClosestRight(position);
  if (position->left == nullptr && position->right == nullptr) {
    if (parent->right == position)
      parent->right = nullptr;
    else
      parent->left = nullptr;
  } else if (position->left == nullptr) {
    if (parent->right == position) {
      parent->right = position->right;
      position->right->parent = parent;
    } else {
      parent->left = position->right;
      position->right->parent = parent;
    }
  } else if (position->right == nullptr) {
    if (parent->right == position) {
      parent->right = position->left;
      position->left->parent = parent;
    } else {
      parent->left = position->left;
      position->left->parent = parent;
    }
  } else {
    StructMultiset<T> *change = ClosestLeft(position);
    position->value = change->value;
    erase(change);
    return result;
  }
  if (parent == anchor_) anchor_->left = anchor_->right;
  size_ -= position->count + 1;
  delete position;
  return result;
}

template <class T, class Compare>
multiset<T, Compare>::~multiset() {
  if (anchor_->right != anchor_ && anchor_->right != nullptr)
    FreeSet(anchor_->right);
  delete anchor_;
  size_ = 0;
}

template <class T, class Compare>
void multiset<T, Compare>::FreeSet(StructMultiset<T> *root) {
  if (root->left != nullptr) FreeSet(root->left);
  if (root->right != nullptr) FreeSet(root->right);
  delete root;
}

template <class T, class Compare>
void multiset<T, Compare>::Adjustment(StructMultiset<T> *value) {
  StructMultiset<T> *parent = value->parent;
  if ((parent->right != nullptr && parent->right->is_red == true) &&
      (parent->left != nullptr && parent->left->is_red == true))
    SwapColors(value);
  if ((parent->right != nullptr && parent->right == value) &&
      value->is_red == true)
    RightTurn(value);
  if (parent->is_red == true && value->is_red == true) LeftTurn(value);
}

template <class T, class Compare>
void multiset<T, Compare>::LeftTurn(StructMultiset<T> *value) {
  StructMultiset<T> *parent = value->parent;
  StructMultiset<T> *grandfather = parent->parent;
  if (grandfather == anchor_->right) {
    anchor_->left = anchor_->right = parent;
    parent->parent = anchor_;
  }
  StructMultiset<T> *great_grandfather = grandfather->parent;
  grandfather->left = parent->right;
  if (parent->right != nullptr) parent->right->parent = grandfather;
  parent->right = grandfather;
  grandfather->parent = parent;
  if (great_grandfather != nullptr) {
    parent->parent = great_grandfather;
    if (great_grandfather->left == grandfather) {
      great_grandfather->left = parent;
    } else {
      great_grandfather->right = parent;
    }
  }
  great_grandfather->is_red = false;
  value->is_red = false;
  parent->is_red = false;
  if (parent != anchor_->right) parent->is_red = true;
  Adjustment(parent);
}

template <class T, class Compare>
void multiset<T, Compare>::RightTurn(StructMultiset<T> *value) {
  StructMultiset<T> *parent = value->parent;
  if (parent == anchor_->right) {
    anchor_->left = anchor_->right = value;
    value->parent = anchor_;
  }
  StructMultiset<T> *grandfather = parent->parent;

  StructMultiset<T> *swap = value->left;
  if (value->left != nullptr) {
    swap->parent = parent;
  }
  value->left = parent;
  parent->right = swap;
  parent->parent = value;
  value->is_red = parent->is_red;
  if (grandfather != nullptr) {
    value->parent = grandfather;
    if (grandfather->left == parent) {
      grandfather->left = value;
    } else {
      grandfather->right = value;
    }
  }
  if (value == anchor_->right) value->is_red = false;
  parent->is_red = true;
  Adjustment(parent);
}

template <class T, class Compare>
void multiset<T, Compare>::SwapColors(StructMultiset<T> *value) {
  StructMultiset<T> *parent = value->parent;
  parent->right->is_red = false;
  parent->left->is_red = false;
  if (parent != anchor_->right) {
    parent->is_red = true;
    Adjustment(parent);
  }
}

template <class T, class Compare>
StructMultiset<T> *multiset<T, Compare>::CreateAnchor() {
  StructMultiset<T> *result;
  result = CreatePart();
  if (!result) return nullptr;
  result->parent = result;
  size_--;
  return result;
}

template <class T, class Compare>
StructMultiset<T> *multiset<T, Compare>::Smallest(
    StructMultiset<T> *value) const {
  while (value->left != nullptr) value = value->left;
  return value;
}

template <class T, class Compare>
typename multiset<T, Compare>::iterator multiset<T, Compare>::end() {
  return anchor_;
}

template <class T, class Compare>
typename multiset<T, Compare>::const_iterator multiset<T, Compare>::end()
    const {
  return anchor_;
}

template <class T, class Compare>
typename multiset<T, Compare>::const_iterator multiset<T, Compare>::cend()
    const {
  return anchor_;
}

template <class T, class Compare>
typename multiset<T, Compare>::iterator multiset<T, Compare>::begin() {
  return anchor_->right ? Smallest(anchor_->right) : anchor_;
}

template <class T, class Compare>
typename multiset<T, Compare>::const_iterator multiset<T, Compare>::begin()
    const {
  return anchor_->right ? Smallest(anchor_->right) : anchor_;
}

template <class T, class Compare>
typename multiset<T, Compare>::const_iterator multiset<T, Compare>::cbegin()
    const {
  return anchor_->right ? Smallest(anchor_->right) : anchor_;
}

template <class T, class Compare>
typename multiset<T, Compare>::reverse_iterator multiset<T, Compare>::rend() {
  return static_cast<reverse_iterator>(begin());
}

template <class T, class Compare>
typename multiset<T, Compare>::const_reverse_iterator
multiset<T, Compare>::rend() const {
  return static_cast<const_reverse_iterator>(begin());
}

template <class T, class Compare>
typename multiset<T, Compare>::const_reverse_iterator
multiset<T, Compare>::crend() const {
  return static_cast<const_reverse_iterator>(begin());
}

template <class T, class Compare>
typename multiset<T, Compare>::reverse_iterator multiset<T, Compare>::rbegin() {
  return static_cast<reverse_iterator>(end());
}

template <class T, class Compare>
typename multiset<T, Compare>::const_reverse_iterator
multiset<T, Compare>::rbegin() const {
  return static_cast<const_reverse_iterator>(end());
}

template <class T, class Compare>
typename multiset<T, Compare>::const_reverse_iterator
multiset<T, Compare>::crbegin() const {
  return static_cast<const_reverse_iterator>(end());
}

template <class T, class Compare>
StructMultiset<T> *multiset<T, Compare>::FindPosition(StructMultiset<T> *root,
                                                      const T &value) const {
  StructMultiset<T> *pos = root;
  if (comp_(root->value, value)) {
    if (root->right == nullptr) {
      pos = root;
    } else {
      pos = FindPosition(root->right, value);
    }
  } else if (comp_(value, root->value)) {
    if (root->left == nullptr) {
      pos = root;
    } else {
      pos = FindPosition(root->left, value);
    }
  }
  return pos;
}

template <class T, class Compare>
StructMultiset<T> *multiset<T, Compare>::InsertStandart(
    StructMultiset<T> *wheere, const T &value) {
  if (!anchor_) return nullptr;
  StructMultiset<T> *position = anchor_;
  if (size_ == 0) {
    anchor_->left = anchor_->right = CreatePart();
    if (!anchor_->left) return nullptr;
    position = anchor_->right;
    position->parent = anchor_;
  } else {
    position = FindPosition(wheere, value);
    if (position->value != value) {
      if (comp_(position->value, value)) {
        position->right = CreatePart();
        if (!position->right) return nullptr;
        position->right->parent = position;
        position = position->right;
      } else {
        position->left = CreatePart();
        if (!position->left) return nullptr;
        position->left->parent = position;
        position = position->left;
      }
      position->is_red = true;
      Adjustment(position);
    } else {
      position->count++;
      size_++;
    }
  }
  if (!position->count) {
    try {
      position->value = value;
    } catch (...) {
      erase(position);
      return nullptr;
    }
  }
  return position;
}

template <class T, class Compare>
StructMultiset<T> *multiset<T, Compare>::CreatePart() {
  StructMultiset<T> *result;
  try {
    result = new StructMultiset<T>;
  } catch (...) {
    return nullptr;
  }
  size_++;
  result->left = nullptr;
  result->right = nullptr;
  result->parent = nullptr;
  result->is_red = false;
  result->count = 0;
  return result;
}

}  // namespace s21
#endif  // CONTAINERS_SRC_MULTISET_HPP_