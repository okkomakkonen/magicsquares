#include <iostream> // std::cout, std::endl
#include <cmath> // std::sqrt
#include <unordered_set> // std::unordered_set
#include <deque> // std::deque
#include <ctime> // std::time
#include <string> // std::string
#include <thread> // std::thread
#include <mutex> // std::mutex
#include <vector> // std::vector
#include <chrono>

#define MAX 1000
#define NUM_THREADS 6

class Timer {
public:
  Timer() {
    start_ = std::chrono::steady_clock::now();
  }

  void reset() {
    start_ = std::chrono::steady_clock::now();
  }

  double elapsed() {
    auto end = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start_).count();
  }

private:
  std::chrono::steady_clock::time_point start_;
};

std::mutex m;

static std::vector<long long> b_range;

static long long loop_count = 0;

std::deque<long long> large_pos_factors(long long n) {
  // n has to be positive
  std::deque<long long> res;
  for (long long i = 1; i < (long long) std::sqrt(n); i++) {
    if (n % i == 0 && i % 2 == (n / i) % 2) {
      res.push_back(n / i);
    }
  }
  return res;
}

// Calculate the square root if it is an long longeger, else return zero
long long inv(long long n) {
  if (n < 0) return 0;
  long long r = std::sqrt(n);
  if (r * r == n)
    return r;
  return 0;
}

void search_magic_squares(int tid) {

  long long b_min = b_range[tid] + 1;
  long long b_max = b_range[tid + 1];

  long long a, b, c, d, e, f, g, h, i, k;

  std::unordered_set<long long> sq; // Set of all numbers in the magic square

  long long local_count = 0;

  for (b = b_min; b <= b_max; b++) { // b loop
    sq.insert(b);
    for (d = 1; d < b; d++) { // d loop
      sq.insert(d);

      long long n = (b+d)*(b-d);
      for (long long x = 1; x < (long long) std::sqrt(n); x++) {
        if (n % x == 0 && x % 2 == (n / x) % 2) {
          g = (n / x + x) / 2;
          c = (n / x - x) / 2;
          if (sq.find(c) != sq.end() || sq.find(g) != sq.end() || c <= 0 || g <= 0) {
            local_count++;
            continue;
          }
          sq.insert(c);
          sq.insert(g);

          long long m = std::abs((g+b)*(g-b));

          for (long long y = 1; y < (long long) std::sqrt(m); y++) {
            if (m % y == 0 && y % 2 == (m / y) % 2) {
              local_count++;
            }
          }
        }

        sq.erase(c);
        sq.erase(g);
      }
      sq.erase(d);
    }
    sq.erase(b);
  }

  m.lock();
  std::cout << "Thread " << tid << " with " << local_count << std::endl;
  loop_count += local_count;
  m.unlock();

}

int main() {

  auto tmr = Timer();

  b_range.push_back(1);
  long long count = 0;
  for (long long b = 2; b <= MAX; b++) {
    if (count >= MAX/NUM_THREADS * (MAX - 1)/2) {
      b_range.push_back(b);
      count = 0;
    }
    for (long long d = 1; d < b; d++) {
      count++;
    }
  }
  b_range.push_back(MAX);

  std::thread t[NUM_THREADS];

  for (int tid = 0; tid < NUM_THREADS; tid++) {
    t[tid] = std::thread(search_magic_squares, tid);
  }

  for (int tid = 0; tid < NUM_THREADS; tid++) {
    t[tid].join();
  }

  std::cout << "Total count is " << loop_count << std::endl;

  std::cout << "Total time is " << tmr.elapsed() << std::endl;

  return 0;
}
