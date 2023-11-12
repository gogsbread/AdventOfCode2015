#include "common.h"

namespace {
int p1(const std::vector<std::string> &in) {
  int t{0};
  for (const std::string_view s : in) {
    int c{0};
    for (size_t i = 0; i < s.size(); ++i) {
      if (s[i] == '"')
        continue;
      if (s[i] == '\\') {
        ++i;
        if (s[i] == 'x') {
          i += 2;
        }
      }
      ++c;
    }
    t += (s.size() - c);
  }
  return t;
}

int p2(const std::vector<std::string> &in) {
  int t{0};
  for (const std::string_view s : in) {
    int c{2};
    for (size_t i = 0; i < s.size(); ++i) {
      if (s[i] == '"')
        ++c;
      if (s[i] == '\\') {
        ++c;
      }
      ++c;
    }
    t += (c - s.size());
  }
  return t;
}
} // namespace

int main() {
  const auto &in = gb::readIn();
  gb::writeOut(std::to_string(p1(in)));
  gb::writeOut(std::to_string(p2(in)));
}