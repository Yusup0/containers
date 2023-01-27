#ifndef CONTAINERS_SRC_VECTOR_H_
#define CONTAINERS_SRC_VECTOR_H_

#include <stdlib.h>

#include <iostream>
#include <iterator>

namespace s21 {

template <class T>
class vector {
 public:
  using iterator = T *;
  using const_iterator = const T *;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  using size_type = size_t;

  vector();
  vector(const vector &other);
  vector(vector &&other);
  explicit vector(size_type count);
  vector(size_type count, T value);
  vector(std::initializer_list<T> init_list);
  template <class InputIterator>
  vector(InputIterator first, InputIterator last);
  vector &operator=(const vector &right);
  vector &operator=(vector &&right);
  template <class Container>
  vector &operator=(const Container &right);
  ~vector();

  template <class... Types>
  iterator emplace(iterator position, Types &&...args);
  template <class... Types>
  void emplace_back(Types &&...args);
  template <class... Types>
  void emplace_front(Types &&...args);
  bool operator<(vector &other) const { return ComparisonVector(other) == -1; }
  bool operator>(vector &other) const { return ComparisonVector(other) == 1; }
  bool operator==(vector &other) const { return !ComparisonVector(other); }
  bool operator!=(vector &other) const { return ComparisonVector(other); }
  bool operator<=(vector &other) const {
    return !ComparisonVector(other) || ComparisonVector(other) == -1;
  }
  bool operator>=(vector &other) const {
    return !ComparisonVector(other) || ComparisonVector(other) == 1;
  }
  T &operator[](const size_type n);
  const T &operator[](const size_type n) const;
  void push_back(const T &value);
  void push_back(T &&value);
  void pop_back();
  void pop_front();
  void reserve(size_type count);
  void shrink_to_fit();
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
  size_type size() const;
  size_type capacity() const;
  void assign(std::initializer_list<T> init_list);
  template <class InputIterator>
  void assign(InputIterator first, InputIterator last);
  void assign(size_type count, const T value);
  void swap(vector &other);
  T &at(size_type position);
  const T &at(size_type position) const;
  T &back();
  const T &back() const;
  T &front();
  const T &front() const;
  iterator insert(const_iterator position, const T &value);
  void insert(const_iterator position, size_type count, const T &value);
  template <class InputIterator>
  void insert(const_iterator position, InputIterator first, InputIterator last);
  void insert(const_iterator position, std::initializer_list<T> init_list);
  void clear();
  void resize(size_type new_size);
  void resize(size_type new_size, const T &value);
  iterator erase(const_iterator position);
  iterator erase(const_iterator first, const_iterator last);

 private:
  T *ptr_ = nullptr;
  size_type size_;
  size_type capacity_;
  int ComparisonVector(vector &other) const;
  inline void ArgumentParser([[maybe_unused]] size_type position) {}
  void CopyList(std::initializer_list<T> init_list);
  void CopyPtr(const vector &other);
  void Moveright(size_type position, size_type count);
  size_type CountAfter(const_iterator position) const;
  template <class... Other>
  void ArgumentParser(size_type position, T first, Other... other);
  void FreeMemory(vector &value);
  void ChangeCapacity(size_type size);
  template <class InputIterator>
  void InsertBack(InputIterator first, InputIterator last);
};

template <class T>
void vector<T>::ChangeCapacity(size_type size) {
  if (size > capacity_) {
    T *new_ptr = new T[size];
    try {
      for (size_type i = 0; i < capacity_; i++) new_ptr[i] = ptr_[i];
    } catch (...) {
      delete[] new_ptr;
      throw;
    }
    delete[] ptr_;
    ptr_ = std::move(new_ptr);
    capacity_ = size;
  } else if (size != capacity_) {
    T *new_ptr = new T[size];
    try {
      for (size_type i = 0; i < size; i++) new_ptr[i] = ptr_[i];
    } catch (...) {
      delete[] new_ptr;
      throw;
    }
    delete[] ptr_;
    ptr_ = std::move(new_ptr);
    size_ = capacity_ = size;
  }
}

template <class T>
void vector<T>::FreeMemory(vector &value) {
  delete[] value.ptr_;
  value.size_ = value.capacity_ = 0;
}

template <class T>
template <class... Types>
void vector<T>::emplace_back(Types &&...args) {
  vector tmp(*this);
  tmp.ArgumentParser(size_, args...);
  swap(tmp);
}

template <class T>
template <class... Types>
void vector<T>::emplace_front(Types &&...args) {
  vector tmp(*this);
  tmp.ArgumentParser(0, args...);
  swap(tmp);
}

template <class T>
vector<T> &vector<T>::operator=(const vector &right) {
  if (this != &right) {
    vector tmp(right);
    swap(tmp);
  }
  return *this;
}

template <class T>
vector<T> &vector<T>::operator=(vector &&right) {
  swap(right);
  return *this;
}

template <class T>
void vector<T>::pop_front() {
  vector tmp(iterator(ptr_ + 1), end());
  swap(tmp);
}

template <class T>
template <class Container>
vector<T> &vector<T>::operator=(const Container &right) {
  assign(right.begin(), right.end());
  return *this;
}

template <class T>
template <class InputIterator>
vector<T>::vector(InputIterator first, InputIterator last) {
  vector tmp(std::distance(first, last));
  for (size_type i = 0; i < tmp.size_; i++) tmp.ptr_[i] = *first++;
  std::swap(*this, tmp);
}

template <class T>
typename vector<T>::reverse_iterator vector<T>::rend() {
  return static_cast<reverse_iterator>(begin());
}

template <class T>
typename vector<T>::const_reverse_iterator vector<T>::rend() const {
  return static_cast<const_reverse_iterator>(begin());
}

template <class T>
typename vector<T>::const_reverse_iterator vector<T>::crend() const {
  return static_cast<const_reverse_iterator>(begin());
}

template <class T>
typename vector<T>::reverse_iterator vector<T>::rbegin() {
  return static_cast<reverse_iterator>(end());
}

template <class T>
typename vector<T>::const_reverse_iterator vector<T>::rbegin() const {
  return static_cast<const_reverse_iterator>(end());
}

template <class T>
typename vector<T>::const_reverse_iterator vector<T>::crbegin() const {
  return static_cast<const_reverse_iterator>(end());
}

template <class T>
template <class... Other>
void vector<T>::ArgumentParser(size_type position, T first, Other... other) {
  if ((size_ + 1) > capacity_) ChangeCapacity(capacity_ ? capacity_ * 2 : 512);
  for (size_type i = position; i < size_; i++) ptr_[i + 1] = ptr_[i];
  size_++;
  ptr_[position] = first;
  ArgumentParser(position + 1, other...);
}

template <class T>
template <class... Types>
typename vector<T>::iterator vector<T>::emplace(iterator position,
                                                Types &&...args) {
  size_type pos = std::distance(begin(), position);
  vector tmp(*this);
  tmp.ArgumentParser(pos, args...);
  swap(tmp);
  return iterator(ptr_ + pos);
}

template <class T>
typename vector<T>::iterator vector<T>::erase(const_iterator first,
                                              const_iterator last) {
  size_type pos = std::distance(cbegin(), first);
  size_type distance = std::distance(first, last);
  vector tmp(size_ - distance);
  for (size_type i = 0; i < pos; i++) tmp.ptr_[i] = ptr_[i];
  for (size_type i = pos; i < tmp.size_; i++) tmp.ptr_[i] = ptr_[i + distance];
  swap(tmp);
  return iterator(ptr_ + pos);
}

template <class T>
typename vector<T>::iterator vector<T>::erase(const_iterator position) {
  size_type pos = std::distance(cbegin(), position);
  vector tmp(size_ - 1);
  for (size_type i = 0; i < pos; i++) tmp.ptr_[i] = ptr_[i];
  for (size_type i = pos; i < tmp.size_; i++) tmp.ptr_[i] = ptr_[i + 1];
  swap(tmp);
  return iterator(ptr_ + pos);
}

template <class T>
void vector<T>::resize(size_type new_size, const T &value) {
  if (size_ < new_size) {
    vector tmp(new_size, value);
    swap(tmp);
  }
}

template <class T>
void vector<T>::resize(size_type new_size) {
  if (size_ < new_size) ChangeCapacity(new_size);
  size_ = new_size;
}

template <class T>
void vector<T>::clear() {
  size_ = 0;
}

template <class T>
void vector<T>::insert(const_iterator position,
                       std::initializer_list<T> init_list) {
  size_type distance = init_list.size();
  size_type count = std::distance(cbegin(), position);
  auto it = init_list.begin();
  vector tmp(distance + size_);
  for (size_type i = 0; i < count; i++) tmp.ptr_[i] = ptr_[i];
  for (size_type i = count; i < count + distance; i++) tmp.ptr_[i] = *it++;
  for (size_type i = count + distance; i < tmp.size_; i++)
    tmp.ptr_[i] = ptr_[i - distance];
  swap(tmp);
}

template <class T>
template <class InputIterator>
void vector<T>::insert(const_iterator position, InputIterator first,
                       InputIterator last) {
  size_type count = std::distance(cbegin(), position);
  size_type distance = std::distance(first, last);
  vector tmp(distance + size_);
  for (size_type i = 0; i < count; i++) tmp.ptr_[i] = ptr_[i];
  for (size_type i = count; i < count + distance; i++) tmp.ptr_[i] = *first++;
  for (size_type i = count + distance; i < tmp.size_; i++)
    tmp.ptr_[i] = ptr_[i - distance];
  swap(tmp);
}

template <class T>
template <class InputIterator>
void vector<T>::InsertBack(InputIterator first, InputIterator last) {}

template <class T>
void vector<T>::insert(const_iterator position, size_type count, const T &value) {
  size_type distance = std::distance(cbegin(), position);
  vector tmp(count + size_);
  for (size_type i = 0; i < distance; i++) tmp.ptr_[i] = ptr_[i];
  for (size_type i = distance; i < distance + count; i++) tmp.ptr_[i] = value;
  for (size_type i = distance + count; i < tmp.size_; i++)
    tmp.ptr_[i] = ptr_[i - count];
  swap(tmp);
}

template <class T>
typename vector<T>::size_type vector<T>::CountAfter(
    const_iterator position) const {
  size_type result = 0;
  while (position != end()) {
    position++;
    result++;
  }
  return result;
}

template <class T>
void vector<T>::Moveright(size_type position, size_type count) {
  if ((size_ + count) > capacity_) ChangeCapacity(size_ + count);
  for (size_type i = 0; i < position; i++) {
    ptr_[size_ - 1 + count - i] = ptr_[size_ - 1 - i];
  }
  size_ += count;
}

template <class T>
typename vector<T>::iterator vector<T>::insert(const_iterator position,
                                               const T &value) {
  size_type distance = std::distance(cbegin(), position);
  vector tmp(1 + size_);
  for (size_type i = 0; i < distance; i++) tmp.ptr_[i] = ptr_[i];
  tmp.ptr_[distance] = value;
  for (size_type i = 1 + distance; i < tmp.size_; i++)
    tmp.ptr_[i] = ptr_[i - 1];
  swap(tmp);
  return ptr_ + distance;
}

template <class T>
void vector<T>::pop_back() {
  if (size_ > 0) size_--;
}

template <class T>
T &vector<T>::front() {
  return *ptr_;
}

template <class T>
const T &vector<T>::front() const {
  return *ptr_;
}

template <class T>
T &vector<T>::back() {
  return *(ptr_ + size_ - 1);
}

template <class T>
const T &vector<T>::back() const {
  return *(ptr_ + size_ - 1);
}

template <class T>
T &vector<T>::at(size_type position) {
  if (position >= size_) throw std::out_of_range("going outside the array");
  return *(ptr_ + position);
}

template <class T>
const T &vector<T>::at(size_type position) const {
  if (position >= size_) throw std::out_of_range("going outside the array");
  return *(ptr_ + position);
}

template <class T>
void vector<T>::swap(vector &other) {
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
  std::swap(ptr_, other.ptr_);
}

template <class T>
void vector<T>::assign(size_type count, const T value) {
  vector tmp(count, value);
  swap(tmp);
}

template <class T>
template <class InputIterator>
void vector<T>::assign(InputIterator first, InputIterator last) {
  vector tmp(first, last);
  swap(tmp);
}

template <class T>
void vector<T>::assign(std::initializer_list<T> init_list) {
  vector tmp(init_list);
  swap(tmp);
}

template <class T>
void vector<T>::CopyList(std::initializer_list<T> init_list) {
  ptr_ = new T[init_list.size()];
  try {
    auto *ptr2 = init_list.begin();
    for (size_type i = 0; i < init_list.size(); i++)
      ptr_[i] = *ptr2++;
  } catch (...) {
    delete[] ptr_;
    ptr_ = nullptr;
    throw;
  }
  size_ = capacity_ = init_list.size();
}

template <class T>
int vector<T>::ComparisonVector(vector &other) const {
  int res = 0;
  size_type size1 = size(), size2 = other.size();
  for (size_type i = 0; i < size1 && i < size2; i++) {
    if (ptr_[i] != other.ptr_[i]) {
      res = ptr_[i] > other.ptr_[i] ? 1 : -1;
      break;
    }
  }
  if (res == 0 && size1 != size2) res = size1 > size2 ? 1 : -1;
  return res;
}

template <class T>
void vector<T>::shrink_to_fit() {
  if (capacity_ > size_) {
    ChangeCapacity(size_);
  }
}

template <class T>
void vector<T>::reserve(size_type count) {
  if (capacity_ < count) {
    ChangeCapacity(count);
    size_ = count;
  }
}

template <class T>
void vector<T>::push_back(const T &value) {
  if (size_ >= capacity_) ChangeCapacity(capacity_ ? capacity_ * 2 : 512);
  ptr_[size_++] = value;
}

template <class T>
void vector<T>::push_back(T &&value) {
  if (size_ >= capacity_) ChangeCapacity(capacity_ ? capacity_ * 2 : 512);
  ptr_[size_++] = std::move(value);
}

template <class T>
bool vector<T>::empty() const {
  return !size_;
}

template <class T>
T &vector<T>::operator[](const size_type n) {
  return *(ptr_ + n);
}

template <class T>
const T &vector<T>::operator[](const size_type n) const {
  return *(ptr_ + n);
}

template <class T>
typename vector<T>::iterator vector<T>::end() {
  return ptr_ + size_;
}

template <class T>
typename vector<T>::const_iterator vector<T>::end() const {
  return ptr_ + size_;
}

template <class T>
typename vector<T>::const_iterator vector<T>::cend() const {
  return ptr_ + size_;
}

template <class T>
typename vector<T>::iterator vector<T>::begin() {
  return ptr_;
}

template <class T>
typename vector<T>::const_iterator vector<T>::begin() const {
  return ptr_;
}

template <class T>
typename vector<T>::const_iterator vector<T>::cbegin() const {
  return ptr_;
}

template <class T>
void vector<T>::CopyPtr(const vector &other) {
  ptr_ = new T[other.capacity_];
  try {
    for (size_type i = 0; i < other.size_; i++)
      ptr_[i] = other.ptr_[i];
  } catch (...) {
    delete[] ptr_;
    ptr_ = nullptr;
    throw;
  }
  size_ = other.size();
  capacity_ = other.capacity();
}

template <class T>
vector<T>::vector(const vector &other) {
  if (other.capacity_) CopyPtr(other);
}

template <class T>
vector<T>::vector(vector &&other) {
  swap(other);
}

template <class T>
vector<T>::~vector() {
  FreeMemory(*this);
}

template <class T> 
typename vector<T>::size_type vector<T>::size() const {
  return size_;
}

template <class T>
typename vector<T>::size_type vector<T>::capacity() const {
  return capacity_;
}

template <class T>
vector<T>::vector() {
  ptr_ = new T[512];
  size_ = 0;
  capacity_ = 512;
}

template <class T>
vector<T>::vector(size_type count) {
  ptr_ = new T[count];
  size_ = capacity_ = count;
}

template <class T>
vector<T>::vector(size_type count, T value) {
  ptr_ = new T[count];
  try {
    for (size_type i = 0; i < count; i++) ptr_[i] = value;
  } catch (...) {
    delete[] ptr_;
    ptr_ = nullptr;
    throw;
  }
  size_ = capacity_ = count;
}

template <class T>
vector<T>::vector(std::initializer_list<T> init_list) : vector() {
  if (init_list.size()) CopyList(init_list);
}

}  // namespace s21
#endif  // CONTAINERS_SRC_VECTOR_H_