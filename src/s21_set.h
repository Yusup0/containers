#ifndef S21_CONTAINERS_SRC_SET_H_
#define S21_CONTAINERS_SRC_SET_H_

#include <iostream>
#include <iterator>
#include <limits>
#include <vector>

#include "./general_btee.h"

namespace s21 {

template <class Key, class Compare = std::less<Key>>
class set {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;

  using iterator = IteratorGeneral<Key, Compare>;
  using const_iterator = IteratorGeneralConst<Key, Compare>;

  set() = default;
  set(std::initializer_list<Key> init_list)
      : tree(init_list.begin(), init_list.end()) {}
  template <class InputIterator>
  set(InputIterator first, InputIterator last) : tree(first, last) {}
  set(const set &right) : tree(right.tree) {}
  set(set &&right) noexcept : tree(std::move(right.tree)) {}
  set<Key, Compare> &operator=(const set &right) {
    tree = right.tree;
    return *this;
  }
  set<Key, Compare> &operator=(set &&right) noexcept {
    tree = std::move(right.tree);
    return *this;
  }
  ~set() = default;
  bool operator<(set &other) const { return tree < other.tree; }
  bool operator>(set &other) const { return tree > other.tree; }
  bool operator==(set &other) const { return tree == other.tree; }
  bool operator!=(set &other) const { return tree != other.tree; }
  bool operator<=(set &other) const { return tree <= other.tree; }
  bool operator>=(set &other) const { return tree >= other.tree; }
  template <class... Types>
  std::vector<std::pair<iterator, bool>> emplace(Types &&...args) {
    return tree.emplace(false, std::forward<Types>(args)...);
  }
  std::pair<iterator, bool> insert(const_reference value) {
    return tree.insert(value);
  }
  iterator begin() noexcept { return tree.begin(); }
  const_iterator begin() const noexcept { return tree.begin(); }
  const_iterator cbegin() const noexcept { return tree.begin(); }
  iterator end() noexcept { return tree.end(); }
  const_iterator end() const noexcept { return tree.end(); }
  const_iterator cend() const noexcept { return tree.end(); }
  void erase(iterator pos) { tree.erase(pos); }
  size_type size() const noexcept { return tree.size(); }
  size_type max_size() const noexcept { return tree.max_size(); }
  bool empty() const noexcept { return tree.empty(); }
  size_type count(const_reference value) const { return tree.count(value); }
  bool contains(const_reference value) const { return tree.contains(value); }
  iterator find(const_reference value) { return tree.find(value); }
  const_iterator find(const_reference value) const { return tree.find(value); }
  void clear() { tree.clear(); }
  void swap(set &right) noexcept { tree.swap(right.tree); }
  void merge(set &other) { tree.merge(other.tree); }

 private:
  BTree<Key, Compare> tree;
};

}  // namespace s21
#endif  //  S21_CONTAINERS_SRC_SET_H_