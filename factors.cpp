#include <set>
#include <map>
#include <cmath>
#include "factors.hpp"

// Find the factors of n
// Complexity is sqrt(n)
std::set<int> factors(int n) {

  n = std::abs(n);

  static std::map<int, std::set<int>> facts;
  if (facts.find(n) != facts.end())
    return facts[n];

  std::set<int> res;
  for (int i = 1; i <= (int) std::sqrt(n); i++) {
    if (n % i == 0 && i % 2 == (n / i) % 2) {
      // res.insert(i);
      res.insert(n / i);
      res.insert(-i);
      // res.insert(-n / i);
    }
  }
  facts[n] = res;
  return res;
}
