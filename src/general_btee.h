#ifndef CONTAINERS_SRC_GENERAL_H_
#define CONTAINERS_SRC_GENERAL_H_

#include <limits>
#include <vector>

namespace s21 {

template <class Key, class Compare = std::less<Key>>
class BTree;
template <class T, class Compare>
class IteratorGeneralConst;

/**
 * @brief Узел бинарного дерева
 */
template <class Key>
struct StructGeneral {
  StructGeneral() = delete;
  StructGeneral(Key key) : key_(key) {}
  StructGeneral<Key> *left_ = nullptr, *right_ = nullptr, *parent_ = nullptr;
  Key key_;
  bool is_red_ = false;
  size_t count_ = 1;
};

/**
 * @brief Ближайший по значению правый элемент
 */
template <class Struct>
Struct *ClosestRight(Struct *value) noexcept {
  Struct *result;
  if (value->right_ != nullptr) {
    value = value->right_;
    while (value->left_ != nullptr) value = value->left_;
    result = value;
  } else {
    result = value->parent_;
    while (result->right_ == value) {
      value = result;
      result = result->parent_;
    }
  }
  return result;
}

/**
 * @brief Ближайший по значению левый элемент
 */
template <class Struct>
Struct *ClosestLeft(Struct *value) noexcept {
  Struct *result;
  if (value->left_ != nullptr) {
    value = value->left_;
    while (value->right_ != nullptr) value = value->right_;
    result = value;
  } else {
    result = value->parent_;
    while (result->left_ == value) {
      value = result;
      result = result->parent_;
    }
  }
  return result;
}

template <class Key, class Compare>
class IteratorGeneral {
  friend class BTree<Key, Compare>;
  friend class IteratorGeneralConst<Key, Compare>;

 public:
  using value_type = Key;
  using pointer = Key *;
  using reference = Key &;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::bidirectional_iterator_tag;

  IteratorGeneral() = delete;
  IteratorGeneral(StructGeneral<Key> *address, size_t count = 1)
      : address_(address), count_(count) {}
  reference operator*() const { return address_->key_; }
  pointer operator->() const { return &address_->key_; }
  IteratorGeneral &operator++() {
    if (count_ < address_->count_) {
      count_++;
    } else {
      address_ = ClosestRight(address_);
      count_ = 1;
    }
    return *this;
  }
  IteratorGeneral operator++(int) {
    IteratorGeneral result = *this;
    ++(*this);
    return result;
  }
  IteratorGeneral &operator--() {
    if (count_ > 1) {
      count_--;
    } else {
      address_ = ClosestLeft(address_);
      count_ = address_->count_;
    }
    return *this;
  }
  IteratorGeneral operator--(int) {
    IteratorGeneral result = *this;
    --(*this);
    return result;
  }
  bool operator==(const IteratorGeneral &it) const {
    return address_ == it.address_ && count_ == it.count_;
  }
  bool operator==(const IteratorGeneralConst<Key, Compare> &it) const {
    return address_ == it.address_ && count_ == it.count_;
  }
  bool operator!=(const IteratorGeneral &it) const {
    return address_ != it.address_ || count_ != it.count_;
  }
  bool operator!=(const IteratorGeneralConst<Key, Compare> &it) const {
    return address_ != it.address_ || count_ != it.count_;
  }

 private:
  StructGeneral<Key> *address_;
  size_t count_;
};

template <class Key, class Compare>
class IteratorGeneralConst {
  friend class BTree<Key, Compare>;
  friend class IteratorGeneral<Key, Compare>;

 public:
  using value_type = const Key;
  using pointer = const Key *;
  using reference = const Key &;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::bidirectional_iterator_tag;

  IteratorGeneralConst() = delete;
  IteratorGeneralConst(StructGeneral<Key> *address, size_t count = 1)
      : address_(address), count_(count) {}
  IteratorGeneralConst(const IteratorGeneral<Key, Compare> &it)
      : address_(it.address_), count_(it.count_) {}
  reference operator*() const { return address_->key_; }
  pointer operator->() const { return &address_->key_; }
  IteratorGeneralConst &operator++() {
    if (count_ < address_->count_) {
      count_++;
    } else {
      address_ = ClosestRight(address_);
      count_ = 1;
    }
    return *this;
  }
  IteratorGeneralConst operator++(int) {
    IteratorGeneralConst result = *this;
    ++(*this);
    return result;
  }
  IteratorGeneralConst &operator--() {
    if (count_ > 1) {
      count_--;
    } else {
      address_ = ClosestLeft(address_);
      count_ = address_->count_;
    }
    return *this;
  }
  IteratorGeneralConst operator--(int) {
    IteratorGeneralConst result = *this;
    --(*this);
    return result;
  }
  bool operator==(const IteratorGeneralConst &it) const {
    return address_ == it.address_ && count_ == it.count_;
  }
  bool operator==(const IteratorGeneral<Key, Compare> &it) const {
    return address_ == it.address_ || count_ == it.count_;
  }
  bool operator!=(const IteratorGeneralConst &it) const {
    return address_ != it.address_ || count_ != it.count_;
  }
  bool operator!=(const IteratorGeneral<Key, Compare> &it) const {
    return address_ != it.address_ || count_ != it.count_;
  }

 private:
  const StructGeneral<Key> *address_;
  size_t count_;
};

template <class Key, class Compare>
class BTree {
 public:
  using iterator = IteratorGeneral<Key, Compare>;
  using const_iterator = IteratorGeneralConst<Key, Compare>;

  BTree() = default;

  template <class InputIterator>
  BTree(InputIterator first, InputIterator last, bool need_duplicates = false) {
    try {
      while (first != last) {
        insert(*first, need_duplicates);
        first++;
      }
    } catch (...) {
      clear();
      delete anchor_;
      throw;
    }
  }

  BTree(const BTree &right) {
    const_iterator begin = right.begin(), end = right.end();
    try {
      while (begin != end) {
        insert(*begin, true);
        begin++;
      }
    } catch (...) {
      clear();
      delete anchor_;
      throw;
    }
  }

  BTree(BTree &&right) noexcept { swap(right); }

  BTree &operator=(const BTree &right) {
    BTree tmp(right);
    swap(tmp);
    return *this;
  }

  BTree &operator=(BTree &&right) noexcept {
    swap(right);
    return *this;
  }

  ~BTree() noexcept {
    clear();
    delete anchor_;
  }

  bool operator<(BTree &other) const { return ComparisonBTee(other) == -1; }
  bool operator>(BTree &other) const { return ComparisonBTee(other) == 1; }
  bool operator==(BTree &other) const { return !ComparisonBTee(other); }
  bool operator!=(BTree &other) const { return ComparisonBTee(other); }
  bool operator<=(BTree &other) const { return ComparisonBTee(other) != 1; }
  bool operator>=(BTree &other) const { return ComparisonBTee(other) != -1; }

  template <class... Args>
  std::vector<std::pair<iterator, bool>> emplace(bool need_duplicates,
                                                 Args &&...args) {
    std::vector<std::pair<iterator, bool>> result;
    ArgumentParser(result, need_duplicates, std::forward<Args>(args)...);
    return result;
  }

  std::pair<iterator, iterator> equal_range(const Key &key) {
    return std::pair<iterator, iterator>(lower_bound(key), upper_bound(key));
  }

  std::pair<const_iterator, const_iterator> equal_range(const Key &key) const {
    return std::pair<const_iterator, const_iterator>(lower_bound(key),
                                                     upper_bound(key));
  }

  iterator lower_bound(const Key &key) {
    iterator result = end();
    if (anchor_->right_ != nullptr) {
      StructGeneral<Key> *position = FindPosition(anchor_->right_, key);
      if (comp_(position->key_, key))
        result = ClosestRight(position);
      else
        result = position;
    }
    return result;
  }

  const_iterator lower_bound(const Key &key) const {
    const_iterator result = end();
    if (anchor_->right_ != nullptr) {
      StructGeneral<Key> *position = FindPosition(anchor_->right_, key);
      if (comp_(position->key_, key))
        result = ClosestRight(position);
      else
        result = position;
    }
    return result;
  }

  iterator upper_bound(const Key &key) {
    iterator result = end();
    if (anchor_->right_ != nullptr) {
      StructGeneral<Key> *position = FindPosition(anchor_->right_, key);
      if (comp_(position->key_, key) || !not_equally(position->key_, key)) {
        result = ClosestRight(position);
      } else {
        result = position;
      }
    }
    return result;
  }

  const_iterator upper_bound(const Key &key) const {
    const_iterator result = end();
    if (anchor_->right_ != nullptr) {
      StructGeneral<Key> *position = FindPosition(anchor_->right_, key);
      if (comp_(position->key_, key) || !not_equally(position->key_, key)) {
        result = ClosestRight(position);
      } else {
        result = position;
      }
    }
    return result;
  }

  iterator find(const Key &key) {
    iterator result = end();
    if (anchor_->right_ != nullptr) {
      StructGeneral<Key> *position = FindPosition(anchor_->right_, key);
      if (!not_equally(position->key_, key)) result = position;
    }
    return result;
  }

  const_iterator find(const Key &key) const {
    const_iterator result = end();
    if (anchor_->right_ != nullptr) {
      StructGeneral<Key> *position = FindPosition(anchor_->right_, key);
      if (!not_equally(position->key_, key)) result = position;
    }
    return result;
  }

  size_t count(const Key &key) const {
    return find(key) != end() ? (find(key)).address_->count_ : 0;
  }

  bool contains(const Key &key) const { return count(key); }

  void merge(BTree &other, bool need_duplicates = false) {
    iterator begin = other.begin();
    while (begin != other.end()) {
      insert(*begin, need_duplicates);
      ++begin;
    }
  }

  void swap(BTree &other) noexcept {
    std::swap(anchor_, other.anchor_);
    std::swap(size_, other.size_);
  }

  std::pair<iterator, bool> insert(const Key &value,
                                   bool need_duplicates = false) {
    return InsertStandart(anchor_->right_, value, need_duplicates);
  }

  iterator erase(iterator pos, bool have_duplicates = false) {
    if (!have_duplicates) return Erase(pos.address_);
    iterator res = end();
    if (pos.address_->count_ > 1) {
      --pos.address_->count_;
      --size_;
      if (pos.address_->count_ < pos.count_) {
        res = ++pos;
      } else {
        res = pos;
      }
    } else {
      res = Erase(pos.address_);
    }
    return res;
  }

  void clear() noexcept {
    if (anchor_->right_ != anchor_ && anchor_->right_ != nullptr)
      FreeSet(anchor_->right_);
    anchor_->left_ = anchor_->right_ = nullptr;
  }

  bool empty() const noexcept { return !size_; }

  size_t size() const noexcept { return size_; }

  size_t max_size() const noexcept {
    return std::numeric_limits<size_t>::max() / 2 / sizeof(StructGeneral<Key>) -
           1;
  }

  iterator end() noexcept { return anchor_; }

  const_iterator end() const noexcept { return anchor_; }

  iterator begin() noexcept {
    return anchor_->right_ ? Leftmost(anchor_->right_) : anchor_;
  }

  const_iterator begin() const noexcept {
    return anchor_->right_ ? Leftmost(anchor_->right_) : anchor_;
  }

 private:
  StructGeneral<Key> *anchor_ = CreateAnchor();

  Compare comp_;

  size_t size_ = 0;

  /**
   * @brief Вставляет узел в дерево
   *
   * @param wheere место откуда начинается поиск позиции для value
   * @param value значение которое нужно вставить
   * @param need_duplicates = true в дерево можно вставить дубликаты
   * @return pair в котором итератор указывающий на место вставки и bool
   * переменная которая true при удачной вставке
   */
  std::pair<iterator, bool> InsertStandart(StructGeneral<Key> *wheere,
                                           const Key &value,
                                           bool need_duplicates = false) {
    if (!anchor_) anchor_ = CreateAnchor();
    bool is_add = true;
    StructGeneral<Key> *position = anchor_;
    if (!size_) {
      anchor_->left_ = anchor_->right_ = new StructGeneral<Key>(value);
      position = anchor_->right_;
      position->parent_ = anchor_;
    } else {
      position = FindPosition(wheere, value);
      if (not_equally(position->key_, value)) {
        if (comp_(position->key_, value)) {
          position->right_ = new StructGeneral<Key>(value);
          position->right_->parent_ = position;
          position = position->right_;
        } else {
          position->left_ = new StructGeneral<Key>(value);
          position->left_->parent_ = position;
          position = position->left_;
        }
        position->is_red_ = true;
        Adjustment(position);
      } else {
        if (need_duplicates) {
          position->count_++;
        } else {
          is_add = false;
        }
      }
    }
    if (is_add) size_++;
    return std::pair<iterator, bool>(iterator(position, position->count_),
                                     is_add);
  }

  /**
   * @brief удаляет узел из дерева
   *
   * @param position позиция узла
   * @return Узел ближайший правый по значению
   */
  StructGeneral<Key> *Erase(StructGeneral<Key> *position) {
    if (position == anchor_) return anchor_;
    StructGeneral<Key> *parent_ = position->parent_;
    StructGeneral<Key> *result = ClosestRight(position);
    if (position->left_ == nullptr && position->right_ == nullptr) {
      if (parent_->right_ == position) {
        parent_->right_ = nullptr;
      } else {
        parent_->left_ = nullptr;
      }
    } else if (position->left_ == nullptr) {
      if (parent_->right_ == position) {
        parent_->right_ = position->right_;
        position->right_->parent_ = parent_;
      } else {
        parent_->left_ = position->right_;
        position->right_->parent_ = parent_;
      }
    } else if (position->right_ == nullptr) {
      if (parent_->right_ == position) {
        parent_->right_ = position->left_;
        position->left_->parent_ = parent_;
      } else {
        parent_->left_ = position->left_;
        position->left_->parent_ = parent_;
      }
    } else {
      StructGeneral<Key> *change = ClosestLeft(position);
      swap_node(position, change);
      erase(position);
      return result;
    }
    if (parent_ == anchor_) anchor_->left_ = anchor_->right_;
    size_ -= position->count_;
    delete position;
    return result;
  }

  /**
   * @brief Поиск узла по значению
   */
  StructGeneral<Key> *FindPosition(StructGeneral<Key> *root,
                                   const Key &value) const noexcept {
    StructGeneral<Key> *pos = root;
    if (comp_(root->key_, value)) {
      if (root->right_ == nullptr) {
        pos = root;
      } else {
        pos = FindPosition(root->right_, value);
      }
    } else if (comp_(value, root->key_)) {
      if (root->left_ == nullptr) {
        pos = root;
      } else {
        pos = FindPosition(root->left_, value);
      }
    }
    return pos;
  }

  /**
   * @brief Сравнение двух деревьев
   */
  int ComparisonBTee(const BTree &other) const {
    int res = 0;
    size_t size1 = size(), size2 = other.size();
    const_iterator our_it = begin();
    const_iterator other_it = other.begin();
    for (size_t i = 0; i < size1 && i < size2; i++, our_it++, other_it++) {
      if (*our_it != *other_it) {
        res = *our_it > *other_it ? 1 : -1;
        break;
      }
    }
    if (!res && size1 != size2) res = size1 > size2 ? 1 : -1;
    return res;
  }

  bool not_equally(const Key &l, const Key &r) const {
    return (comp_(l, r) + comp_(r, l)) == 1;
  }

  /**
   * @brief Рекурсивно вставляет по одному элементу в дерево. Когда элементы
   * закончились, выходит из рекурсии с помощью следующего метода
   */
  template <class... Other>
  void ArgumentParser(std::vector<std::pair<iterator, bool>> &result,
                      bool need_duplicates, Key &&first, Other... other) {
    result.push_back(insert(first, need_duplicates));
    ArgumentParser(result, need_duplicates, std::forward<Other>(other)...);
  }

  void ArgumentParser(
      [[maybe_unused]] std::vector<std::pair<iterator, bool>> &result,
      [[maybe_unused]] bool need_duplicates) {}

  StructGeneral<Key> *Leftmost(StructGeneral<Key> *value) const {
    while (value->left_ != nullptr) value = value->left_;
    return value;
  }

  StructGeneral<Key> *CreateAnchor() {
    StructGeneral<Key> *result;
    result = new StructGeneral<Key>(Key());
    result->parent_ = result;
    return result;
  }

  /**
   * @brief Меняет две ноды местами указателями
   */
  void swap_node(StructGeneral<Key> *first,
                 StructGeneral<Key> *second) noexcept {
    if (first->parent_->right_ == first) {
      first->parent_->right_ = second;
    } else {
      first->parent_->left_ = second;
    }
    if (second->parent_->right_ == second) {
      second->parent_->right_ = first;
    } else {
      second->parent_->left_ = first;
    }
    std::swap(first->is_red_, second->is_red_);
    std::swap(first->left_, second->left_);
    std::swap(first->right_, second->right_);
    std::swap(first->parent_, second->parent_);

    if (first->left_) first->left_->parent_ = first;
    if (first->right_) first->right_->parent_ = first;
    if (second->left_) second->left_->parent_ = second;
    if (second->right_) second->right_->parent_ = second;
    if (anchor_->right_ == second) anchor_->left_ = second;
  }

  /**
   * @brief Балансировка дерева при вставке
   */
  void Adjustment(StructGeneral<Key> *value) {
    StructGeneral<Key> *parent_ = value->parent_;
    if ((parent_->right_ != nullptr && parent_->right_->is_red_ == true) &&
        (parent_->left_ != nullptr && parent_->left_->is_red_ == true))
      SwapColors(value);
    if ((parent_->right_ != nullptr && parent_->right_ == value) &&
        value->is_red_ == true)
      RightTurn(value);
    if (parent_->is_red_ == true && value->is_red_ == true) LeftTurn(value);
  }

  void LeftTurn(StructGeneral<Key> *value) {
    StructGeneral<Key> *parent_ = value->parent_;
    StructGeneral<Key> *grandfather = parent_->parent_;
    if (grandfather == anchor_->right_) {
      anchor_->left_ = anchor_->right_ = parent_;
      parent_->parent_ = anchor_;
    }
    StructGeneral<Key> *great_grandfather = grandfather->parent_;
    grandfather->left_ = parent_->right_;
    if (parent_->right_ != nullptr) parent_->right_->parent_ = grandfather;
    parent_->right_ = grandfather;
    grandfather->parent_ = parent_;
    if (great_grandfather != nullptr) {
      parent_->parent_ = great_grandfather;
      if (great_grandfather->left_ == grandfather) {
        great_grandfather->left_ = parent_;
      } else {
        great_grandfather->right_ = parent_;
      }
    }
    great_grandfather->is_red_ = false;
    value->is_red_ = false;
    parent_->is_red_ = false;
    if (parent_ != anchor_->right_) parent_->is_red_ = true;
    Adjustment(parent_);
  }

  void RightTurn(StructGeneral<Key> *value) {
    StructGeneral<Key> *parent_ = value->parent_;
    if (parent_ == anchor_->right_) {
      anchor_->left_ = anchor_->right_ = value;
      value->parent_ = anchor_;
    }
    StructGeneral<Key> *grandfather = parent_->parent_;
    StructGeneral<Key> *swap = value->left_;
    if (value->left_ != nullptr) {
      swap->parent_ = parent_;
    }
    value->left_ = parent_;
    parent_->right_ = swap;
    parent_->parent_ = value;
    value->is_red_ = parent_->is_red_;
    if (grandfather != nullptr) {
      value->parent_ = grandfather;
      if (grandfather->left_ == parent_) {
        grandfather->left_ = value;
      } else {
        grandfather->right_ = value;
      }
    }
    if (value == anchor_->right_) value->is_red_ = false;
    parent_->is_red_ = true;
    Adjustment(parent_);
  }

  void SwapColors(StructGeneral<Key> *value) {
    StructGeneral<Key> *parent_ = value->parent_;
    parent_->right_->is_red_ = false;
    parent_->left_->is_red_ = false;
    if (parent_ != anchor_->right_) {
      parent_->is_red_ = true;
      Adjustment(parent_);
    }
  }

  void FreeSet(StructGeneral<Key> *root) noexcept {
    if (root->left_ != nullptr) FreeSet(root->left_);
    if (root->right_ != nullptr) FreeSet(root->right_);
    size_ -= root->count_;
    delete root;
  }
};

}  // namespace s21
#endif  // CONTAINERS_SRC_GENERAL_H_