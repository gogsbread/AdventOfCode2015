#include "common.h"

#include <openssl/md5.h>

namespace {
auto md5(std::string_view in) {
  std::array<unsigned char, MD5_DIGEST_LENGTH> digest{};
  MD5(reinterpret_cast<const unsigned char *>(in.data()), in.length(),
      digest.data());
  return digest;
}

int p1(const std::string_view in) {
  auto max = 2 << 20; // 20 bits (5*4)
  std::string s{in};
  for (int i = 1; i < max; ++i) {
    std::string m{s + std::to_string(i)};
    auto byts = md5(m);
    if (static_cast<int>(byts[0]) == 0 && static_cast<int>(byts[1]) == 0 &&
        ((static_cast<int>(byts[2]) & 240) ==
         0)) // 20 bits; 8byts + 8byts + 4nibble
      return i;
  }
  assert(false);
}

int p2(const std::string_view in) {
  auto max = 2 << 24;
  std::string s{in};
  for (int i = 1; i < max; ++i) {
    std::string m{s + std::to_string(i)};
    auto byts = md5(m);
    if (static_cast<int>(byts[0]) == 0 && static_cast<int>(byts[1]) == 0 &&
        static_cast<int>(byts[2]) == 0)
      return i;
  }
  assert(false);
}
} // namespace

int main() {
  const auto &in = gb::readIn();
  gb::writeOut(std::to_string(p1(in.at(0))));
  gb::writeOut(std::to_string(p2(in.at(0))));
}