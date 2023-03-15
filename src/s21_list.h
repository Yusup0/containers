#ifndef S21_CONTAINERS_SRC_LIST_H_
#define S21_CONTAINERS_SRC_LIST_H_

#include <stdlib.h>

#include <iostream>
#include <iterator>
#include <limits>

namespace s21 {

template <class T>
class list;
template <class T>
class ListIteratorConst;

template <class T>
struct StructList {
  StructList(T value) { value_ = value; }
  StructList<T> *p_next = nullptr;
  StructList<T> *p_prev = nullptr;
  T value_ = T();
};

template <class T>
class ListIterator {
  friend class list<T>;
  friend class ListIteratorConst<T>;

 public:
  using value_type = T;
  using pointer = T *;
  using reference = T &;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::bidirectional_iterator_tag;

  ListIterator() = default;
  ListIterator(StructList<T> *address) : address_(address) {}
  reference operator*() const { return address_->value_; }
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
  bool operator==(const ListIterator &it) { return address_ == it.address_; }
  bool operator==(const ListIteratorConst<T> &it1) {
    return address_ == it1.address_;
  }
  bool operator!=(const ListIterator &it) const {
    return address_ != it.address_;
  }
  bool operator!=(const ListIteratorConst<T> &it) const {
    return address_ != it.address_;
  }

 private:
  StructList<T> *address_ = nullptr;
};

template <class T>
class ListIteratorConst {
  friend class list<T>;
  friend class ListIterator<T>;

 public:
  using value_type = const T;
  using pointer = const T *;
  using reference = const T &;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::bidirectional_iterator_tag;

  ListIteratorConst() = default;
  ListIteratorConst(const StructList<T> *address) : address_(address) {}
  ListIteratorConst(ListIterator<T> &other) : address_(other.address_) {}
  ListIteratorConst &operator=(ListIterator<T> &other) {
    address_ = other.address_;
    return *this;
  }
  reference operator*() const { return address_->value_; }
  ListIteratorConst &operator++() {
    address_ = address_->p_next;
    return *this;
  }
  ListIteratorConst operator++(int) {
    address_ = address_->p_next;
    return address_->p_prev;
  }
  ListIteratorConst &operator--() {
    address_ = address_->p_prev;
    return *this;
  }
  ListIteratorConst operator--(int) {
    address_ = address_->p_prev;
    return address_->p_next;
  }
  bool operator==(const ListIteratorConst &it) const {
    return address_ == it.address_;
  }
  bool operator==(const ListIterator<T> &it1) const {
    return address_ == it1.address_;
  }
  bool operator!=(const ListIteratorConst &it) const {
    return address_ != it.address_;
  }
  bool operator!=(const ListIterator<T> &it) const {
    return address_ != it.address_;
  }

 private:
  const StructList<T> *address_ = nullptr;
};

template <class T>
class list {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  using iterator = ListIterator<T>;
  using const_iterator = ListIteratorConst<T>;

  explicit list(size_type count);
  template <class InputIterator>
  list(InputIterator first, InputIterator last);
  list();
  list(size_type count, value_type value);
  list(list &&right) noexcept;
  list(std::initializer_list<T> init_list);
  list(const list &right);
  template <class Container>
  list<T> &operator=(const Container &right);
  list<T> &operator=(list &right);
  list<T> &operator=(list &&right) noexcept;
  ~list() noexcept;
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
  size_type size() const noexcept;
  size_type max_size() const noexcept;
  iterator begin() noexcept;
  const_iterator begin() const noexcept;
  const_iterator cbegin() const noexcept;
  iterator end() noexcept;
  const_iterator end() const noexcept;
  const_iterator cend() const noexcept;
  bool empty() const noexcept;
  void assign(size_type count, value_type value);
  template <class InputIterator>
  void assign(InputIterator first, InputIterator last);
  void assign(std::initializer_list<T> init_list);
  void swap(list &other) noexcept;
  reference front() noexcept;
  const_reference front() const noexcept;
  reference back() noexcept;
  const_reference back() const noexcept;
  void push_back(const_reference value);
  void push_front(const_reference value);
  void pop_back();
  void pop_front();
  iterator insert(iterator where, const_reference value);
  void insert(iterator where, size_type count, const_reference value);
  iterator insert(iterator where, std::initializer_list<T> init_list);
  template <class InputIterator>
  void insert(iterator where, InputIterator first, InputIterator last);
  iterator erase(iterator where);
  iterator erase(iterator first, iterator last);
  void remove(const_reference value);
  void resize(size_type new_size, value_type value = value_type());
  void clear();
  void unique();
  void splice(const_iterator position, list<T> &donor);
  void splice(const_iterator position, list<T> &donor,
              const_iterator donor_position);
  void reverse() noexcept;
  void sort();
  void merge(list<T> &right);

 private:
  StructList<T> *anchor_ = nullptr;
  size_type size_ = 0;
  void CreateAnchor();
  void AddToEnd(StructList<T> *value);
  int ComparisonList(const list &other) const;
  void DeliteValue(StructList<T> *value);
  void DeliteList(StructList<T> *first, StructList<T> *last);
  void FreeMemoryList(StructList<T> *first, StructList<T> *last) noexcept;
  void AddValue(StructList<T> *position, StructList<T> *value);
  void AddList(StructList<T> *position, StructList<T> *first,
               StructList<T> *last) noexcept;
  void ArgumentParser([[maybe_unused]] StructList<T> *position) {}
  void BindList(StructList<T> *begin, StructList<T> *end) const noexcept;
  template <class... Other>
  void ArgumentParser(StructList<T> *position, value_type &&first,
                      Other... other);
  template <class InputIterator>
  void CopyList(InputIterator first, InputIterator last);
};

template <class T>
template <class... Types>
void list<T>::emplace_back(Types &&...args) {
  emplace(end(), std::forward<Types>(args)...);
}

template <class T>
template <class... Types>
void list<T>::emplace_front(Types &&...args) {
  emplace(begin(), std::forward<Types>(args)...);
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
list<T> &list<T>::operator=(list &&right) noexcept {
  swap(right);
  return *this;
}

template <class T>
template <class InputIterator>
void list<T>::CopyList(InputIterator first, InputIterator last) {
  list tmp(std::distance(first, last));
  iterator begin = tmp.begin();
  while (first != last) *begin++ = *first++;
  swap(tmp);
}

template <class T>
void list<T>::merge(list<T> &right) {
  StructList<T> *first = anchor_->p_next, *second = right.anchor_->p_next;
  StructList<T> *next, *next_second;
  while (second != right.anchor_) {
    next = first->p_next;
    if (first->value_ > second->value_) {
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
  right.size_ = 0;
  right.anchor_->p_next = right.anchor_;
  right.anchor_->p_prev = right.anchor_;
}

template <class T>
void list<T>::sort() {
  value_type tmp;
  StructList<T> *begin = anchor_->p_next->p_next;
  for (size_type i = 1; i < size_; i++) {
    for (size_type j = 1; j <= size_ - i; j++) {
      if (begin->value_ < begin->p_prev->value_) {
        tmp = begin->value_;
        begin->value_ = begin->p_prev->value_;
        begin->p_prev->value_ = tmp;
      }
      begin = begin->p_next;
    }
    begin = anchor_->p_next->p_next;
  }
}

template <class T>
void list<T>::reverse() noexcept {
  StructList<T> *temporarily;
  for (size_type i = 0; i < size_ + 1; i++) {
    temporarily = anchor_->p_next;
    anchor_->p_next = anchor_->p_prev;
    anchor_->p_prev = temporarily;
    anchor_ = anchor_->p_prev;
  }
}

template <class T>
void list<T>::splice(const_iterator position, list<T> &donor,
                     const_iterator donor_position) {
  if (position != donor_position && donor.size()) {
    iterator it = const_cast<StructList<T> *>(donor_position.address_);
    BindList(it.address_->p_prev, it.address_->p_next);
    AddValue(const_cast<StructList<T> *>(position.address_), it.address_);
    if (&donor.anchor_ != &anchor_) {
      donor.size_--;
    } else {
      size_--;
    }
  }
}

template <class T>
void list<T>::AddList(StructList<T> *position, StructList<T> *first,
                      StructList<T> *last) noexcept {
  size_ += std::distance(iterator(first), iterator(last)) + 1;
  StructList<T> *begin = position->p_prev;
  begin->p_next = first;
  first->p_prev = begin;
  last->p_next = position;
  position->p_prev = last;
}

template <class T>
void list<T>::splice(const_iterator position, list<T> &donor) {
  if (!donor.size()) return;
  AddList(const_cast<StructList<T> *>(position.address_), donor.anchor_->p_next,
          donor.anchor_->p_prev);
  donor.size_ = 0;
  donor.anchor_->p_next = donor.anchor_;
  donor.anchor_->p_prev = donor.anchor_;
}

template <class T>
void list<T>::unique() {
  StructList<T> *begin = anchor_->p_next->p_next, *next;
  value_type value = begin->p_prev->value_;
  while (begin != anchor_) {
    next = begin->p_next;
    if (value == begin->value_) {
      DeliteValue(begin);
    } else {
      value = begin->value_;
    }
    begin = next;
  }
}

template <class T>
template <class... Other>
void list<T>::ArgumentParser(StructList<T> *position, value_type &&first,
                             Other... other) {
  StructList<T> *part = new StructList<T>(std::move(first));
  AddValue(position, part);
  ArgumentParser(position, std::forward<Other>(other)...);
}

template <class T>
template <class... Types>
typename list<T>::iterator list<T>::emplace(iterator position,
                                            Types &&...args) {
  list tmp;
  tmp.ArgumentParser(tmp.anchor_, std::forward<Types>(args)...);
  if (!tmp.size()) return position;
  iterator result = tmp.begin();
  AddList(position.address_, tmp.anchor_->p_next, tmp.anchor_->p_prev);
  BindList(tmp.anchor_, tmp.anchor_);
  return result;
}

template <class T>
void list<T>::clear() {
  if (size()) DeliteList(anchor_->p_next, anchor_);
}

template <class T>
void list<T>::resize(size_type new_size, value_type value) {
  size_type size_our = size();
  if (size_our < new_size) {
    list tmp(new_size - size_our, value);
    if (tmp.size()) insert(anchor_, tmp.begin(), tmp.end());
  } else if (size_our > new_size) {
    for (size_type i = 0; i < size_our - new_size; i++) {
      DeliteValue(anchor_->p_prev);
    }
  }
}

template <class T>
void list<T>::remove(const_reference value) {
  StructList<T> *begin = anchor_->p_next, *next;
  while (begin != anchor_) {
    next = begin;
    begin = begin->p_next;
    if (next->value_ == value) DeliteValue(next);
  }
}

template <class T>
void list<T>::FreeMemoryList(StructList<T> *first,
                             StructList<T> *last) noexcept {
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
  if (first == last) return;
  list tmp(first, last);
  AddList(where.address_, tmp.anchor_->p_next, tmp.anchor_->p_prev);
  BindList(tmp.anchor_, tmp.anchor_);
}

template <class T>
typename list<T>::iterator list<T>::insert(iterator where,
                                           std::initializer_list<T> init_list) {
  if (!init_list.size()) return where;
  list tmp(init_list);
  iterator result = tmp.begin();
  AddList(where.address_, tmp.anchor_->p_next, tmp.anchor_->p_prev);
  BindList(tmp.anchor_, tmp.anchor_);
  return result;
}

template <class T>
void list<T>::insert(iterator where, size_type count, const_reference value) {
  if (!count) return;
  list tmp(count, value);
  AddList(where.address_, tmp.anchor_->p_next, tmp.anchor_->p_prev);
  BindList(tmp.anchor_, tmp.anchor_);
}

template <class T>
typename list<T>::iterator list<T>::insert(iterator where,
                                           const_reference value) {
  StructList<T> *element = new StructList<T>(value);
  AddValue(where.address_, element);
  return element;
}

template <class T>
void list<T>::push_front(const_reference value) {
  StructList<T> *part = new StructList<T>(value);
  AddValue(anchor_->p_next, part);
}

template <class T>
void list<T>::AddValue(StructList<T> *position, StructList<T> *value) {
  StructList<T> *begin = position->p_prev;
  begin->p_next = value;
  value->p_prev = begin;
  value->p_next = position;
  position->p_prev = value;
  size_++;
}

template <class T>
void list<T>::BindList(StructList<T> *begin,
                       StructList<T> *end) const noexcept {
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
void list<T>::push_back(const_reference value) {
  StructList<T> *part = new StructList<T>(value);
  AddToEnd(part);
}

template <class T>
typename list<T>::const_reference list<T>::back() const noexcept {
  return anchor_->p_prev->value_;
}

template <class T>
typename list<T>::reference list<T>::back() noexcept {
  return anchor_->p_prev->value_;
}

template <class T>
typename list<T>::const_reference list<T>::front() const noexcept {
  return anchor_->p_next->value_;
}

template <class T>
typename list<T>::reference list<T>::front() noexcept {
  return anchor_->p_next->value_;
}

template <class T>
void list<T>::swap(list &other) noexcept {
  std::swap(anchor_, other.anchor_);
  std::swap(size_, other.size_);
}

template <class T>
void list<T>::assign(std::initializer_list<T> init_list) {
  list tmp(init_list);
  swap(tmp);
}

template <class T>
template <class InputIterator>
void list<T>::assign(InputIterator first, InputIterator last) {
  list tmp(first, last);
  swap(tmp);
}

template <class T>
void list<T>::assign(size_type count, value_type value) {
  list tmp(count, value);
  swap(tmp);
}

template <class T>
bool list<T>::empty() const noexcept {
  return !size();
}

template <class T>
int list<T>::ComparisonList(const list &other) const {
  int res = 0;
  size_type size1 = size(), size2 = other.size();
  const_iterator our_it = begin();
  const_iterator other_it = other.begin();
  for (size_type i = 0; i < size1 && i < size2; i++, our_it++, other_it++) {
    if (*our_it != *other_it) {
      res = *our_it > *other_it ? 1 : -1;
      break;
    }
  }
  if (res == 0 && size1 != size2) res = size1 > size2 ? 1 : -1;
  return res;
}

template <class T>
typename list<T>::iterator list<T>::end() noexcept {
  return anchor_;
}

template <class T>
typename list<T>::const_iterator list<T>::end() const noexcept {
  return anchor_;
}

template <class T>
typename list<T>::const_iterator list<T>::cend() const noexcept {
  return anchor_;
}

template <class T>
typename list<T>::iterator list<T>::begin() noexcept {
  return anchor_->p_next;
}

template <class T>
typename list<T>::const_iterator list<T>::begin() const noexcept {
  return static_cast<const_iterator>(anchor_->p_next);
}

template <class T>
typename list<T>::const_iterator list<T>::cbegin() const noexcept {
  return static_cast<const_iterator>(anchor_->p_next);
}

template <class T>
list<T>::list(const list &right) {
  CopyList(right.begin(), right.end());
}

template <class T>
list<T>::list(list &&right) noexcept : list() {
  swap(right);
}

template <class T>
list<T>::list(std::initializer_list<T> init_list) {
  CreateAnchor();
  auto it = init_list.begin();
  try {
    for (size_type i = 1; i <= init_list.size(); i++)
      AddToEnd(new StructList<T>(*it++));
  } catch (...) {
    FreeMemoryList(anchor_, anchor_->p_prev);
    throw;
  }
}

template <class T>
list<T>::list(size_type count) {
  CreateAnchor();
  try {
    for (size_type i = 1; i <= count; i++) AddToEnd(new StructList<T>(T()));
  } catch (...) {
    FreeMemoryList(anchor_, anchor_->p_prev);
    throw;
  }
}

template <class T>
list<T>::list(size_type count, value_type value) {
  CreateAnchor();
  try {
    for (size_type i = 1; i <= count; i++) AddToEnd(new StructList<T>(value));
  } catch (...) {
    FreeMemoryList(anchor_, anchor_->p_prev);
    throw;
  }
}

template <class T>
void list<T>::CreateAnchor() {
  anchor_ = new StructList<T>(T());
  anchor_->p_next = anchor_;
  anchor_->p_prev = anchor_;
}

template <class T>
list<T>::~list() noexcept {
  if (anchor_) FreeMemoryList(anchor_, anchor_->p_prev);
}

template <class T>
void list<T>::AddToEnd(StructList<T> *value) {
  StructList<T> *end = anchor_->p_prev;
  end->p_next = value;
  value->p_prev = end;
  value->p_next = anchor_;
  anchor_->p_prev = value;
  size_++;
}

template <class T>
typename list<T>::size_type list<T>::size() const noexcept {
  return size_;
}

template <class T>
typename list<T>::size_type list<T>::max_size() const noexcept {
  return std::numeric_limits<size_type>::max() / 2 /
             sizeof(StructList<value_type>) -
         1;
}

}  // namespace s21
#endif  // S21_CONTAINERS_SRC_LIST_H_