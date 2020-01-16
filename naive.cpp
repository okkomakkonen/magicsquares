#include <iostream> // std::cout, std::endl
#include <cmath> // std::sqrt
#include <ctime> // std::asctime, std::localtime
#include <set> // std::set
#define MAX 200

unsigned int transform(int number) {
  return number * number;
}

unsigned int inverse_transform(int candidate) {
  if (candidate < 0) return 0;
  int test = std::sqrt(candidate);
  if (test * test == candidate)
    return test;
  return 0;
}

int main() {


  std::time_t result = std::time(nullptr); // Current time
  std::cout << std::asctime(std::localtime(&result));
  std::cout << "Starting" << std::endl;
  std::cout << std::endl;

  unsigned int a, b, c, d, e, f, g, h, i, k;
  std::set<unsigned int> sq;

  for (a = 1; a <= MAX; a++) {
    sq.insert(a);
    for (b = 1; b <= MAX; b++) {
      if (sq.find(b) != sq.end()) continue; // Elements should be unique
      sq.insert(b);
      for (c = 1; c <= MAX; c++) {
        if (sq.find(c) != sq.end()) continue; // Elements should be unique
        sq.insert(c);
        k = transform(a) + transform(b) + transform(c);
        for (d = 1; d <= MAX; d++) {
          if (sq.find(d) != sq.end()) continue; // Elements should be unique
          if (transform(d) >= k) break; // d is too large
          sq.insert(d);
          // Now the magic square is uniquely determined
          g = inverse_transform(k - transform(a) - transform(d));
          if (g == 0 || sq.find(g) != sq.end()) {
            sq.erase(d);
            continue;
          }
          sq.insert(g);
          e = inverse_transform(k - transform(g) - transform(c));
          if (e == 0 || sq.find(e) != sq.end()) {
            sq.erase(d);
            sq.erase(g);
            continue;
          }
          sq.insert(e);
          f = inverse_transform(k - transform(d) - transform(e));
          if (f == 0 || sq.find(f) != sq.end()) {
            sq.erase(d);
            sq.erase(g);
            sq.erase(e);
            continue;
          }
          sq.insert(f);
          h = inverse_transform(k - transform(b) - transform(e));
          if (h == 0 || sq.find(h) != sq.end()) {
            sq.erase(d);
            sq.erase(g);
            sq.erase(e);
            sq.erase(f);
            continue;
          }
          sq.insert(h);
          i = inverse_transform(k - transform(c) - transform(f));
          if (i == 0 || sq.find(i) != sq.end()) {
            sq.erase(d);
            sq.erase(g);
            sq.erase(e);
            sq.erase(f);
            sq.erase(h);
            continue;
          }
          // All elements are unique
          sq.erase(d);
          sq.erase(g);
          sq.erase(e);
          sq.erase(f);
          sq.erase(h);
          if (transform(g) + transform(h) + transform(i) != k) // bottom row
            continue;
          // if (transform(a) + transform(e) + transform(i) != k) // descending diagonal
          //   continue;

          // This is a valid magic square
          result = std::time(nullptr); // Current time
          std::cout << std::asctime(std::localtime(&result));
          std::cout << "Magic square of squares k = " << k << std::endl;
          std::cout << a << " " << b << " " << c << std::endl;
          std::cout << d << " " << e << " " << f << std::endl;
          std::cout << g << " " << h << " " << i << std::endl;
          std::cout << std::endl;

        }
        sq.erase(c);
      }
      sq.erase(b);
    }
    sq.erase(a);
  }
  result = std::time(nullptr); // Current time
  std::cout << std::asctime(std::localtime(&result));
  std::cout << "Ending" << std::endl;

  return 0;
}
