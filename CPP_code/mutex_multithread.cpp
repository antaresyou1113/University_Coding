#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <sstream>
#include <thread>
#include <vector>

using namespace std;

static const int MAX = 10e8;
static double sum = 0;
static mutex exclusive;

void print_time() {
  auto now = chrono::system_clock::now();
  auto in_time_t = chrono::system_clock::to_time_t(now);

  stringstream ss;
  ss << put_time(localtime(&in_time_t), "%Y-%m-%d %X");
  cout << "now is: " << ss.str() << endl;
}

void worker(int min, int max) {
  for (int i = min; i < max; i++) {
    sum += sqrt(i);
  }
}

void concurrent_worker(int min, int max) {
  double tmp_sum = 0;
  for (int i = min; i <= max; i++) {
    tmp_sum += sqrt(i);
    //cout<<"the tmp_sum her is "<<tmp_sum<<endl;
  }
  //cout<<"the tmp_sum her is "<<tmp_sum<<endl;
// when the thread does the sum operation, it just deals with its own data, so there is no need to add the lock there
// when it comes to the sum operation, it is the race condition, I need to add the lock in order to make sure there is no conflict here. 
// think about a situation when I just need to get the data from the memory instead of changing the data, I may not need to add the lock.
  exclusive.lock();
  sum += tmp_sum;
  exclusive.unlock();
}

void serial_task(int min, int max) {
  auto start_time = chrono::steady_clock::now();
  sum = 0;
  worker(min, max);
  auto end_time = chrono::steady_clock::now();
  auto ms = chrono::duration_cast<chrono::milliseconds>(end_time - start_time)
                .count();
  cout << "Serial task has finished: " << ms << " ms consumed, Result: " << sum
       << endl;
}

void concurrent_task(int min, int max) {
  auto start_time = chrono::steady_clock::now();
  // how many threads can be supported by the hardware
  unsigned concurrent_count = thread::hardware_concurrency();
  cout << "hardware_concurrency: " << concurrent_count << endl;
  vector<thread> threads;
  min = 0;
  sum = 0;
  for (int t = 0; t < concurrent_count; t++) {
    // create the threads based on the hardware
    // use the range to decide the wordload for each thread
    int range = max / concurrent_count * (t + 1);
    threads.push_back(thread(concurrent_worker, min, range));
    min = range + 1;
  }

  for (auto& t : threads) {
    t.join();
  }

  auto end_time = chrono::steady_clock::now();
  auto ms = chrono::duration_cast<chrono::milliseconds>(end_time - start_time)
                .count();
  cout << "Concurrent task has finished, " << ms
       << " ms consumed, Result: " << sum << endl;
}

int main() {
  //serial_task(0, MAX);
  concurrent_task(0, MAX);
  serial_task(0, MAX);
  return 0;
}
