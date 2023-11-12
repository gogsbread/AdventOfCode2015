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

int dist(const Graph &g, const std::vector<std::string> &vrts) {
  int d{0};
  for (size_t j = 0; j < vrts.size() - 1; ++j) {
    d += g.at(Edge{vrts[j], vrts[j + 1]});
  }
  return d;
}

int p1(const std::vector<std::string> &in) {
  Graph g{};
  std::set<std::string> st{};
  for (const auto &l : in) {
    std::istringstream ss{l};
    std::string s, e, _, __;
    int d;
    ss >> s >> _ >> e >> __ >> d;
    g[Edge{s, e}] = d;
    g[Edge{e, s}] = d;
    st.emplace(s);
    st.emplace(e);
  }

  std::vector<std::string> vrts{st.begin(), st.end()};
  int min{std::numeric_limits<int>::max()};
  do {
    min = std::min(min, dist(g, vrts));
  } while (std::next_permutation(vrts.begin(), vrts.end()));
  return min;
}

int p2(const std::vector<std::string> &in) {
  Graph g{};
  std::set<std::string> st{};
  for (const auto &l : in) {
    std::istringstream ss{l};
    std::string s, e, _, __;
    int d;
    ss >> s >> _ >> e >> __ >> d;
    g[Edge{s, e}] = d;
    g[Edge{e, s}] = d;
    st.emplace(s);
    st.emplace(e);
  }

  std::vector<std::string> vrts{st.begin(), st.end()};
  int max{std::numeric_limits<int>::min()};
  do {
    max = std::max(max, dist(g, vrts));
  } while (std::next_permutation(vrts.begin(), vrts.end()));
  return max;
}
} // namespace

int main() {
  const auto &in = gb::readIn();
  gb::writeOut(std::to_string(p1(in)));
  gb::writeOut(std::to_string(p2(in)));
}