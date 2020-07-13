#include <iostream>   // std::cout, std::endl
#include <cmath>      // std::sqrt
#include <set>        // std::set
#include <ctime>      // std::time
#include <map>        // std::map
#include <string>     // std::string

#define MAX 300

// Find the factors of n
// Complexity is sqrt(n)
std::set<int> factors(int n) {
  std::set<int> res;
  if (n < 0) {
    res.insert(-1);
    n *= -1;
  }
  for (int i = 1; i <= (int) std::sqrt(n); i++) {
    if (n % i == 0) {
      res.insert(i);
      res.insert(n / i);
    }
  }
  return res;
}

// Find the factors of n * m
// Complexity is log(n)*log(m) + sqrt(n) + sqrt(m)
std::set<int> factors(int n, int m) {
  std::set<int> res;
  for (auto i : factors(n)) {
    for (auto j : factors(m)) {
      res.insert(i * j);
    }
  }
  return res;
}

// Calculate the square root if it is an integer, else return zero
int inv(int candidate) {
  if (candidate < 0) return 0;
  int test = std::sqrt(candidate);
  if (test * test == candidate)
    return test;
  return 0;
}

void log(std::string message) {
  std::time_t result = std::time(nullptr); // Current time
  std::cout << std::asctime(std::localtime(&result));
  std::cout << message << std::endl;
  std::cout << std::endl;
}

void log_magic_square(int a, int b, int c,
  int d, int e, int f, int g,
  int h, int i, int k, bool diagonal=false) {
    std::time_t result = std::time(nullptr); // Current time
    std::cout << std::asctime(std::localtime(&result));
    std::cout << "Magic square of squares k = " << k << std::endl;
    if (diagonal)
      std::cout << "Working diagonal" << std::endl;
    std::cout << a << " " << b << " " << c << std::endl;
    std::cout << d << " " << e << " " << f << std::endl;
    std::cout << g << " " << h << " " << i << std::endl;
    std::cout << std::endl;
  }

int main() {
  int count = 0;
  // log("Calculating factors");
  //
  // // Precompute all factors of numbers in [1, 4*MAX**2] in MAX**3 time
  // std::map<int, std::set<int>> facts;
  // for (int x = 1; x < 4 * MAX * MAX; x++) {
  //   facts.insert({x, factors(x)});
  // }

  log("Finding magic squares");

  int a, b, c, d, e, f, g, h, i, k, x, y;

  std::set<int> sq; // Set of all numbers in the magic square

  for (b = 1; b <= MAX; b++) { // b loop
    sq.insert(b);
    for (d = 1; d <= MAX; d++) { // d loop
      if (sq.find(d) != sq.end()) continue;
      sq.insert(d);
      x = b + d;
      y = b - d;

      for (auto z : factors(x, y)) { // factors loop
        if (z % 2 != x * y / z % 2 || z <= x * y / z)
          continue;
        g = (z + x * y / z) / 2;
        c = (z - x * y / z) / 2;
        if (sq.find(c) != sq.end() || sq.find(g) != sq.end() || c <= 0 || g < 0)
          continue;
        sq.insert(c);
        sq.insert(g);

        for (a = 1; a <= MAX; a++) { // a loop
          count++;
          if (sq.find(a) != sq.end()) continue;
          k = a * a + b * b + c * c;
          if (a * a + d * d + g * g != k) {
            std::cout << "Some error has happened in the arithmetic" << std::endl;
            continue;
          }
          sq.insert(a);
          // Now we can solve it to the end, since we have a, b, c, d and g
          e = inv(k - g * g - c * c);
          if (e == 0 || sq.find(e) != sq.end()) {
            sq.erase(a);
            continue;
          }
          sq.insert(e);
          f = inv(k - d * d - e * e);
          if (f == 0 || sq.find(f) != sq.end()) {
            sq.erase(a);
            sq.erase(e);
            continue;
          }
          sq.insert(f);
          h = inv(k - b * b - e * e);
          if (h == 0 || sq.find(h) != sq.end()) {
            sq.erase(a);
            sq.erase(e);
            sq.erase(f);
            continue;
          }
          sq.insert(h);
          i = inv(k - c * c - f * f);
          if (i == 0 || sq.find(i) != sq.end()) {
            sq.erase(a);
            sq.erase(e);
            sq.erase(f);
            sq.erase(h);
            continue;
          }
          // All elements are unique
          sq.erase(a);
          sq.erase(e);
          sq.erase(f);
          sq.erase(h);
          if (g * g + h * h + i * i != k) // bottom row
            continue;
          // if (a * a + e * e + i * i != k) // descending diagonal
          //   continue;

          // log_magic_square(a, b, c, d, e, f, g, h, i, k, a * a + e * e + i * i == k);
          log_magic_square(a, b, c, d, e, f, g, h, i, k);
        }
        sq.erase(c);
        sq.erase(g);
      }
      sq.erase(d);
    }
    sq.erase(b);
    // Check that the square set is empty
    if (sq.size()) std::cout << "All elements were not deleted from the square" << std::endl;
  }

  log("Ending");

  std::cout << count << std::endl;

  return 0;

}
