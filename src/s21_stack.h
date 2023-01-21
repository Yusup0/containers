#ifndef CONTAINERS_SRC_STACK_H_
#define CONTAINERS_SRC_STACK_H_

#include <stdlib.h>

#include <iostream>
using namespace std;
#include "./s21_list.h"
#include "./s21_vector.h"

namespace s21 {
template <class T, class Container = list<T>>
class stack {
 public:
  stack() {}
  template <class ContainerOther>
  stack(const ContainerOther &right);
  bool empty() const;
  void pop();
  void push(const T &value);
  size_t size() const;
  T &top();
  const T &top() const;
  template <class... Types>
  void emplace_front(Types &&...args);

 private:
  Container stack_;
};

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
void stack<T, Container>::push(const T &value) {
  stack_.push_back(value);
}

template <class T, class Container>
size_t stack<T, Container>::size() const {
  return stack_.size();
}

template <class T, class Container>
T &stack<T, Container>::top() {
  return stack_.back();
}

template <class T, class Container>
const T &stack<T, Container>::top() const {
  return stack_.back();
}

template <class T, class Container>
template <class... Types>
void stack<T, Container>::emplace_front(Types &&...args) {
  stack_.emplace_front(args...);
}

template <class T, class Container>
bool stack<T, Container>::empty() const {
  return stack_.empty();
}

}  // namespace s21
#endif  // CONTAINERS_SRC_STACK_H_