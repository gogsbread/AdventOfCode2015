#include "common.h"

namespace {
std::string next(const std::string &s) {
  assert(s.length() == 8);

  std::string r{s};
  for (int c{1}, i{7}; c != 0 && i >= 0; --i) {
    char t = r[i];
    r[i] = ((t + c - 'a') % 26) + 'a';
    c = (t + c - 'a') / 26;
  }
  return r;
}

bool has_run(const std::string_view s) {
  for (size_t i = 0; i < s.size() - 2; ++i) {
    std::string_view sv{std::addressof(s[i]), 3};
    if ((sv[0] + 1 == sv[1]) && (sv[1] + 1 == sv[2])) {
      return true;
    }
  }
  return false;
};

bool has_pair(const std::string_view s) {
  std::vector<std::string_view> pairs{};
  for (size_t i = 0; i < s.size() - 1; ++i) {
    if (s[i] == s[i + 1]) {
      pairs.emplace_back(std::addressof(s[i]), 2);
      ++i;
    }
  }
  for (int i = 0; i < static_cast<int>(pairs.size()) - 1; ++i) {
    if (pairs[i][0] != pairs[i + 1][0]) {
      return true;
    }
  }
  return false;
};

bool valid(const std::string &s) {
  if (s.find_first_of("iol") != s.npos) {
    return false;
  }
  if (!has_run(s)) {
    return false;
  }
  if (!has_pair(s)) {
    return false;
  }
  return true;
};

std::string p(const std::string &in) {
  std::string s{next(in)};
  for (; !valid(s); s = next(s))
    ;
  return s;
}
} // namespace

int main() {
  const auto &in = gb::readIn();
  gb::writeOut(p(in.at(0)));
}