#include "common.h"

namespace {
long p1(const std::string &in) {
  int u{0}, d{0};
  for (auto c : in) {
    if (c == '(')
      ++u;
    else
      ++d;
  }
  return u - d;
}

long p2(const std::string &input) {
  int sum{0}, i{0};
  while (sum != -1) {
    char c = input.at(i++);
    if (c == '(')
      ++sum;
    else
      --sum;
  }
  return i;
}
} // namespace

int main() {
  const auto &in = gb::readIn();
  gb::writeOut(std::to_string(p1(in.at(0))));
  gb::writeOut(std::to_string(p2(in.at(0))));
}