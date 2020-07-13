#include <iostream>
#include <unordered_set>
#include <list>
#include <vector>
#include <forward_list>
#include <deque>
#include <cmath>
#include <chrono>
#define MAX 2000

class Timer {
public:
  Timer() {
    start_ = std::chrono::steady_clock::now();
  }

  void reset() {
    start_ = std::chrono::steady_clock::now();
  }

  double elapsed() {
    auto end = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start_).count();
  }

private:
  std::chrono::steady_clock::time_point start_;
};

template <typename container>
container factors(int n) {
  container res;
  for (int i = 1; i < (int) std::sqrt(n); i++) {
    if (n % i == 0 && i % 2 == (n / i) % 2) {
      res.push_back(n / i);
    }
  }
  return res;
}

template <>
std::forward_list<int> factors(int n) {
  std::forward_list<int> res;
  for (int i = 1; i < (int) std::sqrt(n); i++) {
    if (n % i == 0 && i % 2 == (n / i) % 2) {
      res.push_front(n / i);
    }
  }
  return res;
}

template <>
std::unordered_set<int> factors(int n) {
  std::unordered_set<int> res;
  for (int i = 1; i < (int) std::sqrt(n); i++) {
    if (n % i == 0 && i % 2 == (n / i) % 2) {
      res.insert(n / i);
    }
  }
  return res;
}

int main() {

  auto tmr = Timer();

  std::list<int> list;

  for (int a = 1; a <= MAX; a++) {
    for (int b = 1; b <= MAX; b++) {
      list = factors<std::list<int>>(a*b);
    }
  }

  std::cout << "List method took " << tmr.elapsed() << "ms" << std::endl;

  tmr.reset();

  std::vector<int> vector;

  for (int a = 1; a <= MAX; a++) {
    for (int b = 1; b <= MAX; b++) {
      vector = factors<std::vector<int>>(a*b);
    }
  }

  std::cout << "Vector method took " << tmr.elapsed() << "ms" << std::endl;

  tmr.reset();

  std::deque<int> deque;

  for (int a = 1; a <= MAX; a++) {
    for (int b = 1; b <= MAX; b++) {
      deque = factors<std::deque<int>>(a*b);
    }
  }

  std::cout << "Deque method took " << tmr.elapsed() << "ms" << std::endl;

  tmr.reset();

  std::forward_list<int> flist;

  for (int a = 1; a <= MAX; a++) {
    for (int b = 1; b <= MAX; b++) {
      flist = factors<std::forward_list<int>>(a*b);
    }
  }

  std::cout << "Forward list method took " << tmr.elapsed() << "ms" << std::endl;

  tmr.reset();

  std::unordered_set<int> uset;

  for (int a = 1; a <= MAX; a++) {
    for (int b = 1; b <= MAX; b++) {
      uset = factors<std::unordered_set<int>>(a*b);
    }
  }

  std::cout << "Unordered set method took " << tmr.elapsed() << "ms" << std::endl;

  tmr.reset();

  long long count = 0;

  for (int a = 1; a <= MAX; a++) {
    for (int b = 1; b <= MAX; b++) {
      for (int i = 1; i < (int) std::sqrt(a*b); i++) {
        if (a*b % i == 0 && i % 2 == (a*b / i) % 2) {
          count++;
        }
      }
    }
  }

  std::cout << "No container method took " << tmr.elapsed() << "ms" << std::endl;

  return 0;

}
