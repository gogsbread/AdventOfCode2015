#include "common.h"

namespace {
long p1(const auto &input) { return 0L; }

long p2(const auto &input) { return 0L; }
} // namespace

int main() {
  for (const auto s : gb::split("", "foo")) {
    std::cout << s << std::endl;
  }
}