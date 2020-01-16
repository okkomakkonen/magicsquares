#include <iostream>
#include <cmath>
#include <set>
#include <ctime>

#define MAX 500

// Find the factors of n
std::set<int> factors(int n) {
  std::set<int> res;
  for (int i = 1; i <= (int) std::sqrt(n); i++) {
    if (n % i == 0) {
      res.insert(i);
      res.insert(n / i);
    }
  }
  return res;
}

std::set<int> factors(int n, int m) {
  std::set<int> res;
  for (auto i : factors(n)) {
    for (auto j : factors(m)) {
      res.insert(i * j);
    }
  }
  return res;
}

int inv(int candidate) {
  if (candidate < 0) return 0;
  int test = std::sqrt(candidate);
  if (test * test == candidate)
    return test;
  return 0;
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

  std::time_t result = std::time(nullptr); // Current time
  std::cout << std::asctime(std::localtime(&result));
  std::cout << "Starting" << std::endl;
  std::cout << std::endl;

  int a, b, c, d, e, f, g, h, i, k, x, y, xy, z, xyz;

  std::set<int> sq;

  for (a = 1; a <= MAX; a++) {
    sq.insert(a);
    for (x = 1; x <= 2 * MAX; x++) {
      for (y = x % 2 ? 1 : 2; y < x; y += 2) {
        b = (x + y) / 2;
        d = (x - y) / 2;
        if (sq.find(b) != sq.end() || sq.find(d) != sq.end() || b == d)
          continue;
        sq.insert(b);
        sq.insert(d);
        xy = x * y;

        auto xy_factors = factors(x, y);
        for (auto z : xy_factors) {
          xyz = xy / z;
          if (z % 2 != xyz % 2 || z <= xyz)
            continue;
          g = (z + xyz) / 2;
          c = (z - xyz) / 2;
          if (sq.find(c) != sq.end() || sq.find(g) != sq.end() || c == g)
            continue;
          sq.insert(c);
          sq.insert(g);

          k = a * a + b * b + c * c;
          if (a * a + d * d + g * g != k) {
            sq.erase(c);
            sq.erase(g);
            continue;
          }
          // Now we can solve it to the end, since we have a, b, c, d and g
          e = inv(k - g * g - c * c);
          if (e == 0 || sq.find(e) != sq.end()) {
            sq.erase(c);
            sq.erase(g);
            continue;
          }
          sq.insert(e);
          f = inv(k - d * d - e * e);
          if (f == 0 || sq.find(f) != sq.end()) {
            sq.erase(c);
            sq.erase(g);
            sq.erase(e);
            continue;
          }
          sq.insert(f);
          h = inv(k - b * b - e * e);
          if (h == 0 || sq.find(h) != sq.end()) {
            sq.erase(c);
            sq.erase(g);
            sq.erase(e);
            sq.erase(f);
            continue;
          }
          sq.insert(h);
          i = inv(k - c * c - f * f);
          if (i == 0 || sq.find(i) != sq.end()) {
            sq.erase(c);
            sq.erase(g);
            sq.erase(e);
            sq.erase(f);
            sq.erase(h);
            continue;
          }
          // All elements are unique
          sq.erase(c);
          sq.erase(g);
          sq.erase(e);
          sq.erase(f);
          sq.erase(h);
          if (g * g + h * h + i * i != k) // bottom row
            continue;
          if (a * a + e * e + i * i != k) // descending diagonal
            continue;

          // This is a valid magic square
          // log_magic_square(a, b, c, d, e, f, g, h, i, k, a * a + e * e + i * i == k);
          log_magic_square(a, b, c, d, e, f, g, h, i, k);
        }
        sq.erase(b);
        sq.erase(d);
      }
    }
    sq.erase(a);
    if (sq.size() != 0) {
      std::cout << "Something has gone wrong" << std::endl;
    }
  }

  result = std::time(nullptr); // Current time
  std::cout << std::asctime(std::localtime(&result));
  std::cout << "Ending" << std::endl;

  return 0;

}
