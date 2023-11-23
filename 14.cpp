#include "common.h"

namespace {
struct Deer {
  std::string name;
  int speed;
  int fly;
  int rest;
};

std::vector<Deer> parse(const std::vector<std::string> &in) {
  std::vector<Deer> deers{};
  for (const std::string &s : in) {
    Deer d{};
    gb::sscanf(
        s,
        "%s can fly %d km/s for %d seconds, but then must rest for %d seconds.",
        d.name, d.speed, d.fly, d.rest);
    deers.emplace_back(std::move(d));
  }
  return deers;
}

int distance(const Deer &d, int duration) {
  int sprints = static_cast<int>(duration / (d.fly + d.rest));
  int reserve = duration % (d.fly + d.rest);
  return (sprints * d.speed * d.fly) + (std::min(reserve, d.fly) * d.speed);
}

int p1(const std::vector<std::string> &in, const int duration) {
  const auto deers = parse(in);
  int best{std::numeric_limits<int>::min()};
  for (const auto &d : deers) {
    best = std::max(best, distance(d, duration));
  }
  return best;
}

int p2(const std::vector<std::string> &in, const int duration) {
  const auto deers = parse(in);
  std::vector<int> points(deers.size(), 0);
  for (int i{1}; i <= duration; ++i) {
    int best{-1};
    for (const auto &d : deers) {
      best = std::max(best, distance(d, i));
    }
    for (size_t j{0}; j < deers.size(); ++j) {
      if (best == distance(deers[j], i)) {
        points[j] += 1;
      }
    }
  }
  return *std::max_element(points.begin(), points.end());
}
} // namespace

int main() {
  const auto &in = gb::readIn();
  gb::writeOut(std::to_string(p1(in, 2503)));
  gb::writeOut(std::to_string(p2(in, 2503)));
}