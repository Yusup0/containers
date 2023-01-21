#ifndef CONTAINERS_SRC_GENERAL_H_
#define CONTAINERS_SRC_GENERAL_H_

namespace s21 {

template <class Struct>
Struct *ClosestRight(Struct *value) {
  Struct *result;
  if (value->right != nullptr) {
    value = value->right;
    while (value->left != nullptr) value = value->left;
    result = value;
  } else {
    result = value->parent;
    while (result->right == value) {
      value = result;
      result = result->parent;
    }
  }
  return result;
}

template <class Struct>
Struct *ClosestLeft(Struct *value) {
  Struct *result;
  if (value->left != nullptr) {
    value = value->left;
    while (value->right != nullptr) value = value->right;
    result = value;
  } else {
    result = value->parent;
    while (result->left == value) {
      value = result;
      result = result->parent;
    }
  }
  return result;
}

}  // namespace s21
#endif  // CONTAINERS_SRC_GENERAL_H_