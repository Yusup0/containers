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

  vector();
  vector(const vector &other);
  vector(vector &&other);
  explicit vector(int count);
  vector(size_t count, T value);
  vector(std::initializer_list<T> init_list);
  vector(iterator first, iterator last);
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
  T &operator[](const size_t n);
  const T &operator[](const size_t n) const;
  void push_back(const T &value);
  void push_back(T &&value);
  void pop_back();
  void pop_front();
  void reserve(size_t count);
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
  size_t size() const;
  size_t capacity() const;
  void assign(std::initializer_list<T> init_list);
  template <class InputIterator>
  void assign(InputIterator first, InputIterator last);
  void assign(size_t count, const T value);
  void swap(vector &other);
  T &at(size_t position);
  const T &at(size_t position) const;
  T &back();
  const T &back() const;
  T &front();
  const T &front() const;
  iterator insert(const_iterator position, const T &value);
  void insert(const_iterator position, size_t count, const T &value);
  template <class InputIterator>
  void insert(const_iterator position, InputIterator first, InputIterator last);
  void insert(const_iterator position, std::initializer_list<T> init_list);
  void clear();
  void resize(size_t new_size);
  void resize(size_t new_size, const T &value);
  iterator erase(const_iterator position);
  iterator erase(const_iterator first, const_iterator last);

 private:
  T *ptr_ = nullptr;
  size_t size_;
  size_t capacity_;
  int ComparisonVector(vector &other) const;
  void CopyIter(iterator first, iterator last);
  inline void ArgumentParser([[maybe_unused]] int position) {}
  void CopyList(std::initializer_list<T> init_list);
  void CopyPtr(const vector &other);
  bool DoubleMemory();
  void Moveright(int position, int count);
  bool MoveLeft(int position, int count);
  int CountAfter(const_iterator position) const;
  template <class Container>
  void CopyContainer(const Container &right);
  template <class... Other>
  void ArgumentParser(int position, T first, Other... other);
  void FreeMemory(vector &value);
  bool ChangeCapacity(size_t size);
};

template <class T>
bool vector<T>::ChangeCapacity(size_t size) {
  if (size > capacity_) {
    T *new_ptr = new T[size];
    try {
      for (int i = 0; i < static_cast<int>(capacity_); i++)
        new_ptr[i] = ptr_[i];
    } catch (...) {
      delete[] new_ptr;
      return true;
    }
    delete[] ptr_;
    ptr_ = std::move(new_ptr);
    capacity_ = size;
  } else if (size != capacity_) {
    T *new_ptr = new T[size];
    try {
      for (int i = 0; i < static_cast<int>(size); i++) new_ptr[i] = ptr_[i];
    } catch (...) {
      delete[] new_ptr;
      return true;
    }
    delete[] ptr_;
    ptr_ = std::move(new_ptr);
    size_ = capacity_ = size;
  }
  return false;
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
  if (tmp.ptr_) {
    try {
      tmp.ArgumentParser(0, args...);
    } catch (...) {
      return;
    }
    swap(tmp);
  }
}

template <class T>
template <class... Types>
void vector<T>::emplace_front(Types &&...args) {
  vector tmp(*this);
  if (tmp.ptr_) {
    try {
      tmp.ArgumentParser(size_, args...);
    } catch (...) {
      return;
    }
    swap(tmp);
  }
}

template <class T>
vector<T> &vector<T>::operator=(const vector &right) {
  if (this != &right) {
    vector tmp(right);
    if (tmp.ptr_) swap(tmp);
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
  vector tmp(*this);
  if (!tmp.MoveLeft(0, 1)) swap(tmp);
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
  assign(first, last);
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
void vector<T>::ArgumentParser(int position, T first, Other... other) {
  Moveright(position, 1);
  ptr_[size_ - position - 1] = first;
  ArgumentParser(position, other...);
}

template <class T>
template <class... Types>
typename vector<T>::iterator vector<T>::emplace(iterator position,
                                                Types &&...args) {
  int count_after = CountAfter(position);
  int size_before = size_;
  vector tmp(*this);
  if (tmp.ptr_) {
    try {
      tmp.ArgumentParser(count_after, args...);
    } catch (...) {
      return ptr_;
    }
    swap(tmp);
    return ptr_ + size_ - count_after - (size_ - size_before);
  }
  return ptr_;
}

template <class T>
typename vector<T>::iterator vector<T>::erase(const_iterator first,
                                              const_iterator last) {
  int count = size_ - CountAfter(first);
  vector tmp(*this);
  if (!tmp.MoveLeft(count, std::distance(first, last))) {
    swap(tmp);
    return ptr_ + count;
  }
  return ptr_;
}

template <class T>
bool vector<T>::MoveLeft(int position, int count) {
  try {
    for (int i = position; i < static_cast<int>(size_ - count); i++)
      ptr_[i] = ptr_[i + count];
  } catch (...) {
    return true;
  }
  size_ -= count;
  return 0;
}

template <class T>
typename vector<T>::iterator vector<T>::erase(const_iterator position) {
  int count_after = CountAfter(position);
  vector tmp(*this);
  if (!tmp.MoveLeft(size_ - count_after, 1)) {
    iterator for_return = tmp.ptr_ + size_ - count_after;
    swap(tmp);
    return for_return;
  }
  return ptr_;
}

template <class T>
void vector<T>::resize(size_t new_size, const T &value) {
  if (size_ < new_size) {
    vector tmp(new_size, value);
    if (tmp.ptr_) swap(tmp);
  }
}

template <class T>
void vector<T>::resize(size_t new_size) {
  if (size_ < new_size) {
    while (new_size > capacity_)
      if (DoubleMemory()) return;
  }
  size_ = new_size;
}

template <class T>
void vector<T>::clear() {
  size_ = 0;
}

template <class T>
void vector<T>::insert(const_iterator position,
                       std::initializer_list<T> init_list) {
  int count_after = CountAfter(position);
  int count = init_list.size();
  vector tmp(*this);
  if (tmp.ptr_) {
    try {
      tmp.Moveright(count_after, count);
      T *ptr2 = (T *)init_list.begin();
      for (int i = 0; i < count; i++)
        tmp.ptr_[tmp.size_ - count_after - count + i] = ptr2[i];
    } catch (...) {
      return;
    }
    swap(tmp);
  }
}

template <class T>
template <class InputIterator>
void vector<T>::insert(const_iterator position, InputIterator first,
                       InputIterator last) {
  int count_after = CountAfter(position);
  int count = std::distance(first, last);
  vector tmp(*this);
  if (tmp.ptr_) {
    try {
      tmp.Moveright(count_after, count);
      for (int i = 0; i < count; i++)
        tmp.ptr_[tmp.size_ - count_after - count + i] = *first++;
    } catch (...) {
      return;
    }
    swap(tmp);
  }
}

template <class T>
void vector<T>::insert(const_iterator position, size_t count, const T &value) {
  int count_after = CountAfter(position);
  vector tmp(*this);
  if (tmp.ptr_) {
    try {
      tmp.Moveright(count_after, count);
      for (int i = 0; i < static_cast<int>(count); i++)
        tmp.ptr_[tmp.size_ - count_after - count + i] = value;
    } catch (...) {
      return;
    }
    swap(tmp);
  }
}

template <class T>
int vector<T>::CountAfter(const_iterator position) const {
  int result = 0;
  while (position != end()) {
    position++;
    result++;
  }
  return result;
}

template <class T>
void vector<T>::Moveright(int position, int count) {
  while ((size_ + count) > capacity_)
    if (DoubleMemory()) std::bad_alloc();
  for (int i = 0; i < position; i++) {
    ptr_[size_ - 1 + count - i] = ptr_[size_ - 1 - i];
  }
  size_ += count;
}

template <class T>
typename vector<T>::iterator vector<T>::insert(const_iterator position,
                                               const T &value) {
  int count_after = CountAfter(position);
  vector tmp(*this);
  if (tmp.ptr_) {
    try {
      tmp.Moveright(count_after, 1);
      tmp.ptr_[tmp.size_ - count_after - 1] = value;
    } catch (...) {
      return ptr_;
    }
    swap(tmp);
  }
  return ptr_ + size_ - count_after - 1;
}

template <class T>
void vector<T>::pop_back() {
  if (size_ > 0) size_--;
}

template <class T>
T &vector<T>::front() {
  return *(ptr_);
}

template <class T>
const T &vector<T>::front() const {
  return *(ptr_);
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
T &vector<T>::at(size_t position) {
  if (position >= size_) throw std::out_of_range("going outside the array");
  return *(ptr_ + position);
}

template <class T>
const T &vector<T>::at(size_t position) const {
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
void vector<T>::assign(size_t count, const T value) {
  vector tmp(count, value);
  if (tmp.ptr_) std::swap(*this, tmp);
}

template <class T>
template <class InputIterator>
void vector<T>::assign(InputIterator first, InputIterator last) {
  vector tmp(std::distance(first, last));
  for (int i = 0; i < static_cast<int>(tmp.size_); i++) tmp.ptr_[i] = *first++;
  std::swap(*this, tmp);
}

template <class T>
void vector<T>::CopyIter(iterator first, iterator last) {
  size_t count = std::distance(first, last);
  ptr_ = new T[count];
  try {
    for (int i = 0; i < static_cast<int>(count); i++) ptr_[i] = *first++;
  } catch (...) {
    delete[] ptr_;
    ptr_ = nullptr;
  }
  size_ = capacity_ = count;
}

template <class T>
void vector<T>::assign(std::initializer_list<T> init_list) {
  vector tmp(init_list);
  if (tmp.ptr_) std::swap(*this, tmp);
}

template <class T>
void vector<T>::CopyList(std::initializer_list<T> init_list) {
  ptr_ = new T[init_list.size()];
  try {
    T *ptr2 = (T *)init_list.begin();
    for (int i = 0; i < static_cast<int>(init_list.size()); i++)
      ptr_[i] = ptr2[i];
  } catch (...) {
    delete[] ptr_;
    ptr_ = nullptr;
  }
  size_ = capacity_ = init_list.size();
}

template <class T>
int vector<T>::ComparisonVector(vector &other) const {
  int res = 0, size1 = size(), size2 = other.size();
  for (int i = 0; i < size1 && i < size2; i++) {
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
void vector<T>::reserve(size_t count) {
  if (capacity_ < count) {
    if (!ChangeCapacity(count)) size_ = count;
  }
}

template <class T>
void vector<T>::push_back(const T &value) {
  if (size_ >= capacity_)
    if (DoubleMemory()) return;
  ptr_[size_++] = value;
}

template <class T>
void vector<T>::push_back(T &&value) {
  if (size_ >= capacity_)
    if (DoubleMemory()) return;
  ptr_[size_++] = std::move(value);
}

template <class T>
bool vector<T>::empty() const {
  return !size_;
}

template <class T>
T &vector<T>::operator[](const size_t n) {
  return *(ptr_ + n);
}

template <class T>
const T &vector<T>::operator[](const size_t n) const {
  return *(ptr_ + n);
}

template <class T>
vector<T>::vector(iterator first, iterator last) {
  CopyIter(first, last);
}

template <class T>
bool vector<T>::DoubleMemory() {
  if (capacity_ == 0) return ChangeCapacity(512);
  return ChangeCapacity(capacity_ * 2);
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
  ptr_ = new (std::nothrow) T[other.capacity_];
  if (!ptr_) return;
  try {
    for (int i = 0; i < static_cast<int>(other.size_); i++)
      ptr_[i] = other.ptr_[i];
  } catch (...) {
    delete[] ptr_;
    ptr_ = nullptr;
    return;
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
size_t vector<T>::size() const {
  return size_;
}

template <class T>
size_t vector<T>::capacity() const {
  return capacity_;
}

template <class T>
vector<T>::vector() {
  ptr_ = new (std::nothrow) T[512];
  if (!ptr_) return;
  size_ = 0;
  capacity_ = 512;
}

template <class T>
vector<T>::vector(int count) {
  ptr_ = new (std::nothrow) T[count];
  if (!ptr_) return;
  size_ = capacity_ = count;
}

template <class T>
vector<T>::vector(size_t count, T value) {
  ptr_ = new (std::nothrow) T[count];
  if (!ptr_) return;
  try {
    for (int i = 0; i < static_cast<int>(count); i++) ptr_[i] = value;
  } catch (...) {
    delete[] ptr_;
    ptr_ = nullptr;
    return;
  }
  size_ = capacity_ = count;
}

template <class T>
vector<T>::vector(std::initializer_list<T> init_list) {
  if (init_list.size()) CopyList(init_list);
}

}  // namespace s21
#endif  // CONTAINERS_SRC_VECTOR_H_