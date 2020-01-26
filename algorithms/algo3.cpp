#include <iostream>   // std::cout, std::endl
#include <cmath>      // std::sqrt
#include <set>        // std::set
#include <ctime>      // std::time
#include <map>        // std::map
#include <string>     // std::string
#include <map>        // std::map

#define MAX 300

// Find those factors i of n that n / i and i have the same parity
std::set<int> factors(int n) {

  n = std::abs(n);

  static std::map<int, std::set<int>> facts;
  if (facts.find(n) != facts.end())
    return facts[n];

  std::set<int> res;
  for (int i = 1; i <= (int) std::sqrt(n); i++) {
    if (n % i == 0 && i % 2 == (n / i) % 2) {
      res.insert(i);
      res.insert(n / i);
      res.insert(-i);
      res.insert(-n / i);
    }
  }
  facts[n] = res;
  return res;
}

// Calculate the square root if it is an integer, else return zero
int inv(int n) {
  if (n < 0) return 0;
  int r = std::sqrt(n);
  if (r * r == n)
    return r;
  return 0;
}

// Log a string to std::cout with a timestamp
void log(std::string message) {
  std::time_t result = std::time(nullptr); // Current time
  std::cout << std::asctime(std::localtime(&result));
  std::cout << message << std::endl;
  std::cout << std::endl;
}

// Log a magic square to std::cout with a timestamp
void log(int a, int b, int c,
  int d, int e, int f, int g,
  int h, int i, int k) {
    std::time_t result = std::time(nullptr); // Current time
    std::cout << std::asctime(std::localtime(&result));
    std::cout << "Magic square of squares k = " << k << std::endl;
    std::cout << a << " " << b << " " << c << std::endl;
    std::cout << d << " " << e << " " << f << std::endl;
    std::cout << g << " " << h << " " << i << std::endl;
    if (a * a + e * e + i * i == k)
      std::cout << "WORKING MAGIC SQUARE OF SQUARES" << std::endl;
    std::cout << std::endl;
}

bool check_magic_square(int a, int b, int c,
  int d, int e, int f, int g,
  int h, int i) {
    int k = a * a + b * b + c * c; // top row
    if (d * d + e * e + f * f != k) // middle row
      return false;
    if (g * g + h * h + i * i != k) // bottom row
      return false;
    if (a * a + d * d + g * g != k) // left column
      return false;
    if (b * b + e * e + h * h != k) // middle column
      return false;
    if (c * c + f * f + i * i != k) // right column
      return false;
    if (a * a + e * e + i * i != k) // descending diagonal
      return false;
    if (g * g + e * e + c * c != k) // ascending diagonal
      return false;
    return true;
}

int main() {

  int count = 0;

  log("Finding magic squares");

  int a, b, c, d, e, f, g, h, i, k, x, y;

  std::set<int> sq; // Set of all numbers in the magic square

  for (b = 1; b <= MAX; b++) { // b loop
    if (b % 100 == 0)
      std::cout << b << " out of " << MAX << std::endl;
    sq.insert(b);
    for (d = 1; d <= MAX; d++) { // d loop
      if (sq.find(d) != sq.end()) continue;
      sq.insert(d);

      for (auto x : factors((b+d)*(b-d))) { // factors loop
        g = (x + (b+d)*(b-d) / x) / 2;
        c = (x - (b+d)*(b-d) / x) / 2;
        if (sq.find(c) != sq.end() || sq.find(g) != sq.end() || c <= 0 || g <= 0) // duplicates
          continue;
        sq.insert(c);
        sq.insert(g);

        for (auto y : factors((g+b)*(g-b))) { // factors loop
          count++;
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
          // if (a * a + e * e + i * i != k) // descending diagonal
          //   continue;

          if (check_magic_square(a, b, c, d, e, f, g, h, i))
            log(a, b, c, d, e, f, g, h, i, k);
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
