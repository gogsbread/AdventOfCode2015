#include "common.h"

namespace {
struct Edge {
  std::string u;
  std::string v;
  bool operator==(const Edge &) const = default;
};

auto hasher = [](const Edge &e) noexcept -> std::size_t {
  auto hu = std::hash<std::string>{}(e.u);
  auto hv = std::hash<std::string>{}(e.v);
  return hu ^ (hv << 1);
};
using Graph = std::unordered_map<Edge, int, decltype(hasher)>;

int p1(const std::vector<std::string> &in) {
  Graph g{};
  std::set<std::string> st{};
  std::string s{}, c{}, e{};
  int p{};
  for (const auto &l : in) {
    gb::sscanf(l,
               "%23s would %9s %d happiness units by sitting next to %23[^.].",
               s, c, p, e);
    g[Edge{s, e}] = (c == "gain") ? p : -p;
    st.emplace(s);
  }

  std::vector<std::string> ppl{st.begin(), st.end()};
  int hmax{std::numeric_limits<int>::min()};
  do {
    int h{0};
    for (size_t i{0}; i < ppl.size(); ++i) {
      int l = (i - 1 + ppl.size()) % ppl.size();
      int r = (i + 1 + ppl.size()) % ppl.size();
      h += g.at(Edge{ppl[i], ppl[l]});
      h += g.at(Edge{ppl[i], ppl[r]});
    }
    hmax = std::max(h, hmax);
  } while (std::next_permutation(ppl.begin(), ppl.end()));
  return hmax;
}
} // namespace

int main() {
  const auto &in = gb::readIn();
  gb::writeOut(std::to_string(p1(in)));
}