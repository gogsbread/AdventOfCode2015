#include "common.h"

namespace {
int64_t p1(const std::vector<std::string> &in) {
  int64_t s{0};
  for (const auto &d : in) {
    std::vector<int> dim{};
    int r;
    for (const auto e : gb::split(d, "x")) {
      std::from_chars(e.data(), e.data() + e.length(), r);
      dim.emplace_back(r);
    }
    std::sort(dim.begin(), dim.end());
    s += (3 * dim[0] * dim[1] + 2 * dim[1] * dim[2] + 2 * dim[2] * dim[0]);
  }
  return s;
}

int64_t p2(const std::vector<std::string> &in) {
  int64_t s{0};
  for (const auto &d : in) {
    std::vector<int> dim{};
    int r;
    for (const auto e : gb::split(d, "x")) {
      std::from_chars(e.data(), e.data() + e.length(), r);
      dim.emplace_back(r);
    }
    std::sort(dim.begin(), dim.end());
    s += ((dim[0] * dim[1] * dim[2]) + 2 * (dim[0] + dim[1]));
  }
  return s;
}
} // namespace

int main() {
  const auto &in = gb::readIn();
  gb::writeOut(std::to_string(p1(in)));
  gb::writeOut(std::to_string(p2(in)));
}