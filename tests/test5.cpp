#include <iostream>   // std::cout, std::endl
#include <set>        // std::set
#include <unordered_set> // std::unordered_set
#include <vector>     // std::vector
#include <cmath>      // std::sqrt
#include <algorithm>  // std::__gcd

static int MAX = 100;

std::vector<long long> small_pos_factors_parity(long long n) {
  std::vector<long long> res;
  for (long long i = 1; i * i < n; i++) {
    if (n % i == 0 && i % 2 == (n / i) % 2)
      res.push_back(i);
  }
  return res;
}

long long inv(long long n) {
  if (n < 0) return 0;
  long long r = std::sqrt(n);
  if (r * r == n)
    return r;
  return 0;
}

bool check_magic_square(long long a, long long b, long long c,
  long long d, long long e, long long f, long long g,
  long long h, long long i) {
    long long k = a * a + b * b + c * c; // top row
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
bool is_primitive(long long a, long long b, long long c,
  long long d, long long e, long long f, long long g,
  long long h, long long i) {
    return 1 == std::__gcd(a,
                std::__gcd(b,
                std::__gcd(c,
                std::__gcd(d,
                std::__gcd(e,
                std::__gcd(f,
                std::__gcd(g,
                std::__gcd(h, i))))))));
}

void search_magic_squares() {

  long long a, b, c, d, e, f, g, h, i; // values in the square
  long long k; // square sum
  long long cg; // c^2 - g^2

  std::unordered_set<long long> sq;

  for (c = 2; c <= MAX; c++) { // c loop
    sq.insert(c);

    for (g = c % 2 ? 1 : 2; g < c; g += 2) { // g loop, g has to be of same parity
      sq.insert(g);

      cg = c * c - g * g; // (c + g) * (c - g)
      auto cg_factors = small_pos_factors_parity(cg);
      for (auto j = 1; j < cg_factors.size(); j++) { // b and d loop
        d = (cg / cg_factors[j] + cg_factors[j]) / 2;
        b = (cg / cg_factors[j] - cg_factors[j]) / 2;
        if (b % 2 != d % 2) continue;
        if (sq.find(d) != sq.end() || sq.find(b) != sq.end() || b <= 0) continue;
        sq.insert(d);
        sq.insert(b);

        for (auto l = 0; l < j; l++) { // f and h loop
          h = (cg / cg_factors[l] + cg_factors[l]) / 2;
          f = (cg / cg_factors[l] - cg_factors[l]) / 2;
          if (h % 2 != f % 2) continue;
          if (b % 2 != f % 2) continue;
          if (sq.find(h) != sq.end() || sq.find(f) != sq.end() || f <= 0) continue;
          sq.insert(h);
          sq.insert(f);

          k = c * c + b * b + (f * f + h * h) / 2;
          a = inv(k - b * b - c * c);
          if (a == 0 || sq.find(a) != sq.end()) {
            sq.erase(h);
            sq.erase(f);
            continue;
          }
          sq.insert(a);

          e = inv(k - b * b - h * h);
          if (e == 0 || sq.find(e) != sq.end()) {
            sq.erase(h);
            sq.erase(f);
            sq.erase(a);
            continue;
          }
          sq.insert(e);

          i = inv(k - c * c - f * f);
          if (i == 0 || sq.find(i) != sq.end()) {
            sq.erase(h);
            sq.erase(f);
            sq.erase(a);
            sq.erase(e);
            continue;
          }
          sq.erase(h);
          sq.erase(f);
          sq.erase(a);
          sq.erase(e);

        } // f and h loop

        sq.erase(d);
        sq.erase(b);
      } // b and d loop

      sq.erase(g);
    } // g loop

    sq.erase(c);
  } // c loop

}

int main(int argc, char* argv[]) {

  // Process input arguments
  if (argc > 1)
    MAX = std::stoi(argv[1]);

  std::cout << "Calculating to " << MAX << std::endl;

  search_magic_squares();

  std::cout << "Finished" << std::endl;

  return 0;
}
