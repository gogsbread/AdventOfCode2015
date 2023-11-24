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

void mix(const std::vector<Ing> &ings, size_t i, int s, std::vector<int> &m,
         int64_t &best) {
  if (i == ings.size() - 1) {
    m[0] += std::max(0, (100 - s)) * ings[i].cap;
    m[1] += std::max(0, (100 - s)) * ings[i].dur;
    m[2] += std::max(0, (100 - s)) * ings[i].flv;
    m[3] += std::max(0, (100 - s)) * ings[i].tex;
    best =
        std::max(best, std::max(static_cast<int64_t>(0),
                                std::accumulate(m.begin(), m.end(),
                                                static_cast<int64_t>(1),
                                                std::multiplies<int64_t>())));
    // std::cout << s << " " << (100 - s) << " " << best << std::endl;
    return;
  }

  for (int j{0}; j <= (100 - s); ++j) {
    m[0] += j * ings[i].cap;
    m[1] += j * ings[i].dur;
    m[2] += j * ings[i].flv;
    m[3] += j * ings[i].tex;
    mix(ings, i + 1, s + j, m, best);
  }
}

int64_t p1(const std::vector<std::string> &in) {
  std::vector<Ing> ings;
  for (const auto &l : in) {
    Ing ing{};
    gb::sscanf(l,
               "%s: capacity %d, durability %d, flavor %d, texture %d, "
               "calories %d",
               ing.name, ing.cap, ing.dur, ing.flv, ing.tex, ing.cal);
    std::cout << ing.dur << " " << ing.tex << std::endl;
    ings.emplace_back(std::move(ing));
  }
  std::vector<int> m(4, 0);
  int64_t best{-1};
  mix(ings, 0, 0, m, best);
  return best;
}
} // namespace

int main() {
  const auto &in = gb::readIn();
  gb::writeOut(std::to_string(p1(in)));
}