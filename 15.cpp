#include "common.h"

namespace {
struct Ing {
  std::string name;
  int cap;
  int dur;
  int flv;
  int tex;
  int cal;
};

int64_t mul(int a, int64_t acc) {
  return a * std::max(static_cast<int64_t>(0), acc);
}

void mix(const std::vector<Ing> &ings, const size_t i, const int s,
         std::vector<int> &m, int64_t &best) {
  if (i == ings.size() - 1) {
    m[0] += (100 - s) * ings[i].cap;
    m[1] += (100 - s) * ings[i].dur;
    m[2] += (100 - s) * ings[i].flv;
    m[3] += (100 - s) * ings[i].tex;
    best = std::max(best, std::accumulate(m.begin(), m.end(),
                                          static_cast<int64_t>(1), mul));
    m[0] -= (100 - s) * ings[i].cap;
    m[1] -= (100 - s) * ings[i].dur;
    m[2] -= (100 - s) * ings[i].flv;
    m[3] -= (100 - s) * ings[i].tex;
    return;
  }

  for (int j{0}; j <= (100 - s); ++j) {
    m[0] += (j * ings[i].cap);
    m[1] += (j * ings[i].dur);
    m[2] += (j * ings[i].flv);
    m[3] += (j * ings[i].tex);
    mix(ings, i + 1, s + j, m, best);
    m[0] -= (j * ings[i].cap);
    m[1] -= (j * ings[i].dur);
    m[2] -= (j * ings[i].flv);
    m[3] -= (j * ings[i].tex);
  }
}

int64_t p1(const std::vector<std::string> &in) {
  std::vector<Ing> ings;
  for (const auto &l : in) {
    Ing ing{};
    gb::sscanf(l,
               "%23[^:]: capacity %d, durability %d, flavor %d, texture %d, "
               "calories %d",
               ing.name, ing.cap, ing.dur, ing.flv, ing.tex, ing.cal);
    ings.emplace_back(std::move(ing));
  }
  std::vector<int> m(4, 0);
  int64_t best{-1};
  mix(ings, 0, 0, m, best);
  return best;
}

void mix2(const std::vector<Ing> &ings, const size_t i, const int s,
          std::vector<int> &m, const int cal, int64_t &best) {
  if (i == ings.size() - 1) {
    if ((100 - s) * ings[i].cal == cal) {
      m[0] += (100 - s) * ings[i].cap;
      m[1] += (100 - s) * ings[i].dur;
      m[2] += (100 - s) * ings[i].flv;
      m[3] += (100 - s) * ings[i].tex;
      best = std::max(best, std::accumulate(m.begin(), m.end(),
                                            static_cast<int64_t>(1), mul));
      m[0] -= (100 - s) * ings[i].cap;
      m[1] -= (100 - s) * ings[i].dur;
      m[2] -= (100 - s) * ings[i].flv;
      m[3] -= (100 - s) * ings[i].tex;
    }
    return;
  }

  for (int j{0}; j <= std::min((100 - s), (cal / ings[i].cal)); ++j) {
    m[0] += j * ings[i].cap;
    m[1] += j * ings[i].dur;
    m[2] += j * ings[i].flv;
    m[3] += j * ings[i].tex;
    mix2(ings, i + 1, s + j, m, cal - j * ings[i].cal, best);
    m[0] -= j * ings[i].cap;
    m[1] -= j * ings[i].dur;
    m[2] -= j * ings[i].flv;
    m[3] -= j * ings[i].tex;
  }
}

int64_t p2(const std::vector<std::string> &in) {
  std::vector<Ing> ings;
  for (const auto &l : in) {
    Ing ing{};
    gb::sscanf(l,
               "%23[^:]: capacity %d, durability %d, flavor %d, texture %d, "
               "calories %d",
               ing.name, ing.cap, ing.dur, ing.flv, ing.tex, ing.cal);
    ings.emplace_back(std::move(ing));
  }
  std::vector<int> m(4, 0);
  int64_t best{-1};
  mix2(ings, 0, 0, m, 500, best);
  return best;
}

} // namespace

int main() {
  const auto &in = gb::readIn();
  gb::writeOut(std::to_string(p1(in)));
  gb::writeOut(std::to_string(p2(in)));
}