#ifndef CONTAINERS_SRC_ARRAY_H_
#define CONTAINERS_SRC_ARRAY_H_

#include <stdlib.h>

#include <iostream>
#include <iterator>

namespace s21 {

template <class T, size_t N>
class array {
 public:
  using iterator = T *;
  using const_iterator = const T *;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  array(std::initializer_list<T> init_list);
  array() { ptr_ = new T[N]; }
  array(const array &right) { CopyPtr(right); }
  array(array &&other);
  array &operator=(const array &right);
  array &operator=(array &&right);
  ~array();
  T &operator[](const size_t n);
  const T &operator[](const size_t n) const;
  iterator begin() noexcept;
  const_iterator begin() const noexcept;
  const_iterator cbegin() const noexcept;
  iterator end() noexcept;
  const_iterator end() const noexcept;
  const_iterator cend() const noexcept;
  reverse_iterator rbegin() noexcept;
  const_reverse_iterator rbegin() const noexcept;
  const_reverse_iterator crbegin() const noexcept;
  reverse_iterator rend() noexcept;
  const_reverse_iterator rend() const noexcept;
  const_reverse_iterator crend() const noexcept;
  T &at(size_t position);
  const T &at(size_t position) const;
  T &back();
  const T &back() const;
  T &front();
  const T &front() const;
  T *data();
  const T *data() const;
  constexpr bool empty() const;
  void fill(const T &value);
  constexpr size_t size() const;
  void swap(array &right);

 private:
  T *ptr_;
  void CopyPtr(const array &other);
  void CopyList(std::initializer_list<T> init_list);
};

template <class T, size_t N>
void array<T, N>::swap(array &right) {
  std::swap(ptr_, right.ptr_);
}

template <class T, size_t N>
constexpr size_t array<T, N>::size() const {
  return N;
}

template <class T, size_t N>
const T &array<T, N>::front() const {
  return *ptr_;
}

template <class T, size_t N>
T &array<T, N>::front() {
  return *ptr_;
}

template <class T, size_t N>
T &array<T, N>::at(size_t position) {
  if (N <= position) throw std::out_of_range("going outside the array");
  return *(ptr_ + position);
}

template <class T, size_t N>
const T &array<T, N>::at(size_t position) const {
  if (N <= position) throw std::out_of_range("going outside the array");
  return *(ptr_ + position);
}

template <class T, size_t N>
void array<T, N>::fill(const T &value) {
  array tmp;
  try {
    for (size_t i = 0; i < N; i++) tmp.ptr_[i] = value;
  } catch (...) {
    throw;
  }
  swap(tmp);
}

template <class T, size_t N>
constexpr bool array<T, N>::empty() const {
  return !N;
}

template <class T, size_t N>
const T *array<T, N>::data() const {
  return ptr_;
}

template <class T, size_t N>
T *array<T, N>::data() {
  return ptr_;
}

template <class T, size_t N>
T &array<T, N>::back() {
  return *(ptr_ + N - 1);
}

template <class T, size_t N>
const T &array<T, N>::back() const {
  return *(ptr_ + N - 1);
}

template <class T, size_t N>
void array<T, N>::CopyList(std::initializer_list<T> init_list) {
  ptr_ = new T[N];
  T *ptr2 = (T *)init_list.begin();
  int size_list = static_cast<int>(init_list.size());
  try {
    for (int i = 0; i < size_list; i++) ptr_[i] = ptr2[i];
  } catch (...) {
    delete[] ptr_;
    throw;
  }
}

template <class T, size_t N>
array<T, N>::array(array &&other) : array() {
  swap(other);
}

template <class T, size_t N>
array<T, N>::array(std::initializer_list<T> init_list) {
  CopyList(init_list);
}

template <class T, size_t N>
array<T, N> &array<T, N>::operator=(const array<T, N> &right) {
  T *tmp = ptr_;
  CopyPtr(right);
  delete[] tmp;
  return *this;
}

template <class T, size_t N>
array<T, N> &array<T, N>::operator=(array<T, N> &&right) {
  swap(right);
  return *this;
}

template <class T, size_t N>
array<T, N>::~array() {
  delete[] ptr_;
}

template <class T, size_t N>
T &array<T, N>::operator[](const size_t n) {
  return *(ptr_ + n);
}

template <class T, size_t N>
const T &array<T, N>::operator[](const size_t n) const {
  return *(ptr_ + n);
}

template <class T, size_t N>
typename array<T, N>::reverse_iterator array<T, N>::rend() noexcept {
  return static_cast<reverse_iterator>(begin());
}

template <class T, size_t N>
typename array<T, N>::const_reverse_iterator array<T, N>::rend()
    const noexcept {
  return static_cast<const_reverse_iterator>(begin());
}

template <class T, size_t N>
typename array<T, N>::const_reverse_iterator array<T, N>::crend()
    const noexcept {
  return static_cast<const_reverse_iterator>(begin());
}

template <class T, size_t N>
typename array<T, N>::const_reverse_iterator array<T, N>::rbegin()
    const noexcept {
  return static_cast<const_reverse_iterator>(end());
}

template <class T, size_t N>
typename array<T, N>::const_reverse_iterator array<T, N>::crbegin()
    const noexcept {
  return static_cast<const_reverse_iterator>(end());
}

template <class T, size_t N>
typename array<T, N>::reverse_iterator array<T, N>::rbegin() noexcept {
  return static_cast<reverse_iterator>(end());
}

template <class T, size_t N>
typename array<T, N>::const_iterator array<T, N>::end() const noexcept {
  return ptr_ + N;
}

template <class T, size_t N>
typename array<T, N>::const_iterator array<T, N>::cend() const noexcept {
  return ptr_ + N;
}

template <class T, size_t N>
typename array<T, N>::iterator array<T, N>::end() noexcept {
  return ptr_ + N;
}

template <class T, size_t N>
typename array<T, N>::iterator array<T, N>::begin() noexcept {
  return ptr_;
}

template <class T, size_t N>
typename array<T, N>::const_iterator array<T, N>::begin() const noexcept {
  return static_cast<const_iterator>(ptr_);
  ;
}

template <class T, size_t N>
typename array<T, N>::const_iterator array<T, N>::cbegin() const noexcept {
  return static_cast<const_iterator>(ptr_);
  ;
}

template <class T, size_t N>
void array<T, N>::CopyPtr(const array &other) {
  ptr_ = new T[N];
  try {
    for (int i = 0; i < static_cast<int>(N); i++) ptr_[i] = other.ptr_[i];
  } catch (...) {
    delete[] ptr_;
    throw;
  }
}
}  // namespace s21
#endif  // CONTAINERS_SRC_ARRAY_H_