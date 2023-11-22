#include "common.h"

namespace {
struct Deer {
  std::string name;
  int speed;
  int fly;
  int rest;
};

int p1(const std::vector<std::string> &in, int duration) {
  std::vector<Deer> deers{};
  for (const std::string &s : in) {
    std::string n;
    int sp, f, r;
    gb::sscanf(
        s,
        "%s can fly %d km/s for %d seconds, but then must rest for %d seconds.",
        n, sp, f, r);
    deers.emplace_back(std::move(n), sp, f, r);
  }

  int best{std::numeric_limits<int>::min()};
  for (const auto &d : deers) {
    int sprints = static_cast<int>(duration / (d.fly + d.rest));
    int reserve = duration % (d.fly + d.rest);
    best = std::max(best, (sprints * d.speed * d.fly) +
                              (std::min(reserve, d.fly) * d.speed));
  }
  return best;
}

int p2(const std::vector<std::string> &in) { return 0; }
} // namespace

int main() {
  const auto &in = gb::readIn();
  gb::writeOut(std::to_string(p1(in, 2503)));
  gb::writeOut(std::to_string(p2(in)));
}