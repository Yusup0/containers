#ifndef CONTAINERS_SRC_QUEUE_H_
#define CONTAINERS_SRC_QUEUE_H_

#include <iostream>
using namespace std;
#include <stdlib.h>

#include "./s21_list.h"
#include "./s21_vector.h"

namespace s21 {
template <class T, class Container = list<T>>
class queue {
 public:
  queue() {}
  template <class ContainerOther>
  queue(const ContainerOther &right);
  bool empty() const;
  void pop();
  void push(const T &value);
  size_t size() const;
  T &back();
  const T &back() const;
  T &front();
  const T &front() const;
  template <class... Types>
  void emplace_back(Types &&...args);

 private:
  Container queue_;
};

template <class T, class Container>
template <class ContainerOther>
queue<T, Container>::queue(const ContainerOther &right) {
  queue_ = right;
}

template <class T, class Container>
bool queue<T, Container>::empty() const {
  return queue_.empty();
}

template <class T, class Container>
void queue<T, Container>::pop() {
  queue_.pop_front();
}

template <class T, class Container>
void queue<T, Container>::push(const T &value) {
  queue_.push_back(value);
}

template <class T, class Container>
size_t queue<T, Container>::size() const {
  return queue_.size();
}

template <class T, class Container>
T &queue<T, Container>::back() {
  return queue_.back();
}

template <class T, class Container>
const T &queue<T, Container>::back() const {
  return queue_.back();
}

template <class T, class Container>
T &queue<T, Container>::front() {
  return queue_.front();
}

template <class T, class Container>
const T &queue<T, Container>::front() const {
  return queue_.front();
}

template <class T, class Container>
template <class... Types>
void queue<T, Container>::emplace_back(Types &&...args) {
  queue_.emplace_back(args...);
}

}  // namespace s21
#endif  // CONTAINERS_SRC_QUEUE_H_