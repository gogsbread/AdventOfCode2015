#include "common.h"

namespace {
auto p1(const std::string_view in) {
  std::set<std::pair<int, int>> houses{std::make_pair(0, 0)};
  std::pair<int, int> p{0, 0};
  for (auto c : in) {
    switch (c) {
    case '>':
      ++p.first;
      break;
    case '^':
      ++p.second;
      break;
    case '<':
      --p.first;
      break;
    case 'v':
      --p.second;
      break;
    default:
      break;
    }
    houses.emplace(p);
  }
  return houses.size();
}

auto p2(const std::string_view in) {
  std::set<std::pair<int, int>> houses{std::make_pair(0, 0)};
  for (size_t i = 0; i < 2; ++i) {
    std::pair<int, int> p{0, 0};
    for (decltype(in.length()) j{i}; j < in.length(); j += 2) {
      switch (in.at(j)) {
      case '>':
        ++p.first;
        break;
      case '^':
        ++p.second;
        break;
      case '<':
        --p.first;
        break;
      case 'v':
        --p.second;
        break;
      default:
        break;
      }
      houses.emplace(p);
    }
  }
  return houses.size();
}
} // namespace

int main() {
  const auto &in = gb::readIn();
  gb::writeOut(std::to_string(p1(in.at(0))));
  gb::writeOut(std::to_string(p2(in.at(0))));
}