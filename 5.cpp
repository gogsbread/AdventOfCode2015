#include "common.h"

using namespace std::literals;

namespace {
int p1(const std::vector<std::string> &in) {
  int nice{0};
  for (const std::string_view s : in) {
    if (s.size() < 3)
      continue;
    bool vow{false}, dbl{false}, bad{false};
    {
      auto it = std::ranges::adjacent_find(s.begin(), s.end());
      dbl = it != s.end();
    }
    vow = std::count_if(s.begin(), s.end(), [](char c) {
            return "aeiou"s.find(c) != std::string::npos;
          }) >= 3;
    {
      auto it =
          std::ranges::adjacent_find(s.begin(), s.end(), [](char a, char b) {
            std::string s{std::string(1, a) + std::string(1, b)};
            return (s == "ab" || s == "cd" || s == "pq" || s == "xy");
          });
      bad = it != s.end();
    }
    if (dbl && vow && !bad)
      ++nice;
  }
  return nice;
}

int64_t p2(const std::vector<std::string> &in) {
  int nice{0};
  for (const std::string_view s : in) {
    bool pair{false}, dbl{false};
    for (size_t i = 0; i < s.size() - 1; ++i) {
      for (size_t j = i + 2; j < s.size() - 1; ++j) {
        if (s.substr(i, 2) == s.substr(j, 2))
          pair = true;
      }
    }
    for (size_t i = 0; i < s.size() - 2; ++i) {
      if (s[i] == s[i + 2])
        dbl = true;
    }
    if (pair && dbl)
      ++nice;
  }
  return nice;
}
} // namespace

int main() {
  const auto &in = gb::readIn();
  gb::writeOut(std::to_string(p1(in)));
  gb::writeOut(std::to_string(p2(in)));
}