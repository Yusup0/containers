#ifndef S21_CONTAINERS_SRC_STACK_H_
#define S21_CONTAINERS_SRC_STACK_H_

#include <iostream>

#include "./s21_list.h"
#include "./s21_vector.h"

namespace s21 {
template <class T, class Container = list<T>>
class stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  stack() = default;
  stack(std::initializer_list<value_type> const &items);
  void swap(stack &other) noexcept;
  template <class ContainerOther>
  stack(const ContainerOther &right);
  bool empty() const noexcept;
  void pop();
  void push(const_reference value);
  size_t size() const noexcept;
  reference top();
  const_reference top() const;
  template <class... Types>
  void emplace_front(Types &&...args);

 private:
  Container stack_;
};

template <class T, class Container>
void stack<T, Container>::swap(stack &other) noexcept {
  return stack_.swap(other.stack_);
}

template <class T, class Container>
template <class ContainerOther>
stack<T, Container>::stack(const ContainerOther &right) {
  stack_ = right;
}

template <class T, class Container>
void stack<T, Container>::pop() {
  stack_.pop_back();
}

template <class T, class Container>
stack<T, Container>::stack(std::initializer_list<value_type> const &items)
    : stack_(items) {}

template <class T, class Container>
void stack<T, Container>::push(const_reference value) {
  stack_.push_back(value);
}

template <class T, class Container>
size_t stack<T, Container>::size() const noexcept {
  return stack_.size();
}

template <class T, class Container>
typename stack<T, Container>::reference stack<T, Container>::top() {
  return stack_.back();
}

template <class T, class Container>
typename stack<T, Container>::const_reference stack<T, Container>::top() const {
  return stack_.back();
}

template <class T, class Container>
template <class... Types>
void stack<T, Container>::emplace_front(Types &&...args) {
  stack_.emplace_front(std::forward<Types>(args)...);
}

template <class T, class Container>
bool stack<T, Container>::empty() const noexcept {
  return stack_.empty();
}

}  // namespace s21
#endif  // S21_CONTAINERS_SRC_STACK_H_