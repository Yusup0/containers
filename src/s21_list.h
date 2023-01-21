#ifndef CONTAINERS_SRC_LIST_H_
#define CONTAINERS_SRC_LIST_H_

#include <stdlib.h>

#include <iostream>
#include <iterator>

namespace s21 {

template <class T>
class list;

template <class T>
struct StructList {
  StructList<T> *p_next;
  StructList<T> *p_prev;
  T value = T();
};

template <class T, class Reference = T, class Struct = StructList<T>>
class ListIterator {
  friend class list<T>;

 public:
  using value_type = Reference;
  using pointer = Reference *;
  using reference = Reference &;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::bidirectional_iterator_tag;

  ListIterator() {}
  ListIterator(StructList<T> *address) : address_(address) {}
  ListIterator(const ListIterator &other) : address_(other.address_) {}
  ListIterator(ListIterator &&other) { address_ = std::move(other.address_); }
  ListIterator &operator=(const ListIterator &other) {
    if (this != &other) address_ = other.address_;
    return *this;
  }
  ListIterator &operator=(ListIterator &&other) {
    if (this != &other) address_ = std::move(other.address_);
    return *this;
  }
  ~ListIterator(){};
  reference operator*() const { return address_->value; }
  ListIterator &operator++() {
    address_ = address_->p_next;
    return *this;
  }
  ListIterator operator++(int) {
    address_ = address_->p_next;
    return address_->p_prev;
  }
  ListIterator &operator--() {
    address_ = address_->p_prev;
    return *this;
  }
  ListIterator operator--(int) {
    address_ = address_->p_prev;
    return address_->p_next;
  }
  bool operator==(const ListIterator it) const {
    return address_ == it.address_;
  }
  bool operator!=(const ListIterator it) const {
    return address_ != it.address_;
  }

 private:
  Struct *address_;
};

template <class T>
class list {
 public:
  using iterator = ListIterator<T>;
  using const_iterator = ListIterator<T, const T, const StructList<T>>;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  explicit list(int count);
  template <class InputIterator>
  list(InputIterator first, InputIterator last);
  list();
  list(size_t count, T value);
  list(list &&right);
  list(std::initializer_list<T> init_list);
  list(const list &right);
  template <class Container>
  list<T> &operator=(const Container &right);
  list<T> &operator=(list &right);
  list<T> &operator=(list &&right);
  ~list();
  bool operator<(list &other) const { return ComparisonList(other) == -1; }
  bool operator>(list &other) const { return ComparisonList(other) == 1; }
  bool operator==(list &other) const { return !ComparisonList(other); }
  bool operator!=(list &other) const { return ComparisonList(other); }
  bool operator<=(list &other) const {
    return !ComparisonList(other) || ComparisonList(other) == -1;
  }
  bool operator>=(list &other) const {
    return !ComparisonList(other) || ComparisonList(other) == 1;
  }
  template <class... Types>
  iterator emplace(iterator position, Types &&...args);
  template <class... Types>
  void emplace_back(Types &&...args);
  template <class... Types>
  void emplace_front(Types &&...args);
  size_t size() const;
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
  bool empty() const;
  void assign(size_t count, T value);
  template <class InputIterator>
  void assign(InputIterator first, InputIterator last);
  void assign(std::initializer_list<T> init_list);
  void swap(list &other);
  T &front();
  const T &front() const;
  T &back();
  const T &back() const;
  void push_back(const T &value);
  void push_front(const T &value);
  void pop_back();
  void pop_front();
  iterator insert(iterator where, const T &value);
  iterator insert(iterator where, size_t count, const T &value);
  iterator insert(iterator where, std::initializer_list<T> init_list);
  template <class InputIterator>
  void insert(iterator where, InputIterator first, InputIterator last);
  iterator erase(iterator where);
  iterator erase(iterator first, iterator last);
  void remove(const T &value);
  template <class Predicate>
  void remove_if(Predicate pred);
  void resize(size_t new_size, T value = T());
  void clear();
  void unique();
  template <class BinaryPredicate>
  void unique(BinaryPredicate pred);
  void splice(iterator position, list<T> &donor);
  void splice(iterator position, list<T> &donor, iterator donor_position);
  void splice(iterator position, list<T> &donor, iterator first, iterator last);
  void reverse();
  void sort();
  void merge(list<T> &right);

 private:
  StructList<T> *anchor_ = nullptr;
  size_t size_ = 0;
  StructList<T> *CreatePart();
  void CreateAnchor();
  bool CreateList(const size_t count);
  void AddToEnd(StructList<T> *value);
  int ComparisonList(const list &other) const;
  bool FillList(T value);
  bool FillList(std::initializer_list<T> init_list);
  void DeliteValue(StructList<T> *value);
  void DeliteList(StructList<T> *first, StructList<T> *last);
  void FreeMemoryList(StructList<T> *first, StructList<T> *last);
  void AddValue(StructList<T> *position, StructList<T> *value);
  void AddList(StructList<T> *position, StructList<T> *first,
               StructList<T> *last);
  void ArgumentParser([[maybe_unused]] StructList<T> *position) {}
  void BindList(StructList<T> *begin, StructList<T> *end) const;
  template <class... Other>
  void ArgumentParser(StructList<T> *position, T first, Other... other);
  template <class InputIterator>
  void CopyList(InputIterator first, InputIterator last);
};

template <class T>
template <class... Types>
void list<T>::emplace_back(Types &&...args) {
  list tmp;
  if (tmp.size_) {
    try {
      tmp.ArgumentParser(tmp.anchor_, args...);
    } catch (...) {
      return;
    }
    AddList(anchor_, tmp.anchor_->p_next, tmp.anchor_->p_prev);
    BindList(tmp.anchor_, tmp.anchor_);
    size_ += tmp.size();
  }
}

template <class T>
template <class... Types>
void list<T>::emplace_front(Types &&...args) {
  list tmp;
  if (tmp.size_) {
    try {
      tmp.ArgumentParser(tmp.anchor_, args...);
    } catch (...) {
      return;
    }
    AddList(anchor_->p_next, tmp.anchor_->p_next, tmp.anchor_->p_prev);
    BindList(tmp.anchor_, tmp.anchor_);
    size_ += tmp.size();
  }
}

template <class T>
list<T>::list() {
  CreateAnchor();
}

template <class T>
template <class InputIterator>
list<T>::list(InputIterator first, InputIterator last) {
  CopyList(first, last);
}

template <class T>
template <class Container>
list<T> &list<T>::operator=(const Container &right) {
  CopyList(right.begin(), right.end());
  return *this;
}

template <class T>
list<T> &list<T>::operator=(list &right) {
  CopyList(right.begin(), right.end());
  return *this;
}

template <class T>
list<T> &list<T>::operator=(list &&right) {
  swap(right);
  return *this;
}

template <class T>
template <class InputIterator>
void list<T>::CopyList(InputIterator first, InputIterator last) {
  list tmp(std::distance(first, last));
  if (tmp.size_) {
    iterator begin1 = tmp.begin();
    try {
      while (first != last) *begin1++ = *first++;
    } catch (...) {
      return;
    }
    swap(tmp);
  }
}

template <class T>
void list<T>::merge(list<T> &right) {
  StructList<T> *first = anchor_->p_next, *second = right.anchor_->p_next;
  StructList<T> *next, *next_second;
  while (second != right.anchor_) {
    next = first->p_next;
    if (first->value > second->value) {
      next_second = second->p_next;
      AddValue(first, second);
      second = next_second;
    } else {
      first = next;
    }
    if (first == anchor_) {
      AddList(first, second, right.anchor_->p_prev);
      break;
    }
  }
  size_ += right.size();
  right.size_ = 1;
  right.anchor_->p_next = right.anchor_;
  right.anchor_->p_prev = right.anchor_;
}

template <class T>
void list<T>::sort() {
  int size = size_ - 1;
  T tmp;
  StructList<T> *begin = anchor_->p_next->p_next;
  for (int i = 1; i < size; i++) {
    for (int j = 1; j <= size - i; j++) {
      if (begin->value < begin->p_prev->value) {
        tmp = begin->value;
        begin->value = begin->p_prev->value;
        begin->p_prev->value = tmp;
      }
      begin = begin->p_next;
    }
    begin = anchor_->p_next->p_next;
  }
}

template <class T>
void list<T>::reverse() {
  StructList<T> *temporarily;
  for (int i = 0; i < static_cast<int>(size_); i++) {
    temporarily = anchor_->p_next;
    anchor_->p_next = anchor_->p_prev;
    anchor_->p_prev = temporarily;
    anchor_ = anchor_->p_prev;
  }
}

template <class T>
void list<T>::splice(iterator position, list<T> &donor, iterator first,
                     iterator last) {
  int count_elements = std::distance(first, last);
  StructList<T> *begin = first.address_->p_prev, *end = last.address_->p_prev;
  BindList(begin, last.address_);
  BindList(position.address_->p_prev, first.address_);
  BindList(end, position.address_);
  if (&donor.anchor_ != &anchor_) {
    size_ += count_elements;
    donor.size_ -= count_elements;
  }
}

template <class T>
void list<T>::splice(iterator position, list<T> &donor,
                     iterator donor_position) {
  if (position != donor_position) {
    BindList(donor_position.address_->p_prev, donor_position.address_->p_next);
    AddValue(position.address_, donor_position.address_);
    if (&donor.anchor_ != &anchor_) {
      size_ += 1;
      donor.size_ -= 1;
    }
  }
}

template <class T>
void list<T>::AddList(StructList<T> *position, StructList<T> *first,
                      StructList<T> *last) {
  StructList<T> *begin = position->p_prev;
  begin->p_next = first;
  first->p_prev = begin;
  last->p_next = position;
  position->p_prev = last;
}

template <class T>
void list<T>::splice(iterator position, list<T> &donor) {
  AddList(position.address_, donor.anchor_->p_next, donor.anchor_->p_prev);
  size_ += donor.size();
  donor.size_ = 1;
  donor.anchor_->p_next = donor.anchor_;
  donor.anchor_->p_prev = donor.anchor_;
}

template <class T>
template <class BinaryPredicate>
void list<T>::unique(BinaryPredicate pred) {
  StructList<T> *begin = anchor_->p_next, *next;
  while (begin != anchor_) {
    next = begin->p_next;
    if (pred(begin->value)) DeliteValue(begin);
    begin = next;
  }
}

template <class T>
void list<T>::unique() {
  StructList<T> *begin = anchor_->p_next->p_next, *next;
  T value = begin->p_prev->value;
  while (begin != anchor_) {
    next = begin->p_next;
    if (value == begin->value) {
      DeliteValue(begin);
    } else {
      value = begin->value;
    }
    begin = next;
  }
}

template <class T>
template <class... Other>
void list<T>::ArgumentParser(StructList<T> *position, T first, Other... other) {
  StructList<T> *part = CreatePart();
  part->value = first;
  AddValue(position, part);
  ArgumentParser(position, other...);
}

template <class T>
template <class... Types>
typename list<T>::iterator list<T>::emplace(iterator position,
                                            Types &&...args) {
  iterator result = position.address_->p_prev;
  list tmp;
  try {
    tmp.ArgumentParser(tmp.anchor_, args...);
  } catch (...) {
    return anchor_;
  }
  AddList(position.address_, tmp.anchor_->p_next, tmp.anchor_->p_prev);
  BindList(tmp.anchor_, tmp.anchor_);
  size_ += tmp.size();
  return result;
}

template <class T>
void list<T>::clear() {
  DeliteList(anchor_->p_next, anchor_);
}

template <class T>
void list<T>::resize(size_t new_size, T value) {
  size_t size_our = size();
  if (size_our < new_size) {
    list tmp(new_size - size_our, value);
    if (tmp.size()) insert(anchor_, tmp.begin(), tmp.end());
  } else if (size_our > new_size) {
    for (int i = 0; i < static_cast<int>(size_our - new_size); i++) {
      DeliteValue(anchor_->p_prev);
    }
  }
}

template <class T>
template <class Predicate>
void list<T>::remove_if(Predicate pred) {
  StructList<T> *begin = anchor_->p_next, *next;
  while (begin != anchor_) {
    next = begin;
    begin = begin->p_next;
    if (pred(next->value)) DeliteValue(next);
  }
}

template <class T>
void list<T>::remove(const T &value) {
  StructList<T> *begin = anchor_->p_next, *next;
  while (begin != anchor_) {
    next = begin;
    begin = begin->p_next;
    if (next->value == value) DeliteValue(next);
  }
}

template <class T>
void list<T>::FreeMemoryList(StructList<T> *first, StructList<T> *last) {
  StructList<T> *next;
  while (first != last) {
    next = first->p_next;
    delete first;
    first = next;
    size_--;
  }
  size_--;
  delete last;
}

template <class T>
void list<T>::DeliteList(StructList<T> *first, StructList<T> *last) {
  StructList<T> *begin = first->p_prev;
  StructList<T> *end = last->p_prev;
  begin->p_next = last;
  last->p_prev = begin;
  FreeMemoryList(first, end);
}

template <class T>
typename list<T>::iterator list<T>::erase(iterator first, iterator last) {
  StructList<T> *result = last.address_;
  DeliteList(first.address_, last.address_);
  return result;
}

template <class T>
typename list<T>::iterator list<T>::erase(iterator where) {
  StructList<T> *result = where.address_->p_next;
  DeliteValue(where.address_);
  return result;
}

template <class T>
template <class InputIterator>
void list<T>::insert(iterator where, InputIterator first, InputIterator last) {
  list tmp(first, last);
  if (tmp.size()) {
    AddList(where.address_, tmp.anchor_->p_next, tmp.anchor_->p_prev);
    BindList(tmp.anchor_, tmp.anchor_);
    size_ += tmp.size();
  }
}

template <class T>
typename list<T>::iterator list<T>::insert(iterator where,
                                           std::initializer_list<T> init_list) {
  StructList<T> *result = where.address_->p_prev;
  list tmp(init_list);
  if (tmp.size()) {
    AddList(where.address_, tmp.anchor_->p_next, tmp.anchor_->p_prev);
    BindList(tmp.anchor_, tmp.anchor_);
    size_ += tmp.size();
    return result->p_next;
  }
  return anchor_->p_next;
}

template <class T>
typename list<T>::iterator list<T>::insert(iterator where, size_t count,
                                           const T &value) {
  StructList<T> *result = where.address_->p_prev;
  list tmp(count, value);
  if (tmp.size()) {
    AddList(where.address_, tmp.anchor_->p_next, tmp.anchor_->p_prev);
    BindList(tmp.anchor_, tmp.anchor_);
    size_ += tmp.size();
    return result->p_next;
  }
  return anchor_->p_next;
}

template <class T>
typename list<T>::iterator list<T>::insert(iterator where, const T &value) {
  size_t size_before = size_;
  StructList<T> *element = CreatePart();
  if (size_before == size_) return begin();
  element->value = value;
  AddValue(where.address_, element);
  return element;
}

template <class T>
void list<T>::push_front(const T &value) {
  size_t size_before = size_;
  StructList<T> *part = CreatePart();
  if (size_before < size_) {
    part->value = value;
    AddValue(anchor_->p_next, part);
  }
}

template <class T>
void list<T>::AddValue(StructList<T> *position, StructList<T> *value) {
  StructList<T> *begin = position->p_prev;
  begin->p_next = value;
  value->p_prev = begin;
  value->p_next = position;
  position->p_prev = value;
}

template <class T>
void list<T>::BindList(StructList<T> *begin, StructList<T> *end) const {
  begin->p_next = end;
  end->p_prev = begin;
}

template <class T>
void list<T>::DeliteValue(StructList<T> *value) {
  if (value != anchor_) {
    BindList(value->p_prev, value->p_next);
    delete value;
    size_--;
  }
}

template <class T>
void list<T>::pop_back() {
  DeliteValue(anchor_->p_prev);
}

template <class T>
void list<T>::pop_front() {
  DeliteValue(anchor_->p_next);
}

template <class T>
void list<T>::push_back(const T &value) {
  size_t size_before = size_;
  StructList<T> *part = CreatePart();
  if (size_before < size_) {
    part->value = value;
    AddToEnd(part);
  }
}

template <class T>
const T &list<T>::back() const {
  return anchor_->p_prev->value;
}

template <class T>
T &list<T>::back() {
  return anchor_->p_prev->value;
}

template <class T>
const T &list<T>::front() const {
  return anchor_->p_next->value;
}

template <class T>
T &list<T>::front() {
  return anchor_->p_next->value;
}

template <class T>
void list<T>::swap(list &other) {
  std::swap(anchor_, other.anchor_);
  std::swap(size_, other.size_);
}

template <class T>
void list<T>::assign(std::initializer_list<T> init_list) {
  list tmp(init_list);
  if (tmp.size_) swap(tmp);
}

template <class T>
template <class InputIterator>
void list<T>::assign(InputIterator first, InputIterator last) {
  list tmp(first, last);
  if (tmp.size_) swap(tmp);
}

template <class T>
void list<T>::assign(size_t count, T value) {
  list tmp(count, value);
  if (tmp.size_) swap(tmp);
}

template <class T>
bool list<T>::empty() const {
  return !size();
}

template <class T>
int list<T>::ComparisonList(const list &other) const {
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

template <class T>
typename list<T>::iterator list<T>::end() {
  return anchor_;
}

template <class T>
typename list<T>::const_iterator list<T>::end() const {
  return anchor_;
}

template <class T>
typename list<T>::const_iterator list<T>::cend() const {
  return anchor_;
}

template <class T>
typename list<T>::iterator list<T>::begin() {
  return anchor_->p_next;
}

template <class T>
typename list<T>::const_iterator list<T>::begin() const {
  return static_cast<const_iterator>(anchor_->p_next);
}

template <class T>
typename list<T>::const_iterator list<T>::cbegin() const {
  return static_cast<const_iterator>(anchor_->p_next);
}

template <class T>
typename list<T>::reverse_iterator list<T>::rend() {
  return static_cast<reverse_iterator>(anchor_->p_next);
}

template <class T>
typename list<T>::const_reverse_iterator list<T>::rend() const {
  return static_cast<const_reverse_iterator>(anchor_->p_next);
}

template <class T>
typename list<T>::const_reverse_iterator list<T>::crend() const {
  return static_cast<const_reverse_iterator>(anchor_->p_next);
}

template <class T>
typename list<T>::reverse_iterator list<T>::rbegin() {
  return static_cast<reverse_iterator>(anchor_);
}

template <class T>
typename list<T>::const_reverse_iterator list<T>::rbegin() const {
  return static_cast<const_reverse_iterator>(anchor_);
}

template <class T>
typename list<T>::const_reverse_iterator list<T>::crbegin() const {
  return static_cast<const_reverse_iterator>(anchor_);
}

template <class T>
bool list<T>::CreateList(const size_t count) {
  CreateAnchor();
  if (size_) {
    for (int i = 1; i <= static_cast<int>(count); i++) {
      StructList<T> *part = CreatePart();
      if (static_cast<int>(size_) > i) {
        AddToEnd(part);
      } else {
        return true;
      }
    }
  } else {
    return true;
  }
  return false;
}

template <class T>
list<T>::list(std::initializer_list<T> init_list) {
  if (!CreateList(init_list.size()) && FillList(init_list))
    FreeMemoryList(anchor_, anchor_->p_prev);
}

template <class T>
list<T>::list(const list &right) {
  CopyList(right.begin(), right.end());
}

template <class T>
list<T>::list(list &&right) : list() {
  swap(right);
}

template <class T>
list<T>::list(int count) {
  CreateList(count);
}

template <class T>
list<T>::list(size_t count, T value) {
  if (!CreateList(count) && FillList(value))
    FreeMemoryList(anchor_, anchor_->p_prev);
}

template <class T>
bool list<T>::FillList(T value) {
  iterator begin = anchor_->p_next;
  try {
    while (begin != anchor_) *begin++ = value;
  } catch (...) {
    return true;
  }
  return false;
}

template <class T>
bool list<T>::FillList(std::initializer_list<T> init_list) {
  iterator begin = anchor_->p_next;
  T *ptr = (T *)init_list.begin();
  try {
    for (; begin != anchor_; begin++, ptr++) *begin = *ptr;
  } catch (...) {
    return true;
  }
  return false;
}

template <class T>
void list<T>::CreateAnchor() {
  anchor_ = CreatePart();
  anchor_->p_next = anchor_;
  anchor_->p_prev = anchor_;
}

template <class T>
list<T>::~list() {
  if (anchor_) FreeMemoryList(anchor_, anchor_->p_prev);
}

template <class T>
void list<T>::AddToEnd(StructList<T> *value) {
  StructList<T> *end = anchor_->p_prev;
  end->p_next = value;
  value->p_prev = end;
  value->p_next = anchor_;
  anchor_->p_prev = value;
}

template <class T>
size_t list<T>::size() const {
  return size_ - 1;
}

template <class T>
StructList<T> *list<T>::CreatePart() {
  StructList<T> *res;
  try {
    res = new StructList<T>;
  } catch (...) {
    return nullptr;
  }
  size_++;
  res->p_next = nullptr;
  res->p_prev = nullptr;
  return res;
}

}  // namespace s21
#endif  // CONTAINERS_SRC_LIST_H_