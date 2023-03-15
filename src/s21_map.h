#ifndef S21_CONTAINERS_SRC_MAP_H_
#define S21_CONTAINERS_SRC_MAP_H_

#include <stdlib.h>

#include <iostream>
#include <limits>
#include <vector>

#include "./general.h"

namespace s21 {

template <class T, class Compare>
struct My_Compare {
  bool operator()(const T &l, const T &r) const {
    return comp_(l.first, r.first);
  }
 private:
  Compare comp_;
};

template <class Key, class T, class Compare = std::less<Key>>
class map {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;

  using iterator = IteratorGeneral<value_type, My_Compare<value_type, Compare>>;
  using const_iterator =
      IteratorGeneralConst<value_type, My_Compare<value_type, Compare>>;

  map() = default;
  map(std::initializer_list<value_type> init_list)
      : tree(init_list.begin(), init_list.end()) {}
  template <class InputIterator>
  map(InputIterator first, InputIterator last) : tree(first, last) {}
  map(const map &right) : tree(right.tree) {}
  map(map &&right) noexcept : tree(std::move(right.tree)) {}
  map<key_type, T, Compare> &operator=(const map &right) {
    tree = right.tree;
    return *this;
  }
  map<key_type, T, Compare> &operator=(map &&right) noexcept {
    tree = std::move(right.tree);
    return *this;
  }
  ~map() = default;
  bool operator<(map &other) const { return tree < other.tree; }
  bool operator>(map &other) const { return tree > other.tree; }
  bool operator==(map &other) const { return tree == other.tree; }
  bool operator!=(map &other) const { return tree != other.tree; }
  bool operator<=(map &other) const { return tree <= other.tree; }
  bool operator>=(map &other) const { return tree >= other.tree; }
  template <class... Types>
  std::vector<std::pair<iterator, bool>> emplace(Types &&...args) {
    return tree.emplace(false, std::forward<Types>(args)...);
  }
  mapped_type &operator[](const Key &key) {
    iterator it = find(key);
    if (it == end()) {
      return (insert(value_type(key, T()))).first->second;
    } else {
      return it->second;
    }
  }
  mapped_type &at(const key_type &key) {
    iterator it = find(key);
    if (it == end()) throw std::out_of_range("going outside the array");
    return (*it).second;
  }
  const mapped_type &at(const key_type &key) const {
    const_iterator it = find(key);
    if (it == end()) throw std::out_of_range("going outside the array");
    return (*it).second;
  }
  std::pair<iterator, bool> insert(const_reference value) {
    return tree.insert(value);
  }
  std::pair<iterator, bool> insert(const Key &key, const T &obj) {
    return tree.insert(value_type(key, obj));
  }
  std::pair<iterator, bool> insert_or_assign(const Key &key, const T &obj) {
    auto it = find(key);
    if (it == end()) {
      return insert(key, obj);
    } else {
      it->second = obj;
      return std::pair<iterator, bool>(it, true);
    }
  }
  bool contains(const key_type &key) const {
    return tree.contains(value_type(key, mapped_type()));
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
  size_type count(const Key &key) const {
    return tree.count(value_type(key, mapped_type()));
  }
  iterator find(const key_type &key) {
    return tree.find(value_type(key, mapped_type()));
  }
  const_iterator find(const key_type &key) const {
    return tree.find(value_type(key, mapped_type()));
  }
  void clear() { tree.clear(); }
  void swap(map &right) noexcept { tree.swap(right.tree); }
  void merge(map &other) { tree.merge(other.tree); }

 private:
  BTree<value_type, My_Compare<value_type, Compare>> tree;
};

}  // namespace s21
#endif  // S21_CONTAINERS_SRC_MAP_H_