#include "common.h"

namespace {
auto p(const std::string_view in, int iterations) {
  std::string s{in};
  for (int i = 0; i < iterations; ++i) {
    std::ostringstream ss{};
    for (size_t j = 0; j < s.length(); ++j) {
      int c{1};
      for (; j + 1 < s.length() && s[j] == s[j + 1]; ++j, ++c)
        ;
      ss << c << s[j];
    }
    s = ss.str();
  }
  return s.length();
}
} // namespace

int main() {
  const auto &in = gb::readIn();
  gb::writeOut(std::to_string(p(in.at(0), 40)));
  gb::writeOut(std::to_string(p(in.at(0), 50)));
}