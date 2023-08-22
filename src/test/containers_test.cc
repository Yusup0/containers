#include <gtest/gtest.h>

#include "../s21_containers.h"
#include "../s21_containersplus.h"

template <class Container_first, class Container_second>
int Comparison(Container_first first, Container_second second) {
  int res = 0;
  size_t size1 = first.size(), size2 = second.size();
  auto first_it = first.begin();
  auto second_it = second.begin();
  for (size_t i = 0; i < size1 && i < size2; i++, first_it++, second_it++) {
    if (*first_it != *second_it) {
      res = *first_it > *second_it ? 1 : -1;
      break;
    }
  }
  if (!res && size1 != size2) res = size1 > size2 ? 1 : -1;
  return res;
}

TEST(queue, list) {
  s21::queue<std::string> st1 = {"7", "123", "333"};
  s21::queue<std::string> st2;
  EXPECT_EQ("333", st1.back());
  st1.push("3312");
  EXPECT_EQ("3312", st1.back());
  st1.swap(st2);
  EXPECT_EQ("3312", st2.back());
  EXPECT_EQ(static_cast<size_t>(4), st2.size());

  s21::list<std::string> li = {"7"};
  s21::queue<std::string> st(li);
  EXPECT_EQ(false, st.empty());
  EXPECT_EQ(1, static_cast<int>(st.size()));
  st.pop();
  EXPECT_EQ(true, st.empty());
  EXPECT_EQ(0, static_cast<int>(st.size()));
  st.push("123");
  st.push("312");
  st.push("43");
  st.push("512");
  EXPECT_EQ("512", st.back());
  st.pop();
  EXPECT_EQ("512", st.back());
  EXPECT_EQ("312", st.front());
  EXPECT_EQ(false, st.empty());
  EXPECT_EQ(3, static_cast<int>(st.size()));
  st.emplace_back("3333");
  EXPECT_EQ("3333", st.back());
  EXPECT_EQ(4, static_cast<int>(st.size()));
}

TEST(queue, vector) {
  s21::queue<std::string, s21::vector<std::string>> st1 = {"7", "123", "333"};
  s21::queue<std::string, s21::vector<std::string>> st2;
  EXPECT_EQ("333", st1.back());
  st1.push("3312");
  EXPECT_EQ("3312", st1.back());
  st1.swap(st2);
  EXPECT_EQ("3312", st2.back());
  EXPECT_EQ(static_cast<size_t>(4), st2.size());

  const s21::queue<std::string, s21::vector<std::string>> st3 = {"7", "123",
                                                                 "333"};
  EXPECT_EQ("333", st3.back());
  EXPECT_EQ("7", st3.front());

  s21::vector<std::string> li = {"7"};
  s21::queue<std::string, s21::vector<std::string>> st(li);
  EXPECT_EQ(false, st.empty());
  EXPECT_EQ(1, static_cast<int>(st.size()));
  st.pop();
  EXPECT_EQ(true, st.empty());
  EXPECT_EQ(0, static_cast<int>(st.size()));
  st.push("123");
  st.push("312");
  st.push("43");
  st.push("512");
  EXPECT_EQ("512", st.back());
  st.pop();
  EXPECT_EQ("512", st.back());
  EXPECT_EQ("312", st.front());
  EXPECT_EQ(false, st.empty());
  EXPECT_EQ(3, static_cast<int>(st.size()));
  st.emplace_back("3333");
  EXPECT_EQ("3333", st.back());
  EXPECT_EQ(4, static_cast<int>(st.size()));
}

TEST(stack, list) {
  s21::stack<std::string> st1 = {"7", "123", "333"};
  s21::stack<std::string> st2;
  EXPECT_EQ("333", st1.top());
  st1.push("3312");
  EXPECT_EQ("3312", st1.top());
  st1.swap(st2);
  EXPECT_EQ("3312", st2.top());
  EXPECT_EQ(static_cast<size_t>(4), st2.size());

  s21::list<std::string> li = {"7"};
  s21::stack<std::string, s21::list<std::string>> st(li);
  EXPECT_EQ(false, st.empty());
  EXPECT_EQ(1, static_cast<int>(st.size()));
  st.pop();
  EXPECT_EQ(true, st.empty());
  EXPECT_EQ(0, static_cast<int>(st.size()));
  st.push("123");
  st.push("312");
  EXPECT_EQ("312", st.top());
  st.pop();
  EXPECT_EQ("123", st.top());
  EXPECT_EQ(false, st.empty());
  EXPECT_EQ(1, static_cast<int>(st.size()));
  st.emplace_front("3333");
  EXPECT_EQ(2, static_cast<int>(st.size()));
  EXPECT_EQ("123", st.top());
  st.pop();
  EXPECT_EQ(1, static_cast<int>(st.size()));
  EXPECT_EQ("3333", st.top());
}

TEST(stack, vector) {
  s21::stack<std::string, s21::vector<std::string>> st1 = {"7", "123", "333"};
  s21::stack<std::string, s21::vector<std::string>> st2;
  EXPECT_EQ("333", st1.top());
  st1.push("3312");
  EXPECT_EQ("3312", st1.top());
  st1.swap(st2);
  EXPECT_EQ("3312", st2.top());
  EXPECT_EQ(static_cast<size_t>(4), st2.size());

  const s21::stack<std::string, s21::vector<std::string>> st3 = {"7", "123",
                                                                 "333"};
  EXPECT_EQ("333", st3.top());

  s21::vector<std::string> ve = {"7"};
  s21::stack<std::string, s21::vector<std::string>> st(ve);
  EXPECT_EQ(false, st.empty());
  EXPECT_EQ(1, static_cast<int>(st.size()));
  st.pop();
  EXPECT_EQ(true, st.empty());
  EXPECT_EQ(0, static_cast<int>(st.size()));
  st.push("123");
  st.push("312");
  EXPECT_EQ("312", st.top());
  st.pop();
  EXPECT_EQ("123", st.top());
  EXPECT_EQ(false, st.empty());
  EXPECT_EQ(1, static_cast<int>(st.size()));
  st.emplace_front("3333");
  EXPECT_EQ(2, static_cast<int>(st.size()));
  EXPECT_EQ("123", st.top());
  st.pop();
  EXPECT_EQ(1, static_cast<int>(st.size()));
  EXPECT_EQ("3333", st.top());
}

TEST(map, test_iq) {
  s21::map<int, std::string> a1 = {{1, "1"}, {2, "2"}, {3, "3"}};
  s21::map<int, std::string> a2 = {{1, "12"}, {2, "22"}, {3, "32"}};
  a1 = a2;
  s21::map<int, std::string>::iterator it = a1.begin();
  s21::map<int, std::string>::iterator it1 = a2.begin();
  EXPECT_EQ("12", (*it).second);
  it++;
  EXPECT_EQ("22", (*it).second);
  it++;
  EXPECT_EQ("32", (*it).second);
  EXPECT_EQ("12", (*it1).second);
  it1++;
  EXPECT_EQ("22", (*it1).second);
  it1++;
  EXPECT_EQ("32", (*it1).second);
}

TEST(map, iterator) {
  s21::map<int, std::string> a1 = {{1, "1"}, {2, "2"}, {3, "3"}};
  s21::map<int, std::string>::iterator it = a1.begin();
  s21::map<int, std::string>::iterator it1 = a1.begin();
  EXPECT_EQ("1", (*it++).second);
  EXPECT_EQ("3", (*++it).second);
  EXPECT_EQ("2", (*--it).second);
  EXPECT_EQ("2", (*it--).second);
  EXPECT_EQ("1", (*it++).second);
  EXPECT_EQ("2", (*it).second);
  EXPECT_EQ(true, it != it1);
  EXPECT_EQ(true, --it == it1);
}

TEST(map, erase) {
  s21::map<int, std::string> a1 = {
      {1, "1"},   {2, "2"},   {3, "3"},   {4, "4"},   {5, "5"},   {6, "6"},
      {7, "7"},   {8, "8"},   {9, "9"},   {10, "10"}, {11, "11"}, {12, "12"},
      {13, "13"}, {14, "14"}, {15, "15"}, {16, "16"}};

  std::map<int, std::string> a2 = {
      {1, "1"},   {2, "2"},   {3, "3"},   {4, "4"},   {5, "5"},   {6, "6"},
      {7, "7"},   {8, "8"},   {9, "9"},   {10, "10"}, {11, "11"}, {12, "12"},
      {13, "13"}, {14, "14"}, {15, "15"}, {16, "16"}};
  a1.erase(a1.find(1));
  a2.erase(a2.find(1));
  EXPECT_EQ(0, Comparison(a1, a2));
  a1.erase(a1.find(12));
  a2.erase(a2.find(12));
  EXPECT_EQ(0, Comparison(a1, a2));
  a1.erase(a1.find(15));
  a2.erase(a2.find(15));
  EXPECT_EQ(0, Comparison(a1, a2));
  a1.erase(a1.find(7));
  a2.erase(a2.find(7));
  EXPECT_EQ(0, Comparison(a1, a2));
  a1.erase(a1.find(5));
  a2.erase(a2.find(5));
  EXPECT_EQ(0, Comparison(a1, a2));
  a1.erase(a1.find(6));
  a2.erase(a2.find(6));
  EXPECT_EQ(0, Comparison(a1, a2));
  a1.erase(a1.find(3));
  a2.erase(a2.find(3));
  EXPECT_EQ(0, Comparison(a1, a2));
  a1.erase(a1.find(10));
  a2.erase(a2.find(10));
  EXPECT_EQ(0, Comparison(a1, a2));
  a1.erase(a1.find(11));
  a2.erase(a2.find(11));
  EXPECT_EQ(0, Comparison(a1, a2));
  a1.erase(a1.find(2));
  a2.erase(a2.find(2));
  EXPECT_EQ(0, Comparison(a1, a2));
  a1.erase(a1.find(4));
  a2.erase(a2.find(4));
  EXPECT_EQ(0, Comparison(a1, a2));
  a1.erase(a1.find(9));
  a2.erase(a2.find(9));
  EXPECT_EQ(0, Comparison(a1, a2));
  a1.erase(a1.find(8));
  a2.erase(a2.find(8));
  EXPECT_EQ(0, Comparison(a1, a2));
  a1.erase(a1.find(14));
  a2.erase(a2.find(14));
  EXPECT_EQ(0, Comparison(a1, a2));
  a1.erase(a1.find(13));
  a2.erase(a2.find(13));
  EXPECT_EQ(0, Comparison(a1, a2));
  a1.erase(a1.find(16));
  a2.erase(a2.find(16));
  EXPECT_EQ(0, Comparison(a1, a2));
}

TEST(map, clear) {
  s21::map<int, std::string> a1 = {{1, "1"}, {2, "2"}, {3, "3"}};
  a1.clear();
  EXPECT_EQ(static_cast<int>(a1.size()), 0);
}

TEST(map, insert) {
  s21::map<int, int> a1 = {{1, 1}, {2, 2}, {3, 3}};
  s21::map<int, int>::iterator it1 = a1.begin();
  std::pair<s21::map<int, int>::iterator, bool> pa = a1.insert(62, 33);
  EXPECT_EQ(33, (*pa.first).second);
  pa = a1.insert({56, 22});
  EXPECT_EQ(22, (*pa.first).second);
  it1 = a1.begin();
  EXPECT_EQ(1, (*it1++).second);
  EXPECT_EQ(2, (*it1++).second);
  EXPECT_EQ(3, (*it1++).second);
  EXPECT_EQ(22, (*it1++).second);
  EXPECT_EQ(33, (*it1++).second);
  pa = a1.insert({76, 88});
  EXPECT_EQ(88, (*pa.first).second);
  EXPECT_EQ(6, static_cast<int>(a1.size()));

  s21::map<int, int> a3 = {{1, 1}, {2, 2}, {3, 3}};
  auto pa1 = a3.insert_or_assign(4, 34);
  EXPECT_EQ(4, (*pa1.first).first);
  EXPECT_EQ(34, (*pa1.first).second);
  pa1 = a3.insert_or_assign(4, 355);
  EXPECT_EQ(4, (*pa1.first).first);
  EXPECT_EQ(355, (*pa1.first).second);
}

TEST(map, cbegin) {
  const s21::map<int, int> a1 = {{12, 1}, {223, 2}, {3123, 3}};
  s21::map<int, int>::const_iterator it = a1.cbegin();
  EXPECT_EQ(1, (*it).second);
}

TEST(map, cend) {
  s21::map<int, std::string> a1 = {{1, "1"}, {2, "2"}, {3, "3"}};
  s21::map<int, std::string>::const_iterator it = a1.cend();
  EXPECT_EQ("3", (*--it).second);
}

TEST(map, begin_const) {
  const s21::map<int, int> a1 = {{12, 1}, {223, 2}, {3123, 3}};
  s21::map<int, int>::const_iterator it = a1.begin();
  EXPECT_EQ(1, (*it).second);
}

TEST(map, end_const) {
  const s21::map<int, std::string> a1 = {{1, "1"}, {2, "2"}, {3, "3"}};
  s21::map<int, std::string>::const_iterator it = a1.end();
  EXPECT_EQ("3", (*--it).second);
}

TEST(map, move) {
  s21::map<int, int> a1 = {{12, 1}, {223, 2}, {3123, 3}};
  s21::map<int, int> a2(std::move(a1));
  s21::map<int, int>::iterator it = a2.begin();
  EXPECT_EQ(1, (*it).second);

  s21::map<int, int> a3 = {{12, 8}, {223, 9}, {331, 10}};
  a2 = std::move(a3);
  it = a2.begin();
  EXPECT_EQ(8, (*it).second);
}

TEST(map, begin) {
  s21::map<int, int> a1 = {{12, 1}, {223, 2}, {3123, 3}};
  s21::map<int, int>::iterator it = a1.begin();
  EXPECT_EQ(1, (*it).second);
}

TEST(map, end) {
  s21::map<int, std::string> a1 = {{1, "1"}, {2, "2"}, {3, "3"}};
  s21::map<int, std::string>::iterator it = a1.end();
  EXPECT_EQ("3", (*--it).second);
}

TEST(map, size) {
  s21::map<int, int> a1 = {{12, 1}, {223, 2}, {3123, 3}};
  EXPECT_EQ(static_cast<int>(a1.size()), 3);
}

TEST(map, empty) {
  s21::map<int, int> a1 = {{12, 1}, {223, 2}, {3123, 3}};
  EXPECT_EQ(a1.empty(), false);
  a1.clear();
  EXPECT_EQ(a1.empty(), true);
}

TEST(map, swap) {
  s21::map<int, int> a1 = {{1, 1}, {2, 2}, {3, 3}};
  s21::map<int, int> a2 = {{4, 4}, {5, 5}, {6, 6}, {466, 55}};
  a1.swap(a2);
  s21::map<int, int>::iterator it1 = a1.begin();
  s21::map<int, int>::iterator it2 = a2.begin();
  EXPECT_EQ(4, (*it1++).second);
  EXPECT_EQ((*it1++).second, 5);
  EXPECT_EQ((*it1++).second, 6);
  EXPECT_EQ((*it1++).second, 55);
  EXPECT_EQ((*it2++).second, 1);
  EXPECT_EQ((*it2++).second, 2);
  EXPECT_EQ((*it2++).second, 3);
  EXPECT_EQ(static_cast<int>(a2.size()), 3);
  EXPECT_EQ(static_cast<int>(a1.size()), 4);
}

TEST(map, map) {
  s21::map<int, std::string> a1({{1, "1"}, {2, "2"}, {3, "3"}});
  s21::map<int, std::string>::iterator it1 = a1.begin();
  EXPECT_EQ("1", (*it1++).second);
  EXPECT_EQ("2", (*it1++).second);
  EXPECT_EQ("3", (*it1).second);
}

TEST(map, map3) {
  s21::map<int, std::string> a({{1, "c"}, {2, "cc"}, {3, "c"}});
  s21::map<int, std::string> a1(a);
  s21::map<int, std::string>::iterator it1 = a1.begin();

  EXPECT_EQ(3, static_cast<int>(a1.size()));
  EXPECT_EQ("c", (*it1++).second);
  EXPECT_EQ("cc", (*it1++).second);
  EXPECT_EQ("c", (*it1).second);
}

TEST(map, map4) {
  s21::map<int, std::string> a({{1, "c"}, {2, "cc"}, {3, "c"}});
  s21::map<int, std::string> a1(a.begin(), a.end());
  s21::map<int, std::string>::iterator it1 = a1.begin();
  EXPECT_EQ(3, static_cast<int>(a1.size()));
  EXPECT_EQ("c", (*it1++).second);
  EXPECT_EQ("cc", (*it1++).second);
  EXPECT_EQ("c", (*it1).second);
}

TEST(map, operator) {
  s21::map<int, std::string> a = {{1, "1"}, {2, "2"}, {3, "3"}};
  s21::map<int, std::string> a1 = {{1, "1"}, {2, "2"}, {3, "3"}};
  EXPECT_EQ(true, a == a1);
  EXPECT_EQ(false, a != a1);
  EXPECT_EQ(false, a < a1);
  EXPECT_EQ(true, a <= a1);
  EXPECT_EQ(true, a >= a1);
  EXPECT_EQ(false, a > a1);
}

TEST(map, operator1) {
  s21::map<int, std::string> a = {{1, "1"}, {2, "2"}, {3, "3"}};
  s21::map<int, std::string> a1 = {{1, "1"}, {2, "2"}, {3, "3"}, {4, "4"}};
  EXPECT_EQ(false, a == a1);
  EXPECT_EQ(true, a != a1);
  EXPECT_EQ(true, a < a1);
  EXPECT_EQ(true, a <= a1);
  EXPECT_EQ(false, a >= a1);
  EXPECT_EQ(false, a > a1);
}

TEST(map, operator2) {
  s21::map<int, std::string> a = {{1, "1"}, {4, "4"}, {3, "3"}};
  s21::map<int, std::string> a1 = {{1, "1"}, {2, "2"}, {3, "3"}, {4, "4"}};
  EXPECT_EQ(false, a == a1);
  EXPECT_EQ(true, a != a1);
  EXPECT_EQ(false, a < a1);
  EXPECT_EQ(false, a <= a1);
  EXPECT_EQ(true, a >= a1);
  EXPECT_EQ(true, a > a1);
}

TEST(map, operator3) {
  s21::map<int, std::string> a = {{1, "1"}, {4, "4"}, {3, "3"}};
  s21::map<int, std::string> a1 = {{1, "1"}, {2, "2"}, {3, "3"}, {4, "4"}};
  a = a1;
  EXPECT_EQ(true, a == a1);
  EXPECT_EQ(false, a != a1);
  EXPECT_EQ(false, a < a1);
  EXPECT_EQ(true, a <= a1);
  EXPECT_EQ(true, a >= a1);
  EXPECT_EQ(false, a > a1);
}

TEST(map, operator4) {
  s21::map<int, std::string> a = {{1, "1"}, {4, "4"}, {3, "3"}};
  EXPECT_EQ("1", a[1]);
  EXPECT_EQ("12", a[1] = "12");
  EXPECT_EQ("175", a[1] = "175");
  EXPECT_EQ(static_cast<size_t>(3), a.size());
  EXPECT_EQ("", a[11]);
  EXPECT_EQ(static_cast<size_t>(4), a.size());
  EXPECT_EQ("175", a.at(1));
}

TEST(map, merge) {
  s21::map<int, std::string> a = {{1, "1"}, {4, "4"}, {3, "3"}};
  s21::map<int, std::string> a1 = {{1, "1"}, {4, "4"}, {3, "3"}, {44, "33"}};
  s21::map<int, std::string> a2 = {{1, "1"}, {4, "4"}, {3, "3"}, {44, "33"}};
  a.merge(a1);
  EXPECT_EQ(true, a == a2);
  EXPECT_EQ(static_cast<size_t>(4), a.size());
}

TEST(map, emplace) {
  typedef std::pair<const int, std::string> value_type;
  s21::map<int, std::string> a = {{1, "1"}};
  s21::map<int, std::string> a1 = {{1, "1"}, {2, "2"}, {3, "3"}, {4, "4"}};
  a.emplace(value_type(4, "4"), value_type(2, "2"), value_type(3, "3"));
  EXPECT_EQ(true, a == a1);
  EXPECT_EQ(false, a != a1);
  EXPECT_EQ(false, a < a1);
  EXPECT_EQ(true, a <= a1);
  EXPECT_EQ(true, a >= a1);
  EXPECT_EQ(false, a > a1);

  s21::map<int, std::string> a2;
  s21::map<int, std::string> a3 = {{2, "2"}, {3, "3"}, {4, "4"}};
  s21::map<int, std::string> a4 = {{2, "2"},   {3, "3"},   {4, "4"},
                                   {12, "12"}, {13, "13"}, {1, "1"}};
  a2.emplace(value_type(4, "4"), value_type(2, "2"), value_type(3, "3"));
  EXPECT_EQ(true, a3 == a2);
  a2.emplace(value_type(4, "4"), value_type(2, "2"), value_type(3, "3"));
  EXPECT_EQ(true, a3 == a2);
  a2.emplace(value_type(1, "1"), value_type(12, "12"), value_type(13, "13"));
  EXPECT_EQ(true, a4 == a2);
  a2.clear();
  a2.emplace(value_type(4, "4"), value_type(2, "2"), value_type(3, "3"));
  EXPECT_EQ(true, a3 == a2);
}

TEST(map, find) {
  s21::map<int, int> a1 = {{1, 1}, {2, 2}, {4, 4}, {5, 5}, {6, 6}, {55, 55}};
  s21::map<int, int>::iterator it1 = a1.find(6);
  EXPECT_EQ(6, (*it1).second);
  it1 = a1.find(4);
  EXPECT_EQ(4, (*it1).second);
}

TEST(map, contains) {
  s21::map<int, int> a1 = {{1, 1}, {2, 2}, {4, 4}, {5, 5}, {6, 6}, {55, 55}};
  EXPECT_EQ(true, a1.contains(4));
  EXPECT_EQ(false, a1.contains(42));
}

TEST(map, find_const) {
  const s21::map<int, int> a1 = {{1, 1}, {2, 2}, {4, 4},
                                 {5, 5}, {6, 6}, {55, 55}};
  s21::map<int, int>::const_iterator it1 = a1.find(6);
  EXPECT_EQ(6, (*it1).second);
  it1 = a1.find(4);
  EXPECT_EQ(4, (*it1).second);
}

TEST(map, count) {
  s21::map<int, int> a1 = {{1, 1}, {2, 2}, {4, 4}, {5, 5}, {6, 6}, {55, 55}};
  EXPECT_EQ(1, static_cast<int>(static_cast<int>(a1.count(6))));
  EXPECT_EQ(1, static_cast<int>(a1.count(4)));
  EXPECT_EQ(0, static_cast<int>(a1.count(3)));
}

TEST(map, test_greater) {
  s21::map<int, std::string, std::greater<int>> a1 = {
      {1, "1"}, {2, "2"}, {3, "3"}};
  s21::map<int, std::string, std::greater<int>> a = {
      {12, "12"}, {22, "22"}, {32, "32"}};
  a1 = a;

  EXPECT_EQ(true, a == a1);
  EXPECT_EQ(false, a != a1);
  EXPECT_EQ(false, a < a1);
  EXPECT_EQ(true, a <= a1);
  EXPECT_EQ(true, a >= a1);
  EXPECT_EQ(false, a > a1);
}

TEST(map, iterator_greater) {
  s21::map<int, int, std::greater<int>> a1 = {{3, 3}, {2, 2}, {1, 1}};
  s21::map<int, int, std::greater<int>>::iterator it = a1.begin();
  s21::map<int, int, std::greater<int>>::iterator it1 = a1.begin();
  EXPECT_EQ(3, (*it++).second);
  EXPECT_EQ(1, (*++it).second);
  EXPECT_EQ(2, (*--it).second);
  EXPECT_EQ(2, (*it--).second);
  EXPECT_EQ(3, (*it++).second);
  EXPECT_EQ(2, (*it).second);
  EXPECT_EQ(true, it != it1);
  EXPECT_EQ(true, --it == it1);
}

//
TEST(map, erase_greater) {
  s21::map<int, int, std::greater<int>> a1 = {
      {3123, 3123}, {12, 12},   {23123, 23123}, {312, 312}, {31, 31},
      {2313, 2313}, {213, 213}, {1, 1},         {64, 64},   {456, 456},
      {45, 45},     {37, 37},   {8, 8}};
  std::map<int, int, std::greater<int>> a2 = {
      {3123, 3123}, {12, 12},   {23123, 23123}, {312, 312}, {31, 31},
      {2313, 2313}, {213, 213}, {1, 1},         {64, 64},   {456, 456},
      {45, 45},     {37, 37},   {8, 8}};
  a1.erase(a1.find(213));
  a2.erase(a2.find(213));
  EXPECT_EQ(0, Comparison(a1, a2));
  a1.erase(a1.find(8));
  a2.erase(a2.find(8));
  EXPECT_EQ(0, Comparison(a1, a2));
  a1.erase(a1.find(64));
  a2.erase(a2.find(64));
  EXPECT_EQ(0, Comparison(a1, a2));
  a1.erase(a1.find(31));
  a2.erase(a2.find(31));
  EXPECT_EQ(0, Comparison(a1, a2));
  a1.erase(a1.find(12));
  a2.erase(a2.find(12));
  EXPECT_EQ(0, Comparison(a1, a2));
  a1.erase(a1.find(45));
  a2.erase(a2.find(45));
  EXPECT_EQ(0, Comparison(a1, a2));
  a1.erase(a1.find(37));
  a2.erase(a2.find(37));
  EXPECT_EQ(0, Comparison(a1, a2));
  a1.erase(a1.find(2313));
  a2.erase(a2.find(2313));
  EXPECT_EQ(0, Comparison(a1, a2));
}

TEST(map, clear_greater) {
  s21::map<int, int, std::greater<int>> a1 = {{1, 1}, {2, 2}, {3, 3}};
  a1.clear();
  EXPECT_EQ(static_cast<int>(a1.size()), 0);
}

TEST(map, at) {
  s21::map<int, int> a1 = {{1, 15}, {2, 25}, {3, 35}};
  EXPECT_EQ(15, a1.at(1));
  EXPECT_EQ(35, a1.at(3));
  a1.at(3) = 99;
  EXPECT_EQ(99, a1.at(3));
  EXPECT_THROW(a1.at(55), std::out_of_range);
}

TEST(map, at_const) {
  const s21::map<int, int> a1 = {{1, 15}, {2, 25}, {3, 35}};
  EXPECT_EQ(15, a1.at(1));
  EXPECT_EQ(35, a1.at(3));
  EXPECT_EQ(25, a1.at(2));
}

TEST(map, insert_greater) {
  s21::map<int, int, std::greater<int>> a1 = {{1, 1}, {2, 2}, {3, 3}};
  s21::map<int, int, std::greater<int>>::iterator it1 = a1.begin();
  std::pair<s21::map<int, int, std::greater<int>>::iterator, bool> pa =
      a1.insert({33, 33});
  EXPECT_EQ(33, (*pa.first).second);
  pa = a1.insert({22, 22});
  EXPECT_EQ(22, (*pa.first).second);
  it1 = a1.begin();
  EXPECT_EQ(33, (*it1++).second);
  EXPECT_EQ(22, (*it1++).second);
  EXPECT_EQ(3, (*it1++).second);
  EXPECT_EQ(2, (*it1++).second);
  EXPECT_EQ(1, (*it1++).second);
  pa = a1.insert({88, 88});
  EXPECT_EQ(88, (*pa.first).second);
  EXPECT_EQ(6, static_cast<int>(a1.size()));
}

TEST(map, begin_greater) {
  s21::map<int, int, std::greater<int>> a1 = {{1, 1}, {2, 2}, {3, 3}};
  s21::map<int, int, std::greater<int>>::iterator it = a1.begin();
  EXPECT_EQ(3, (*it).second);
}

TEST(map, end_greater) {
  s21::map<int, int, std::greater<int>> a1 = {{1, 1}, {2, 2}, {3, 3}};
  s21::map<int, int, std::greater<int>>::iterator it = a1.end();
  EXPECT_EQ(1, (*--it).second);
}

TEST(map, size_greater) {
  s21::map<int, int, std::greater<int>> a1 = {{1, 1}, {2, 2}, {3, 3}};
  EXPECT_EQ(static_cast<int>(a1.size()), 3);
}

TEST(map, empty_greater) {
  s21::map<int, int, std::greater<int>> a1 = {{1, 1}, {2, 2}, {3, 3}};
  EXPECT_EQ(a1.empty(), false);
  a1.clear();
  EXPECT_EQ(a1.empty(), true);
}

TEST(map, swap_greater) {
  s21::map<int, int, std::greater<int>> a1 = {{1, 1}, {2, 2}, {3, 3}};
  s21::map<int, int, std::greater<int>> a2 = {{4, 4}, {5, 5}, {6, 6}, {55, 55}};
  a1.swap(a2);
  s21::map<int, int, std::greater<int>>::iterator it1 = a1.begin();
  s21::map<int, int, std::greater<int>>::iterator it2 = a2.begin();
  EXPECT_EQ(55, (*it1++).second);
  EXPECT_EQ((*it1++).second, 6);
  EXPECT_EQ((*it1++).second, 5);
  EXPECT_EQ((*it1++).second, 4);
  EXPECT_EQ((*it2++).second, 3);
  EXPECT_EQ((*it2++).second, 2);
  EXPECT_EQ((*it2++).second, 1);
  EXPECT_EQ(static_cast<int>(a2.size()), 3);
  EXPECT_EQ(static_cast<int>(a1.size()), 4);
}

TEST(map, map_greater) {
  s21::map<int, int, std::greater<int>> a1({{1, 1}, {2, 2}, {3, 3}});
  s21::map<int, int, std::greater<int>>::iterator it1 = a1.begin();
  EXPECT_EQ(3, (*it1++).second);
  EXPECT_EQ(2, (*it1++).second);
  EXPECT_EQ(1, (*it1).second);
}

TEST(map, map3_greater) {
  s21::map<int, int, std::greater<int>> a({{1, 1}, {2, 2}, {3, 3}});
  s21::map<int, int, std::greater<int>> a1(a);
  s21::map<int, int, std::greater<int>>::iterator it1 = a1.begin();

  EXPECT_EQ(3, static_cast<int>(a1.size()));
  EXPECT_EQ(3, (*it1++).second);
  EXPECT_EQ(2, (*it1++).second);
  EXPECT_EQ(1, (*it1).second);
}

TEST(map, map4_greater) {
  s21::map<int, int, std::greater<int>> a({{1, 1}, {2, 2}, {3, 3}});
  s21::map<int, int, std::greater<int>> a1(a.begin(), a.end());
  s21::map<int, int, std::greater<int>>::iterator it1 = a1.begin();
  EXPECT_EQ(3, static_cast<int>(a1.size()));
  EXPECT_EQ(3, (*it1).second);
  ++it1;
  EXPECT_EQ(2, (*it1).second);
  ++it1;
  EXPECT_EQ(1, (*it1).second);
}

TEST(map, operator_greater) {
  s21::map<int, int, std::greater<int>> a = {{1, 1}, {2, 2}, {3, 3}};
  s21::map<int, int, std::greater<int>> a1 = {{1, 1}, {2, 2}, {3, 3}};
  EXPECT_EQ(true, a == a1);
  EXPECT_EQ(false, a != a1);
  EXPECT_EQ(false, a < a1);
  EXPECT_EQ(true, a <= a1);
  EXPECT_EQ(true, a >= a1);
  EXPECT_EQ(false, a > a1);
}

TEST(map, operator1_greater) {
  s21::map<int, int, std::greater<int>> a = {{1, 1}, {2, 2}, {3, 3}};
  s21::map<int, int, std::greater<int>> a1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}};
  EXPECT_EQ(false, a == a1);
  EXPECT_EQ(true, a != a1);
  EXPECT_EQ(true, a < a1);
  EXPECT_EQ(true, a <= a1);
  EXPECT_EQ(false, a >= a1);
  EXPECT_EQ(false, a > a1);
}

TEST(map, operator2_greater) {
  s21::map<int, int, std::greater<int>> a = {{1, 1}, {5, 5}, {3, 3}};
  s21::map<int, int, std::greater<int>> a1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}};
  EXPECT_EQ(false, a == a1);
  EXPECT_EQ(true, a != a1);
  EXPECT_EQ(false, a < a1);
  EXPECT_EQ(false, a <= a1);
  EXPECT_EQ(true, a >= a1);
  EXPECT_EQ(true, a > a1);
}

TEST(map, operator3_greater) {
  s21::map<int, int, std::greater<int>> a = {{1, 1}, {4, 4}, {3, 3}};
  s21::map<int, int, std::greater<int>> a1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}};
  a = a1;
  EXPECT_EQ(true, a == a1);
  EXPECT_EQ(false, a != a1);
  EXPECT_EQ(false, a < a1);
  EXPECT_EQ(true, a <= a1);
  EXPECT_EQ(true, a >= a1);
  EXPECT_EQ(false, a > a1);
}

TEST(map, emplace_greater) {
  typedef std::pair<const int, int> value_type;
  s21::map<int, int, std::greater<int>> a = {{1, 1}};
  s21::map<int, int, std::greater<int>> a1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}};
  std::vector<std::pair<s21::map<int, int, std::greater<int>>::iterator, bool>>
      result = a.emplace(value_type(4, 4), value_type(4, 4), value_type(2, 2),
                         value_type(3, 3));
  EXPECT_EQ(true, a == a1);
  EXPECT_EQ(false, a != a1);
  EXPECT_EQ(false, a < a1);
  EXPECT_EQ(true, a <= a1);
  EXPECT_EQ(true, a >= a1);
  EXPECT_EQ(false, a > a1);
  EXPECT_EQ(4, (*result[0].first).second);
  EXPECT_EQ(true, result[0].second);
  EXPECT_EQ(false, result[1].second);
}

TEST(map, find_greater) {
  s21::map<int, int, std::greater<int>> a1 = {{1, 1}, {2, 2}, {4, 4},
                                              {5, 5}, {6, 6}, {55, 55}};
  s21::map<int, int, std::greater<int>>::iterator it1 = a1.find(6);
  EXPECT_EQ(6, (*it1).second);
  it1 = a1.find(4);
  EXPECT_EQ(4, (*it1).second);
}

TEST(map, count_greater) {
  s21::map<int, int, std::greater<int>> a1 = {{1, 1}, {2, 2}, {4, 4},
                                              {5, 5}, {6, 6}, {55, 55}};
  EXPECT_EQ(1, static_cast<int>(static_cast<int>(a1.count(6))));
  EXPECT_EQ(1, static_cast<int>(a1.count(4)));
  EXPECT_EQ(0, static_cast<int>(a1.count(3)));
}

TEST(set, test_iq) {
  s21::set<std::string> a1 = {"1", "2", "3"};
  s21::set<std::string> a2 = {"12", "22", "32"};
  a1 = a2;
  s21::set<std::string>::iterator it = a1.begin();
  s21::set<std::string>::iterator it1 = a2.begin();
  EXPECT_EQ("12", *it++);
  EXPECT_EQ("22", *it++);
  EXPECT_EQ("32", *it);
  EXPECT_EQ("12", *it1++);
  EXPECT_EQ("22", *it1++);
  EXPECT_EQ("32", *it1);
}

TEST(set, iterator) {
  s21::set<std::string> a1 = {"1", "2", "3"};
  s21::set<std::string>::iterator it = a1.begin();
  s21::set<std::string>::iterator it1 = a1.begin();
  EXPECT_EQ("1", *it++);
  EXPECT_EQ("3", *++it);
  EXPECT_EQ("2", *--it);
  EXPECT_EQ("2", *it--);
  EXPECT_EQ("1", *it++);
  EXPECT_EQ("2", *it);
  EXPECT_EQ(true, it != it1);
  EXPECT_EQ(true, --it == it1);
}

TEST(set, const_iterator) {
  s21::set<std::string> a1 = {"1", "2", "3"};
  s21::set<std::string>::const_iterator it = a1.cbegin();
  s21::set<std::string>::const_iterator it1 = a1.cbegin();
  EXPECT_EQ("1", *it++);
  EXPECT_EQ("3", *++it);
  EXPECT_EQ("2", *--it);
  EXPECT_EQ("2", *it--);
  EXPECT_EQ("1", *it++);
  EXPECT_EQ("2", *it);
  EXPECT_EQ(true, it != it1);
  EXPECT_EQ(true, --it == it1);
}

TEST(set, erase) {
  s21::set<std::string> a1 = {"1", "2", "2",  "3",     "3",       "4", "4",
                              "1", "4", "22", "dcasd", "1sd21es", "1e"};
  a1.erase(a1.find("1"));
  a1.erase(a1.find("3"));
  a1.erase(a1.find("4"));
  a1.erase(a1.find("1e"));

  std::set<std::string> a2 = {"1", "2", "2",  "3",     "3",       "4", "4",
                              "1", "4", "22", "dcasd", "1sd21es", "1e"};
  a2.erase(a2.find("1"));
  a2.erase(a2.find("3"));
  a2.erase(a2.find("4"));
  a2.erase(a2.find("1e"));

  EXPECT_EQ(0, Comparison(a1, a2));
}

TEST(set, clear) {
  s21::set<std::string> a1 = {"1", "2", "3"};
  a1.clear();
  EXPECT_EQ(static_cast<int>(a1.size()), 0);
}

TEST(set, insert) {
  s21::set<int> a1 = {1, 2, 3};
  s21::set<int>::iterator it1 = a1.begin();
  std::pair<s21::set<int>::iterator, bool> pa = a1.insert(33);
  EXPECT_EQ(33, *pa.first);
  pa = a1.insert(22);
  EXPECT_EQ(22, *pa.first);
  it1 = a1.begin();
  EXPECT_EQ(1, *it1++);
  EXPECT_EQ(2, *it1++);
  EXPECT_EQ(3, *it1++);
  EXPECT_EQ(22, *it1++);
  EXPECT_EQ(33, *it1++);
  pa = a1.insert(88);
  EXPECT_EQ(88, *pa.first);
  EXPECT_EQ(6, static_cast<int>(a1.size()));
}

TEST(set, begin) {
  s21::set<int> a1 = {1, 2, 3};
  s21::set<int>::iterator it = a1.begin();
  EXPECT_EQ(1, *it);
}

TEST(set, end) {
  s21::set<std::string> a1 = {"1", "2", "3"};
  s21::set<std::string>::iterator it = a1.end();
  EXPECT_EQ("3", *--it);
}

TEST(set, size) {
  s21::set<int> a1 = {1, 2, 3};
  EXPECT_EQ(static_cast<int>(a1.size()), 3);
}

TEST(set, empty) {
  s21::set<int> a1 = {1, 2, 3};
  EXPECT_EQ(a1.empty(), false);
  a1.clear();
  EXPECT_EQ(a1.empty(), true);
}

TEST(set, swap) {
  s21::set<int> a1 = {1, 2, 3};
  s21::set<int> a2 = {4, 5, 6, 55};
  a1.swap(a2);
  s21::set<int>::iterator it1 = a1.begin();
  s21::set<int>::iterator it2 = a2.begin();
  EXPECT_EQ(4, *it1++);
  EXPECT_EQ(*it1++, 5);
  EXPECT_EQ(*it1++, 6);
  EXPECT_EQ(*it1++, 55);
  EXPECT_EQ(*it2++, 1);
  EXPECT_EQ(*it2++, 2);
  EXPECT_EQ(*it2++, 3);
  EXPECT_EQ(static_cast<int>(a2.size()), 3);
  EXPECT_EQ(static_cast<int>(a1.size()), 4);
}

TEST(set, set) {
  s21::set<std::string> a1({"1", "2", "3"});
  s21::set<std::string>::iterator it1 = a1.begin();
  EXPECT_EQ("1", *it1++);
  EXPECT_EQ("2", *it1++);
  EXPECT_EQ("3", *it1);
}

TEST(set, set3) {
  s21::set<std::string> a({"c", "cc", "ccc"});
  s21::set<std::string> a1(a);
  s21::set<std::string>::iterator it1 = a1.begin();

  EXPECT_EQ(3, static_cast<int>(a1.size()));
  EXPECT_EQ("c", *it1++);
  EXPECT_EQ("cc", *it1++);
  EXPECT_EQ("ccc", *it1);
}

TEST(set, set4) {
  s21::set<std::string> a({"c", "cc", "ccc"});
  s21::set<std::string> a1(a.begin(), a.end());
  s21::set<std::string>::iterator it1 = a1.begin();
  EXPECT_EQ(3, static_cast<int>(a1.size()));
  EXPECT_EQ("c", *it1++);
  EXPECT_EQ("cc", *it1++);
  EXPECT_EQ("ccc", *it1);
}

TEST(set, operator) {
  s21::set<std::string> a = {"1", "2", "3"};
  s21::set<std::string> a1 = {"1", "2", "3"};
  EXPECT_EQ(true, a == a1);
  EXPECT_EQ(false, a != a1);
  EXPECT_EQ(false, a < a1);
  EXPECT_EQ(true, a <= a1);
  EXPECT_EQ(true, a >= a1);
  EXPECT_EQ(false, a > a1);
}

TEST(set, operator1) {
  s21::set<std::string> a = {"1", "2", "3"};
  s21::set<std::string> a1 = {"1", "2", "3", "4"};
  EXPECT_EQ(false, a == a1);
  EXPECT_EQ(true, a != a1);
  EXPECT_EQ(true, a < a1);
  EXPECT_EQ(true, a <= a1);
  EXPECT_EQ(false, a >= a1);
  EXPECT_EQ(false, a > a1);
}

TEST(set, operator2) {
  s21::set<std::string> a = {"1", "4", "3"};
  s21::set<std::string> a1 = {"1", "2", "3", "4"};
  EXPECT_EQ(false, a == a1);
  EXPECT_EQ(true, a != a1);
  EXPECT_EQ(false, a < a1);
  EXPECT_EQ(false, a <= a1);
  EXPECT_EQ(true, a >= a1);
  EXPECT_EQ(true, a > a1);
}

TEST(set, operator3) {
  s21::set<std::string> a = {"1", "4", "3"};
  s21::set<std::string> a1 = {"1", "2", "3", "4"};
  a = a1;
  EXPECT_EQ(true, a == a1);
  EXPECT_EQ(false, a != a1);
  EXPECT_EQ(false, a < a1);
  EXPECT_EQ(true, a <= a1);
  EXPECT_EQ(true, a >= a1);
  EXPECT_EQ(false, a > a1);
}

TEST(set, emplace) {
  s21::set<std::string> a = {"1"};
  s21::set<std::string> a1 = {"1", "2", "3", "4"};
  a.emplace("2", "3", "4");
  EXPECT_EQ(true, a == a1);
  EXPECT_EQ(false, a != a1);
  EXPECT_EQ(false, a < a1);
  EXPECT_EQ(true, a <= a1);
  EXPECT_EQ(true, a >= a1);
  EXPECT_EQ(false, a > a1);

  s21::set<std::string> a2;
  s21::set<std::string> a3 = {"2", "3", "4"};
  s21::set<std::string> a4 = {"2", "3", "4", "12", "13", "1"};
  a2.emplace("2", "3", "4");
  EXPECT_EQ(true, a3 == a2);
  a2.emplace("2", "3", "4");
  EXPECT_EQ(true, a3 == a2);
  a2.emplace("1", "12", "13");
  EXPECT_EQ(true, a4 == a2);
  a2.clear();
  a2.emplace("2", "3", "4", "11", "12", "14", "112");
  s21::set<std::string> a5 = {"2", "3", "4", "11", "12", "14", "112"};
  EXPECT_EQ(true, a5 == a2);
}

TEST(set, find) {
  s21::set<int> a1 = {1, 2, 4, 5, 6, 55};
  s21::set<int>::iterator it1 = a1.find(6);
  EXPECT_EQ(6, *it1);
  it1 = a1.find(4);
  EXPECT_EQ(4, *it1);
}

TEST(set, contains) {
  s21::set<int> a1 = {1, 2, 4, 5, 6, 55};
  EXPECT_EQ(true, a1.contains(4));
  EXPECT_EQ(false, a1.contains(42));
  EXPECT_EQ(true, a1.contains(55));
}

TEST(set, find_const) {
  const s21::set<int> a1 = {1, 2, 4, 5, 6, 55};
  s21::set<int>::const_iterator it1 = a1.find(6);
  EXPECT_EQ(6, *it1);
  it1 = a1.find(4);
  EXPECT_EQ(4, *it1);
}

TEST(set, cbegin) {
  s21::set<int> a1 = {1, 2, 3};
  s21::set<int>::const_iterator it = a1.cbegin();
  EXPECT_EQ(1, *it);
}

TEST(set, cend) {
  s21::set<std::string> a1 = {"1", "2", "3"};
  s21::set<std::string>::const_iterator it = a1.cend();
  EXPECT_EQ("3", *--it);
}

TEST(set, begin_const) {
  const s21::set<int> a1 = {1, 2, 3};
  s21::set<int>::const_iterator it = a1.begin();
  EXPECT_EQ(1, *it);
}

TEST(set, end_const) {
  const s21::set<std::string> a1 = {"1", "2", "3"};
  s21::set<std::string>::const_iterator it = a1.end();
  EXPECT_EQ("3", *--it);
}

TEST(set, move) {
  s21::set<int> a1 = {1, 2, 3};
  s21::set<int> a2(std::move(a1));
  s21::set<int>::iterator it = a2.begin();
  EXPECT_EQ(1, *it);

  s21::set<int> a3 = {8, 9, 10};
  a2 = std::move(a3);
  it = a2.begin();
  EXPECT_EQ(8, *it);
}

TEST(set, count) {
  s21::set<int> a1 = {1, 2, 4, 5, 6, 55, 6};
  EXPECT_EQ(1, static_cast<int>(a1.count(6)));
  EXPECT_EQ(1, static_cast<int>(a1.count(4)));
  EXPECT_EQ(0, static_cast<int>(a1.count(3)));
}

TEST(set, test_greater) {
  s21::set<std::string, std::greater<std::string>> a1 = {"1", "2", "3"};
  s21::set<std::string, std::greater<std::string>> a = {"12", "22", "32"};
  a1 = a;

  EXPECT_EQ(true, a == a1);
  EXPECT_EQ(false, a != a1);
  EXPECT_EQ(false, a < a1);
  EXPECT_EQ(true, a <= a1);
  EXPECT_EQ(true, a >= a1);
  EXPECT_EQ(false, a > a1);
}

TEST(set, iterator_greater) {
  s21::set<int, std::greater<int>> a1 = {2, 3, 1};
  s21::set<int, std::greater<int>>::iterator it = a1.begin();
  s21::set<int, std::greater<int>>::iterator it1 = a1.begin();
  EXPECT_EQ(3, *it++);
  EXPECT_EQ(1, *++it);
  EXPECT_EQ(2, *--it);
  EXPECT_EQ(2, *it--);
  EXPECT_EQ(3, *it++);
  EXPECT_EQ(2, *it);
  EXPECT_EQ(true, it != it1);
  EXPECT_EQ(true, --it == it1);
}

TEST(set, erase_greater) {
  s21::set<std::string> a1 = {"1", "2", "2",  "3",     "3",       "4", "4",
                              "1", "4", "22", "dcasd", "1sd21es", "1e"};
  std::set<std::string> a2 = {"1", "2", "2",  "3",     "3",       "4", "4",
                              "1", "4", "22", "dcasd", "1sd21es", "1e"};
  a1.erase(a1.find("1"));
  a2.erase(a2.find("1"));
  EXPECT_EQ(0, Comparison(a1, a2));
  a2.erase(a2.find("3"));
  a1.erase(a1.find("3"));
  EXPECT_EQ(0, Comparison(a1, a2));
  a1.erase(a1.find("4"));
  a2.erase(a2.find("4"));
  EXPECT_EQ(0, Comparison(a1, a2));
  a1.erase(a1.find("1e"));
  a2.erase(a2.find("1e"));
  EXPECT_EQ(0, Comparison(a1, a2));
}

TEST(set, clear_greater) {
  s21::set<int, std::greater<int>> a1 = {1, 2, 3};
  a1.clear();
  EXPECT_EQ(static_cast<int>(a1.size()), 0);
}

TEST(set, merge) {
  s21::set<std::string> a = {"2", "5", "1"};
  s21::set<std::string> a2 = {"1", "3", "4", "5"};
  s21::set<std::string> a1 = {"1", "2", "3", "4", "5"};
  a.merge(a2);
  EXPECT_EQ(true, a == a1);
  EXPECT_EQ(false, a != a1);
  EXPECT_EQ(false, a < a1);
  EXPECT_EQ(true, a <= a1);
  EXPECT_EQ(true, a >= a1);
  EXPECT_EQ(false, a > a1);
}

TEST(set, insert_greater) {
  s21::set<int, std::greater<int>> a1 = {1, 2, 3};
  s21::set<int, std::greater<int>>::iterator it1 = a1.begin();
  std::pair<s21::set<int, std::greater<int>>::iterator, bool> pa =
      a1.insert(33);
  EXPECT_EQ(33, *pa.first);
  pa = a1.insert(22);
  EXPECT_EQ(22, *pa.first);
  it1 = a1.begin();
  EXPECT_EQ(33, *it1++);
  EXPECT_EQ(22, *it1++);
  EXPECT_EQ(3, *it1++);
  EXPECT_EQ(2, *it1++);
  EXPECT_EQ(1, *it1++);
  pa = a1.insert(88);
  EXPECT_EQ(88, *pa.first);
  EXPECT_EQ(6, static_cast<int>(a1.size()));
}

TEST(set, begin_greater) {
  s21::set<int, std::greater<int>> a1 = {1, 2, 3};
  s21::set<int, std::greater<int>>::iterator it = a1.begin();
  EXPECT_EQ(3, *it);
}

TEST(set, end_greater) {
  s21::set<int, std::greater<int>> a1 = {1, 2, 3};
  s21::set<int, std::greater<int>>::iterator it = a1.end();
  EXPECT_EQ(1, *--it);
}

TEST(set, size_greater) {
  s21::set<int, std::greater<int>> a1 = {1, 2, 3};
  EXPECT_EQ(static_cast<int>(a1.size()), 3);
}

TEST(set, empty_greater) {
  s21::set<int, std::greater<int>> a1 = {1, 2, 3};
  EXPECT_EQ(a1.empty(), false);
  a1.clear();
  EXPECT_EQ(a1.empty(), true);
}

TEST(set, swap_greater) {
  s21::set<int, std::greater<int>> a1 = {1, 2, 3};
  s21::set<int, std::greater<int>> a2 = {4, 5, 6, 55};
  a1.swap(a2);
  s21::set<int, std::greater<int>>::iterator it1 = a1.begin();
  s21::set<int, std::greater<int>>::iterator it2 = a2.begin();
  EXPECT_EQ(55, *it1++);
  EXPECT_EQ(*it1++, 6);
  EXPECT_EQ(*it1++, 5);
  EXPECT_EQ(*it1++, 4);
  EXPECT_EQ(*it2++, 3);
  EXPECT_EQ(*it2++, 2);
  EXPECT_EQ(*it2++, 1);
  EXPECT_EQ(static_cast<int>(a2.size()), 3);
  EXPECT_EQ(static_cast<int>(a1.size()), 4);
}

TEST(set, set_greater) {
  s21::set<int, std::greater<int>> a1({1, 2, 3});
  s21::set<int, std::greater<int>>::iterator it1 = a1.begin();
  EXPECT_EQ(3, *it1++);
  EXPECT_EQ(2, *it1++);
  EXPECT_EQ(1, *it1);
}

TEST(set, set3_greater) {
  s21::set<int, std::greater<int>> a({3, 2, 1});
  s21::set<int, std::greater<int>> a1(a);
  s21::set<int, std::greater<int>>::iterator it1 = a1.begin();

  EXPECT_EQ(3, static_cast<int>(a1.size()));
  EXPECT_EQ(3, *it1++);
  EXPECT_EQ(2, *it1++);
  EXPECT_EQ(1, *it1);
}

TEST(set, set4_greater) {
  s21::set<int, std::greater<int>> a({3, 2, 1});
  s21::set<int, std::greater<int>> a1(a.begin(), a.end());
  s21::set<int, std::greater<int>>::iterator it1 = a1.begin();
  EXPECT_EQ(3, static_cast<int>(a1.size()));
  EXPECT_EQ(3, *it1++);
  EXPECT_EQ(2, *it1++);
  EXPECT_EQ(1, *it1);
}

TEST(set, operator_greater) {
  s21::set<int, std::greater<int>> a = {1, 2, 3};
  s21::set<int, std::greater<int>> a1 = {1, 2, 3};
  EXPECT_EQ(true, a == a1);
  EXPECT_EQ(false, a != a1);
  EXPECT_EQ(false, a < a1);
  EXPECT_EQ(true, a <= a1);
  EXPECT_EQ(true, a >= a1);
  EXPECT_EQ(false, a > a1);
}

TEST(set, operator1_greater) {
  s21::set<int, std::greater<int>> a = {1, 2, 3};
  s21::set<int, std::greater<int>> a1 = {1, 2, 3, 4};
  EXPECT_EQ(false, a == a1);
  EXPECT_EQ(true, a != a1);
  EXPECT_EQ(true, a < a1);
  EXPECT_EQ(true, a <= a1);
  EXPECT_EQ(false, a >= a1);
  EXPECT_EQ(false, a > a1);
}

TEST(set, operator2_greater) {
  s21::set<int, std::greater<int>> a = {1, 5, 3};
  s21::set<int, std::greater<int>> a1 = {1, 2, 3, 4};
  EXPECT_EQ(false, a == a1);
  EXPECT_EQ(true, a != a1);
  EXPECT_EQ(false, a < a1);
  EXPECT_EQ(false, a <= a1);
  EXPECT_EQ(true, a >= a1);
  EXPECT_EQ(true, a > a1);
}

TEST(set, operator3_greater) {
  s21::set<int, std::greater<int>> a = {1, 4, 3};
  s21::set<int, std::greater<int>> a1 = {1, 2, 3, 4};
  a = a1;
  EXPECT_EQ(true, a == a1);
  EXPECT_EQ(false, a != a1);
  EXPECT_EQ(false, a < a1);
  EXPECT_EQ(true, a <= a1);
  EXPECT_EQ(true, a >= a1);
  EXPECT_EQ(false, a > a1);
}

TEST(set, emplace_greater) {
  s21::set<int, std::greater<int>> a = {1};
  s21::set<int, std::greater<int>> a1 = {1, 2, 3, 4};
  a.emplace(2, 3, 4);
  EXPECT_EQ(true, a == a1);
  EXPECT_EQ(false, a != a1);
  EXPECT_EQ(false, a < a1);
  EXPECT_EQ(true, a <= a1);
  EXPECT_EQ(true, a >= a1);
  EXPECT_EQ(false, a > a1);
}

TEST(set, find_greater) {
  s21::set<int, std::greater<int>> a1 = {1, 2, 4, 5, 6, 55};
  s21::set<int, std::greater<int>>::iterator it1 = a1.find(6);
  EXPECT_EQ(6, *it1);
  it1 = a1.find(4);
  EXPECT_EQ(4, *it1);
}

TEST(set, count_greater) {
  s21::set<int, std::greater<int>> a1 = {1, 2, 4, 5, 6, 55, 6};
  EXPECT_EQ(1, static_cast<int>(static_cast<int>(a1.count(6))));
  EXPECT_EQ(1, static_cast<int>(a1.count(4)));
  EXPECT_EQ(0, static_cast<int>(a1.count(3)));
}

TEST(list, test_iq) {
  s21::list<std::string> a1 = {"1", "2", "3"};
  s21::list<std::string> a2 = {"12", "22", "32"};
  a1 = a2;
  s21::list<std::string>::iterator it = a1.begin();
  s21::list<std::string>::iterator it1 = a2.begin();
  EXPECT_EQ("12", *it++);
  EXPECT_EQ("22", *it++);
  EXPECT_EQ("32", *it);
  EXPECT_EQ("12", *it1++);
  EXPECT_EQ("22", *it1++);
  EXPECT_EQ("32", *it1);
}

TEST(list, iterator) {
  s21::list<std::string> a1 = {"1", "2", "3"};
  s21::list<std::string>::iterator it = a1.begin();
  s21::list<std::string>::iterator it1 = a1.begin();
  EXPECT_EQ("1", *it++);
  EXPECT_EQ("3", *++it);
  EXPECT_EQ("2", *--it);
  EXPECT_EQ("2", *it--);
  EXPECT_EQ("1", *it++);
  EXPECT_EQ("2", *it);
  EXPECT_EQ(true, it != it1);
  EXPECT_EQ(true, --it == it1);
}

TEST(list, const_iterator) {
  s21::list<std::string> a1 = {"1", "2", "3"};
  s21::list<std::string>::const_iterator it = a1.cbegin();
  s21::list<std::string>::const_iterator it1 = a1.cbegin();
  EXPECT_EQ("1", *it++);
  EXPECT_EQ("3", *++it);
  EXPECT_EQ("2", *--it);
  EXPECT_EQ("2", *it--);
  EXPECT_EQ("1", *it++);
  EXPECT_EQ("2", *it);
  EXPECT_EQ(true, it != it1);
  EXPECT_EQ(true, --it == it1);
}

TEST(list, erase) {
  s21::list<std::string> a1 = {"1", "2", "3", "4", "5", "6", "7", "8"};
  s21::list<std::string>::iterator it = a1.begin();
  it = a1.erase(it);
  EXPECT_EQ("2", *it);
  it = a1.erase(it);
  it++;
  it++;
  it = a1.erase(it);
  EXPECT_EQ("6", *it);

  s21::list<int> a2 = {1, 2, 3, 4, 5, 6, 7, 8};
  s21::list<int>::iterator it2 = a2.begin();
  it2 = a2.erase(it2);
  EXPECT_EQ(2, *it2);
  it2 = a2.erase(it2);
  it2++;
  it2++;
  it2 = a2.erase(it2);
  EXPECT_EQ(6, *it2);

  s21::list<std::string> a3 = {"1", "2", "3", "4", "5", "6", "7", "8"};
  s21::list<std::string>::iterator it3 = a3.begin();
  it3 = a3.erase(++it3, --a3.end());
  EXPECT_EQ("8", *it3);
  it3 = a3.begin();
  EXPECT_EQ("1", *it3);
  it3 = a3.erase(it3);
  EXPECT_EQ("8", *it3);
  EXPECT_EQ(static_cast<int>(a3.size()), 1);
  a3.erase(it3);
  EXPECT_EQ(static_cast<int>(a3.size()), 0);
}

TEST(list, resize) {
  s21::list<std::string> a1 = {"1", "2", "3"};
  a1.resize(2);
  EXPECT_EQ(static_cast<int>(a1.size()), 2);
  a1.resize(4, "5");
  s21::list<std::string>::iterator it = a1.end();
  EXPECT_EQ(*--it, "5");
}

TEST(list, clear) {
  s21::list<std::string> a1 = {"1", "2", "3"};
  a1.clear();
  EXPECT_EQ(static_cast<int>(a1.size()), 0);
}

TEST(list, insert) {
  s21::list<std::string> a1 = {"1", "2", "3"};
  s21::list<std::string>::iterator it1 = a1.begin();
  it1 = a1.insert(++it1, "33");
  EXPECT_EQ("33", *it1);
  it1 = a1.insert(++(++it1), "22");
  EXPECT_EQ("22", *it1);
  it1 = a1.begin();
  EXPECT_EQ("1", *it1++);
  EXPECT_EQ("33", *it1++);
  EXPECT_EQ("2", *it1++);
  EXPECT_EQ("22", *it1++);
  EXPECT_EQ("3", *it1++);
  a1.insert(it1, 8, "88");
  it1 = a1.begin();
  EXPECT_EQ("88", *--(--it1));
  EXPECT_EQ(13, static_cast<int>(a1.size()));

  s21::list<std::string> a2;
  a2.insert(a2.begin(), ++a1.begin(), --a1.end());
  it1 = a2.begin();
  EXPECT_EQ("33", *it1++);
  EXPECT_EQ("2", *it1++);
  EXPECT_EQ("22", *it1++);
  EXPECT_EQ("3", *it1++);
  EXPECT_EQ("88", *it1++);
  EXPECT_EQ(11, static_cast<int>(a2.size()));
  a2.clear();
  a2.insert(a2.begin(), {"1", "2", "333"});
  it1 = a2.begin();
  EXPECT_EQ(3, static_cast<int>(a2.size()));
  EXPECT_EQ("1", *it1++);
  EXPECT_EQ("2", *it1++);
  EXPECT_EQ("333", *it1++);
  it1 = a2.begin();
  a2.insert(it1, 0, "88");
}

TEST(list, front) {
  s21::list<std::string> a1 = {"1", "2", "3"};
  std::string r = a1.front();
  EXPECT_EQ(r, "1");

  s21::list<std::string> a2 = {"44", "2", "3"};
  std::string r2 = a2.front();
  EXPECT_EQ(r2, "44");
}

TEST(list, back) {
  s21::list<std::string> a1 = {"1", "2", "3"};
  std::string r = a1.back();
  EXPECT_EQ(r, "3");

  s21::list<std::string> a2 = {"4", "2", "44"};
  std::string r2 = a2.back();
  EXPECT_EQ(r2, "44");
}

TEST(list, front1) {
  s21::list<int> a1 = {1, 2, 3};
  int a = a1.front();
  EXPECT_EQ(a, 1);
  s21::list<int> a2 = {444, 2, 3};
  a = a2.front();
  EXPECT_EQ(a, 444);
}

TEST(list, back1) {
  s21::list<int> a1 = {1, 2, 3};
  int a = a1.back();
  EXPECT_EQ(a, 3);
  s21::list<int> a2 = {444, 2, 123};
  a = a2.back();
  EXPECT_EQ(a, 123);
}

TEST(list, front_const) {
  const s21::list<int> a1 = {1, 2, 3};
  int a = a1.front();
  EXPECT_EQ(a, 1);
  const s21::list<int> a2 = {444, 2, 3};
  a = a2.front();
  EXPECT_EQ(a, 444);
}

TEST(list, back_const) {
  const s21::list<int> a1 = {1, 2, 3};
  int a = a1.back();
  EXPECT_EQ(a, 3);
  const s21::list<int> a2 = {444, 2, 123};
  a = a2.back();
  EXPECT_EQ(a, 123);
}

TEST(list, begin) {
  s21::list<int> a1 = {1, 2, 3};
  s21::list<int>::iterator it = a1.begin();
  EXPECT_EQ(1, *it);
}

TEST(list, end) {
  s21::list<std::string> a1 = {"1", "2", "3"};
  s21::list<std::string>::iterator it = a1.end();
  EXPECT_EQ("3", *--it);
}

TEST(list, cbegin) {
  s21::list<int> a1 = {1, 2, 3};
  s21::list<int>::const_iterator it = a1.cbegin();
  EXPECT_EQ(1, *it);
}

TEST(list, cend) {
  s21::list<std::string> a1 = {"1", "2", "3"};
  s21::list<std::string>::const_iterator it = a1.cend();
  EXPECT_EQ("3", *--it);
}

TEST(list, move) {
  s21::list<int> a1 = {1, 2, 3};
  s21::list<int> a2(std::move(a1));
  s21::list<int>::iterator it = a2.begin();
  EXPECT_EQ(1, *it);

  s21::list<int> a3 = {8, 9, 10};
  a2 = std::move(a3);
  it = a2.begin();
  EXPECT_EQ(8, *it);
}

TEST(list, size) {
  s21::list<int> a1 = {1, 2, 3};
  EXPECT_EQ(static_cast<int>(a1.size()), 3);
}

TEST(list, empty) {
  s21::list<int> a1 = {1, 2, 3};
  EXPECT_EQ(a1.empty(), false);
  a1.clear();
  EXPECT_EQ(a1.empty(), true);
}

TEST(list, swap) {
  s21::list<int> a1 = {1, 2, 3};
  s21::list<int> a2 = {4, 5, 6, 55};
  a1.swap(a2);
  s21::list<int>::iterator it1 = a1.begin();
  s21::list<int>::iterator it2 = a2.begin();
  EXPECT_EQ(4, *it1++);
  EXPECT_EQ(*it1++, 5);
  EXPECT_EQ(*it1++, 6);
  EXPECT_EQ(*it1++, 55);
  EXPECT_EQ(*it2++, 1);
  EXPECT_EQ(*it2++, 2);
  EXPECT_EQ(*it2++, 3);
  EXPECT_EQ(static_cast<int>(a2.size()), 3);
  EXPECT_EQ(static_cast<int>(a1.size()), 4);
}

TEST(list, assign) {
  s21::list<std::string> a1 = {"1", "2", "3"};
  a1.assign(2, "22");
  s21::list<std::string>::iterator it = a1.begin();
  EXPECT_EQ("22", *it++);
  EXPECT_EQ("22", *it);
  EXPECT_EQ(2, static_cast<int>(a1.size()));
  a1.assign(3, "rr");
  it = a1.begin();
  EXPECT_EQ("rr", *it++);
  EXPECT_EQ("rr", *it++);
  EXPECT_EQ("rr", *it);
  EXPECT_EQ(3, static_cast<int>(a1.size()));

  s21::list<std::string> a2 = {"1", "2", "3"};
  a2.assign({"44", "23"});
  s21::list<std::string>::iterator it2 = a2.begin();
  EXPECT_EQ("44", *it2++);
  EXPECT_EQ("23", *it2);
  EXPECT_EQ(2, static_cast<int>(a2.size()));

  a2.assign({"ww", "ee", "rr"});
  it2 = a2.begin();
  EXPECT_EQ("ww", *it2++);
  EXPECT_EQ("ee", *it2++);
  EXPECT_EQ("rr", *it2);
  EXPECT_EQ(3, static_cast<int>(a2.size()));

  s21::list<std::string> a3 = {"1", "2", "3"};
  a3.assign(a2.begin(), a2.end());
  s21::list<std::string>::iterator it3 = a3.begin();
  EXPECT_EQ("ww", *it3++);
  EXPECT_EQ("ee", *it3++);
  EXPECT_EQ("rr", *it3);
  EXPECT_EQ(3, static_cast<int>(a3.size()));
}

TEST(list, list) {
  s21::list<std::string> a1({"1", "2", "3"});
  s21::list<std::string>::iterator it1 = a1.begin();
  EXPECT_EQ("1", *it1++);
  EXPECT_EQ("2", *it1++);
  EXPECT_EQ("3", *it1);
}

TEST(list, list1) {
  s21::list<std::string> a1(3);
  EXPECT_EQ(3, static_cast<int>(a1.size()));
}

TEST(list, list2) {
  s21::list<std::string> a1(3, "cc");
  s21::list<std::string>::iterator it1 = a1.begin();
  EXPECT_EQ(3, static_cast<int>(a1.size()));
  EXPECT_EQ("cc", *it1++);
  EXPECT_EQ("cc", *it1++);
  EXPECT_EQ("cc", *it1);
}

TEST(list, list3) {
  s21::list<std::string> a(3, "cc");
  s21::list<std::string> a1(a);
  s21::list<std::string>::iterator it1 = a1.begin();
  EXPECT_EQ(3, static_cast<int>(a1.size()));
  EXPECT_EQ("cc", *it1++);
  EXPECT_EQ("cc", *it1++);
  EXPECT_EQ("cc", *it1);
}

TEST(list, list4) {
  s21::list<std::string> a(3, "cc");
  s21::list<std::string> a1(a.begin(), a.end());
  s21::list<std::string>::iterator it1 = a1.begin();
  EXPECT_EQ(3, static_cast<int>(a1.size()));
  EXPECT_EQ("cc", *it1++);
  EXPECT_EQ("cc", *it1++);
  EXPECT_EQ("cc", *it1);
}

TEST(list, pop_front) {
  s21::list<std::string> a1 = {"1", "2", "3"};
  a1.pop_front();
  s21::list<std::string>::iterator it = a1.begin();
  EXPECT_EQ("2", *it++);
  EXPECT_EQ("3", *it);
}

TEST(list, pop_back) {
  s21::list<std::string> a1 = {"1", "2", "3"};
  a1.pop_back();
  s21::list<std::string>::iterator it = a1.end();
  EXPECT_EQ("2", *--it);
  EXPECT_EQ("1", *--it);
}

TEST(list, push_back) {
  s21::list<std::string> a1 = {"1", "2", "3"};
  a1.push_back("44");
  s21::list<std::string>::iterator it = a1.begin();
  EXPECT_EQ("1", *it++);
  EXPECT_EQ("2", *it++);
  EXPECT_EQ("3", *it++);
  EXPECT_EQ("44", *it);
}

TEST(list, operator) {
  s21::list<std::string> a = {"1", "2", "3"};
  s21::list<std::string> a1 = {"1", "2", "3"};
  EXPECT_EQ(true, a == a1);
  EXPECT_EQ(false, a != a1);
  EXPECT_EQ(false, a < a1);
  EXPECT_EQ(true, a <= a1);
  EXPECT_EQ(true, a >= a1);
  EXPECT_EQ(false, a > a1);
}

TEST(list, operator1) {
  s21::list<std::string> a = {"1", "2", "3"};
  s21::list<std::string> a1 = {"1", "2", "3", "4"};
  EXPECT_EQ(false, a == a1);
  EXPECT_EQ(true, a != a1);
  EXPECT_EQ(true, a < a1);
  EXPECT_EQ(true, a <= a1);
  EXPECT_EQ(false, a >= a1);
  EXPECT_EQ(false, a > a1);
}

TEST(list, operator2) {
  s21::list<std::string> a = {"1", "4", "3"};
  s21::list<std::string> a1 = {"1", "2", "3", "4"};
  EXPECT_EQ(false, a == a1);
  EXPECT_EQ(true, a != a1);
  EXPECT_EQ(false, a < a1);
  EXPECT_EQ(false, a <= a1);
  EXPECT_EQ(true, a >= a1);
  EXPECT_EQ(true, a > a1);
}

TEST(list, operator3) {
  s21::list<std::string> a = {"1", "4", "3"};
  s21::list<std::string> a1 = {"1", "2", "3", "4"};
  a = a1;
  EXPECT_EQ(true, a == a1);
  EXPECT_EQ(false, a != a1);
  EXPECT_EQ(false, a < a1);
  EXPECT_EQ(true, a <= a1);
  EXPECT_EQ(true, a >= a1);
  EXPECT_EQ(false, a > a1);
}

TEST(list, emplace) {
  s21::list<std::string> a = {"1"};
  s21::list<std::string> a1 = {"1", "2", "3", "4"};
  a.emplace(a.end(), "2", "3", "4");
  EXPECT_EQ(true, a == a1);
  EXPECT_EQ(false, a != a1);
  EXPECT_EQ(false, a < a1);
  EXPECT_EQ(true, a <= a1);
  EXPECT_EQ(true, a >= a1);
  EXPECT_EQ(false, a > a1);

  s21::list<std::string> a2;
  s21::list<std::string> a3 = {"2", "3", "4"};
  s21::list<std::string> a4 = {"2", "3", "4", "12", "13", "1"};
  a2.emplace(a2.end(), "2", "3", "4");
  EXPECT_EQ(true, a3 == a2);
  a2.emplace(a2.end(), "2", "3", "4");
  s21::list<std::string> a6 = {"2", "3", "4", "2", "3", "4"};
  EXPECT_EQ(true, a6 == a2);
  s21::list<std::string>::iterator it = a2.begin();
  a2.emplace(++it, "1", "12", "13");
  s21::list<std::string> a7 = {"2", "1", "12", "13", "3", "4", "2", "3", "4"};
  EXPECT_EQ(true, a7 == a2);
  a2.clear();
  a2.emplace(a2.end(), "2", "3", "4", "11", "12", "14", "112");
  s21::list<std::string> a5 = {"2", "3", "4", "11", "12", "14", "112"};
  EXPECT_EQ(true, a5 == a2);
}

TEST(list, emplace_back) {
  s21::list<std::string> a = {"1"};
  s21::list<std::string> a1 = {"1", "2", "3", "4"};
  a.emplace_back("2", "3", "4");
  EXPECT_EQ(true, a == a1);
  EXPECT_EQ(false, a != a1);
  EXPECT_EQ(false, a < a1);
  EXPECT_EQ(true, a <= a1);
  EXPECT_EQ(true, a >= a1);
  EXPECT_EQ(false, a > a1);
}

TEST(list, emplace_front) {
  s21::list<std::string> a = {"4"};
  s21::list<std::string> a1 = {"1", "2", "3", "4"};
  a.emplace_front("1", "2", "3");
  EXPECT_EQ(true, a == a1);
  EXPECT_EQ(false, a != a1);
  EXPECT_EQ(false, a < a1);
  EXPECT_EQ(true, a <= a1);
  EXPECT_EQ(true, a >= a1);
  EXPECT_EQ(false, a > a1);
}

TEST(list, merge) {
  s21::list<std::string> a = {"2", "5"};
  s21::list<std::string> a2 = {"1", "3", "4", "5"};
  s21::list<std::string> a1 = {"1", "2", "3", "4", "5", "5"};
  a.merge(a2);
  EXPECT_EQ(true, a == a1);
  EXPECT_EQ(false, a != a1);
  EXPECT_EQ(false, a < a1);
  EXPECT_EQ(true, a <= a1);
  EXPECT_EQ(true, a >= a1);
  EXPECT_EQ(false, a > a1);
}

TEST(list, sort) {
  s21::list<std::string> a = {"2", "5", "4", "3", "5", "1"};
  s21::list<std::string> a1 = {"1", "2", "3", "4", "5", "5"};
  a.sort();
  EXPECT_EQ(true, a == a1);
  EXPECT_EQ(false, a != a1);
  EXPECT_EQ(false, a < a1);
  EXPECT_EQ(true, a <= a1);
  EXPECT_EQ(true, a >= a1);
  EXPECT_EQ(false, a > a1);
}

TEST(list, reverse) {
  s21::list<std::string> a = {"5", "5", "4", "3", "2", "1"};
  s21::list<std::string> a1 = {"1", "2", "3", "4", "5", "5"};
  a.reverse();
  EXPECT_EQ(true, a == a1);
  EXPECT_EQ(false, a != a1);
  EXPECT_EQ(false, a < a1);
  EXPECT_EQ(true, a <= a1);
  EXPECT_EQ(true, a >= a1);
  EXPECT_EQ(false, a > a1);
}

TEST(list, splice) {
  s21::list<std::string> a = {"5", "5", "4", "3", "2", "1"};
  s21::list<std::string> a3 = {"5", "4", "3", "2", "5", "1"};
  a.splice(--a.cend(), a, ++a.cbegin());

  EXPECT_EQ(true, a == a3);
  EXPECT_EQ(false, a != a3);
  EXPECT_EQ(false, a < a3);
  EXPECT_EQ(true, a <= a3);
  EXPECT_EQ(true, a >= a3);
  EXPECT_EQ(false, a > a3);
  EXPECT_EQ(static_cast<int>(a.size()), 6);
}

TEST(list, splice2) {
  s21::list<std::string> a = {"5", "5", "4", "3", "2", "1"};
  s21::list<std::string> a1 = {"4", "34", "54"};
  s21::list<std::string> a3 = {"5", "4", "34", "54", "5", "4", "3", "2", "1"};
  a.splice(++a.cbegin(), a1);
  EXPECT_EQ(true, a == a3);
  EXPECT_EQ(false, a != a3);
  EXPECT_EQ(false, a < a3);
  EXPECT_EQ(true, a <= a3);
  EXPECT_EQ(true, a >= a3);
  EXPECT_EQ(false, a > a3);
  EXPECT_EQ(static_cast<int>(a1.size()), 0);
  EXPECT_EQ(static_cast<int>(a.size()), 9);
}

TEST(list, unique) {
  s21::list<std::string> a = {"5", "5", "4", "3", "2", "2"};
  s21::list<std::string> a3 = {"5", "4", "3", "2"};
  a.unique();
  EXPECT_EQ(true, a == a3);
  EXPECT_EQ(false, a != a3);
  EXPECT_EQ(false, a < a3);
  EXPECT_EQ(true, a <= a3);
  EXPECT_EQ(true, a >= a3);
  EXPECT_EQ(false, a > a3);
  EXPECT_EQ(static_cast<int>(a.size()), 4);
}

TEST(list, remove) {
  s21::list<int> a = {1, 2, 3, 4, 2, 6};
  s21::list<int> a3 = {1, 3, 4, 6};
  a.remove(2);
  EXPECT_EQ(true, a == a3);
  EXPECT_EQ(false, a != a3);
  EXPECT_EQ(false, a < a3);
  EXPECT_EQ(true, a <= a3);
  EXPECT_EQ(true, a >= a3);
  EXPECT_EQ(false, a > a3);
  EXPECT_EQ(static_cast<int>(a.size()), 4);
}

TEST(list, push_front) {
  s21::list<int> a = {2, 4, 6};
  s21::list<int> a3 = {3, 2, 1, 2, 4, 6};
  a.push_front(1);
  a.push_front(2);
  a.push_front(3);
  EXPECT_EQ(true, a == a3);
  EXPECT_EQ(false, a != a3);
  EXPECT_EQ(false, a < a3);
  EXPECT_EQ(true, a <= a3);
  EXPECT_EQ(true, a >= a3);
  EXPECT_EQ(false, a > a3);
  EXPECT_EQ(static_cast<int>(a.size()), 6);
}

TEST(vector, test_iq) {
  s21::vector<std::string> a1 = {"1", "2", "3"};
  s21::vector<std::string> a2 = {"12", "22", "32"};
  a1 = a2;
  EXPECT_EQ("12", a1[0]);
  EXPECT_EQ("22", a1[1]);
  EXPECT_EQ("32", a1[2]);
  EXPECT_EQ("12", a2[0]);
  EXPECT_EQ("22", a2[1]);
  EXPECT_EQ("32", a2[2]);
}

TEST(vector, iterator) {
  s21::vector<std::string> a1 = {"1", "2", "3"};
  s21::vector<std::string>::iterator it = a1.begin();
  s21::vector<std::string>::iterator it1 = a1.begin();
  EXPECT_EQ("1", *it++);
  EXPECT_EQ("3", *++it);
  EXPECT_EQ("2", *--it);
  EXPECT_EQ("2", *it--);
  EXPECT_EQ("1", *it++);
  EXPECT_EQ("2", *it);
  EXPECT_EQ(true, it != it1);
  EXPECT_EQ(true, --it == it1);
}

TEST(vector, erase) {
  s21::vector<std::string> a1 = {"1", "2", "3", "4", "5", "6", "7", "8"};
  s21::vector<std::string>::iterator it = a1.begin();
  it = a1.erase(it);
  EXPECT_EQ("2", *it);
  it = a1.erase(it);
  it++;
  it++;
  it = a1.erase(it);
  EXPECT_EQ("6", *it);

  s21::vector<int> a2 = {1, 2, 3, 4, 5, 6, 7, 8};
  s21::vector<int>::iterator it2 = a2.begin();
  it2 = a2.erase(it2);
  EXPECT_EQ(2, *it2);
  it2 = a2.erase(it2);
  it2++;
  it2++;
  it2 = a2.erase(it2);
  EXPECT_EQ(6, *it2);

  s21::vector<std::string> a3 = {"1", "2", "3", "4", "5", "6", "7", "8"};
  s21::vector<std::string>::iterator it3 = a3.begin();
  it3 = a3.erase(++ ++it3, (a3.end()));
  EXPECT_EQ("2", *--it3);
  it3 = a3.begin();
  EXPECT_EQ("1", *it3);
  it3 = a3.erase(it3);
  EXPECT_EQ("2", *it3);
  EXPECT_EQ(static_cast<int>(a3.size()), 1);
  a3.erase(it3);
  EXPECT_EQ(static_cast<int>(a3.size()), 0);
}

TEST(vector, resize) {
  s21::vector<std::string> a1 = {"1", "2", "3"};
  a1.resize(2);
  EXPECT_EQ(static_cast<int>(a1.size()), 2);
  a1.resize(4, "5");
  EXPECT_EQ(a1[2], "5");
}

TEST(vector, clear) {
  s21::vector<std::string> a1 = {"1", "2", "3"};
  a1.clear();
  EXPECT_EQ(static_cast<int>(a1.size()), 0);
}

TEST(vector, insert) {
  s21::vector<std::string> a1 = {"1", "2", "3"};
  s21::vector<std::string>::iterator it1 = a1.begin();
  it1 = a1.insert(++it1, "33");
  EXPECT_EQ("33", *it1);
  it1 = a1.insert(++(++it1), "22");
  EXPECT_EQ("22", *it1);
  EXPECT_EQ("22", a1[3]);
  EXPECT_EQ("33", a1[1]);
  a1.insert(++it1, 8, "88");
  EXPECT_EQ("88", a1[11]);
  EXPECT_EQ(13, static_cast<int>(a1.size()));

  s21::vector<std::string> a2;
  a2.insert(a2.begin(), a1.begin(), a1.end());
  EXPECT_EQ("1", a2[0]);
  EXPECT_EQ("88", a2[10]);
  EXPECT_EQ(13, static_cast<int>(a2.size()));
  a2.clear();
  a2.insert(a2.begin(), {"1", "2", "333"});
  EXPECT_EQ(3, static_cast<int>(a2.size()));
  EXPECT_EQ("1", a2[0]);
  EXPECT_EQ("333", a2[2]);
}

TEST(vector, front) {
  s21::vector<std::string> a1 = {"1", "2", "3"};
  std::string r = a1.front();
  EXPECT_EQ(r, "1");

  s21::vector<std::string> a2 = {"44", "2", "3"};
  std::string r2 = a2.front();
  EXPECT_EQ(r2, "44");
}

TEST(vector, back) {
  s21::vector<std::string> a1 = {"1", "2", "3"};
  std::string r = a1.back();
  EXPECT_EQ(r, "3");

  s21::vector<std::string> a2 = {"4", "2", "44"};
  std::string r2 = a2.back();
  EXPECT_EQ(r2, "44");
}

TEST(vector, date) {
  s21::vector<int> a1 = {1, 2, 3};
  int *a = a1.data();
  EXPECT_EQ(*a, 1);
  s21::vector<int> a2 = {444, 2, 3};
  a = a2.data();
  EXPECT_EQ(*a, 444);
}

TEST(vector, date_const) {
  const s21::vector<int> a1 = {1, 2, 3};
  const int *a = a1.data();
  EXPECT_EQ(*a, 1);
  const s21::vector<int> a2 = {444, 2, 3};
  a = a2.data();
  EXPECT_EQ(*a, 444);
}

TEST(vector, front1) {
  s21::vector<int> a1 = {1, 2, 3};
  int a = a1.front();
  EXPECT_EQ(a, 1);
  s21::vector<int> a2 = {444, 2, 3};
  a = a2.front();
  EXPECT_EQ(a, 444);
}

TEST(vector, front_const) {
  const s21::vector<int> a1 = {1, 2, 3};
  int a = a1.front();
  EXPECT_EQ(a, 1);
  const s21::vector<int> a2 = {444, 2, 3};
  a = a2.front();
  EXPECT_EQ(a, 444);
}

TEST(vector, back1) {
  s21::vector<int> a1 = {1, 2, 3};
  int a = a1.back();
  EXPECT_EQ(a, 3);
  s21::vector<int> a2 = {444, 2, 123};
  a = a2.back();
  EXPECT_EQ(a, 123);
}

TEST(vector, back_const) {
  const s21::vector<int> a1 = {1, 2, 3};
  int a = a1.back();
  EXPECT_EQ(a, 3);
  const s21::vector<int> a2 = {444, 2, 123};
  a = a2.back();
  EXPECT_EQ(a, 123);
}

TEST(vector, constryctor) {
  s21::vector<int> a1(123);
  s21::vector<int> a2(a1);
  EXPECT_EQ(static_cast<int>(a1.size()), 123);
  EXPECT_EQ(static_cast<int>(a2.size()), 123);
}

TEST(vector, at) {
  s21::vector<int> a1 = {1, 2, 3};
  int a = a1.at(1);
  EXPECT_EQ(a, 2);
  EXPECT_THROW(a1.at(55), std::out_of_range);
}

TEST(vector, at_const) {
  const s21::vector<int> a1 = {1, 2, 3};
  int a = a1.at(1);
  EXPECT_EQ(a, 2);
}

TEST(vector, begin) {
  s21::vector<int> a1 = {1, 2, 3};
  s21::vector<int>::iterator it = a1.begin();
  EXPECT_EQ(1, *it);
}

TEST(vector, cbegin) {
  const s21::vector<int> a1 = {1, 2, 3};
  s21::vector<int>::const_iterator it = a1.cbegin();
  EXPECT_EQ(1, *it);

  const s21::vector<int> a2 = {1, 2, 3};
  s21::vector<int>::const_iterator it1 = a2.begin();
  EXPECT_EQ(1, *it1);
}

TEST(vector, cend) {
  const s21::vector<std::string> a1 = {"1", "2", "3"};
  s21::vector<std::string>::const_iterator it = a1.end();
  EXPECT_EQ("3", *--it);
}

TEST(vector, cend_const) {
  const s21::vector<std::string> a1 = {"1", "2", "3"};
  s21::vector<std::string>::const_iterator it = a1.cend();
  EXPECT_EQ("3", *--it);
}

TEST(vector, size) {
  const s21::vector<int> a1 = {1, 2, 3};
  EXPECT_EQ(static_cast<int>(a1.size()), 3);
}

TEST(vector, empty) {
  s21::vector<int> a1 = {1, 2, 3};
  EXPECT_EQ(a1.empty(), false);
  a1.clear();
  EXPECT_EQ(a1.empty(), true);
}

TEST(vector, swap) {
  s21::vector<int> a1 = {1, 2, 3};
  s21::vector<int> a2 = {4, 5, 6, 55};
  a1.swap(a2);
  EXPECT_EQ(a1[0], 4);
  EXPECT_EQ(a1[1], 5);
  EXPECT_EQ(a1[2], 6);
  EXPECT_EQ(a1[3], 55);
  EXPECT_EQ(a2[0], 1);
  EXPECT_EQ(a2[1], 2);
  EXPECT_EQ(a2[2], 3);
  EXPECT_EQ(static_cast<int>(a2.size()), 3);
  EXPECT_EQ(static_cast<int>(a1.size()), 4);
}

TEST(vector, operator5) {
  const s21::vector<int> a1 = {1, 2, 3};
  EXPECT_EQ(a1[0], 1);
  EXPECT_EQ(a1[1], 2);
  EXPECT_EQ(a1[2], 3);
  EXPECT_EQ(static_cast<int>(a1.size()), 3);
}

TEST(vector, assign) {
  s21::vector<std::string> a1 = {"1", "2", "3"};
  a1.assign(2, "22");
  s21::vector<std::string>::iterator it = a1.begin();
  EXPECT_EQ("22", *it++);
  EXPECT_EQ("22", *it);
  EXPECT_EQ(2, static_cast<int>(a1.size()));
  a1.assign(3, "rr");
  it = a1.begin();
  EXPECT_EQ("rr", *it++);
  EXPECT_EQ("rr", *it++);
  EXPECT_EQ("rr", *it);
  EXPECT_EQ(3, static_cast<int>(a1.size()));

  s21::vector<std::string> a2 = {"1", "2", "3"};
  a2.assign({"44", "23"});
  s21::vector<std::string>::iterator it2 = a2.begin();
  EXPECT_EQ("44", *it2++);
  EXPECT_EQ("23", *it2);
  EXPECT_EQ(2, static_cast<int>(a2.size()));

  a2.assign({"ww", "ee", "rr"});
  it2 = a2.begin();
  EXPECT_EQ("ww", *it2++);
  EXPECT_EQ("ee", *it2++);
  EXPECT_EQ("rr", *it2);
  EXPECT_EQ(3, static_cast<int>(a2.size()));

  s21::vector<std::string> a3 = {"1", "2", "3"};
  a3.assign(a2.begin(), a2.end());
  s21::vector<std::string>::iterator it3 = a3.begin();
  EXPECT_EQ("ww", *it3++);
  EXPECT_EQ("ee", *it3++);
  EXPECT_EQ("rr", *it3);
  EXPECT_EQ(3, static_cast<int>(a3.size()));
}

TEST(vector, vector) {
  s21::vector<std::string> a1({"1", "2", "3"});
  s21::vector<std::string>::iterator it1 = a1.begin();
  EXPECT_EQ("1", *it1++);
  EXPECT_EQ("2", *it1++);
  EXPECT_EQ("3", *it1);
}

TEST(vector, vector1) {
  s21::vector<std::string> a1(3);
  EXPECT_EQ(3, static_cast<int>(a1.size()));
  EXPECT_EQ(3, static_cast<int>(a1.capacity()));
}

TEST(vector, vector2) {
  s21::vector<std::string> a1(3, "cc");
  s21::vector<std::string>::iterator it1 = a1.begin();
  EXPECT_EQ(3, static_cast<int>(a1.size()));
  EXPECT_EQ(3, static_cast<int>(a1.capacity()));
  EXPECT_EQ("cc", *it1++);
  EXPECT_EQ("cc", *it1++);
  EXPECT_EQ("cc", *it1);
}

TEST(vector, vector3) {
  s21::vector<std::string> a(3, "cc");
  s21::vector<std::string> a1(a);
  s21::vector<std::string>::iterator it1 = a1.begin();
  EXPECT_EQ(3, static_cast<int>(a1.size()));
  EXPECT_EQ(3, static_cast<int>(a1.capacity()));
  EXPECT_EQ("cc", *it1++);
  EXPECT_EQ("cc", *it1++);
  EXPECT_EQ("cc", *it1);
}

TEST(vector, vector4) {
  s21::vector<std::string> a(3, "cc");
  s21::vector<std::string> a1(a.begin(), a.end());
  s21::vector<std::string>::iterator it1 = a1.begin();
  EXPECT_EQ(3, static_cast<int>(a1.size()));
  EXPECT_EQ(3, static_cast<int>(a1.capacity()));
  EXPECT_EQ("cc", *it1++);
  EXPECT_EQ("cc", *it1++);
  EXPECT_EQ("cc", *it1);
}

TEST(vector, vector5) {
  std::vector<std::string> a(3, "cc");
  s21::vector<std::string> a1(a.begin(), a.end());
  s21::vector<std::string>::iterator it1 = a1.begin();
  EXPECT_EQ(3, static_cast<int>(a1.size()));
  EXPECT_EQ(3, static_cast<int>(a1.capacity()));
  EXPECT_EQ("cc", *it1++);
  EXPECT_EQ("cc", *it1++);
  EXPECT_EQ("cc", *it1);
}

TEST(vector, shrink_to_fit) {
  s21::vector<std::string> a1(3, "cc");
  a1.clear();
  EXPECT_EQ(0, static_cast<int>(a1.size()));
  EXPECT_EQ(3, static_cast<int>(a1.capacity()));
  a1.shrink_to_fit();
  EXPECT_EQ(0, static_cast<int>(a1.size()));
  EXPECT_EQ(0, static_cast<int>(a1.capacity()));
}

TEST(vector, reserve) {
  s21::vector<std::string> a1(3, "cc");
  a1.reserve(7);
  EXPECT_EQ(3, static_cast<int>(a1.size()));
  EXPECT_EQ(7, static_cast<int>(a1.capacity()));
}

TEST(vector, pop_front) {
  s21::vector<std::string> a1 = {"1", "2", "3"};
  a1.pop_front();
  s21::vector<std::string>::iterator it = a1.begin();
  EXPECT_EQ("2", *it++);
  EXPECT_EQ("3", *it);
}

TEST(vector, pop_back) {
  s21::vector<std::string> a1 = {"1", "2", "3"};
  a1.pop_back();
  s21::vector<std::string>::iterator it = a1.end();
  EXPECT_EQ("2", *--it);
  EXPECT_EQ("1", *--it);
}

TEST(vector, push_back) {
  s21::vector<std::string> a1 = {"1", "2", "3"};
  a1.push_back("44");
  s21::vector<std::string>::iterator it = a1.begin();
  EXPECT_EQ("1", *it++);
  EXPECT_EQ("2", *it++);
  EXPECT_EQ("3", *it++);
  EXPECT_EQ("44", *it);
}

TEST(vector, operator) {
  s21::vector<std::string> a = {"1", "2", "3"};
  s21::vector<std::string> a1 = {"1", "2", "3"};
  EXPECT_EQ(true, a == a1);
  EXPECT_EQ(false, a != a1);
  EXPECT_EQ(false, a < a1);
  EXPECT_EQ(true, a <= a1);
  EXPECT_EQ(true, a >= a1);
  EXPECT_EQ(false, a > a1);
}

TEST(vector, operator1) {
  s21::vector<std::string> a = {"1", "2", "3"};
  s21::vector<std::string> a1 = {"1", "2", "3", "4"};
  EXPECT_EQ(false, a == a1);
  EXPECT_EQ(true, a != a1);
  EXPECT_EQ(true, a < a1);
  EXPECT_EQ(true, a <= a1);
  EXPECT_EQ(false, a >= a1);
  EXPECT_EQ(false, a > a1);
}

TEST(vector, operator2) {
  s21::vector<std::string> a = {"1", "4", "3"};
  s21::vector<std::string> a1 = {"1", "2", "3", "4"};
  EXPECT_EQ(false, a == a1);
  EXPECT_EQ(true, a != a1);
  EXPECT_EQ(false, a < a1);
  EXPECT_EQ(false, a <= a1);
  EXPECT_EQ(true, a >= a1);
  EXPECT_EQ(true, a > a1);
}

TEST(vector, operator3) {
  s21::vector<std::string> a = {"1", "4", "3"};
  s21::vector<std::string> a1 = {"1", "2", "3", "4"};
  a = a1;
  EXPECT_EQ(true, a == a1);
  EXPECT_EQ(false, a != a1);
  EXPECT_EQ(false, a < a1);
  EXPECT_EQ(true, a <= a1);
  EXPECT_EQ(true, a >= a1);
  EXPECT_EQ(false, a > a1);
}

TEST(vector, emplace) {
  s21::vector<std::string> a = {"1"};
  s21::vector<std::string> a1 = {"1", "2", "3", "4"};
  a.emplace(a.end(), "2", "3", "4");
  EXPECT_EQ(true, a == a1);
  EXPECT_EQ(false, a != a1);
  EXPECT_EQ(false, a < a1);
  EXPECT_EQ(true, a <= a1);
  EXPECT_EQ(true, a >= a1);
  EXPECT_EQ(false, a > a1);

  s21::vector<std::string> a2;
  s21::vector<std::string> a3 = {"2", "3", "4"};
  s21::vector<std::string> a4 = {"2", "3", "4", "12", "13", "1"};
  a2.emplace(a2.end(), "2", "3", "4");
  EXPECT_EQ(true, a3 == a2);
  a2.emplace(a2.end(), "2", "3", "4");
  s21::vector<std::string> a6 = {"2", "3", "4", "2", "3", "4"};
  EXPECT_EQ(true, a6 == a2);
  s21::vector<std::string>::iterator it = a2.begin();
  a2.emplace(++it, "1", "12", "13");
  s21::vector<std::string> a7 = {"2", "1", "12", "13", "3", "4", "2", "3", "4"};
  EXPECT_EQ(true, a7 == a2);
  a2.clear();
  a2.emplace(a2.end(), "2", "3", "4", "11", "12", "14", "112");
  s21::vector<std::string> a5 = {"2", "3", "4", "11", "12", "14", "112"};
  EXPECT_EQ(true, a5 == a2);
}

TEST(vector, emplace_back) {
  s21::vector<std::string> a = {"1"};
  s21::vector<std::string> a1 = {"1", "2", "3", "4"};
  a.emplace_back("2", "3", "4");
  EXPECT_EQ(true, a == a1);
  EXPECT_EQ(false, a != a1);
  EXPECT_EQ(false, a < a1);
  EXPECT_EQ(true, a <= a1);
  EXPECT_EQ(true, a >= a1);
  EXPECT_EQ(false, a > a1);
}

TEST(vector, emplace_front) {
  s21::vector<std::string> a = {"4"};
  s21::vector<std::string> a1 = {"1", "2", "3", "4"};
  a.emplace_front("1", "2", "3");
  EXPECT_EQ(true, a == a1);
  EXPECT_EQ(false, a != a1);
  EXPECT_EQ(false, a < a1);
  EXPECT_EQ(true, a <= a1);
  EXPECT_EQ(true, a >= a1);
  EXPECT_EQ(false, a > a1);
}

TEST(multiset, test_iq) {
  s21::multiset<std::string> a1 = {"1", "2", "3"};
  s21::multiset<std::string> a2 = {"12", "22", "32"};
  a1 = a2;
  s21::multiset<std::string>::iterator it = a1.begin();
  s21::multiset<std::string>::iterator it1 = a2.begin();
  EXPECT_EQ("12", *it++);
  EXPECT_EQ("22", *it++);
  EXPECT_EQ("32", *it);
  EXPECT_EQ("12", *it1++);
  EXPECT_EQ("22", *it1++);
  EXPECT_EQ("32", *it1);
}

TEST(multiset, iterator) {
  s21::multiset<std::string> a1 = {"1", "2", "3"};
  s21::multiset<std::string>::iterator it = a1.begin();
  s21::multiset<std::string>::iterator it1 = a1.begin();
  EXPECT_EQ("1", *it++);
  EXPECT_EQ("3", *++it);
  EXPECT_EQ("2", *--it);
  EXPECT_EQ("2", *it--);
  EXPECT_EQ("1", *it++);
  EXPECT_EQ("2", *it);
  EXPECT_EQ(true, it != it1);
  EXPECT_EQ(true, --it == it1);
}

TEST(multiset, erase) {
  s21::multiset<std::string> a1 = {"1", "2", "2", "3", "3", "4", "4", "1", "4"};
  s21::multiset<std::string>::iterator it = ++(a1.begin());
  it++;
  it++;
  a1.erase(it);
  it = ++a1.find("2");
  a1.erase(it);
  it = a1.find("4");
  a1.erase(it);
  it = a1.find("4");
  a1.erase(it);

  std::multiset<std::string> a2 = {"1", "2", "2", "3", "3", "4", "4", "1", "4"};
  std::multiset<std::string>::iterator it2 = ++(a2.begin());
  it2++;
  it2++;
  a2.erase(it2);
  it2 = ++a2.find("2");
  a2.erase(it2);
  it2 = a2.find("4");
  a2.erase(it2);
  it2 = a2.find("4");
  a2.erase(it2);
  Comparison(a1, a2);

  EXPECT_EQ(0, Comparison(a1, a2));
}

TEST(multiset, clear) {
  s21::multiset<std::string> a1 = {"1", "2", "3"};
  a1.clear();
  EXPECT_EQ(static_cast<int>(a1.size()), 0);
}

TEST(multiset, insert) {
  s21::multiset<int> a1 = {1, 2, 3};
  s21::multiset<int>::iterator it1 = a1.begin();
  s21::multiset<int>::iterator pa = a1.insert(33);
  EXPECT_EQ(33, *pa);
  pa = a1.insert(22);
  EXPECT_EQ(22, *pa);
  it1 = a1.begin();
  EXPECT_EQ(1, *it1++);
  EXPECT_EQ(2, *it1++);
  EXPECT_EQ(3, *it1++);
  EXPECT_EQ(22, *it1++);
  EXPECT_EQ(33, *it1++);
  pa = a1.insert(88);
  EXPECT_EQ(88, *pa);
  pa = a1.insert(33);
  EXPECT_EQ(88, *++pa);
  pa = a1.insert(33);
  EXPECT_EQ(88, *++pa);
  EXPECT_EQ(8, static_cast<int>(a1.size()));
}

TEST(multiset, lower_bound_const) {
  const s21::multiset<int> a1 = {1, 2, 4, 5, 6, 55};
  s21::multiset<int>::const_iterator it1 = a1.lower_bound(8);
  EXPECT_EQ(55, *it1);
  it1 = a1.lower_bound(4);
  EXPECT_EQ(4, *it1);
  it1 = a1.lower_bound(3);
  EXPECT_EQ(4, *it1);
}

TEST(multiset, upper_bound_const) {
  const s21::multiset<int> a1 = {1, 2, 4, 5, 6, 55};
  s21::multiset<int>::const_iterator it1 = a1.upper_bound(8);
  EXPECT_EQ(55, *it1);
  it1 = a1.upper_bound(4);
  EXPECT_EQ(5, *it1);
  it1 = a1.upper_bound(3);
  EXPECT_EQ(4, *it1);
}

TEST(multiset, equal_range_const) {
  const s21::multiset<int> a1 = {1, 2, 4, 5, 6, 55};
  std::pair<s21::multiset<int>::const_iterator,
            s21::multiset<int>::const_iterator>
      it1 = a1.equal_range(8);
  EXPECT_EQ(55, *it1.first);
  EXPECT_EQ(55, *it1.second);
  it1 = a1.equal_range(4);
  EXPECT_EQ(4, *it1.first);
  EXPECT_EQ(5, *it1.second);
  it1 = a1.equal_range(3);
  EXPECT_EQ(4, *it1.first);
  EXPECT_EQ(4, *it1.second);
}

TEST(multiset, merge) {
  s21::multiset<std::string> a = {"2", "5", "1"};
  s21::multiset<std::string> a2 = {"1", "3", "4", "5"};
  s21::multiset<std::string> a1 = {"1", "1", "2", "3", "4", "5", "5"};
  a.merge(a2);
  EXPECT_EQ(true, a == a1);
  EXPECT_EQ(false, a != a1);
  EXPECT_EQ(false, a < a1);
  EXPECT_EQ(true, a <= a1);
  EXPECT_EQ(true, a >= a1);
  EXPECT_EQ(false, a > a1);
}

TEST(multiset, find_const) {
  const s21::multiset<int> a1 = {1, 2, 4, 5, 6, 55};
  s21::multiset<int>::const_iterator it1 = a1.find(6);
  EXPECT_EQ(6, *it1);
  it1 = a1.find(4);
  EXPECT_EQ(4, *it1);
}

TEST(multiset, cbegin1) {
  s21::multiset<int> a1 = {1, 2, 3};
  s21::multiset<int>::const_iterator it = a1.cbegin();
  EXPECT_EQ(1, *it);
}

TEST(multiset, cend1) {
  s21::multiset<std::string> a1 = {"1", "2", "3"};
  s21::multiset<std::string>::const_iterator it = a1.cend();
  EXPECT_EQ("3", *--it);
}

TEST(multiset, begin_const) {
  const s21::multiset<int> a1 = {1, 2, 3};
  s21::multiset<int>::const_iterator it = a1.begin();
  EXPECT_EQ(1, *it);
}

TEST(multiset, end_const) {
  const s21::multiset<std::string> a1 = {"1", "2", "3"};
  s21::multiset<std::string>::const_iterator it = a1.end();
  EXPECT_EQ("3", *--it);
}

TEST(multiset, move) {
  s21::multiset<int> a1 = {1, 2, 3};
  s21::multiset<int> a2(std::move(a1));
  s21::multiset<int>::iterator it = a2.begin();
  EXPECT_EQ(1, *it);

  s21::multiset<int> a3 = {8, 9, 10};
  a2 = std::move(a3);
  it = a2.begin();
  EXPECT_EQ(8, *it);
}

TEST(multiset, begin) {
  s21::multiset<int> a1 = {1, 2, 3};
  s21::multiset<int>::iterator it = a1.begin();
  EXPECT_EQ(1, *it);
}

TEST(multiset, cbegin) {
  s21::multiset<int> a1 = {1, 2, 3};
  s21::multiset<int>::const_iterator it = a1.cbegin();
  EXPECT_EQ(1, *it);
}

TEST(multiset, end) {
  s21::multiset<std::string> a1 = {"1", "2", "3"};
  s21::multiset<std::string>::iterator it = a1.end();
  EXPECT_EQ("3", *--it);
}

TEST(multiset, cend) {
  s21::multiset<std::string> a1 = {"1", "2", "3"};
  s21::multiset<std::string>::const_iterator it = a1.cend();
  EXPECT_EQ("3", *--it);
}

TEST(multiset, size) {
  s21::multiset<int> a1 = {1, 2, 3};
  EXPECT_EQ(static_cast<int>(a1.size()), 3);
}

TEST(multiset, empty) {
  s21::multiset<int> a1 = {1, 2, 3};
  EXPECT_EQ(a1.empty(), false);
  a1.clear();
  EXPECT_EQ(a1.empty(), true);
}

TEST(multiset, swap) {
  s21::multiset<int> a1 = {1, 2, 3};
  s21::multiset<int> a2 = {4, 5, 6, 55};
  a1.swap(a2);
  s21::multiset<int>::iterator it1 = a1.begin();
  s21::multiset<int>::iterator it2 = a2.begin();
  EXPECT_EQ(4, *it1++);
  EXPECT_EQ(*it1++, 5);
  EXPECT_EQ(*it1++, 6);
  EXPECT_EQ(*it1++, 55);
  EXPECT_EQ(*it2++, 1);
  EXPECT_EQ(*it2++, 2);
  EXPECT_EQ(*it2++, 3);
  EXPECT_EQ(static_cast<int>(a2.size()), 3);
  EXPECT_EQ(static_cast<int>(a1.size()), 4);
}

TEST(multiset, multiset) {
  s21::multiset<std::string> a1({"1", "2", "3"});
  s21::multiset<std::string>::iterator it1 = a1.begin();
  EXPECT_EQ("1", *it1++);
  EXPECT_EQ("2", *it1++);
  EXPECT_EQ("3", *it1);
}

TEST(multiset, multiset3) {
  s21::multiset<std::string> a({"c", "cc", "ccc"});
  s21::multiset<std::string> a1(a);
  s21::multiset<std::string>::iterator it1 = a1.begin();

  EXPECT_EQ(3, static_cast<int>(a1.size()));
  EXPECT_EQ("c", *it1++);
  EXPECT_EQ("cc", *it1++);
  EXPECT_EQ("ccc", *it1);
}

TEST(multiset, multiset4) {
  s21::multiset<std::string> a({"c", "cc", "ccc"});
  s21::multiset<std::string> a1(a.begin(), a.end());
  s21::multiset<std::string>::iterator it1 = a1.begin();
  EXPECT_EQ(3, static_cast<int>(a1.size()));
  EXPECT_EQ("c", *it1++);
  EXPECT_EQ("cc", *it1++);
  EXPECT_EQ("ccc", *it1);
}

TEST(multiset, operator) {
  s21::multiset<std::string> a = {"1", "2", "3"};
  s21::multiset<std::string> a1 = {"1", "2", "3"};
  EXPECT_EQ(true, a == a1);
  EXPECT_EQ(false, a != a1);
  EXPECT_EQ(false, a < a1);
  EXPECT_EQ(true, a <= a1);
  EXPECT_EQ(true, a >= a1);
  EXPECT_EQ(false, a > a1);
}

TEST(multiset, operator1) {
  s21::multiset<std::string> a = {"1", "2", "3"};
  s21::multiset<std::string> a1 = {"1", "2", "3", "4"};
  EXPECT_EQ(false, a == a1);
  EXPECT_EQ(true, a != a1);
  EXPECT_EQ(true, a < a1);
  EXPECT_EQ(true, a <= a1);
  EXPECT_EQ(false, a >= a1);
  EXPECT_EQ(false, a > a1);
}

TEST(multiset, operator2) {
  s21::multiset<std::string> a = {"1", "4", "3"};
  s21::multiset<std::string> a1 = {"1", "2", "3", "4"};
  EXPECT_EQ(false, a == a1);
  EXPECT_EQ(true, a != a1);
  EXPECT_EQ(false, a < a1);
  EXPECT_EQ(false, a <= a1);
  EXPECT_EQ(true, a >= a1);
  EXPECT_EQ(true, a > a1);
}

TEST(multiset, operator3) {
  s21::multiset<std::string> a = {"1", "4", "3"};
  s21::multiset<std::string> a1 = {"1", "2", "3", "4"};
  a = a1;
  EXPECT_EQ(true, a == a1);
  EXPECT_EQ(false, a != a1);
  EXPECT_EQ(false, a < a1);
  EXPECT_EQ(true, a <= a1);
  EXPECT_EQ(true, a >= a1);
  EXPECT_EQ(false, a > a1);
}

TEST(multiset, emplace) {
  s21::multiset<std::string> a = {"1"};
  s21::multiset<std::string> a1 = {"1", "2", "3", "4"};
  a.emplace("2", "3", "4");
  EXPECT_EQ(true, a == a1);
  EXPECT_EQ(false, a != a1);
  EXPECT_EQ(false, a < a1);
  EXPECT_EQ(true, a <= a1);
  EXPECT_EQ(true, a >= a1);
  EXPECT_EQ(false, a > a1);

  s21::multiset<std::string> a2;
  s21::multiset<std::string> a3 = {"2", "3", "4"};

  a2.emplace("2", "3", "4");
  EXPECT_EQ(true, a3 == a2);
  a2.emplace("2", "3", "4");
  s21::multiset<std::string> a6 = {"2", "3", "4", "2", "3", "4"};
  EXPECT_EQ(true, a6 == a2);
  a2.emplace("1", "12", "13");
  s21::multiset<std::string> a4 = {"2", "3", "4",  "2", "3",
                                   "4", "1", "12", "13"};
  EXPECT_EQ(true, a4 == a2);
  a2.clear();
  a2.emplace("2", "3", "4", "11", "12", "14", "112");
  s21::multiset<std::string> a5 = {"2", "3", "4", "11", "12", "14", "112"};
  EXPECT_EQ(true, a5 == a2);
}

TEST(multiset, lower_bound) {
  s21::multiset<int> a1 = {1, 2, 4, 5, 6, 55};
  s21::multiset<int>::iterator it1 = a1.lower_bound(8);
  EXPECT_EQ(55, *it1);
  it1 = a1.lower_bound(4);
  EXPECT_EQ(4, *it1);
  it1 = a1.lower_bound(3);
  EXPECT_EQ(4, *it1);
}

TEST(multiset, upper_bound) {
  s21::multiset<int> a1 = {1, 2, 4, 5, 6, 55};
  s21::multiset<int>::iterator it1 = a1.upper_bound(8);
  EXPECT_EQ(55, *it1);
  it1 = a1.upper_bound(4);
  EXPECT_EQ(5, *it1);
  it1 = a1.upper_bound(3);
  EXPECT_EQ(4, *it1);
}

TEST(multiset, equal_range) {
  s21::multiset<int> a1 = {1, 2, 4, 5, 6, 55};
  std::pair<s21::multiset<int>::iterator, s21::multiset<int>::iterator> it1 =
      a1.equal_range(8);
  EXPECT_EQ(55, *it1.first);
  EXPECT_EQ(55, *it1.second);
  it1 = a1.equal_range(4);
  EXPECT_EQ(4, *it1.first);
  EXPECT_EQ(5, *it1.second);
  it1 = a1.equal_range(3);
  EXPECT_EQ(4, *it1.first);
  EXPECT_EQ(4, *it1.second);
}

TEST(multiset, find) {
  s21::multiset<int> a1 = {1, 2, 4, 5, 6, 55};
  s21::multiset<int>::iterator it1 = a1.find(6);
  EXPECT_EQ(6, *it1);
  it1 = a1.find(4);
  EXPECT_EQ(4, *it1);
}

TEST(multiset, contains) {
  s21::multiset<int> a1 = {1, 2, 4, 5, 6, 55, 55, 55};
  EXPECT_EQ(true, a1.contains(4));
  EXPECT_EQ(false, a1.contains(42));
  EXPECT_EQ(true, a1.contains(55));
}

TEST(multiset, count) {
  s21::multiset<int> a1 = {1, 2, 4, 5, 6, 55, 6, 6, 66, 4};
  EXPECT_EQ(3, static_cast<int>(static_cast<int>(a1.count(6))));
  EXPECT_EQ(2, static_cast<int>(a1.count(4)));
  EXPECT_EQ(0, static_cast<int>(a1.count(3)));
  EXPECT_EQ(0, static_cast<int>(a1.count(123)));
  EXPECT_EQ(1, static_cast<int>(a1.count(66)));
}

TEST(multiset, test_greater) {
  s21::multiset<std::string, std::greater<std::string>> a1 = {"1", "2", "3"};
  s21::multiset<std::string, std::greater<std::string>> a = {"12", "22", "32"};
  a1 = a;

  EXPECT_EQ(true, a == a1);
  EXPECT_EQ(false, a != a1);
  EXPECT_EQ(false, a < a1);
  EXPECT_EQ(true, a <= a1);
  EXPECT_EQ(true, a >= a1);
  EXPECT_EQ(false, a > a1);
}

TEST(multiset, iterator_greater) {
  s21::multiset<int, std::greater<int>> a1 = {2, 3, 1};
  s21::multiset<int, std::greater<int>>::iterator it = a1.begin();
  s21::multiset<int, std::greater<int>>::iterator it1 = a1.begin();
  EXPECT_EQ(3, *it++);
  EXPECT_EQ(1, *++it);
  EXPECT_EQ(2, *--it);
  EXPECT_EQ(2, *it--);
  EXPECT_EQ(3, *it++);
  EXPECT_EQ(2, *it);
  EXPECT_EQ(true, it != it1);
  EXPECT_EQ(true, --it == it1);
}

TEST(multiset, erase_greater) {
  s21::multiset<int, std::greater<int>> a1 = {
      3123, 12, 23123, 312, 31, 2313, 213, 1, 64, 456, 45, 37, 8};
  a1.erase(a1.find(312));
  a1.erase(a1.find(31));
  a1.erase(a1.find(37));
  a1.erase(a1.find(12));
  a1.erase(a1.find(1));
  a1.erase(a1.find(8));

  std::multiset<int, std::greater<int>> a2 = {
      3123, 12, 23123, 312, 31, 2313, 213, 1, 64, 456, 45, 37, 8};
  a2.erase(a2.find(312));
  a2.erase(a2.find(31));
  a2.erase(a2.find(37));
  a2.erase(a2.find(12));
  a2.erase(a2.find(1));
  a2.erase(a2.find(8));

  EXPECT_EQ(0, Comparison(a1, a2));
}

TEST(multiset, clear_greater) {
  s21::multiset<int, std::greater<int>> a1 = {1, 2, 3};
  a1.clear();
  EXPECT_EQ(static_cast<int>(a1.size()), 0);
}

TEST(multiset, insert_greater) {
  s21::multiset<int, std::greater<int>> a1 = {1, 2, 3};
  s21::multiset<int, std::greater<int>>::iterator it1 = a1.begin();
  s21::multiset<int, std::greater<int>>::iterator pa = a1.insert(33);
  EXPECT_EQ(33, *pa);
  pa = a1.insert(22);
  EXPECT_EQ(22, *pa);
  it1 = a1.begin();
  EXPECT_EQ(33, *it1++);
  EXPECT_EQ(22, *it1++);
  EXPECT_EQ(3, *it1++);
  EXPECT_EQ(2, *it1++);
  EXPECT_EQ(1, *it1++);
  pa = a1.insert(88);
  EXPECT_EQ(88, *pa);
  EXPECT_EQ(6, static_cast<int>(a1.size()));
}

TEST(multiset, begin_greater) {
  s21::multiset<int, std::greater<int>> a1 = {1, 2, 3};
  s21::multiset<int, std::greater<int>>::iterator it = a1.begin();
  EXPECT_EQ(3, *it);
}

TEST(multiset, end_greater) {
  s21::multiset<int, std::greater<int>> a1 = {1, 2, 3};
  s21::multiset<int, std::greater<int>>::iterator it = a1.end();
  EXPECT_EQ(1, *--it);
}

TEST(multiset, size_greater) {
  s21::multiset<int, std::greater<int>> a1 = {1, 2, 3};
  EXPECT_EQ(static_cast<int>(a1.size()), 3);
}

TEST(multiset, empty_greater) {
  s21::multiset<int, std::greater<int>> a1 = {1, 2, 3};
  EXPECT_EQ(a1.empty(), false);
  a1.clear();
  EXPECT_EQ(a1.empty(), true);
}

TEST(multiset, swap_greater) {
  s21::multiset<int, std::greater<int>> a1 = {1, 2, 3};
  s21::multiset<int, std::greater<int>> a2 = {4, 5, 6, 55};
  a1.swap(a2);
  s21::multiset<int, std::greater<int>>::iterator it1 = a1.begin();
  s21::multiset<int, std::greater<int>>::iterator it2 = a2.begin();
  EXPECT_EQ(55, *it1++);
  EXPECT_EQ(*it1++, 6);
  EXPECT_EQ(*it1++, 5);
  EXPECT_EQ(*it1++, 4);
  EXPECT_EQ(*it2++, 3);
  EXPECT_EQ(*it2++, 2);
  EXPECT_EQ(*it2++, 1);
  EXPECT_EQ(static_cast<int>(a2.size()), 3);
  EXPECT_EQ(static_cast<int>(a1.size()), 4);
}

TEST(multiset, multiset_greater) {
  s21::multiset<int, std::greater<int>> a1({1, 2, 3});
  s21::multiset<int, std::greater<int>>::iterator it1 = a1.begin();
  EXPECT_EQ(3, *it1++);
  EXPECT_EQ(2, *it1++);
  EXPECT_EQ(1, *it1);
}

TEST(multiset, multiset3_greater) {
  s21::multiset<int, std::greater<int>> a({3, 2, 1});
  s21::multiset<int, std::greater<int>> a1(a);
  s21::multiset<int, std::greater<int>>::iterator it1 = a1.begin();

  EXPECT_EQ(3, static_cast<int>(a1.size()));
  EXPECT_EQ(3, *it1++);
  EXPECT_EQ(2, *it1++);
  EXPECT_EQ(1, *it1);
}

TEST(multiset, multiset4_greater) {
  s21::multiset<int, std::greater<int>> a({3, 2, 1});
  s21::multiset<int, std::greater<int>> a1(a.begin(), a.end());
  s21::multiset<int, std::greater<int>>::iterator it1 = a1.begin();
  EXPECT_EQ(3, static_cast<int>(a1.size()));
  EXPECT_EQ(3, *it1++);
  EXPECT_EQ(2, *it1++);
  EXPECT_EQ(1, *it1);
}

TEST(multiset, operator_greater) {
  s21::multiset<int, std::greater<int>> a = {1, 2, 3};
  s21::multiset<int, std::greater<int>> a1 = {1, 2, 3};
  EXPECT_EQ(true, a == a1);
  EXPECT_EQ(false, a != a1);
  EXPECT_EQ(false, a < a1);
  EXPECT_EQ(true, a <= a1);
  EXPECT_EQ(true, a >= a1);
  EXPECT_EQ(false, a > a1);
}

TEST(multiset, operator1_greater) {
  s21::multiset<int, std::greater<int>> a = {1, 2, 3};
  s21::multiset<int, std::greater<int>> a1 = {1, 2, 3, 4};
  EXPECT_EQ(false, a == a1);
  EXPECT_EQ(true, a != a1);
  EXPECT_EQ(true, a < a1);
  EXPECT_EQ(true, a <= a1);
  EXPECT_EQ(false, a >= a1);
  EXPECT_EQ(false, a > a1);
}

TEST(multiset, operator2_greater) {
  s21::multiset<int, std::greater<int>> a = {1, 5, 3};
  s21::multiset<int, std::greater<int>> a1 = {1, 2, 3, 4};
  EXPECT_EQ(false, a == a1);
  EXPECT_EQ(true, a != a1);
  EXPECT_EQ(false, a < a1);
  EXPECT_EQ(false, a <= a1);
  EXPECT_EQ(true, a >= a1);
  EXPECT_EQ(true, a > a1);
}

TEST(multiset, operator3_greater) {
  s21::multiset<int, std::greater<int>> a = {1, 4, 3};
  s21::multiset<int, std::greater<int>> a1 = {1, 2, 3, 4};
  a = a1;
  EXPECT_EQ(true, a == a1);
  EXPECT_EQ(false, a != a1);
  EXPECT_EQ(false, a < a1);
  EXPECT_EQ(true, a <= a1);
  EXPECT_EQ(true, a >= a1);
  EXPECT_EQ(false, a > a1);
}

TEST(multiset, emplace_greater) {
  s21::multiset<int, std::greater<int>> a = {1};
  s21::multiset<int, std::greater<int>> a1 = {1, 2, 3, 4};
  a.emplace(2, 3, 4);
  EXPECT_EQ(true, a == a1);
  EXPECT_EQ(false, a != a1);
  EXPECT_EQ(false, a < a1);
  EXPECT_EQ(true, a <= a1);
  EXPECT_EQ(true, a >= a1);
  EXPECT_EQ(false, a > a1);
}

TEST(multiset, lower_bound_greater) {
  s21::multiset<int, std::greater<int>> a1 = {1, 2, 4, 5, 6, 55};
  s21::multiset<int, std::greater<int>>::iterator it1 = a1.lower_bound(8);
  EXPECT_EQ(6, *it1);
  it1 = a1.lower_bound(4);
  EXPECT_EQ(4, *it1);
  it1 = a1.lower_bound(3);
  EXPECT_EQ(2, *it1);
}

TEST(multiset, upper_bound_greater) {
  s21::multiset<int, std::greater<int>> a1 = {1, 2, 4, 5, 6, 55};
  s21::multiset<int, std::greater<int>>::iterator it1 = a1.upper_bound(8);
  EXPECT_EQ(6, *it1);
  it1 = a1.upper_bound(4);
  EXPECT_EQ(2, *it1);
  it1 = a1.upper_bound(3);
  EXPECT_EQ(2, *it1);
}

TEST(multiset, equal_range_greater) {
  s21::multiset<int, std::greater<int>> a1 = {1, 2, 4, 5, 6, 55};
  std::pair<s21::multiset<int, std::greater<int>>::iterator,
            s21::multiset<int, std::greater<int>>::iterator>
      it1 = a1.equal_range(8);
  EXPECT_EQ(6, *it1.first);
  EXPECT_EQ(6, *it1.second);
  it1 = a1.equal_range(4);
  EXPECT_EQ(4, *it1.first);
  EXPECT_EQ(2, *it1.second);
  it1 = a1.equal_range(3);
  EXPECT_EQ(2, *it1.first);
  EXPECT_EQ(2, *it1.second);
}

TEST(multiset, find_greater) {
  s21::multiset<int, std::greater<int>> a1 = {1, 2, 4, 5, 6, 55};
  s21::multiset<int, std::greater<int>>::iterator it1 = a1.find(6);
  EXPECT_EQ(6, *it1);
  it1 = a1.find(4);
  EXPECT_EQ(4, *it1);
}

TEST(multiset, count_greater) {
  s21::multiset<int, std::greater<int>> a1 = {1, 2, 4, 5, 6, 55, 6};
  EXPECT_EQ(2, static_cast<int>(static_cast<int>(a1.count(6))));
  EXPECT_EQ(1, static_cast<int>(a1.count(4)));
  EXPECT_EQ(0, static_cast<int>(a1.count(3)));
}

TEST(array, swap) {
  s21::array<int, 3> a1 = {1, 2, 3};
  s21::array<int, 3> a2 = {4, 5, 6};
  a1.swap(a2);
  EXPECT_EQ(a1[0], 4);
  EXPECT_EQ(a1[1], 5);
  EXPECT_EQ(a1[2], 6);
  EXPECT_EQ(a2[0], 1);
  EXPECT_EQ(a2[1], 2);
  EXPECT_EQ(a2[2], 3);
}

TEST(array, operator) {
  s21::array<std::string, 3> a1 = {"1", "2", "3"};
  EXPECT_EQ(a1[0], "1");
  EXPECT_EQ(a1[1], "2");
  EXPECT_EQ(a1[2], "3");
}

TEST(array, operator1) {
  const s21::array<std::string, 3> a1 = {"1", "2", "3"};
  EXPECT_EQ(a1[0], "1");
  EXPECT_EQ(a1[1], "2");
  EXPECT_EQ(a1[2], "3");
}

TEST(array, size) {
  s21::array<int, 3> a1 = {1, 2, 3};
  EXPECT_EQ(static_cast<int>(a1.size()), 3);
}

TEST(array, fill) {
  s21::array<std::string, 3> a1 = {"1", "2", "3"};
  a1.fill("5");
  EXPECT_EQ(a1[0], "5");
  EXPECT_EQ(a1[1], "5");
  EXPECT_EQ(a1[2], "5");
}

TEST(array, empty) {
  s21::array<int, 15> a1 = {1, 3, 34, 5, 6, 4};
  s21::array<int, 0> a2;
  EXPECT_EQ(a1.empty(), false);
  EXPECT_EQ(a2.empty(), true);
}

TEST(array, data) {
  s21::array<int, 3> a1 = {1, 2, 3};
  int *a = a1.data();
  EXPECT_EQ(*a, 1);
}

TEST(array, data_const) {
  const s21::array<int, 3> a1 = {1, 2, 3};
  const int *a = a1.data();
  EXPECT_EQ(*a, 1);
}

TEST(array, front) {
  s21::array<int, 3> a1 = {1, 2, 3};
  int a = a1.front();
  EXPECT_EQ(a, 1);
  const s21::array<int, 3> a2 = {444, 2, 3};
  const int a3 = a2.front();
  EXPECT_EQ(a3, 444);
}

TEST(array, back) {
  s21::array<int, 3> a1 = {1, 2, 3};
  int a = a1.back();
  EXPECT_EQ(a, 3);
  s21::array<int, 3> a2 = {444, 2, 123};
  a = a2.back();
  EXPECT_EQ(a, 123);
}

TEST(array, back_const) {
  const s21::array<int, 3> a1 = {1, 2, 3};
  int a = a1.back();
  EXPECT_EQ(a, 3);
  const s21::array<int, 3> a2 = {444, 2, 123};
  a = a2.back();
  EXPECT_EQ(a, 123);
}

TEST(array, at) {
  s21::array<int, 3> a1 = {1, 2, 3};
  int a = a1.at(1);
  EXPECT_EQ(a, 2);
  EXPECT_THROW(a1.at(55), std::out_of_range);
}

TEST(array, at_const) {
  const s21::array<int, 3> a1 = {1, 2, 3};
  int a = a1.at(1);
  EXPECT_EQ(a, 2);
}

TEST(array, begin) {
  s21::array<int, 3> a1 = {1, 2, 3};
  s21::array<int, 3>::iterator it = a1.begin();
  EXPECT_EQ(1, *it);
}

TEST(array, cbegin) {
  s21::array<int, 3> a1 = {1, 2, 3};
  s21::array<int, 3>::const_iterator it = a1.cbegin();
  EXPECT_EQ(1, *it);
}

TEST(array, end) {
  s21::array<std::string, 3> a1 = {"1", "2", "3"};
  s21::array<std::string, 3>::iterator it = a1.end();
  EXPECT_EQ("3", *--it);
}

TEST(array, cend) {
  s21::array<std::string, 3> a = {"1", "2", "3"};
  s21::array<std::string, 3> a1(a);
  s21::array<std::string, 3>::const_iterator it = a1.cend();
  EXPECT_EQ("3", *--it);
  const s21::array<std::string, 3> a2 = {"1", "2", "3"};
  s21::array<std::string, 3>::const_iterator it1 = a2.end();
  EXPECT_EQ("3", *--it1);
}

TEST(array, test_iq) {
  s21::array<std::string, 3> a1 = {"1", "2", "3"};
  s21::array<std::string, 3> a2 = {"12", "22", "32"};
  a1 = a2;
  EXPECT_EQ("12", a1[0]);
  EXPECT_EQ("22", a1[1]);
  EXPECT_EQ("32", a1[2]);
  EXPECT_EQ("12", a2[0]);
  EXPECT_EQ("22", a2[1]);
  EXPECT_EQ("32", a2[2]);
}

TEST(array, move) {
  s21::array<std::string, 3> a1 = {"1", "2", "3"};
  s21::array<std::string, 3> a2(std::move(a1));
  EXPECT_EQ("1", a2[0]);
  EXPECT_EQ("2", a2[1]);
  EXPECT_EQ("3", a2[2]);

  s21::array<std::string, 3> a3 = {"131", "1232", "3131"};
  a3 = std::move(a2);
  EXPECT_EQ("1", a3[0]);
  EXPECT_EQ("2", a3[1]);
  EXPECT_EQ("3", a3[2]);
}

TEST(array, iterator) {
  s21::array<std::string, 3> a1 = {"1", "2", "3"};
  s21::array<std::string, 3>::iterator it = a1.begin();
  s21::array<std::string, 3>::iterator it1 = a1.begin();
  EXPECT_EQ("1", *it++);
  EXPECT_EQ("3", *++it);
  EXPECT_EQ("2", *--it);
  EXPECT_EQ("2", *it--);
  EXPECT_EQ("1", *it++);
  EXPECT_EQ("2", *it);
  EXPECT_EQ(true, it != it1);
  EXPECT_EQ(true, --it == it1);
}

TEST(array, const_iterator) {
  const s21::array<std::string, 3> a1 = {"1", "2", "3"};
  s21::array<std::string, 3>::const_iterator it1 = a1.begin();
  EXPECT_EQ("2", *++it1);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}