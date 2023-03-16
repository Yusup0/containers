#ifndef S21_CONTAINERS_SRC_QUEUE_H_
#define S21_CONTAINERS_SRC_QUEUE_H_

// 3) Не реализовали queue(std::initializer_list<value_type> const
// &items) - а по заданию надо 4) Не реализовали void swap(queue& other) - а по
// заданию надо

#include <iostream>

#include "./s21_list.h"
#include "./s21_vector.h"

namespace s21 {
template <class T, class Container = list<T>>
class queue {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  queue() = default;
  queue(std::initializer_list<value_type> const &items);
  void swap(queue &other) noexcept;
  template <class ContainerOther>
  queue(const ContainerOther &right);
  bool empty() const noexcept;
  void pop();
  void push(const_reference value);
  size_t size() const noexcept;
  reference back();
  const_reference back() const;
  reference front();
  const_reference front() const;
  template <class... Types>
  void emplace_back(Types &&...args);

 private:
  Container queue_;
};

template <class T, class Container>
void queue<T, Container>::swap(queue &other) noexcept {
  queue_.swap(other.queue_);
}

template <class T, class Container>
template <class ContainerOther>
queue<T, Container>::queue(const ContainerOther &right) {
  queue_ = right;
}

template <class T, class Container>
queue<T, Container>::queue(std::initializer_list<value_type> const &items)
    : queue_(items) {}

template <class T, class Container>
bool queue<T, Container>::empty() const noexcept {
  return queue_.empty();
}

template <class T, class Container>
void queue<T, Container>::pop() {
  queue_.pop_front();
}

template <class T, class Container>
void queue<T, Container>::push(const_reference value) {
  queue_.push_back(value);
}

template <class T, class Container>
size_t queue<T, Container>::size() const noexcept {
  return queue_.size();
}

template <class T, class Container>
typename queue<T, Container>::reference queue<T, Container>::back() {
  return queue_.back();
}

template <class T, class Container>
typename queue<T, Container>::const_reference queue<T, Container>::back()
    const {
  return queue_.back();
}

template <class T, class Container>
typename queue<T, Container>::reference queue<T, Container>::front() {
  return queue_.front();
}

template <class T, class Container>
typename queue<T, Container>::const_reference queue<T, Container>::front()
    const {
  return queue_.front();
}

template <class T, class Container>
template <class... Types>
void queue<T, Container>::emplace_back(Types &&...args) {
  queue_.emplace_back(std::forward<Types>(args)...);
}

}  // namespace s21
#endif  // S21_CONTAINERS_SRC_QUEUE_H_