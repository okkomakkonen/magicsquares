#include <iostream> // std::cout, std::endl
#include <cmath> // std::sqrt
#include <set> // std::set
#include <ctime> // std::time
#include <map> // std::map
#include <string> // std::string

#define MAX 10000

// Find the factors of n
// Complexity is sqrt(n)
std::set<int> factors(int n) {
  std::set<int> res;
  for (int i = 1; i <= (int) std::sqrt(n); i++) {
    if (n % i == 0) {
      res.insert(i);
      res.insert(n / i);
      res.insert(-i);
      res.insert(-n / i);
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

  // log("Calculating factors");

  // Precompute all factors of numbers of form x * y for x, y in [-2N, 2N]
  // std::map<int, std::set<int>> facts;
  // for (int x = 2; x <= MAX*MAX/2 + MAX; x++) {
  //   for (int y = -2*MAX; y <= MAX*MAX/2; y++) {
  //     facts.insert({x*y, })
  //   }
  // }

  // Precompute all factors of numbers in [1, 4*MAX**2] in MAX**3 time
  // std::map<int, std::set<int>> facts;
  // for (int x = 1; x < 4 * MAX * MAX; x++) {
  //   facts.insert({x, factors(x)});
  // }

  log("Finding magic squares");

  int a, b, c, d, e, f, g, h, i, k, x, y;

  std::map<int, std::set<int>> facts;

  std::set<int> sq; // Set of all numbers in the magic square

  for (b = 1; b <= MAX; b++) { // b loop
    sq.insert(b);
    for (d = 1; d <= MAX; d++) { // d loop
      if (sq.find(d) != sq.end()) continue;
      sq.insert(d);

      if (facts.find((b+d)*(b-d)) == facts.end())
        facts.insert({(b+d)*(b-d), factors(b+d, b-d)});

      for (auto x : facts[(b+d)*(b-d)]) { // factors loop, facts[(b+d)*(b-d)]
        if (x % 2 != (b+d)*(b-d) / x % 2 || x <= (b+d)*(b-d) / x) // invalid factor
          continue;
        g = (x + (b+d)*(b-d) / x) / 2;
        c = (x - (b+d)*(b-d) / x) / 2;
        if (sq.find(c) != sq.end() || sq.find(g) != sq.end() || c <= 0 || g <= 0) // duplicates
          continue;
        sq.insert(c);
        sq.insert(g);
        // Now we have b, c, d, g, (a + e)(a - e) = (g + c)(g - c)

        if (facts.find((g+b)*(g-b)) == facts.end())
          facts.insert({(g+b)*(g-b), factors(g+b, g-b)});

        for (auto y : facts[(g+b)*(g-b)]) { // factors loop, facts[(g+b)*(g-b)]
          if (y % 2 != (g+b)*(g-b) / y % 2 || y <= (g+b)*(g-b) / y) // invalid factor
            continue;
          a = (y + (g+b)*(g-b) / y) / 2;
          e = (y - (g+b)*(g-b) / y) / 2;
          if (sq.find(a) != sq.end() || sq.find(e) != sq.end() || e <= 0 || a <= 0) // duplicates
            continue;
          sq.insert(a);
          sq.insert(e);

          // Now we have a, b, c, d, e, g so we just solve the square
          k = a * a + b * b + c * c;
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
          if (a * a + e * e + i * i != k) // descending diagonal
            continue;

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

  return 0;

}
