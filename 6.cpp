#include "common.h"

using namespace std::literals;

namespace p1 {
using Row = std::bitset<1000>;
using Grid = std::array<Row, 1000>;

auto flip = [](Row &r, int i) { r.flip(i); };
auto set = [](Row &r, int i) { r.set(i); };
auto reset = [](Row &r, int i) { r.reset(i); };

void manip(Grid &g, int x1, int y1, int x2, int y2,
           std::invocable<Row &, int> auto op) {
  assert(x1 <= x2);
  assert(y1 <= y2);

  for (int j = y1; j <= y2; ++j) {
    for (int i = x1; i <= x2; ++i) {
      op(g[j], i);
    }
  }
}

int solve(const std::vector<std::string> &in) {
  Grid g{};
  for (const std::string &s : in) {
    std::istringstream ss{s};
    std::string token, dim, _;
    int x1, y1, x2, y2;
    ss >> token;
    if (token == "turn") {
      ss >> token;
      {
        ss >> dim;
        auto d = gb::split(dim, ",");
        x1 = std::stoi(std::string{d[0]});
        y1 = std::stoi(std::string{d[1]});
      }
      ss >> _;
      {
        ss >> dim;
        auto d = gb::split(dim, ",");
        x2 = std::stoi(std::string{d[0]});
        y2 = std::stoi(std::string{d[1]});
      }

      if (token == "on") {
        manip(g, x1, y1, x2, y2, set);
      } else {
        manip(g, x1, y1, x2, y2, reset);
      }
    } else {
      {
        ss >> dim;
        auto d = gb::split(dim, ",");
        x1 = std::stoi(std::string{d[0]});
        y1 = std::stoi(std::string{d[1]});
      }
      ss >> _;
      {
        ss >> dim;
        auto d = gb::split(dim, ",");
        x2 = std::stoi(std::string{d[0]});
        y2 = std::stoi(std::string{d[1]});
      }
      manip(g, x1, y1, x2, y2, flip);
    }
  }
  int lit{0};
  for (const Row &r : g) {
    lit += r.count();
  }
  return lit;
}
} // namespace p1

namespace p2 {
using Row = std::array<int, 1000>;
using Grid = std::array<Row, 1000>;

auto flip = [](Row &r, int i) { r[i] += 2; };
auto set = [](Row &r, int i) { r[i] += 1; };
auto reset = [](Row &r, int i) { r[i] = std::max(0, r[i] - 1); };

void manip(Grid &g, int x1, int y1, int x2, int y2,
           std::invocable<Row &, int> auto op) {
  assert(x1 <= x2);
  assert(y1 <= y2);

  for (int j = y1; j <= y2; ++j) {
    for (int i = x1; i <= x2; ++i) {
      op(g[j], i);
    }
  }
}

int64_t solve(const std::vector<std::string> &in) {
  Grid g{};
  for (const std::string &s : in) {
    std::istringstream ss{s};
    std::string token, dim, _;
    int x1, y1, x2, y2;
    ss >> token;
    if (token == "turn") {
      ss >> token;
      {
        ss >> dim;
        auto d = gb::split(dim, ",");
        x1 = std::stoi(std::string{d[0]});
        y1 = std::stoi(std::string{d[1]});
      }
      ss >> _;
      {
        ss >> dim;
        auto d = gb::split(dim, ",");
        x2 = std::stoi(std::string{d[0]});
        y2 = std::stoi(std::string{d[1]});
      }

      if (token == "on") {
        manip(g, x1, y1, x2, y2, set);
      } else {
        manip(g, x1, y1, x2, y2, reset);
      }
    } else {
      {
        ss >> dim;
        auto d = gb::split(dim, ",");
        x1 = std::stoi(std::string{d[0]});
        y1 = std::stoi(std::string{d[1]});
      }
      ss >> _;
      {
        ss >> dim;
        auto d = gb::split(dim, ",");
        x2 = std::stoi(std::string{d[0]});
        y2 = std::stoi(std::string{d[1]});
      }
      manip(g, x1, y1, x2, y2, flip);
    }
  }
  int lit{0};
  for (const Row &r : g) {
    for (const int b : r) {
      lit += b;
    }
  }
  return lit;
}
} // namespace p2

int main() {
  const auto &in = gb::readIn();
  gb::writeOut(std::to_string(p1::solve(in)));
  gb::writeOut(std::to_string(p2::solve(in)));
}