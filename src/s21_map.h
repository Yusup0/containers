#ifndef CONTAINERS_SRC_MAP_H_
#define CONTAINERS_SRC_MAP_H_

#include <stdlib.h>

#include <iostream>

#include "./general.h"
#include "./s21_vector.h"

namespace s21 {

template <class Key, class T, class Compare = std::less<Key>>
class map;

template <class Key, class T>
struct StructMap {
  StructMap<Key, T> *left;
  StructMap<Key, T> *right;
  StructMap<Key, T> *parent;
  Key first;
  T second;
  bool is_red;
};

template <class Key, class T, class Compare, class ConstType = T,
          class Struct = StructMap<Key, T>>
class MapIterator {
  friend class map<Key, T, Compare>;

 public:
  using value_type = ConstType;
  using pointer = ConstType *;
  using reference = ConstType &;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::bidirectional_iterator_tag;

  MapIterator() {}
  MapIterator(StructMap<Key, T> *address) : address_(address) {}
  MapIterator(const MapIterator &other) : address_(other.address_) {}
  MapIterator(MapIterator &&other) { address_ = std::move(other.address_); }
  MapIterator &operator=(const MapIterator &other) {
    if (this != &other) address_ = other.address_;
    return *this;
  }
  MapIterator &operator=(MapIterator &&other) {
    if (this != &other) address_ = std::move(other.address_);
    return *this;
  }
  ~MapIterator() {}
  const Key first() const { return address_->first; }
  reference second() const { return address_->second; }
  reference operator*() const { return address_->second; }
  MapIterator &operator++() {
    address_ = ClosestRight(address_);
    return *this;
  }
  MapIterator operator++(int) {
    MapIterator result = *this;
    address_ = ClosestRight(address_);
    return result;
  }
  MapIterator &operator--() {
    address_ = ClosestLeft(address_);
    return *this;
  }
  MapIterator operator--(int) {
    MapIterator result = *this;
    address_ = ClosestLeft(address_);
    return result;
  }
  bool operator==(const MapIterator it) const {
    return address_ == it.address_;
  }
  bool operator!=(const MapIterator it) const {
    return address_ != it.address_;
  }

 private:
  Struct *address_;
};

template <class Key, class T, class Compare>
class map {
 public:
  using value_type = std::pair<const Key, T>;
  using iterator = MapIterator<Key, T, Compare>;
  using const_iterator =
      MapIterator<Key, T, Compare, const T, const StructMap<Key, T>>;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  map();
  map(std::initializer_list<value_type> init_list);
  template <class InputIterator>
  map(InputIterator first, InputIterator last);
  map(map &&right);
  map(const map &right);
  map<Key, T, Compare> &operator=(const map &right);
  map<Key, T, Compare> &operator=(map &&right);
  ~map();
  template <class... Types>
  vector<std::pair<iterator, bool>> emplace(Types &&...args);
  bool operator<(map &other) const { return ComparisonList(other) == -1; }
  bool operator>(map &other) const { return ComparisonList(other) == 1; }
  bool operator==(map &other) const { return !ComparisonList(other); }
  bool operator!=(map &other) const { return ComparisonList(other); }
  bool operator<=(map &other) const {
    return !ComparisonList(other) || ComparisonList(other) == -1;
  }
  bool operator>=(map &other) const {
    return !ComparisonList(other) || ComparisonList(other) == 1;
  }
  std::pair<iterator, bool> insert(const value_type &value);
  void insert(std::initializer_list<value_type> init_list);
  iterator insert(iterator where, const value_type &value);
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
  size_t erase(const Key &value);
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
  void swap(map &right);
  std::pair<iterator, iterator> equal_range(const T &value);
  std::pair<const_iterator, const_iterator> equal_range(const T &value) const;

 private:
  StructMap<Key, T> *anchor_ = CreateAnchor();
  Compare comp_;
  size_t size_ = 0;
  void Adjustment(StructMap<Key, T> *value);
  StructMap<Key, T> *CreatePart();
  StructMap<Key, T> *FindPosition(StructMap<Key, T> *root,
                                  const Key &value) const;
  StructMap<Key, T> *Smallest(StructMap<Key, T> *value) const;
  StructMap<Key, T> *CreateAnchor();
  void SwapColors(StructMap<Key, T> *value);
  void LeftTurn(StructMap<Key, T> *value);
  void RightTurn(StructMap<Key, T> *value);
  void FreeSet(StructMap<Key, T> *root);
  int ComparisonList(const map &other) const;
  void CopyMap(const map &right);
  void AddList(std::initializer_list<value_type> init_list);
  StructMap<Key, T> *InsertStandart(StructMap<Key, T> *wheere,
                                    const value_type &value, bool &is_add);
  template <class... Other>
  void ArgumentParser(vector<std::pair<iterator, bool>> &result,
                      value_type first, Other... other);
  void ArgumentParser(
      [[maybe_unused]] vector<std::pair<iterator, bool>> &result) {}
};

template <class Key, class T, class Compare>
template <class... Types>
vector<std::pair<typename map<Key, T, Compare>::iterator, bool>>
map<Key, T, Compare>::emplace(Types &&...args) {
  vector<std::pair<iterator, bool>> result;
  ArgumentParser(result, args...);
  return result;
}

template <class Key, class T, class Compare>
template <class... Other>
void map<Key, T, Compare>::ArgumentParser(
    vector<std::pair<iterator, bool>> &result, value_type first,
    Other... other) {
  result.push_back(insert(first));
  ArgumentParser(result, other...);
}

template <class Key, class T, class Compare>
typename map<Key, T, Compare>::iterator map<Key, T, Compare>::insert(
    iterator where, const value_type &value) {
  bool is_add = true;
  StructMap<Key, T> *res = InsertStandart(where.address_, value, is_add);
  return res ? res : anchor_;
}

template <class Key, class T, class Compare>
template <class InputIterator>
void map<Key, T, Compare>::insert(InputIterator first, InputIterator last) {
  bool is_add = true;
  while (first != last) {
    value_type i(first.first(), first.second());
    if (!InsertStandart(anchor_->right, i, is_add)) return;
    first++;
  }
}

template <class Key, class T, class Compare>
void map<Key, T, Compare>::insert(std::initializer_list<value_type> init_list) {
  AddList(init_list);
}

template <class Key, class T, class Compare>
std::pair<typename map<Key, T, Compare>::iterator, bool>
map<Key, T, Compare>::insert(const value_type &value) {
  bool second = true;
  iterator first = anchor_;
  StructMap<Key, T> *tmp = InsertStandart(anchor_->right, value, second);
  if (tmp) first = tmp;
  std::pair<iterator, bool> result(first, second);
  return result;
}

template <class Key, class T, class Compare>
class std::pair<typename map<Key, T, Compare>::iterator,
                typename map<Key, T, Compare>::iterator>
map<Key, T, Compare>::equal_range(const T &value) {
  iterator first = lower_bound(value);
  iterator second = upper_bound(value);
  std::pair<iterator, iterator> result(first, second);
  return result;
}

template <class Key, class T, class Compare>
class std::pair<typename map<Key, T, Compare>::const_iterator,
                typename map<Key, T, Compare>::const_iterator>
map<Key, T, Compare>::equal_range(const T &value) const {
  const_iterator first = lower_bound(value);
  const_iterator second = upper_bound(value);
  std::pair<const_iterator, const_iterator> result(first, second);
  return result;
}

template <class Key, class T, class Compare>
void map<Key, T, Compare>::AddList(
    std::initializer_list<value_type> init_list) {
  value_type *ptr = (value_type *)init_list.begin();
  bool is_add = true;
  for (int i = 0; i < static_cast<int>(init_list.size()); i++, ptr++) {
    if (!InsertStandart(anchor_->right, *ptr, is_add)) {
      clear();
      return;
    }
  }
}

template <class Key, class T, class Compare>
void map<Key, T, Compare>::swap(map &right) {
  std::swap(anchor_, right.anchor_);
  std::swap(size_, right.size_);
}

template <class Key, class T, class Compare>
map<Key, T, Compare> &map<Key, T, Compare>::operator=(const map &right) {
  map tmp(right);
  swap(tmp);
  return *this;
}

template <class Key, class T, class Compare>
map<Key, T, Compare> &map<Key, T, Compare>::operator=(map &&right) {
  swap(right);
  return *this;
}

template <class Key, class T, class Compare>
void map<Key, T, Compare>::clear() {
  if (anchor_->right != anchor_ && anchor_->right != nullptr)
    FreeSet(anchor_->right);
  anchor_->left = anchor_->right = nullptr;
}

template <class Key, class T, class Compare>
typename map<Key, T, Compare>::iterator map<Key, T, Compare>::upper_bound(
    const T &value) {
  iterator result = end();
  if (anchor_->right != nullptr) {
    StructMap<Key, T> *position = FindPosition(anchor_->right, value);
    if (comp_(position->first, value) || position->first == value)
      result = ClosestRight(position);
    else
      result = position;
  }
  return result;
}

template <class Key, class T, class Compare>
typename map<Key, T, Compare>::const_iterator map<Key, T, Compare>::upper_bound(
    const T &value) const {
  const_iterator result = end();
  if (anchor_->right != nullptr) {
    StructMap<Key, T> *position = FindPosition(anchor_->right, value);
    if (comp_(position->first, value) || position->first == value)
      result = ClosestRight(position);
    else
      result = position;
  }
  return result;
}

template <class Key, class T, class Compare>
typename map<Key, T, Compare>::iterator map<Key, T, Compare>::lower_bound(
    const T &value) {
  iterator result = end();
  if (anchor_->right != nullptr) {
    StructMap<Key, T> *position = FindPosition(anchor_->right, value);
    if (comp_(position->first, value))
      result = ClosestRight(position);
    else
      result = position;
  }
  return result;
}

template <class Key, class T, class Compare>
typename map<Key, T, Compare>::const_iterator map<Key, T, Compare>::lower_bound(
    const T &value) const {
  const_iterator result = end();
  if (anchor_->right != nullptr) {
    StructMap<Key, T> *position = FindPosition(anchor_->right, value);
    if (comp_(position->first, value))
      result = ClosestRight(position);
    else
      result = position;
  }
  return result;
}

template <class Key, class T, class Compare>
typename map<Key, T, Compare>::iterator map<Key, T, Compare>::find(
    const T &value) {
  iterator result = end();
  if (anchor_->right != nullptr) {
    StructMap<Key, T> *position = FindPosition(anchor_->right, value);
    if (position->first == value) result = position;
  }
  return result;
}

template <class Key, class T, class Compare>
typename map<Key, T, Compare>::const_iterator map<Key, T, Compare>::find(
    const T &value) const {
  const_iterator result = end();
  if (anchor_->right != nullptr) {
    StructMap<Key, T> *position = FindPosition(anchor_->right, value);
    if (position->first == value) result = position;
  }
  return result;
}

template <class Key, class T, class Compare>
size_t map<Key, T, Compare>::count(const T &value) const {
  if (anchor_->right != nullptr) {
    StructMap<Key, T> *position = FindPosition(anchor_->right, value);
    if (position->first == value) return 1;
  }
  return 0;
}

template <class Key, class T, class Compare>
bool map<Key, T, Compare>::empty() const {
  return !size_;
}

template <class Key, class T, class Compare>
map<Key, T, Compare>::map() {}

template <class Key, class T, class Compare>
map<Key, T, Compare>::map(std::initializer_list<value_type> init_list) {
  AddList(init_list);
}

template <class Key, class T, class Compare>
template <class InputIterator>
map<Key, T, Compare>::map(InputIterator first, InputIterator last) {
  bool is_add = true;
  while (first != last) {
    value_type value(first.first(), first.second());
    if (!InsertStandart(anchor_->right, value, is_add)) {
      clear();
      return;
    }
    first++;
  }
}

template <class Key, class T, class Compare>
void map<Key, T, Compare>::CopyMap(const map &right) {
  bool is_add = true;
  const_iterator begin = right.begin(), end = right.end();
  while (begin != end) {
    value_type value(begin.first(), begin.second());
    if (!InsertStandart(anchor_->right, value, is_add)) {
      clear();
      return;
    }
    begin++;
  }
}

template <class Key, class T, class Compare>
map<Key, T, Compare>::map(map &&right) {
  swap(right);
}

template <class Key, class T, class Compare>
map<Key, T, Compare>::map(const map &right) {
  CopyMap(right);
}

template <class Key, class T, class Compare>
size_t map<Key, T, Compare>::size() const {
  return size_;
}

template <class Key, class T, class Compare>
int map<Key, T, Compare>::ComparisonList(const map &other) const {
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

template <class Key, class T, class Compare>
typename map<Key, T, Compare>::iterator map<Key, T, Compare>::erase(
    iterator first, iterator last) {
  while (first != last) {
    first = erase(first);
  }
  return first;
}

template <class Key, class T, class Compare>
size_t map<Key, T, Compare>::erase(const Key &value) {
  size_t result = 0;
  if (anchor_->right != nullptr) {
    StructMap<Key, T> *position = FindPosition(anchor_->right, value);
    if (value == position->first) {
      erase(position);
      result++;
    }
  }
  return result;
}

template <class Key, class T, class Compare>
typename map<Key, T, Compare>::iterator map<Key, T, Compare>::erase(
    iterator where) {
  StructMap<Key, T> *position = where.address_, *parent = position->parent;
  iterator result = ClosestRight(where.address_);
  if (position == anchor_) return result;
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
    StructMap<Key, T> *change = ClosestLeft(position);
    position->first = change->first;
    position->second = change->second;
    erase(change);
    return result;
  }
  if (parent == anchor_) anchor_->left = anchor_->right;
  delete position;
  size_--;
  return result;
}

template <class Key, class T, class Compare>
map<Key, T, Compare>::~map() {
  if (anchor_->right != anchor_ && anchor_->right != nullptr)
    FreeSet(anchor_->right);
  delete anchor_;
}

template <class Key, class T, class Compare>
void map<Key, T, Compare>::FreeSet(StructMap<Key, T> *root) {
  if (root->left != nullptr) FreeSet(root->left);
  if (root->right != nullptr) FreeSet(root->right);
  delete root;
  size_--;
}

template <class Key, class T, class Compare>
void map<Key, T, Compare>::Adjustment(StructMap<Key, T> *value) {
  StructMap<Key, T> *parent = value->parent;
  if ((parent->right != nullptr && parent->right->is_red == true) &&
      (parent->left != nullptr && parent->left->is_red == true))
    SwapColors(value);
  if ((parent->right != nullptr && parent->right == value) &&
      value->is_red == true)
    RightTurn(value);
  if (parent->is_red == true && value->is_red == true) LeftTurn(value);
}

template <class Key, class T, class Compare>
void map<Key, T, Compare>::LeftTurn(StructMap<Key, T> *value) {
  StructMap<Key, T> *parent = value->parent;
  StructMap<Key, T> *grandfather = parent->parent;
  if (grandfather == anchor_->right) {
    anchor_->left = anchor_->right = parent;
    parent->parent = anchor_;
  }
  StructMap<Key, T> *great_grandfather = grandfather->parent;
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

template <class Key, class T, class Compare>
void map<Key, T, Compare>::RightTurn(StructMap<Key, T> *value) {
  StructMap<Key, T> *parent = value->parent;
  if (parent == anchor_->right) {
    anchor_->left = anchor_->right = value;
    value->parent = anchor_;
  }
  StructMap<Key, T> *grandfather = parent->parent;

  StructMap<Key, T> *swap = value->left;
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

template <class Key, class T, class Compare>
void map<Key, T, Compare>::SwapColors(StructMap<Key, T> *value) {
  StructMap<Key, T> *parent = value->parent;
  parent->right->is_red = false;
  parent->left->is_red = false;
  if (parent != anchor_->right) {
    parent->is_red = true;
    Adjustment(parent);
  }
}

template <class Key, class T, class Compare>
StructMap<Key, T> *map<Key, T, Compare>::CreateAnchor() {
  StructMap<Key, T> *result;
  result = CreatePart();
  if (!result) return nullptr;
  result->parent = result;
  size_--;
  return result;
}

template <class Key, class T, class Compare>
StructMap<Key, T> *map<Key, T, Compare>::Smallest(
    StructMap<Key, T> *value) const {
  while (value->left != nullptr) value = value->left;
  return value;
}

template <class Key, class T, class Compare>
typename map<Key, T, Compare>::iterator map<Key, T, Compare>::end() {
  return anchor_;
}

template <class Key, class T, class Compare>
typename map<Key, T, Compare>::const_iterator map<Key, T, Compare>::end()
    const {
  return anchor_;
}

template <class Key, class T, class Compare>
typename map<Key, T, Compare>::const_iterator map<Key, T, Compare>::cend()
    const {
  return anchor_;
}

template <class Key, class T, class Compare>
typename map<Key, T, Compare>::iterator map<Key, T, Compare>::begin() {
  return anchor_->right ? Smallest(anchor_->right) : anchor_;
}

template <class Key, class T, class Compare>
typename map<Key, T, Compare>::const_iterator map<Key, T, Compare>::begin()
    const {
  return anchor_->right ? Smallest(anchor_->right) : anchor_;
}

template <class Key, class T, class Compare>
typename map<Key, T, Compare>::const_iterator map<Key, T, Compare>::cbegin()
    const {
  return anchor_->right ? Smallest(anchor_->right) : anchor_;
}

template <class Key, class T, class Compare>
typename map<Key, T, Compare>::reverse_iterator map<Key, T, Compare>::rend() {
  return static_cast<reverse_iterator>(begin());
}

template <class Key, class T, class Compare>
typename map<Key, T, Compare>::const_reverse_iterator
map<Key, T, Compare>::rend() const {
  return static_cast<const_reverse_iterator>(begin());
}

template <class Key, class T, class Compare>
typename map<Key, T, Compare>::const_reverse_iterator
map<Key, T, Compare>::crend() const {
  return static_cast<const_reverse_iterator>(begin());
}

template <class Key, class T, class Compare>
typename map<Key, T, Compare>::reverse_iterator map<Key, T, Compare>::rbegin() {
  return static_cast<reverse_iterator>(end());
}

template <class Key, class T, class Compare>
typename map<Key, T, Compare>::const_reverse_iterator
map<Key, T, Compare>::rbegin() const {
  return static_cast<const_reverse_iterator>(end());
}

template <class Key, class T, class Compare>
typename map<Key, T, Compare>::const_reverse_iterator
map<Key, T, Compare>::crbegin() const {
  return static_cast<const_reverse_iterator>(end());
}

template <class Key, class T, class Compare>
StructMap<Key, T> *map<Key, T, Compare>::FindPosition(StructMap<Key, T> *root,
                                                      const Key &value) const {
  StructMap<Key, T> *pos = root;
  if (comp_(root->first, value)) {
    if (root->right == nullptr) {
      pos = root;
    } else {
      pos = FindPosition(root->right, value);
    }
  } else if (comp_(value, root->first)) {
    if (root->left == nullptr) {
      pos = root;
    } else {
      pos = FindPosition(root->left, value);
    }
  }
  return pos;
}

template <class Key, class T, class Compare>
StructMap<Key, T> *map<Key, T, Compare>::InsertStandart(
    StructMap<Key, T> *wheere, const value_type &value, bool &is_add) {
  if (!anchor_) return nullptr;
  StructMap<Key, T> *position = anchor_;
  if (size_ == 0) {
    anchor_->left = anchor_->right = CreatePart();
    if (!anchor_->left) return nullptr;
    position = anchor_->right;
    position->parent = anchor_;
  } else {
    position = FindPosition(wheere, value.first);
    if (position->first != value.first) {
      if (comp_(position->first, value.first)) {
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
      position->first = value.first;
      position->second = value.second;
    } catch (...) {
      erase(position);
      is_add = false;
      return nullptr;
    }
  }
  return position;
}

template <class Key, class T, class Compare>
StructMap<Key, T> *map<Key, T, Compare>::CreatePart() {
  StructMap<Key, T> *result;
  try {
    result = new StructMap<Key, T>;
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
#endif  // CONTAINERS_SRC_MAP_H_