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
}
} // namespace

int main() {
  const auto &in = gb::readIn();
  gb::writeOut(std::to_string(p1(in)));
}