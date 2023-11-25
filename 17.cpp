#include "common.h"

namespace {
int p1(const std::vector<std::string> &in, int tgt) {
  std::vector<int> conts;
  for (const std::string &s : in) {
    conts.emplace_back(std::stoi(s));
  }
  int r{0};
  for (int i{1}; i < std::pow(2, conts.size()); ++i) {
    int t{0};
    for (int j{0}, n{i}; n != 0; n >>= 1, ++j) {
      if (n & 1) {
        t += conts[j];
      }
    }
    if (t == tgt) {
      ++r;
    }
  }
  return r;
}

int p1(const std::vector<std::string> &in, int tgt) {
  std::vector<int> conts;
  for (const std::string &s : in) {
    conts.emplace_back(std::stoi(s));
  }
  std::map<int, int> r{};
  for (int i{1}; i < std::pow(2, conts.size()); ++i) {
    int t{0};
    for (int j{0}, n{i}; n != 0; n >>= 1, ++j) {
      if (n & 1) {
        t += conts[j];
      }
    }
    if (t == tgt) {
      r[std::bitset<sizeof(int) * 8>(i).count()] += 1;
    }
  }
  return r;
}
} // namespace

int main() {
  const auto &in = gb::readIn();
  gb::writeOut(std::to_string(p1(in, 150)));
  // gb::writeOut(std::to_string(p2(in)));
}