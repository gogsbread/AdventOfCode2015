#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <charconv>
#include <climits>
#include <cmath>
#include <complex>
#include <concepts>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <ranges>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <variant>
#include <vector>

using vs = std::vector<std::string>;
#define ASSERT_EXPR(expr, err)                                                 \
  if (!(expr))                                                                 \
    throw std::runtime_error((err));

using namespace std::string_view_literals;

namespace gb {
std::vector<std::string_view> split(std::string_view sentence,
                                    std::string_view delim) {
  if (sentence.length() == 0)
    return {};
  if (delim.length() == 0)
    return {sentence};

  std::vector<std::string_view> r;
  std::string_view::size_type s{0}, e{0};
  while ((e = sentence.find(delim, s)) != sentence.npos) {
    r.emplace_back(sentence.substr(s, e - s));
    s = e + delim.length();
  }
  r.emplace_back(sentence.substr(s, sentence.length() - s));
  return r;
}

std::vector<std::string> readIn() {
  std::vector<std::string> lines;
  for (std::string l; getline(std::cin, l);) {
    lines.emplace_back(l);
  }
  return lines;
}

void writeOut(std::string_view s) { std::cout << s << std::endl; }
} // namespace gb