#ifndef CONTAINERS_SRC_SET_H_
#define CONTAINERS_SRC_SET_H_

#include <stdlib.h>

#include <iostream>
#include <iterator>

#include "./general.h"
#include "./s21_vector.h"

namespace s21 {

template <class T, class Compare = std::less<T>>
class set;

template <class T>
struct StructSet {
  StructSet<T> *left;
  StructSet<T> *right;
  StructSet<T> *parent;
  T value;
  bool is_red;
};

template <class T, class Compare, class ConstType = T,
          class Struct = StructSet<T>>
class SetIterator {
  friend class set<T, Compare>;

 public:
  using value_type = ConstType;
  using pointer = ConstType *;
  using reference = ConstType &;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::bidirectional_iterator_tag;

  SetIterator() {}
  SetIterator(StructSet<T> *address) : address_(address) {}
  SetIterator(const SetIterator &other) : address_(other.address_) {}
  SetIterator(SetIterator &&other) { address_ = std::move(other.address_); }
  SetIterator &operator=(const SetIterator &other) {
    if (this != &other) address_ = other.address_;
    return *this;
  }
  SetIterator &operator=(SetIterator &&other) {
    if (this != &other) address_ = std::move(other.address_);
    return *this;
  }
  ~SetIterator() {}
  reference operator*() const { return address_->value; }
  SetIterator &operator++() {
    address_ = ClosestRight(address_);
    return *this;
  }
  SetIterator operator++(int) {
    SetIterator result = *this;
    address_ = ClosestRight(address_);
    return result;
  }
  SetIterator &operator--() {
    address_ = ClosestLeft(address_);
    return *this;
  }
  SetIterator operator--(int) {
    SetIterator result = *this;
    address_ = ClosestLeft(address_);
    return result;
  }
  bool operator==(const SetIterator it) const {
    return address_ == it.address_;
  }
  bool operator!=(const SetIterator it) const {
    return address_ != it.address_;
  }

 private:
  Struct *address_;
};

template <class T, class Compare>
class set {
 public:
  using iterator = SetIterator<T, Compare>;
  using const_iterator = SetIterator<T, Compare, const T, const StructSet<T>>;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  set();
  set(std::initializer_list<T> init_list);
  template <class InputIterator>
  set(InputIterator first, InputIterator last);
  set(set &&right);
  set(const set &right);
  set<T, Compare> &operator=(const set &right);
  set<T, Compare> &operator=(set &&right);
  ~set();
  template <class... Types>
  vector<std::pair<iterator, bool>> emplace(Types &&...args);
  bool operator<(set &other) const { return ComparisonList(other) == -1; }
  bool operator>(set &other) const { return ComparisonList(other) == 1; }
  bool operator==(set &other) const { return !ComparisonList(other); }
  bool operator!=(set &other) const { return ComparisonList(other); }
  bool operator<=(set &other) const {
    return !ComparisonList(other) || ComparisonList(other) == -1;
  }
  bool operator>=(set &other) const {
    return !ComparisonList(other) || ComparisonList(other) == 1;
  }
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
  void swap(set &right);
  std::pair<iterator, iterator> equal_range(const T &value);
  std::pair<const_iterator, const_iterator> equal_range(const T &value) const;

 private:
  StructSet<T> *anchor_ = CreateAnchor();
  Compare comp_;
  size_t size_ = 0;
  void Adjustment(StructSet<T> *value);
  StructSet<T> *CreatePart();
  StructSet<T> *FindPosition(StructSet<T> *root, const T &value) const;
  StructSet<T> *Smallest(StructSet<T> *value) const;
  StructSet<T> *CreateAnchor();
  void SwapColors(StructSet<T> *value);
  void LeftTurn(StructSet<T> *value);
  void RightTurn(StructSet<T> *value);
  void FreeSet(StructSet<T> *root);
  int ComparisonList(const set &other) const;
  void CopySet(const set &right);
  void AddList(std::initializer_list<T> init_list);
  StructSet<T> *InsertStandart(StructSet<T> *wheere, const T &value,
                               bool &is_add);
  template <class... Other>
  void ArgumentParser(vector<std::pair<iterator, bool>> &result, T first,
                      Other... other);
  void ArgumentParser(
      [[maybe_unused]] vector<std::pair<iterator, bool>> &result) {}
};

template <class T, class Compare>
template <class... Types>
s21::vector<std::pair<typename set<T, Compare>::iterator, bool>>
set<T, Compare>::emplace(Types &&...args) {
  vector<std::pair<iterator, bool>> result;
  ArgumentParser(result, args...);
  return result;
}

template <class T, class Compare>
template <class... Other>
void set<T, Compare>::ArgumentParser(vector<std::pair<iterator, bool>> &result,
                                     T first, Other... other) {
  result.push_back(insert(first));
  ArgumentParser(result, other...);
}

template <class T, class Compare>
typename set<T, Compare>::iterator set<T, Compare>::insert(iterator where,
                                                           const T &value) {
  bool is_add = true;
  StructSet<T> *res = InsertStandart(where.address_, value, is_add);
  return res ? res : anchor_;
}

template <class T, class Compare>
template <class InputIterator>
void set<T, Compare>::insert(InputIterator first, InputIterator last) {
  bool is_add = true;
  while (first != last) {
    if (!InsertStandart(anchor_->right, *first, is_add)) return;
    first++;
  }
}

template <class T, class Compare>
void set<T, Compare>::insert(std::initializer_list<T> init_list) {
  AddList(init_list);
}

template <class T, class Compare>
std::pair<typename set<T, Compare>::iterator, bool> set<T, Compare>::insert(
    const T &value) {
  bool second = true;
  iterator first = anchor_;
  StructSet<T> *tmp = InsertStandart(anchor_->right, value, second);
  if (tmp) first = tmp;
  std::pair<iterator, bool> result(first, second);
  return result;
}

template <class T, class Compare>
class std::pair<typename set<T, Compare>::iterator,
                typename set<T, Compare>::iterator>
set<T, Compare>::equal_range(const T &value) {
  iterator first = lower_bound(value);
  iterator second = upper_bound(value);
  std::pair<iterator, iterator> result(first, second);
  return result;
}

template <class T, class Compare>
class std::pair<typename set<T, Compare>::const_iterator,
                typename set<T, Compare>::const_iterator>
set<T, Compare>::equal_range(const T &value) const {
  const_iterator first = lower_bound(value);
  const_iterator second = upper_bound(value);
  std::pair<const_iterator, const_iterator> result(first, second);
  return result;
}

template <class T, class Compare>
void set<T, Compare>::AddList(std::initializer_list<T> init_list) {
  T *ptr = (T *)init_list.begin();
  bool is_add = true;
  for (int i = 0; i < static_cast<int>(init_list.size()); i++, ptr++) {
    if (!InsertStandart(anchor_->right, *ptr, is_add)) {
      clear();
      return;
    }
  }
}

template <class T, class Compare>
void set<T, Compare>::swap(set &right) {
  std::swap(anchor_, right.anchor_);
  std::swap(size_, right.size_);
}

template <class T, class Compare>
set<T, Compare> &set<T, Compare>::operator=(const set &right) {
  set tmp(right);
  swap(tmp);
  return *this;
}

template <class T, class Compare>
set<T, Compare> &set<T, Compare>::operator=(set &&right) {
  swap(right);
  return *this;
}

template <class T, class Compare>
void set<T, Compare>::clear() {
  if (anchor_->right != anchor_ && anchor_->right != nullptr)
    FreeSet(anchor_->right);
  anchor_->left = anchor_->right = nullptr;
}

template <class T, class Compare>
typename set<T, Compare>::iterator set<T, Compare>::upper_bound(
    const T &value) {
  iterator result = end();
  if (anchor_->right != nullptr) {
    StructSet<T> *position = FindPosition(anchor_->right, value);
    if (comp_(position->value, value) || position->value == value)
      result = ClosestRight(position);
    else
      result = position;
  }
  return result;
}

template <class T, class Compare>
typename set<T, Compare>::iterator set<T, Compare>::lower_bound(
    const T &value) {
  iterator result = end();
  if (anchor_->right != nullptr) {
    StructSet<T> *position = FindPosition(anchor_->right, value);
    if (comp_(position->value, value))
      result = ClosestRight(position);
    else
      result = position;
  }
  return result;
}

template <class T, class Compare>
typename set<T, Compare>::const_iterator set<T, Compare>::upper_bound(
    const T &value) const {
  const_iterator result = end();
  if (anchor_->right != nullptr) {
    StructSet<T> *position = FindPosition(anchor_->right, value);
    if (comp_(position->value, value) || position->value == value)
      result = ClosestRight(position);
    else
      result = position;
  }
  return result;
}

template <class T, class Compare>
typename set<T, Compare>::const_iterator set<T, Compare>::lower_bound(
    const T &value) const {
  const_iterator result = end();
  if (anchor_->right != nullptr) {
    StructSet<T> *position = FindPosition(anchor_->right, value);
    if (comp_(position->value, value))
      result = ClosestRight(position);
    else
      result = position;
  }
  return result;
}

template <class T, class Compare>
typename set<T, Compare>::iterator set<T, Compare>::find(const T &value) {
  iterator result = end();
  if (anchor_->right != nullptr) {
    StructSet<T> *position = FindPosition(anchor_->right, value);
    if (position->value == value) result = position;
  }
  return result;
}

template <class T, class Compare>
typename set<T, Compare>::const_iterator set<T, Compare>::find(
    const T &value) const {
  const_iterator result = end();
  if (anchor_->right != nullptr) {
    StructSet<T> *position = FindPosition(anchor_->right, value);
    if (position->value == value) result = position;
  }
  return result;
}

template <class T, class Compare>
size_t set<T, Compare>::count(const T &value) const {
  size_t result = 0;
  if (anchor_->right != nullptr) {
    StructSet<T> *position = FindPosition(anchor_->right, value);
    if (position->value == value) result = 1;
  }
  return result;
}

template <class T, class Compare>
bool set<T, Compare>::empty() const {
  return !size_;
}

template <class T, class Compare>
set<T, Compare>::set() {}

template <class T, class Compare>
set<T, Compare>::set(std::initializer_list<T> init_list) {
  AddList(init_list);
}

template <class T, class Compare>
template <class InputIterator>
set<T, Compare>::set(InputIterator first, InputIterator last) {
  bool is_add = true;
  while (first != last) {
    if (!InsertStandart(anchor_->right, *first, is_add)) {
      clear();
      return;
    }
    first++;
  }
}

template <class T, class Compare>
void set<T, Compare>::CopySet(const set &right) {
  bool is_add = true;
  const_iterator begin = right.begin(), end = right.end();
  while (begin != end) {
    if (!InsertStandart(anchor_->right, *begin, is_add)) {
      clear();
      return;
    }
    begin++;
  }
}

template <class T, class Compare>
set<T, Compare>::set(set &&right) {
  swap(right);
}

template <class T, class Compare>
set<T, Compare>::set(const set &right) {
  CopySet(right);
}

template <class T, class Compare>
size_t set<T, Compare>::size() const {
  return size_;
}

template <class T, class Compare>
int set<T, Compare>::ComparisonList(const set &other) const {
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
typename set<T, Compare>::iterator set<T, Compare>::erase(iterator first,
                                                          iterator last) {
  while (first != last) {
    first = erase(first);
  }
  return first;
}

template <class T, class Compare>
size_t set<T, Compare>::erase(const T &value) {
  size_t result = 0;
  if (anchor_->right != nullptr) {
    StructSet<T> *position = FindPosition(anchor_->right, value);
    if (value == position->value) {
      erase(position);
      result++;
    }
  }
  return result;
}

template <class T, class Compare>
typename set<T, Compare>::iterator set<T, Compare>::erase(iterator where) {
  StructSet<T> *position = where.address_;
  StructSet<T> *parent = position->parent;
  iterator result = ClosestRight(where.address_);
  if (position == anchor_) return result;
  if (position->left == nullptr && position->right == nullptr) {
    if (parent->right == position) {
      parent->right = nullptr;
    } else {
      parent->left = nullptr;
    }
  } else if (position->left == nullptr) {
    if (parent->right == position) {
      parent->right = position->right;
      parent->right->parent = parent;
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
    StructSet<T> *change = ClosestLeft(position);
    position->value = change->value;
    erase(change);
    return result;
  }
  if (parent == anchor_) anchor_->left = anchor_->right;
  delete position;
  size_--;
  return result;
}

template <class T, class Compare>
set<T, Compare>::~set() {
  if (anchor_->right != anchor_ && anchor_->right) FreeSet(anchor_->right);
  delete anchor_;
}

template <class T, class Compare>
void set<T, Compare>::FreeSet(StructSet<T> *root) {
  if (root->left != nullptr) FreeSet(root->left);
  if (root->right != nullptr) FreeSet(root->right);
  delete root;
  size_--;
}

template <class T, class Compare>
void set<T, Compare>::Adjustment(StructSet<T> *value) {
  StructSet<T> *parent = value->parent;
  if ((parent->right != nullptr && parent->right->is_red == true) &&
      (parent->left != nullptr && parent->left->is_red == true))
    SwapColors(value);
  if ((parent->right != nullptr && parent->right == value) &&
      value->is_red == true)
    RightTurn(value);
  if (parent->is_red == true && value->is_red == true) LeftTurn(value);
}

template <class T, class Compare>
void set<T, Compare>::LeftTurn(StructSet<T> *value) {
  StructSet<T> *parent = value->parent;
  StructSet<T> *grandfather = parent->parent;
  if (grandfather == anchor_->right) {
    anchor_->left = anchor_->right = parent;
    parent->parent = anchor_;
  }
  StructSet<T> *great_grandfather = grandfather->parent;
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
void set<T, Compare>::RightTurn(StructSet<T> *value) {
  StructSet<T> *parent = value->parent;
  if (parent == anchor_->right) {
    anchor_->left = anchor_->right = value;
    value->parent = anchor_;
  }
  StructSet<T> *grandfather = parent->parent;
  StructSet<T> *swap = value->left;
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
void set<T, Compare>::SwapColors(StructSet<T> *value) {
  StructSet<T> *parent = value->parent;
  parent->right->is_red = false;
  parent->left->is_red = false;
  if (parent != anchor_->right) {
    parent->is_red = true;
    Adjustment(parent);
  }
}

template <class T, class Compare>
StructSet<T> *set<T, Compare>::CreateAnchor() {
  StructSet<T> *result;
  result = CreatePart();
  if (!result) return nullptr;
  result->parent = result;
  size_--;
  return result;
}

template <class T, class Compare>
StructSet<T> *set<T, Compare>::Smallest(StructSet<T> *value) const {
  while (value->left != nullptr) value = value->left;
  return value;
}

template <class T, class Compare>
typename set<T, Compare>::iterator set<T, Compare>::end() {
  return anchor_;
}

template <class T, class Compare>
typename set<T, Compare>::const_iterator set<T, Compare>::end() const {
  return anchor_;
}

template <class T, class Compare>
typename set<T, Compare>::const_iterator set<T, Compare>::cend() const {
  return anchor_;
}

template <class T, class Compare>
typename set<T, Compare>::iterator set<T, Compare>::begin() {
  return anchor_->right ? Smallest(anchor_->right) : anchor_;
}

template <class T, class Compare>
typename set<T, Compare>::const_iterator set<T, Compare>::begin() const {
  return anchor_->right ? Smallest(anchor_->right) : anchor_;
}

template <class T, class Compare>
typename set<T, Compare>::const_iterator set<T, Compare>::cbegin() const {
  return anchor_->right ? Smallest(anchor_->right) : anchor_;
}

template <class T, class Compare>
typename set<T, Compare>::reverse_iterator set<T, Compare>::rend() {
  return static_cast<reverse_iterator>(begin());
}

template <class T, class Compare>
typename set<T, Compare>::const_reverse_iterator set<T, Compare>::rend() const {
  return static_cast<const_reverse_iterator>(begin());
}

template <class T, class Compare>
typename set<T, Compare>::const_reverse_iterator set<T, Compare>::crend()
    const {
  return static_cast<const_reverse_iterator>(begin());
}

template <class T, class Compare>
typename set<T, Compare>::reverse_iterator set<T, Compare>::rbegin() {
  return static_cast<reverse_iterator>(end());
}

template <class T, class Compare>
typename set<T, Compare>::const_reverse_iterator set<T, Compare>::rbegin()
    const {
  return static_cast<const_reverse_iterator>(end());
}

template <class T, class Compare>
typename set<T, Compare>::const_reverse_iterator set<T, Compare>::crbegin()
    const {
  return static_cast<const_reverse_iterator>(end());
}

template <class T, class Compare>
StructSet<T> *set<T, Compare>::FindPosition(StructSet<T> *root,
                                            const T &value) const {
  StructSet<T> *pos = root;
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
StructSet<T> *set<T, Compare>::InsertStandart(StructSet<T> *wheere,
                                              const T &value, bool &is_add) {
  if (!anchor_) return nullptr;
  StructSet<T> *position = anchor_;
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
      is_add = false;
    }
  }
  if (is_add) {
    try {
      position->value = value;
    } catch (...) {
      erase(position);
      is_add = false;
      return nullptr;
    }
  }
  return position;
}

template <class T, class Compare>
StructSet<T> *set<T, Compare>::CreatePart() {
  StructSet<T> *result;
  try {
    result = new StructSet<T>;
  } catch (...) {
    return nullptr;
  }
  size_++;
  result->left = nullptr;
  result->right = nullptr;
  result->parent = nullptr;
  result->is_red = false;
  return result;
}

}  // namespace s21
#endif  // SRC_SET_H_