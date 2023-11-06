#include "common.h"

namespace {
using Eval = std::function<uint16_t(void)>;

class Cached {
public:
  Cached(Eval eval) : eval_{eval} {}
  uint16_t operator()() {
    if (cache_.has_value()) {
      return cache_.value();
    }
    cache_ = eval_();
    return cache_.value();
  }

private:
  Eval eval_;
  std::optional<uint16_t> cache_;
};

std::unordered_map<std::string, Eval>
instructions(const std::vector<std::string> &in) {
  std::unordered_map<std::string, Eval> ins{};

  for (const std::string_view s : in) {
    auto sep = s.rfind(" -> ");
    assert(sep != std::string_view::npos);

    auto wire = std::string{s.substr(sep + 4)};
    auto con = gb::split(s.substr(0, sep), " ");
    if (con.size() == 1) { // literal
      ins[wire] = Cached([x = std::string{con[0]}, &ins]() {
        try { // can be a literal of a instruction
          return static_cast<uint16_t>(std::stoi(x));
        } catch (const std::invalid_argument &) {
          return ins[x]();
        }
      });
    } else if (con.size() == 2) { // unary
      assert(con[0] == "NOT");
      ins[wire] =
          Cached([x = std::string{con[1]}, &ins]() { return ~ins[x](); });
    } else if (con.size() == 3) { // binary
      assert(con[1] == "AND" || con[1] == "OR" || con[1] == "RSHIFT" ||
             con[1] == "LSHIFT");

      if (con[1] == "AND") {
        ins[wire] =
            Cached([x = std::string{con[0]}, y = std::string{con[2]}, &ins]() {
              try { // AND can have literal as first argument
                return static_cast<uint16_t>(std::stoi(x)) & ins[y]();
              } catch (const std::invalid_argument &) {
                return ins[x]() & ins[y]();
              }
            });
      } else if (con[1] == "OR") {
        ins[wire] = [x = std::string{con[0]}, y = std::string{con[2]}, &ins]() {
          return (ins[x]() | ins[y]());
        };
      } else if (con[1] == "LSHIFT") {
        ins[wire] =
            Cached([x = std::string{con[0]}, y = std::string{con[2]}, &ins]() {
              return ins[x]() << static_cast<uint16_t>(std::stoi(y));
            });
      } else if (con[1] == "RSHIFT") {
        ins[wire] =
            Cached([x = std::string{con[0]}, y = std::string{con[2]}, &ins]() {
              return ins[x]() >> static_cast<uint16_t>(std::stoi(y));
            });
      }
    } else {
      assert(false); // fail
    }
  }

  return ins;
}

uint16_t p1(const std::vector<std::string> &in, std::string &&w) {
  return instructions(in)[w]();
}

uint16_t p2(const std::vector<std::string> in, std::string &&w,
            std::string &&wo) {
  auto wv = instructions(in)[w]();
  auto ins = instructions(in);
  ins[wo] = [wv]() { return wv; };
  return ins[w]();
}
} // namespace

int main() {
  const auto &in = gb::readIn();
  gb::writeOut(std::to_string(p1(in, "a")));
  gb::writeOut(std::to_string(p2(in, "a", "b")));
}