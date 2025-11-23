#include <rtsan_standalone/rtsan.hh>
#include <vector>

int process() {
  auto vec = std::vector<int>(3);
  vec.push_back(42);
  return 0;
}

int main() { 
  rtsan::ScopedRealtimeSanitizer srs;
  return process(); }