#include <iostream>       // std::cout, std::endl
#include <cmath>          // std::sqrt
#include <unordered_set>  // std::unordered_set
#include <ctime>          // std::time
#include <string>         // std::string
#include <thread>         // std::thread
#include <mutex>          // std::mutex
#include <vector>         // std::vector

#define MAX 1000
#define NUM_THREADS 6

std::mutex m;

static std::vector<int> b_range; // ranges for the values of b for different threads

static int magic_square_count = 0;

// Calculate the square root of n if it is an integer, else return zero
int inv(long long n) {
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

bool check_magic_square(int a, int b, int c,
  int d, int e, int f, int g,
  int h, int i) {
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

// Log a magic square to std::cout with a timestamp
void log(int a, int b, int c, int d, int e, int f, int g, int h, int i, long long k) {
  if (check_magic_square(a, b, c, d, e, f, g, h, i) || true) {
    std::time_t result = std::time(nullptr); // Current time
    std::cout << std::asctime(std::localtime(&result));
    std::cout << "Magic square of squares k = " << k << std::endl;
    std::cout << a << " " << b << " " << c << std::endl;
    std::cout << d << " " << e << " " << f << std::endl;
    std::cout << g << " " << h << " " << i << std::endl;
    if (check_magic_square(a, b, c, d, e, f, g, h, i))
      std::cout << "WORKING MAGIC SQUARE OF SQUARES" << std::endl;
    std::cout << std::endl;
  }
}

void search_magic_squares(int tid) {

  int b_min = b_range[tid] + 1;
  int b_max = b_range[tid + 1];

  int a, b, c, d, e, f, g, h, i;
  long long k;

  std::unordered_set<int> sq; // Set of all numbers in the magic square

  for (b = b_min; b <= b_max; b++) { // b loop
    sq.insert(b);
    for (d = 1; d < b; d++) { // d loop
      sq.insert(d);

      auto bd = (b+d)*(b-d);
      for (int x = 1; x < (int) std::sqrt(bd); x++) { // factors loop
        if (bd % x != 0 || bd / x % 2 != x % 2) continue;
        g = (bd / x + x) / 2;
        c = (bd / x - x) / 2;
        if (sq.find(c) != sq.end() || sq.find(g) != sq.end() || c <= 0 || g <= 0) // duplicates
          continue;
        sq.insert(c);
        sq.insert(g);

        auto gb = (g+b)*(g-b);
        for (int y = 1; y < (int) std::sqrt(std::abs(gb)); y++) { // factors loop
          if (gb % y != 0 || gb / y % 2 != y % 2) continue;
          // Handle g^2 - b^2 > 0 and < 0 separately
          if (gb > 0) {
            a = (gb / y + y) / 2;
            e = (gb / y - y) / 2;
          } else {
            e = (gb / y + y) / 2;
            a = (gb / y - y) / 2;
          }
          if (sq.find(a) != sq.end() || sq.find(e) != sq.end()) // duplicates
            continue;
          sq.insert(a);
          sq.insert(e);

          // Now we can solve for the magic square, since we have a, b, c, d, g and e
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

          m.lock();
          log(a, b, c, d, e, f, g, h, i, k);
          if (check_magic_square(a, b, c, d, e, f, g, h, i))
            magic_square_count++;
          m.unlock();
        }

        sq.erase(c);
        sq.erase(g);
      }
      sq.erase(d);
    }
    sq.erase(b);
  }

}

int main() {

  log("Finding magic squares");

  b_range.push_back(1);
  long long count = 0;
  for (int b = 2; b <= MAX; b++) {
    if (count >= MAX/NUM_THREADS * (MAX - 1)/2) {
      b_range.push_back(b);
      count = 0;
    }
    for (int d = 1; d < b; d++) {
      count++;
    }
  }
  b_range.push_back(MAX);

  // for (auto b : b_range) std::cout << b << std::endl;
  // return 0;

  std::thread t[NUM_THREADS];

  for (int tid = 0; tid < NUM_THREADS; tid++) {
    t[tid] = std::thread(search_magic_squares, tid);
  }

  for (int tid = 0; tid < NUM_THREADS; tid++) {
    t[tid].join();
  }

  log("Ending");
  std::cout << "Found " << magic_square_count << " magic squares" << std::endl;

  return 0;
}
