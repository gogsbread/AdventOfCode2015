#include "common.h"

namespace {
std::unordered_map<std::string, int> mfscam{
    {"children", 3}, {"cats", 7},    {"samoyeds", 2}, {"pomeranians", 3},
    {"akitas", 0},   {"vizslas", 0}, {"goldfish", 5}, {"trees", 3},
    {"cars", 2},     {"perfumes", 1}};

void p1(const std::vector<std::string> &in) {
  for (const std::string &l : in) {
    bool failed{false};
    for (const auto &[k, v] : mfscam) {
      if (size_t s = l.find(k); s != l.npos) {
        int n = std::stoi(l.substr(s + k.size() + 2, l.find_first_of(",", s) -
                                                         (s + k.size() + 2)));
        if (n != v) {
          failed = true;
          break;
        }
      }
    }
    if (!failed) {
      std::cout << "Possible: " << l << std::endl;
    }
  }
}

void p2(const std::vector<std::string> &in) {
  for (const std::string &l : in) {
    bool failed{false};
    for (const auto &[k, v] : mfscam) {
      if (size_t s = l.find(k); s != l.npos) {
        int n = std::stoi(l.substr(s + k.size() + 2, l.find_first_of(",", s) -
                                                         (s + k.size() + 2)));
        if (k == "cat" || k == "trees") {
          if (n < v) {
            failed = true;
            break;
          }
        } else if (k == "pomeranians" || k == "goldfish") {
          if (n > v) {
            failed = true;
            break;
          }
        } else if (n != v) {
          failed = true;
          break;
        }
      }
    }
    if (!failed) {
      std::cout << "Possible: " << l << std::endl;
    }
  }
}
} // namespace

int main() {
  const auto &in = gb::readIn();
  std::cout << "p1" << std::endl;
  p1(in);
  std::cout << "p2" << std::endl;
  p2(in);
}