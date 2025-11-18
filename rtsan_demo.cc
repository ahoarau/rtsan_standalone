#include <vector>

int process() [[clang::nonblocking]] {
  auto vec = std::vector<int>(3);
  vec.push_back(42);
  return 0;
}

auto main() -> int { return process(); }