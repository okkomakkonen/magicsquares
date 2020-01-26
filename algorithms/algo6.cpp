#include <iostream> // std::cout, std::endl
#include <set> // std::set
#include <vector> // std::vector
#include <cmath> // std::sqrt
#include <ctime> // std::time
// #include <thread> // std::thread
// #include <mutex> // std::mutex
#include <algorithm> // std::__gcd

#define MAX 100

std::vector<int> small_pos_factors_parity(int n) {
  std::vector<int> res;
  for (int i = 1; i * i < n; i++) {
    if (n % i == 0 && i % 2 == (n / i) % 2)
      res.push_back(i);
  }
  return res;
}

int inv(int n) {
  if (n < 0) return 0;
  int r = std::sqrt(n);
  if (r * r == n)
    return r;
  return 0;
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

// Return true if the numbers don't have common factors
bool is_primitive(int a, int b, int c,
  int d, int e, int f, int g,
  int h, int i) {
    return 1 == std::__gcd(a,
                std::__gcd(b,
                std::__gcd(c,
                std::__gcd(d,
                std::__gcd(e,
                std::__gcd(f,
                std::__gcd(g,
                std::__gcd(h, i))))))));
}

// Log a string to std::cout with a timestamp
void log(std::string message) {
  std::time_t result = std::time(nullptr); // Current time
  std::cout << std::asctime(std::localtime(&result));
  std::cout << message << std::endl;
  std::cout << std::endl;
}

// Log a magic square to std::cout with a timestamp
void log(int a, int b, int c, int d, int e, int f, int g, int h, int i, int k) {
  if (check_magic_square(a, b, c, d, e, f, g, h, i) || true) {
    std::time_t result = std::time(nullptr); // Current time
    std::cout << std::asctime(std::localtime(&result));
    std::cout << "Magic square of squares k = " << k << std::endl;
    std::cout << a << " " << b << " " << c << std::endl;
    std::cout << d << " " << e << " " << f << std::endl;
    std::cout << g << " " << h << " " << i << std::endl;
    if (check_magic_square(a, b, c, d, e, f, g, h, i))
      std::cout << "WORKING MAGIC SQUARE OF SQUARES" << std::endl;
    if (is_primitive(a, b, c, d, e, f, g, h, i))
      std::cout << "THIS IS A PRIMITIVE MAGIC SQUARE" << std::endl;
    std::cout << std::endl;
  }
}

void search_magic_squares() {

  int count = 0;

  int a, b, c, d, e, f, g, h, i;
  int k;
  int bd;

  std::set<int> sq;

  for (b = 2; b <= MAX; b++) { // b loop
    sq.insert(b);

    for (d = b % 2 ? 1 : 2; d < b; d += 2) { // d loop
      sq.insert(d);

      bd = b * b - d * d;
      auto factors_bd = small_pos_factors_parity(bd);
      for (auto x : factors_bd) { // bd factors loop
        f = (bd / x + x) / 2;
        h = (bd / x - x) / 2;
        if (f % 2 != h % 2 || f % 2 != b % 2) continue;
        if (sq.find(h) != sq.end() || sq.find(f) != sq.end()) continue;
        sq.insert(h);
        sq.insert(f);

        for (auto y : factors_bd) {
            g = (bd / y + y) / 2;
            c = (bd / y - y) / 2;
            if (g % 2 != c % 2) continue;
            if (sq.find(g) != sq.end() || sq.find(c) != sq.end()) continue;

            std::cout << "   " << b << " " << c << std::endl;
            std::cout << d << " " << "   " << f << std::endl;
            std::cout << g << " " << h << "   " << std::endl;
            std::cout << std::endl;
        }

        sq.erase(h);
        sq.erase(f);
      } // bd factors loop

      sq.erase(d);
    } // d loop

    sq.erase(b);
  } // b loop

  std::cout << count << std::endl;

}

int main() {

  search_magic_squares();

  return 0;

}
