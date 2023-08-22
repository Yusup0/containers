#ifndef S21_CONTAINERS_SRC_MULTISET_H_
#define S21_CONTAINERS_SRC_MULTISET_H_

#include <iostream>
#include <limits>
#include <vector>

#include "./general_btee.h"

namespace s21 {

template <class Key, class Compare = std::less<Key>>
class multiset {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;

  using iterator = IteratorGeneral<Key, Compare>;
  using const_iterator = IteratorGeneralConst<Key, Compare>;

  multiset() = default;
  multiset(std::initializer_list<Key> init_list)
      : tree(init_list.begin(), init_list.end(), true) {}
  template <class InputIterator>
  multiset(InputIterator first, InputIterator last) : tree(first, last, true) {}
  multiset(const multiset &right) : tree(right.tree) {}
  multiset(multiset &&right) noexcept : tree(std::move(right.tree)) {}
  multiset &operator=(const multiset &right) {
    tree = right.tree;
    return *this;
  }
  multiset &operator=(multiset &&right) noexcept {
    tree = std::move(right.tree);
    return *this;
  }
  ~multiset() = default;
  bool operator<(multiset &other) const { return tree < other.tree; }
  bool operator>(multiset &other) const { return tree > other.tree; }
  bool operator==(multiset &other) const { return tree == other.tree; }
  bool operator!=(multiset &other) const { return tree != other.tree; }
  bool operator<=(multiset &other) const { return tree <= other.tree; }
  bool operator>=(multiset &other) const { return tree >= other.tree; }
  template <class... Types>
  std::vector<std::pair<iterator, bool>> emplace(Types &&...args) {
    return tree.emplace(true, std::forward<Types>(args)...);
  }
  iterator insert(const_reference value) {
    return (tree.insert(value, true)).first;
  }
  iterator begin() noexcept { return tree.begin(); }
  const_iterator begin() const noexcept { return tree.begin(); }
  const_iterator cbegin() const noexcept { return tree.begin(); }
  iterator end() noexcept { return tree.end(); }
  const_iterator end() const noexcept { return tree.end(); }
  const_iterator cend() const noexcept { return tree.end(); }
  void erase(iterator pos) { tree.erase(pos, true); }
  size_type size() const noexcept { return tree.size(); }
  size_type max_size() const noexcept { return tree.max_size(); }
  bool empty() const noexcept { return tree.empty(); }
  size_type count(const_reference value) const { return tree.count(value); }
  iterator find(const_reference value) { return tree.find(value); }
  const_iterator find(const_reference value) const { return tree.find(value); }
  bool contains(const_reference key) const { return tree.contains(key); }
  iterator lower_bound(const_reference value) {
    return tree.lower_bound(value);
  }
  const_iterator lower_bound(const_reference value) const {
    return tree.lower_bound(value);
  }
  iterator upper_bound(const_reference value) {
    return tree.upper_bound(value);
  }
  const_iterator upper_bound(const_reference value) const {
    return tree.upper_bound(value);
  }
  void clear() { tree.clear(); }
  void swap(multiset &right) noexcept { tree.swap(right.tree); }
  std::pair<iterator, iterator> equal_range(const_reference value) {
    return tree.equal_range(value);
  }
  std::pair<const_iterator, const_iterator> equal_range(
      const_reference value) const {
    return tree.equal_range(value);
  }
  void merge(multiset &other) { tree.merge(other.tree, true); }

 private:
  BTree<Key, Compare> tree;
};

}  // namespace s21
#endif  // S21_CONTAINERS_SRC_MULTISET_HPP_