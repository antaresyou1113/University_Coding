#include <iostream>
#include <thread>

void foo() { std::cout << "Hello C++11" << std::endl; }

int main() {
  std::thread thread(foo);  // start the thread foo
  thread.join();            // wait until it finishes

  return 0;
}

// join is really important here, because it could wait the finish of the thread
