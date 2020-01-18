#include <iostream> // std::cout, std::endl
#include <cmath> // std::sqrt
#include <set> // std::set
#include <ctime> // std::time
#include <map> // std::map
#include <string> // std::string
#include "factors.hpp"

#define MAX 5000

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

int main() {

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
        if (std::abs(x) % 2 != std::abs((b+d)*(b-d) / x) % 2) // invalid factor
          continue;
        g = (x + (b+d)*(b-d) / x) / 2;
        c = (x - (b+d)*(b-d) / x) / 2;
        if (sq.find(c) != sq.end() || sq.find(g) != sq.end() || c <= 0 || g <= 0) // duplicates
          continue;
        sq.insert(c);
        sq.insert(g);

        for (auto y : factors((g+b)*(g-b))) { // factors loop
          if (std::abs(y) % 2 != std::abs((g+b)*(g-b) / y) % 2) // invalid factor
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

  return 0;

}
